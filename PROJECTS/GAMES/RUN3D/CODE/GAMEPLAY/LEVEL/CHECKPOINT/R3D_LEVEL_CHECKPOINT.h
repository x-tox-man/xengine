//
//  R3D_LEVEL_CHECKPOINT.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_LEVEL_CHECKPOINT_hpp
#define R3D_LEVEL_CHECKPOINT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "LEVEL_ENVIRONMENT.h"
#include "R3D_PLAYER.h"
#include "R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT.h"

XS_CLASS_BEGIN( R3D_LEVEL_CHECKPOINT )

    static GAMEPLAY_COMPONENT_ENTITY::PTR CreateEntity( const CORE_MATH_VECTOR & position);

private:

    R3D_LEVEL_CHECKPOINT();

XS_CLASS_END

#endif /* R3D_LEVEL_CHECKPOINT_hpp */
