//
//  AUDIO_OPENAL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

// online ref//sample : http://benbritten.com/2010/05/04/streaming-in-openal/

#include "AUDIO_OPENAL.h"
#include "GRAPHIC_RENDERER.h"
#include "AUDIO_SYSTEM.h"
#include "AUDIO_LOADER.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_MEMORY.h"

AUDIO_OPENAL::AUDIO_OPENAL() :
    AUDIO_INTERFACE() {
    
}

/*
#if PLATFORM_WINDOWS
    template< >
    AUDIO_INTERFACE< AUDIO_OPENAL >::~AUDIO_INTERFACE< AUDIO_OPENAL >() {

    }
#endif
*/
AUDIO_OPENAL::~AUDIO_OPENAL() {
    
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alcCloseDevice( Device ); )
    
        Device = NULL;
        Context = NULL;
    #endif
}

void AUDIO_OPENAL::Initialize() {
    
    #if __AUDIO_OPENAL__
        SERVICE_LOGGER_Error( "AUDIO_OPENAL Initialize" );
        Device = alcOpenDevice(NULL);
    
        SERVICE_LOGGER_Error( "AUDIO_OPENAL Initialize 1" );

        AUDIO_CHECK( Device = alcOpenDevice(NULL); ) // open default device
    
        SERVICE_LOGGER_Error( "AUDIO_OPENAL Initialize 2" );
        if ( Device != NULL ) {
            
            AUDIO_CHECK( Context = alcCreateContext( Device, NULL); ) // create context
        
            SERVICE_LOGGER_Error( "AUDIO_OPENAL Initialize 3" );
            if ( Context != NULL ) {
                
                AUDIO_CHECK( alcMakeContextCurrent( Context ); ) // set active context
                
                SERVICE_LOGGER_Error( "AUDIO_OPENAL Initialize 4" );
            }
        }
    #endif
}

void AUDIO_OPENAL::Finalize() {
    
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alcDestroyContext( Context ); )
    #endif
}


void AUDIO_OPENAL::Update( const float time_step ) {
    
    #if __AUDIO_OPENAL__
        const CORE_MATH_VECTOR & position = GRAPHIC_RENDERER::GetInstance().GetCamera().GetPosition();
    
        AUDIO_CHECK( alListener3f(AL_POSITION, position[0], position[1], position[2]); )
        
        /*float directionvect[6];
        
        directionvect[0] = (float) sinf(90.0f);
        directionvect[1] = 0;
        directionvect[2] = (float) cosf(90.0f);
        directionvect[3] = 0;
        directionvect[4] = 1;
        directionvect[5] = 0;
        
        AUDIO_CHECK( alListenerfv(AL_ORIENTATION, directionvect); )*/
    
        AUDIO_SOUND * sound = AUDIO_SYSTEM::GetInstance().GetPlayingMusic();
    
        if ( sound ) {
            
            ALint val;
            
            AUDIO_CHECK( alGetSourcei( sound->GetSource(), AL_BUFFERS_PROCESSED, &val); )
            
            if ( val > 0 ) {
                
                ALuint buffer_id = 0;
                
                AUDIO_CHECK( alSourceUnqueueBuffers( sound->GetSource(), 1, &buffer_id ); )
                
                if ( sound->IsOpen() ) {
                    
                    AUDIO_SOUND_CHUNK * chunk = sound->GetSoundChunksTable()[ sound->GetCurrentChunkIndex() ];
                
                    bool end = AUDIO_LOADER_ReadChunk( *sound, sound->GetCurrentChunkIndex() );
                    
                    sound->SetCurrentChunkIndex( ( sound->GetCurrentChunkIndex() + 1) % sound->GetSoundChunksTable().size() );
                    
                    if ( end ) {
                        
                        sound->SetIsOpen( false );
                        AUDIO_LOADER_Close( *sound );
                        
                        sound->SetCurrentChunkIndex( 0 );
                    }
                    
                    AUDIO_CHECK( alBufferData (chunk->GetChunkBufferName(),
                                               GetSoundFormat( *sound ),
                                               chunk->Data,
                                               chunk->Size,
                                               sound->GetFrequency() ); )
                    
                    AUDIO_CHECK( alSourceQueueBuffers(
                                                      sound->GetSource(),
                                                      1,
                                                      &buffer_id ); )
                }
            }
        }
    #endif
}

