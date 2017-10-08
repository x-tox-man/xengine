//
//  R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 23/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT_hpp
#define R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "LEVEL_ENVIRONMENT.h"
#include "R3D_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT, GAMEPLAY_COMPONENT_ENTITY )

    R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT();

    void Initialize( const CORE_MATH_VECTOR & position );
    virtual void CollidesWith( GAMEPLAY_COMPONENT_ENTITY * other ) override;

XS_CLASS_END

#endif /* R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT_hpp */
