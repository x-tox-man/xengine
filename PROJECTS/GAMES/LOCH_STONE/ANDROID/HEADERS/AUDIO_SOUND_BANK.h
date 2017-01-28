//
//  AUDIO_SOUND_BANK.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_SOUND_BANK__
#define __GAME_ENGINE_REBORN__AUDIO_SOUND_BANK__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "AUDIO_SOUND.h"

XS_CLASS_BEGIN( AUDIO_SOUND_BANK )

AUDIO_SOUND_BANK();

void LoadBank( const char * sound_bank_file_path );

inline AUDIO_SOUND * GetSound( const CORE_HELPERS_IDENTIFIER & sound ) {
    
    return SoundTable[ sound ];
}

private:

std::map< CORE_HELPERS_IDENTIFIER, AUDIO_SOUND *> SoundTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_SOUND_BANK__) */
