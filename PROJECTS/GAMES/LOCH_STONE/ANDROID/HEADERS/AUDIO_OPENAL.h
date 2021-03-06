//
//  AUDIO_OPENAL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_OPENAL__
#define __GAME_ENGINE_REBORN__AUDIO_OPENAL__

#if __AUDIO_OPENAL__
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#endif
#include "AUDIO_INTERFACE.h"
#include "CORE_HELPERS_CLASS.h"

#include <math.h>

#if __AUDIO_OPENAL__
    #define AUDIO_CHECK( __function__ ) \
        { \
            __function__ \
            ALenum error = alGetError(); \
            if ( error != AL_NO_ERROR ) { \
                SERVICE_LOGGER::Error( "OPENAL error %d\n", error ); \
            }\
        }
#else 
    #define AUDIO_CHECK( __function__ )
#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( AUDIO_OPENAL, AUDIO_INTERFACE< AUDIO_OPENAL > )

    AUDIO_OPENAL();

    virtual void Initialize();

    virtual void Finalize();

    void PlaySound( AUDIO_SOUND & sound);

    void Update( const float time_step );

    void Suspend();

    void Resume();

    private :

    #if __AUDIO_OPENAL__
        ALCdevice * Device;
        ALCcontext * Context;
    #endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_OPENAL__) */