void AUDIO_OPENAL::PlaySound( AUDIO_SOUND & sound ) {
    
    #if __AUDIO_OPENAL__
    
        ALenum format = GetSoundFormat( sound );
    
        ALuint sources = GenerateSources( 1 );
    
        sound.SetSource( sources );
    
        if ( sound.GetSoundChunksTable().size() > 1 ) {
            
            ALuint * buffers = (ALuint *) CORE_MEMORY_ALLOCATOR::Allocate(sound.GetSoundChunksTable().size() );
            
            AUDIO_CHECK( alGenBuffers( (ALsizei) sound.GetSoundChunksTable().size(), buffers); )
            
            // attach OpenAL Buffer to OpenAL Source
            AUDIO_CHECK( alSourcei( sources, AL_BUFFER, 0 ); )
            
            for ( int i = 0; i < sound.GetSoundChunksTable().size(); i++ ) {
                
                sound.GetSoundChunksTable()[i]->SetChunkBufferName( buffers[i] );
                
                AUDIO_CHECK( alBufferData (sound.GetSoundChunksTable()[i]->GetChunkBufferName(),
                                           format ,
                                           sound.GetSoundChunksTable()[i]->Data,
                                           sound.GetSoundChunksTable()[i]->Size,
                                           sound.GetFrequency() ); )
            }
            
            AUDIO_CHECK( alSourceQueueBuffers( sources, (ALsizei) sound.GetSoundChunksTable().size(), buffers); )
            
            CORE_MEMORY_ALLOCATOR_Free( buffers );
            buffers = NULL;
        }
        else {
            
            ALuint buffer;
            
            AUDIO_CHECK( alGenBuffers(1, &buffer); )
            
            AUDIO_SOUND_CHUNK * chunk = sound.GetSoundChunksTable()[0];
            
            chunk->SetChunkBufferName( buffer );
            AUDIO_CHECK( alBufferData ( chunk->GetChunkBufferName(),
                                       format,
                                       chunk->Data,
                                       chunk->Size,
                                       sound.GetFrequency() ); )
            
            AUDIO_CHECK( alSourcei( sources, AL_BUFFER, chunk->GetChunkBufferName()); )
        }
        
        static float source_position[3] = { -1.0f, 0.0f, 0.0f };
        
        // Set Source Position
        AUDIO_CHECK( alSourcefv( sources, AL_POSITION, source_position); )
        // Set Source Reference Distance
        AUDIO_CHECK( alSourcef( sources, AL_REFERENCE_DISTANCE, 0.0f); )
        
        // only load data and start playing the non capture sourcesq
        
        // Start Playing Sound
        AUDIO_CHECK( alSourcePlay( sources ); )
    
        #if DEBUG
            ALenum state = 0;
    
            AUDIO_CHECK( alGetSourcei(sources,AL_SOURCE_STATE,&state); )
    
            if (state != AL_PLAYING ) {
                #if PLATFORM_OSX                
                    CORE_RUNTIME_Abort();
                #endif
            }
        #endif
    #endif
}

void AUDIO_OPENAL::StopSound( AUDIO_SOUND & sound) {
    
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alSourceStop( sound.GetSource() ); )
        
        for ( int i = 0; i < sound.GetSoundChunksTable().size(); i++ ) {
            
            AUDIO_CHECK( alDeleteBuffers(1, &sound.GetSoundChunksTable()[ i ]->GetChunkBufferName()); )
        }
    #endif
}

void AUDIO_OPENAL::ResumeSound( AUDIO_SOUND & sound) {
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alSourcePlay( sound.GetSource() ); )
    #endif
}

void AUDIO_OPENAL::PauseSound( AUDIO_SOUND & sound) {
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alSourcePause( sound.GetSource() ); )
    #endif
}

void AUDIO_OPENAL::Suspend() {
    
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alcSuspendContext ( Context ); )
    #endif
}

void AUDIO_OPENAL::Resume() {
    
    #if __AUDIO_OPENAL__
        AUDIO_CHECK( alcMakeContextCurrent( Context ); )
    #endif
}

#if __AUDIO_OPENAL__
    ALuint AUDIO_OPENAL::GenerateSources( int source_count ) {
        
        ALuint source;
        
        AUDIO_CHECK( alGenSources( source_count, &source ); );
        
        return source;
    }

    ALenum AUDIO_OPENAL::GetSoundFormat( const AUDIO_SOUND & sound ) {
        
        if( sound.GetBufferWidth() == 8 && sound.IsMono() ) {
            
            return AL_FORMAT_MONO8;
        }
        else if( sound.GetBufferWidth() == 16 && sound.IsMono() ) {
            
            return AL_FORMAT_MONO16;
        }
        else if( sound.GetBufferWidth() == 8 && !sound.IsMono() ) {
            
            return AL_FORMAT_STEREO8;
        }
        else if( sound.GetBufferWidth() == 16 && !sound.IsMono() ) {
            
            return AL_FORMAT_STEREO16;
        }
        else {
            #if PLATFORM_OSX
                CORE_RUNTIME_Abort();
            #endif
            
            return -1;
        }
    }
#endif
