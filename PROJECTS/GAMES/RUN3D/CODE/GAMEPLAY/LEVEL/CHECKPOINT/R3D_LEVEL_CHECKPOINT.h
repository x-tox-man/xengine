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

XS_CLASS_BEGIN_WITH_ANCESTOR(R3D_LEVEL_CHECKPOINT, GAMEPLAY_COMPONENT_ENTITY )

    R3D_LEVEL_CHECKPOINT();

    void Initialize( const CORE_MATH_VECTOR & position );

    virtual GAMEPLAY_COMPONENT_ENTITY * Clone() const {
        
        return new R3D_LEVEL_CHECKPOINT();
    }

private:

XS_CLASS_END

#endif /* R3D_LEVEL_CHECKPOINT_hpp */
