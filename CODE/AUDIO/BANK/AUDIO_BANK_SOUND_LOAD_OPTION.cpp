//
//  AUDIO_BANK_SOUND_OPTION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 10/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

const int MUSIC_STREAM_LENGHT = 1024 * 512;

#include "AUDIO_BANK_SOUND_LOAD_OPTION.h"

AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_SoundStartupLoad( true, false );
AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_SoundDelayedLoad( false, false );
AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_StartupStreamMusic( true, true, MUSIC_STREAM_LENGHT );
AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_DelayedStreamMusic( false, true, MUSIC_STREAM_LENGHT );
