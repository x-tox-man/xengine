//
//  AUDIO_SYSTEM.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_SYSTEM__
#define __GAME_ENGINE_REBORN__AUDIO_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "AUDIO_SOUND.h"
#include "AUDIO_INTERFACE.h"
#include "AUDIO_OPENAL.h"
#include "AUDIO_SOUND_BANK.h"

XS_CLASS_BEGIN( AUDIO_SYSTEM )
    XS_DEFINE_UNIQUE( AUDIO_SYSTEM )

    void Initialize();

    void PlaySound( AUDIO_SOUND & sound );
    void PlaySound( CORE_HELPERS_IDENTIFIER & sound_identifier );

    void Update( const float time_step );

    void Finalize();

private:

//#if OPENAL
AUDIO_INTERFACE< AUDIO_OPENAL > * Interface;
AUDIO_SOUND_BANK Bank;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_SYSTEM__) */
