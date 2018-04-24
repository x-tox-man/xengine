//
//  AUDIO_MP3_LOADER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 25/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_MP3_LOADER__
#define __GAME_ENGINE_REBORN__AUDIO_MP3_LOADER__

#include "AUDIO_SOUND.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "AUDIO_BANK_SOUND_LOAD_OPTION.h"

void AUDIO_LOADER_Reset( AUDIO_SOUND & sound );
void AUDIO_LOADER_Open( const CORE_FILESYSTEM_PATH & file_path, const char * extension, AUDIO_SOUND & sound, const AUDIO_BANK_SOUND_LOAD_OPTION & option );
bool AUDIO_LOADER_ReadChunk( AUDIO_SOUND & sound, int chunk_index );
void AUDIO_LOADER_Close( AUDIO_SOUND & sound );

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_MP3_LOADER__) */
