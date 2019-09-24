//
//  GRAPHIC_PARTICLE_SYSTEM.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 7/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_SYSTEM_hpp
#define GRAPHIC_PARTICLE_SYSTEM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_PARTICLE_MANAGER.h"
#include "GRAPHIC_CAMERA_BILLBOARD.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_PARTICLE.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_PARTICLE_SYSTEM, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_PARTICLE_SYSTEM();
    ~GAMEPLAY_COMPONENT_PARTICLE_SYSTEM();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step ) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

    void Update(float time_step, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat);
    void Render( GRAPHIC_RENDERER & renderer );

XS_CLASS_END

#endif /* GRAPHIC_PARTICLE_SYSTEM_hpp */
