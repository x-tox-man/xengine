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

//#if OPENAL
#include <OpenAL/al.h>
//#endif

XS_CLASS_BEGIN( AUDIO_SOUND )

AUDIO_SOUND();

void * GetData() const { return Data; }
bool IsMono() const { return Mono; }
bool IsCompressed() const { return Compressed; }
int GetBufferWidth() const { return BufferWidth; }
int GetSize() const { return Size; }
int GetFrequency() const { return Frequency; }

void SetData( void * data ) { Data = data; }
void SetIsMono( bool is_mono ) { Mono = is_mono; }
void SetIsCompressed( bool is_compressed) { Compressed = is_compressed; }
void SetBufferWidth(int width ) { BufferWidth = width; }
void SetSize( int buffer_size ) { Size = buffer_size; }
void SetFrequency( int frequency ) { Frequency = frequency; }

ALuint GetBufferName() const { return BufferName; }
void SetBufferName( const ALuint buffer_name ) { BufferName = buffer_name; }

private:

void * Data;
bool Mono;
bool Compressed;
int BufferWidth;
int Size;
int Frequency;

//#if OPENAL
    ALuint BufferName;
//#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_SOUND__) */
