//
//  GRAPHIC_WINDOW_ANDROID.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_WINDOW_ANDROID.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))

GRAPHIC_WINDOW_ANDROID::GRAPHIC_WINDOW_ANDROID() :
	GRAPHIC_WINDOW(),
	Display(),
    Surface(),
    Context(),
    SharedContext() {
    
}

GRAPHIC_WINDOW_ANDROID::~GRAPHIC_WINDOW_ANDROID() {

}

void GRAPHIC_WINDOW_ANDROID::Initialize() {

}

void GRAPHIC_WINDOW_ANDROID::EnableBackgroundContext(bool enable) {
    
    if ( enable ) {
    	if ( eglMakeCurrent( Display, 0, 0, SharedContext ) == EGL_FALSE) {
	        LOGW("native-activity Unable to SHARED eglMakeCurrent");
	        return;
	    }
	    else {
			LOGW("native-activity OK SHARED eglMakeCurrent");
	    }
    }
    else {
    	/*if ( eglMakeCurrent(Display, Surface, Surface, Context) == EGL_FALSE) {
	        LOGW("native-activity Unable to eglMakeCurrent");
	        return;
	    }
	    else {
			LOGW("native-activity OK eglMakeCurrent");
	    }*/
    }
}
