//
//  PERIPHERIC_INTERRACTION_VIBRATOR.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "PERIPHERIC_INTERRACTION_VIBRATOR.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "SERVICE_LOGGER.h"

#if PLATFORM_ANDROID
    #include <jni.h>
#endif

PERIPHERIC_INTERRACTION_VIBRATOR::PERIPHERIC_INTERRACTION_VIBRATOR() :
    EffectTable() {
    
    for (int i = 0; i < MAX_VIBRATION_COUNT; i++) {
        EffectTable[ i ] = NULL;
    }
}

PERIPHERIC_INTERRACTION_VIBRATOR::~PERIPHERIC_INTERRACTION_VIBRATOR() {
    
}

void PERIPHERIC_INTERRACTION_VIBRATOR::Initialize() {
    
#if PLATFORM_ANDROID
    SERVICE_LOGGER_Error( "PERIPHERIC_INTERRACTION_VIBRATOR Initialize" );
    
    jobject obj = jniActivityClaszz; 
    jclass sys_svc = JNIEnvironment->GetObjectClass(obj);
    jmethodID method_id = JNIEnvironment->GetMethodID(sys_svc,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
    jstring method_str = JNIEnvironment->NewStringUTF("vibrator");
    
    vibrator_svc = JNIEnvironment->CallObjectMethod(obj, method_id,method_str );
    
    jclass vib_cls = JNIEnvironment->GetObjectClass(vibrator_svc);
    vib_method_id = JNIEnvironment->GetMethodID(vib_cls, "vibrate","(J)V");
#endif
}

void PERIPHERIC_INTERRACTION_VIBRATOR::Vibrate(float duration ) {
    
    for (int i = 0; i < MAX_VIBRATION_COUNT; i++) {
        if ( EffectTable[ i ] == NULL ) {
            
            EffectTable[ i ] = new PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT(duration);
            
#if PLATFORM_ANDROID
            SERVICE_LOGGER_Error( "PERIPHERIC_INTERRACTION_VIBRATOR Vibrate" );
            
            jlong var1 = (long) (duration * 1000.0f); //vibrate for one second
            JNIEnvironment->CallVoidMethod(vibrator_svc, vib_method_id, var1);
#endif
            break;
        }
    }
}

void PERIPHERIC_INTERRACTION_VIBRATOR::Update( const float step ) {
    
    for (int i = 0; i < MAX_VIBRATION_COUNT; i++) {
        if ( EffectTable[ i ] != NULL ) {
            
            EffectTable[ i ]->Update( step );
            
            if ( EffectTable[ i ]->IsDone() ) {
                
                delete EffectTable[ i ];
            }
        }
    }
}
