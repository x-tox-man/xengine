//
//  R3D_GAMEPLAY_WEAPON_SYSTEM.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 28/04/2019.
//  Copyright © 2019 IGZ. All rights reserved.
//

#ifndef R3D_GAMEPLAY_WEAPON_SYSTEM_hpp
#define R3D_GAMEPLAY_WEAPON_SYSTEM_hpp

#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_MESH_ANIMATION.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_GAMEPLAY_WEAPON_SYSTEM, GAMEPLAY_COMPONENT_SYSTEM )

    R3D_GAMEPLAY_WEAPON_SYSTEM();
    virtual ~R3D_GAMEPLAY_WEAPON_SYSTEM();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step ) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

XS_CLASS_END

#endif /* R3D_GAMEPLAY_WEAPON_SYSTEM_hpp */
