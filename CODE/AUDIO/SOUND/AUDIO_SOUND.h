//
//  AUDIO_SOUND.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_SOUND__
#define __GAME_ENGINE_REBORN__AUDIO_SOUND__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "AUDIO_SOUND_CHUNK.h"
#include "RESOURCE_SOUND.h"

#include <vector>

#if __AUDIO_OPENAL__
    #include <OpenAL/al.h>
#endif

#if defined AUDIO_MPG
    #include <mpg123.h>
#endif

#if __AUDIO_OPENSL__
    #include <SLES/OpenSLES.h>

    #if PLATFORM_ANDROID
        #include <SLES/OpenSLES_Android.h>
    #endif
#endif

XS_CLASS_BEGIN( AUDIO_SOUND )

    AUDIO_SOUND();
    ~AUDIO_SOUND();

    inline void * GetData() const { return Data; }
    inline bool IsMono() const { return Mono; }
    inline bool IsCompressed() const { return Compressed; }
    inline int GetBufferWidth() const { return BufferWidth; }
    inline int GetSize() const { return Size; }
    inline int GetFrequency() const { return Frequency; }
    inline int GetChannels() const { return Channels; }
    inline int GetFrameSize() const { return FrameSize; }
    inline bool IsOpen() const { return ItIsOpen; }

    inline void SetData( void * data ) { Data = data; }
    inline void SetIsMono( bool is_mono ) { Mono = is_mono; }
    inline void SetIsCompressed( bool is_compressed) { Compressed = is_compressed; }
    inline void SetBufferWidth(int width ) { BufferWidth = width; }
    inline void SetSize( int buffer_size ) { Size = buffer_size; }
    inline void SetFrequency( int frequency ) { Frequency = frequency; }
    inline void SetChannels( int channels ) { Channels = channels; }
    inline void SetFrameSize( int frame_size ) { FrameSize = frame_size; }
    inline void SetIsOpen( bool open ) { ItIsOpen = open; }
    inline std::vector< AUDIO_SOUND_CHUNK::PTR > & GetSoundChunksTable() { return SoundChunksTable; }
    inline void SetResourceSound( RESOURCE_SOUND * sound ) { Sound = sound; }

    #if __AUDIO_OPENAL__
        void SetSource( ALuint source ) { Source = source; }
        ALuint GetSource() { return Source; }
    #elif __AUDIO_OPENSL__
        SLObjectItf GetSLPlayerObject() { return SLPlayerObject; }
        SLPlayItf GetSLPlayer() { return SLPlayer; }
        SLVolumeItf GetSLPlayerVolume() { return SLPlayerVolume; }
        SLAndroidSimpleBufferQueueItf GetPlayerBufferQueue() { return PlayerBufferQueue; }
    #endif

private:

    void
        * Data;
    bool
        Mono,
        Compressed,
        Looping,
        ItIsOpen;
    int
        BufferWidth,
        Size,
        FrameSize,
        Channels,
        Frequency;
    RESOURCE_SOUND
        * Sound;

    Scalar_SGet( int, CurrentChunkIndex );
    std::vector< AUDIO_SOUND_CHUNK::PTR > SoundChunksTable;

#if __AUDIO_OPENAL__
    ALuint
        Source;
#elif __AUDIO_OPENSL__
public :
    SLObjectItf
        SLPlayerObject;
    SLPlayItf
        SLPlayer;
    SLVolumeItf
        SLPlayerVolume;
    #ifdef PLATFORM_ANDROID
    SLAndroidSimpleBufferQueueItf
        PlayerBufferQueue;
    #endif
private :
#endif

    #if PLATFORM_OSX
        #include "AUDIO_SOUND_OSX.hpp"
    #elif PLATFORM_IOS
        #include "AUDIO_SOUND_IOS.hpp"
    #elif PLATFORM_WINDOWS
        #include "AUDIO_SOUND_WINDOWS.hpp"
    #elif PLATFORM_ANDROID
        #include "AUDIO_SOUND_ANDROID.hpp"
    #else
        #error 1
    #endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_SOUND__) */
