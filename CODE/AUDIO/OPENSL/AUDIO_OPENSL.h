//
//  AUDIO_OPENSL.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef AUDIO_OPENSL_hpp
#define AUDIO_OPENSL_hpp

#include "AUDIO_INTERFACE.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "SERVICE_LOGGER.h"

#if __AUDIO_OPENSL__
    #include <SLES/OpenSLES.h>

    #if PLATFORM_ANDROID
        #include <SLES/OpenSLES_Android.h>
    #endif
#endif

#if __AUDIO_OPENSL__ && DEBUG
#define AUDIO_CHECK( __function__ ) \
    { \
        SLresult res = __function__ \
        if( res != SL_RESULT_SUCCESS ) \
            SERVICE_LOGGER_Error( "OPENSL error %d %s\n", res, #__function__ ); \
    }

#elif __AUDIO_OPENSL__
    #define AUDIO_CHECK( __function__ ) \
        __function__

#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( AUDIO_OPENSL, AUDIO_INTERFACE< AUDIO_OPENSL > )

    AUDIO_OPENSL();
    virtual ~AUDIO_OPENSL();

    virtual void Initialize();

    virtual void Finalize();

    void PlaySound( AUDIO_SOUND & sound);

    void StopSound( AUDIO_SOUND & sound);

    void ResumeSound( AUDIO_SOUND & sound);

    void PauseSound( AUDIO_SOUND & sound);

    void Update( const float time_step );

    void Suspend();

    void Resume();

    void OnSoundIsRead();

private :

#if __AUDIO_OPENSL__
    SLEngineItf
        SLEngine;
    SLVolumeItf
        SLOutputMixVolume;
    SLObjectItf
        SLEngineObject,
        SLOutputMixObject;
    SLEnvironmentalReverbItf
        OutputMixEnvironmentalReverb;
    SLAudioIODeviceCapabilitiesItf
        SLAudioIODeviceCapabilitiesObject;
    SLEffectSendItf
        SLPlayerEffectSend;
#endif

    int
        MaxOutputCount;

private :


XS_CLASS_END

#endif /* AUDIO_OPENSL_hpp */
