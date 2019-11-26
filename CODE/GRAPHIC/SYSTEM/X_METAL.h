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

//renderer in scope
#define GRAPHIC_SYSTEM_ApplyMatrix(index, size, transpose, array) \
    memcpy( renderer.GetOffsetPointer( index ), array, 64 ); \
    renderer.OffsetPointer( 64 );

#define GRAPHIC_SYSTEM_ApplyVector(index, size, array) \
    memcpy( renderer.GetOffsetPointer( index ), array, 16 ); \
    renderer.OffsetPointer( 16 );

#define GRAPHIC_SYSTEM_ApplyFloat(index, value) \
    memcpy( renderer.GetOffsetPointer( index ), (void *) &value, 4 ); \
    renderer.OffsetPointer( 4 );

#define GRAPHIC_SYSTEM_ApplyFloatArray(index, size, array) \
    memcpy( renderer.GetOffsetPointer( index ), array, (size * 4) ); \
    renderer.OffsetPointer( (size * 4) );


#endif /* METAL_h */
