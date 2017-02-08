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

#include <vector>

#if __AUDIO_OPENAL__
    #include <OpenAL/al.h>
#endif

XS_CLASS_BEGIN( AUDIO_SOUND )

    AUDIO_SOUND();
    ~AUDIO_SOUND();

    void * GetData() const { return Data; }
    bool IsMono() const { return Mono; }
    bool IsCompressed() const { return Compressed; }
    int GetBufferWidth() const { return BufferWidth; }
    int GetSize() const { return Size; }
    int GetFrequency() const { return Frequency; }
    int GetChannels() const { return Channels; }
    int GetFrameSize() const { return FrameSize; }
    bool IsOpen() const { return ItIsOpen; }

    void SetData( void * data ) { Data = data; }
    void SetIsMono( bool is_mono ) { Mono = is_mono; }
    void SetIsCompressed( bool is_compressed) { Compressed = is_compressed; }
    void SetBufferWidth(int width ) { BufferWidth = width; }
    void SetSize( int buffer_size ) { Size = buffer_size; }
    void SetFrequency( int frequency ) { Frequency = frequency; }
    void SetChannels( int channels ) { Channels = channels; }
    void SetFrameSize( int frame_size ) { FrameSize = frame_size; }
    void SetIsOpen( bool open ) { ItIsOpen = open; }
    std::vector< AUDIO_SOUND_CHUNK::PTR > & GetSoundChunksTable() { return SoundChunksTable; }

    #if __AUDIO_OPENAL__
        void SetSource( ALuint source ) { Source = source; }
        ALuint GetSource() { return Source; }
    #endif

private:

void * Data;
bool Mono;
bool Compressed;
bool Looping;
bool ItIsOpen;
int BufferWidth;
int Size;
int FrameSize;
int Channels;
int Frequency;
Scalar_SGet( int, CurrentChunkIndex );
std::vector< AUDIO_SOUND_CHUNK::PTR > SoundChunksTable;

#if __AUDIO_OPENAL__
    ALuint
        Source;
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
