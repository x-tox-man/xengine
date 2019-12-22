//
//  GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER_hpp
#define GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GAMEPLAY_COMPONENT_AABB_NODE.h"

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER )

    GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER();

    void Collide( GAMEPLAY_COMPONENT_AABB_NODE * node );
    void RenderFrontToBack( CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback );
    void Reset();

private:

    int
        Amount;
    GAMEPLAY_COMPONENT_AABB_NODE
        * RenderRoot;
    GRAPHIC_CAMERA::PTR
        Camera;
    bool
        FrontToBack;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER_hpp */