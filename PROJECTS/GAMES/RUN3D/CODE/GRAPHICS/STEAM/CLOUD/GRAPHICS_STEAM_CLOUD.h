//
//  GRAPHICS_STEAM_CLOUD.hpp
//  Run3d
//
//  Created by Christophe Bernard on 27/03/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef GRAPHICS_STEAM_CLOUD_hpp
#define GRAPHICS_STEAM_CLOUD_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MANAGER.h"
#include "GRAPHIC_PARTICLE_EMITER.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_PARTICLE_MODIFIER_GRAVITY.h"
#include "GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY.h"
#include "R3D_RESOURCES.h"

#define PARTICLE_SIZE 256

/*XS_CLASS_BEGIN( GRAPHICS_STEAM_CLOUD )

    GRAPHICS_STEAM_CLOUD();
    ~GRAPHICS_STEAM_CLOUD();

    void Initialize();
    void Update( float step );

    static void InternalEmit( GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_CLOUD, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> & emiter,
                             int start,
                             int end );

    private:

    GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_CLOUD, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>
        * Emiter;

XS_CLASS_END

 */

#endif /* GRAPHICS_STEAM_CLOUD_hpp */
