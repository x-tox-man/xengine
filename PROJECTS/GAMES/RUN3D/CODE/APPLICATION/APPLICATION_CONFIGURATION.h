//
//  APPLICATION_CONFIGURATION.h
//  RUN3D
//
//  Created by Christophe Bernard on 22/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef APPLICATION_CONFIGURATION_h
#define APPLICATION_CONFIGURATION_h

#define APPLICATION_LEVEL_DISTANCE_UNIT 1

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"

XS_CLASS_BEGIN(APPLICATION_CONFIGURATION_OPTIONS )

    XS_DEFINE_UNIQUE( APPLICATION_CONFIGURATION_OPTIONS )

    void Initialize();

    inline int GetGraphicsOptionRenderTargetResolutionDivider() const { return GraphicsOptionRenderTargetResolutionDivider; }

private :

    int
        GraphicsOptionRenderTargetResolutionDivider;
    
XS_CLASS_END

#endif /* APPLICATION_CONFIGURATION_h */
