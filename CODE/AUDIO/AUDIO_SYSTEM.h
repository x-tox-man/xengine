//
//  AUDIO_SYSTEM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_SYSTEM__
#define __GAME_ENGINE_REBORN__AUDIO_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_MATH_VECTOR.h"
#include "AUDIO_RUNTIME_ENVIRONMENT.h"
#include "AUDIO_SOUND.h"
#include "AUDIO_INTERFACE.h"
#include "AUDIO_BANK.h"

#if AUDIO_PLATFORM_OPENAL
    #include "AUDIO_OPENAL.h"
#elif AUDIO_PLATFORM_OPENSLES
    #include "AUDIO_OPENSL.h"
#endif

XS_CLASS_BEGIN( AUDIO_SYSTEM )

    XS_DEFINE_UNIQUE( AUDIO_SYSTEM )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( AUDIO_SYSTEM );

    ~AUDIO_SYSTEM();

    void Initialize();
    void Finalize();

    void PlaySound( AUDIO_SOUND & sound );
    void PlaySound( const CORE_HELPERS_IDENTIFIER & sound_identifier );
    void PlaySound( const char * sound_identifier );
    void PlayMusic( const char * sound_identifier );
    void PlayMusic( const CORE_HELPERS_IDENTIFIER & sound_identifier );
    void StopMusic();

    void OnSoundIsRead();

    void Update( const float time_step );

    inline AUDIO_SOUND_BANK & GetBank() { return Bank; }
    inline const AUDIO_SOUND_BANK & GetBank() const { return Bank; }
    inline AUDIO_SOUND * GetPlayingMusic() { return PlayingMusic; }
    inline void SetPosition( const CORE_MATH_VECTOR & v ) { Position = v; }

private:

    #if __AUDIO_OPENAL__
        AUDIO_INTERFACE< AUDIO_OPENAL >
            * Interface;
    #elif __AUDIO_OPENSL__
        AUDIO_INTERFACE< AUDIO_OPENSL >
            * Interface;
    #endif
    AUDIO_SOUND_BANK
        Bank;
    AUDIO_SOUND
        * PlayingMusic;
    CORE_MATH_VECTOR
        Position;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_SYSTEM__) */
