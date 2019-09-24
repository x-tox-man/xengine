//
//  R3D_LEVEL_TRACK.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_LEVEL_TRACK_hpp
#define R3D_LEVEL_TRACK_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

//Should be a component
XS_CLASS_BEGIN( R3D_LEVEL_TRACK )

    GAMEPLAY_COMPONENT_ENTITY::PTR CreateEntity( const CORE_MATH_VECTOR & position );
    void AddToSystems();

private:

    R3D_LEVEL_TRACK();

XS_CLASS_END

#endif /* R3D_LEVEL_TRACK_hpp */
