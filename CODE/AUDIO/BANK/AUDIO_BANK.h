//
//  AUDIO_SOUND_BANK.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_SOUND_BANK__
#define __GAME_ENGINE_REBORN__AUDIO_SOUND_BANK__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "AUDIO_RUNTIME_ENVIRONMENT.h"
#include "AUDIO_BANK_SOUND.h"

XS_CLASS_BEGIN( AUDIO_SOUND_BANK )

AUDIO_SOUND_BANK();
~AUDIO_SOUND_BANK();

void Load();
void Unload();

void RegisterSoundFilePath( const CORE_FILESYSTEM_PATH & sound_path, CORE_HELPERS_IDENTIFIER sound_identifier, const AUDIO_BANK_SOUND_LOAD_OPTION & option, const char * type );

void PlaySound( const CORE_HELPERS_IDENTIFIER sound_identifier );

inline AUDIO_BANK_SOUND * GetSound( const CORE_HELPERS_IDENTIFIER & sound ) {
    
    return SoundTable[ sound ];
}

private:

    std::map< CORE_HELPERS_IDENTIFIER, AUDIO_BANK_SOUND *> SoundTable;

    static const char *
        Mpeg3FileType,
        WavFileType;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_SOUND_BANK__) */
