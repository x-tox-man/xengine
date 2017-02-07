//
//  AUDIO_BANK_SOUND.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 10/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef AUDIO_BANK_SOUND_h
#define AUDIO_BANK_SOUND_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "AUDIO_SOUND.h"
#include "AUDIO_BANK_SOUND_LOAD_OPTION.h"

XS_CLASS_BEGIN_WITH_COPY( AUDIO_BANK_SOUND )

    AUDIO_BANK_SOUND( const AUDIO_BANK_SOUND_LOAD_OPTION & option );
    virtual    ~AUDIO_BANK_SOUND();

    AUDIO_SOUND * Sound;
    CORE_FILESYSTEM_PATH SoundPath;
    const char * SoundFileType;
    const AUDIO_BANK_SOUND_LOAD_OPTION * Option;

XS_CLASS_END


#endif /* AUDIO_BANK_SOUND_hpp */
