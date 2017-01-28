//
//  CORE_RUNTIME_ENVIRONMENT_ANDROID.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include <map>
#include <vector>
#include <string>
#include <list>
#include <stdlib.h>
#include <assert.h>
#include <cstddef>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#define CORE_RUNTIME_Abort() printf( "CORE_RUNTIME_Abort" ); abort();