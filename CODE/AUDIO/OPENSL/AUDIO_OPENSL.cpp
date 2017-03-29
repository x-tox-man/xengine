//
//  AUDIO_OPENSL.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "AUDIO_OPENSL.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "AUDIO_LOADER.h"
#include "AUDIO_SYSTEM.h"

#include <pthread.h>

#define MAX_NUMBER_INTERFACES       4
#define MAX_NUMBER_OUTPUT_DEVICES   6
#define POSITION_UPDATE_PERIOD      1000

// check http://vec3.ca/getting-started-with-opensl-on-android/
#if __AUDIO_OPENSL__

void play_callback( SLAndroidSimpleBufferQueueItf bq, void *context )
{
    //if( event & SL_PLAYEVENT_HEADATEND ) {
        
        AUDIO_SYSTEM::GetInstance().OnSoundIsRead();// player, context );
        SERVICE_LOGGER_Info( "SLengine play_callback" );
    //}
}

AUDIO_OPENSL::AUDIO_OPENSL() :
    SLEngine(),
    SLOutputMixVolume(),
    SLEngineObject(),
    SLOutputMixObject(),
    SLAudioIODeviceCapabilitiesObject(),
    SLPlayerEffectSend(),
    MaxOutputCount() {
    
}

AUDIO_OPENSL::~AUDIO_OPENSL() {
    
}
static pthread_mutex_t audioEngineLock = PTHREAD_MUTEX_INITIALIZER;

void AUDIO_OPENSL::OnSoundIsRead() {
    AUDIO_SOUND * sound = AUDIO_SYSTEM::GetInstance().GetPlayingMusic();
    
#if __AUDIO_OPENSL__
    
    if ( sound->IsOpen() ) {
        SERVICE_LOGGER_Info("SLOnSoundIsRead");
        
        bool end = AUDIO_LOADER_ReadChunk( *sound, sound->GetCurrentChunkIndex() );
        sound->SetCurrentChunkIndex( ( sound->GetCurrentChunkIndex() + 1) % sound->GetSoundChunksTable().size() );
        AUDIO_SOUND_CHUNK * chunk = sound->GetSoundChunksTable()[ sound->GetCurrentChunkIndex() ];
        
        AUDIO_CHECK( (*sound->PlayerBufferQueue)->Enqueue( sound->PlayerBufferQueue, chunk->Data, chunk->Size ); )
        
        SERVICE_LOGGER_Info( "SLengine ENQUEUE : size %d - %d", chunk->Size, *(int*)chunk->Data);
        
        sound->SetCurrentChunkIndex( ( sound->GetCurrentChunkIndex() + 1) % sound->GetSoundChunksTable().size() );
        
        if ( end ) {
            
            sound->SetIsOpen( false );
            AUDIO_LOADER_Close( *sound );
            
            sound->SetCurrentChunkIndex( 0 );
        }
    }
#endif
}

