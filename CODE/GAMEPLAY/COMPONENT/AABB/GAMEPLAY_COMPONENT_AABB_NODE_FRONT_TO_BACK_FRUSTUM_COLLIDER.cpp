//
//  GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER.h"

GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER::GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER() :
    Amount( 0 ),
    RenderRoot( NULL ),
    FrontToBack( true ) {
    
}

void GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER::Collide( GAMEPLAY_COMPONENT_AABB_NODE * node ) {
    
    Amount++;
    
    if ( RenderRoot == NULL ) {
        
        RenderRoot = node;
    }
    else {
        if ( FrontToBack ) {
            RenderRoot->InsertFrontToBack( node );
        }
        else {
            RenderRoot->InsertBackToFront( node );
        }
    }
}

void GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER::RenderFrontToBack( CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback ) {
    
    if ( FrontToBack ) {
        
        if ( RenderRoot ) {
            
            RenderRoot->RenderFrontToBack( callback );
        }
    }
    else {
        abort();
    }
}

void GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER::Reset() {
    
    Amount = 0;
    RenderRoot = NULL;
}
