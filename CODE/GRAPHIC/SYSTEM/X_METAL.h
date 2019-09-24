//
//  METAL.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/12/2018.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef METAL_h
#define METAL_h

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

#include "GRAPHIC_TEXTURE_INFO.h"
#include "SERVICE_LOGGER.h"

#if PLATFORM_OSX || PLATFORM_IOS
#define GFX_CHECK( __METHOD__ ) \
__METHOD__ \
{ \
abort();\
}
#else
#define GFX_CHECK( __METHOD__ ) \
__METHOD__ \
{ \
abort();\
}
#endif


#define GRAPHIC_SYSTEM_ApplyMatrix(index, size, transpose, array) \
abort();

#define GRAPHIC_SYSTEM_ApplyVector(index, size, array) \
abort();

#define GRAPHIC_SYSTEM_ApplyFloat(index, value) \
abort();

#define GRAPHIC_SYSTEM_ApplyFloatArray(index, size, array) \
abort();



#endif /* METAL_h */