void AUDIO_OPENSL::Initialize() {
#if __AUDIO_OPENSL__
    
    if (pthread_mutex_trylock(&audioEngineLock)) {
        // If we could not acquire audio engine lock, reject this request and client should re-try
        SERVICE_LOGGER_Info("SLpthread_mutex_trylock failed");
    }
    
    SLresult result;
    SLuint32 OutputDeviceIDs[MAX_NUMBER_OUTPUT_DEVICES];
    
    SERVICE_LOGGER_Info("slCreateEngine ");
    AUDIO_CHECK( slCreateEngine(&SLEngineObject, 0, NULL, 0, NULL, NULL); )
    SERVICE_LOGGER_Info("slEngine Realize");
    AUDIO_CHECK( (*SLEngineObject)->Realize( SLEngineObject, SL_BOOLEAN_FALSE ); )
    SERVICE_LOGGER_Info("slEngine GetInterface SL_IID_ENGINE");
    AUDIO_CHECK( (*SLEngineObject)->GetInterface( SLEngineObject, SL_IID_ENGINE, &SLEngine ); )
    //SERVICE_LOGGER_Info("slEngine GetInterface SL_IID_AUDIOIODEVICECAPABILITIES");
    //AUDIO_CHECK( (*SLEngineObject)->GetInterface(SLEngineObject, SL_IID_AUDIOIODEVICECAPABILITIES, (void *)&SLAudioIODeviceCapabilitiesObject); )
    //MaxOutputCount = MAX_NUMBER_OUTPUT_DEVICES;
    //AUDIO_CHECK( (*SLAudioIODeviceCapabilitiesObject)->GetAvailableAudioOutputs( SLAudioIODeviceCapabilitiesObject, &MaxOutputCount, OutputDeviceIDs); )
    
    
    //SERVICE_LOGGER_Info("slCreateEngine MaxOutputCount :%d -", MaxOutputCount);
    
    const SLInterfaceID ids[] = { SL_IID_ENVIRONMENTALREVERB };
    const SLboolean req[] = { SL_BOOLEAN_FALSE };
    SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_CITY;
    AUDIO_CHECK( (*SLEngine)->CreateOutputMix( SLEngine, &SLOutputMixObject, 1, ids, req ); )
    AUDIO_CHECK( (*SLOutputMixObject)->Realize( SLOutputMixObject, SL_BOOLEAN_FALSE ); )
    AUDIO_CHECK( (*SLOutputMixObject)->GetInterface( SLOutputMixObject, SL_IID_ENVIRONMENTALREVERB, &OutputMixEnvironmentalReverb ); )
    AUDIO_CHECK( (*OutputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties( OutputMixEnvironmentalReverb, &reverbSettings); )
    
    pthread_mutex_unlock(&audioEngineLock);
    SERVICE_LOGGER_Info("pthread_mutex_unlock");
#endif
    
}

void AUDIO_OPENSL::Finalize() {
#if __AUDIO_OPENSL__
    (*SLOutputMixObject)->Destroy( SLOutputMixObject );
#endif
}

void AUDIO_OPENSL::PlaySound( AUDIO_SOUND & sound ) {
#if __AUDIO_OPENSL__
    #if PLATFORM_ANDROID
        SLDataLocator_AndroidSimpleBufferQueue in_loc;
        in_loc.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
        in_loc.numBuffers = 1;
    #else
        SLDataLocator_Address in_loc;
        in_loc.locatorType = SL_DATALOCATOR_ADDRESS;
        in_loc.pAddress = clip_samples;
        in_loc.length = sound.GetFrameSize() * 2;
    #endif
    
    /*SLDataLocator_BufferQueue in_loc;
    in_loc.locatorType = SL_DATALOCATOR_BUFFERQUEUE;
    in_loc.numBuffers = 1;*/
    
    SLDataFormat_PCM format;
    format.formatType = SL_DATAFORMAT_PCM;
    format.numChannels = 2;
    format.samplesPerSec = SL_SAMPLINGRATE_44_1;
    format.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    format.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    format.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    format.endianness = SL_BYTEORDER_LITTLEENDIAN;
    
    SLDataSource
        src;
    
    src.pLocator = &in_loc;
    src.pFormat = &format;
    
    SLDataLocator_OutputMix
        out_loc;
    
    out_loc.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    out_loc.outputMix = SLOutputMixObject;
    
    SLDataSink
        dst;
    
    dst.pLocator = &out_loc;
    dst.pFormat = nullptr;
        
    //create the object
        
    /*#ifdef PLATFORM_ANDROID
        const SLInterfaceID ids[] = { SL_IID_VOLUME,
            SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
        const SLboolean req[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    #else*/
        //const SLInterfaceID ids[] = { SL_IID_BUFFERQUEUE };
        //const SLboolean req[] = { SL_BOOLEAN_TRUE };
    //#endif
    
    const SLInterfaceID ids[4] = { SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND };
    const SLboolean req[4] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_FALSE, SL_BOOLEAN_TRUE };
        
    AUDIO_CHECK( (*SLEngine)->CreateAudioPlayer( SLEngine, &sound.SLPlayerObject, &src, &dst, 3, ids, req ); )
    AUDIO_CHECK( (*sound.SLPlayerObject)->Realize( sound.SLPlayerObject, SL_BOOLEAN_FALSE ); )
    AUDIO_CHECK( (*sound.SLPlayerObject)->GetInterface( sound.SLPlayerObject, SL_IID_PLAY, &sound.SLPlayer ); )
    
    #ifdef PLATFORM_ANDROID
        AUDIO_CHECK( (*sound.SLPlayerObject)->GetInterface( sound.SLPlayerObject, SL_IID_BUFFERQUEUE, &sound.PlayerBufferQueue ); )
    #endif
    
    //AUDIO_CHECK( (*sound.SLPlayer)->SetCallbackEventsMask( sound.SLPlayer, SL_PLAYEVENT_HEADATEND ); )
    AUDIO_CHECK( (*sound.PlayerBufferQueue)->RegisterCallback( sound.PlayerBufferQueue, play_callback, NULL ); )
    
    bool is_playing = true;
    bool is_done_buffer = false;
    
    AUDIO_CHECK( (*sound.SLPlayerObject)->GetInterface( sound.SLPlayerObject, SL_IID_VOLUME, &sound.SLPlayerVolume ); )
    AUDIO_CHECK( (*sound.SLPlayerObject)->GetInterface( sound.SLPlayerObject, SL_IID_EFFECTSEND, &SLPlayerEffectSend ); )
    
    AUDIO_CHECK( (*sound.SLPlayer)->SetPlayState( sound.SLPlayer, SL_PLAYSTATE_PLAYING ); )
    //play_start_time = current_time();
    
    AUDIO_SOUND_CHUNK * chunk = sound.GetSoundChunksTable()[ sound.GetCurrentChunkIndex() ];
    AUDIO_CHECK( (*sound.PlayerBufferQueue)->Enqueue( sound.PlayerBufferQueue, chunk->Data, chunk->Size ); )
    SERVICE_LOGGER_Info("SLSoundPlayer created");
    
#endif
}

void AUDIO_OPENSL::StopSound( AUDIO_SOUND & sound) {
#if __AUDIO_OPENSL__
    AUDIO_CHECK( (*sound.GetSLPlayer())->SetPlayState( sound.GetSLPlayer(), SL_PLAYSTATE_STOPPED ); )
    
    #ifdef PLATFORM_ANDROID
        AUDIO_CHECK( (*sound.GetPlayerBufferQueue())->Clear( sound.GetPlayerBufferQueue() ); )
    #endif
        
    bool is_playing = false;
    
    (*sound.GetSLPlayerObject())->Destroy( sound.GetSLPlayerObject() );
    
    //player_obj = nullptr;
    //player = nullptr;
    //player_vol = nullptr;
    
    #ifdef PLATFORM_ANDROID
        //player_buf_q = nullptr;
    #endif
#endif
}

void AUDIO_OPENSL::ResumeSound( AUDIO_SOUND & sound) {
#if __AUDIO_OPENSL__
    
#endif
}

void AUDIO_OPENSL::PauseSound( AUDIO_SOUND & sound) {
#if __AUDIO_OPENSL__
    
#endif
}

void AUDIO_OPENSL::Update( const float time_step ) {
#if __AUDIO_OPENSL__
    
#endif
}

void AUDIO_OPENSL::Suspend() {
#if __AUDIO_OPENSL__
    
#endif
}

void AUDIO_OPENSL::Resume() {
#if __AUDIO_OPENSL__
    
#endif
}

#endif
