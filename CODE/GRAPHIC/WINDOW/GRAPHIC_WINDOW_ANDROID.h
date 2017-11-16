//
//  GRAPHIC_WINDOW_ANDROID.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_WINDOW_ANDROID__
#define __GAME_ENGINE_REBORN__GRAPHIC_WINDOW_ANDROID__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_WINDOW.h"

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <iostream>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_ANDROID, GRAPHIC_WINDOW )

    GRAPHIC_WINDOW_ANDROID();
    virtual ~GRAPHIC_WINDOW_ANDROID();

    virtual void Initialize() override;
    virtual void EnableBackgroundContext(bool enable) override;

	EGLDisplay
		Display;
    EGLSurface
    	Surface;
    EGLContext
    	Context,
        SharedContext;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_WINDOW_ANDROID__) */
