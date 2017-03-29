//
//  PERIPHERIC_INTERRACTION_VIBRATOR.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef PERIPHERIC_INTERRACTION_VIBRATOR_hpp
#define PERIPHERIC_INTERRACTION_VIBRATOR_hpp

#include "CORE_HELPERS_CLASS.h"
#include "PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

#define MAX_VIBRATION_COUNT 16

XS_CLASS_BEGIN( PERIPHERIC_INTERRACTION_VIBRATOR )

    PERIPHERIC_INTERRACTION_VIBRATOR();
    ~PERIPHERIC_INTERRACTION_VIBRATOR();

    void Initialize();

    void Vibrate(float duration );
    void Update( const float step );

    #if PLATFORM_ANDROID
        void SetJNIActivityEnvAndClass( JNIEnv* jni, jobject &obj ) { JNIEnvironment = jni; jniActivityClaszz = obj; }

        JNIEnv* JNIEnvironment;
        jobject vibrator_svc;
        jmethodID vib_method_id;
        jobject jniActivityClaszz;
    #endif

    PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT
        * EffectTable[ MAX_VIBRATION_COUNT ];


XS_CLASS_END

#endif /* PERIPHERIC_INTERRACTION_VIBRATOR_hpp */
