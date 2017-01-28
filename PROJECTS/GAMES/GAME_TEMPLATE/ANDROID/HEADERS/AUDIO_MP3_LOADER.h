//
//  AUDIO_MP3_LOADER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 25/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_MP3_LOADER__
#define __GAME_ENGINE_REBORN__AUDIO_MP3_LOADER__

#include "AUDIO_SOUND.h"

void AUDIO_MP3_LOADER_Load( const char * mp3_filename, AUDIO_SOUND & sound );
void AUDIO_WAV_LOADER_Load( const char * wav_filename, AUDIO_SOUND & sound );

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_MP3_LOADER__) */
