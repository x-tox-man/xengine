//
//  APPLICATION_CONFIGURATION.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "APPLICATION_CONFIGURATION.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

APPLICATION_CONFIGURATION_OPTIONS::APPLICATION_CONFIGURATION_OPTIONS() :
    GraphicsOptionRenderTargetResolutionDivider( 1 ) {
    
}

void APPLICATION_CONFIGURATION_OPTIONS::Initialize() {
    
#if PLATFORM_ANDROID
    GraphicsOptionRenderTargetResolutionDivider = 2;
#elif PLATFORM_OSX
#elif PLATFORM_IOS
    GraphicsOptionRenderTargetResolutionDivider = 2;
#elif PLATFORM_WINDOWS
#else
#endif
    
}
