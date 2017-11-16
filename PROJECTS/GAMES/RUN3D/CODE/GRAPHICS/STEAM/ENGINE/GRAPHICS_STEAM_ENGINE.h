//
//  GRAPHICS_STEAM_ENGINE.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 15/10/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef GRAPHICS_STEAM_ENGINE_hpp
#define GRAPHICS_STEAM_ENGINE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MANAGER.h"
#include "GRAPHIC_PARTICLE_EMITER.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_PARTICLE_MODIFIER_GRAVITY.h"
#include "GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY.h"
#include "GRAPHIC_PARTICLE_SYSTEM.h"
#include "R3D_RESOURCES.h"

#define PARTICLE_SIZE 4096

XS_CLASS_BEGIN( GRAPHICS_STEAM_ENGINE )

    GRAPHICS_STEAM_ENGINE();
    ~GRAPHICS_STEAM_ENGINE();

    void Initialize();
    inline void SetPosition( CORE_MATH_VECTOR & position) { Emiter->SetPosition( position ); }
    inline void SetVelocity( CORE_MATH_VECTOR & velocity) { Emiter->SetVelocity( velocity ); }

    static void InternalEmit( GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_ENGINE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> & emiter,
                             int start,
                             int end );

private:

    GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_ENGINE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>
        * Emiter;

XS_CLASS_END

#endif /* GRAPHICS_STEAM_ENGINE_hpp */
