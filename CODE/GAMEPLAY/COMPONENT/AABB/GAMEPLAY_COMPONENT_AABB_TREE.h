//
//  AABBTree.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef AABBTree_hpp
#define AABBTree_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GAMEPLAY_COMPONENT_AABB_NODE.h"

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_AABB_TREE )
    
    GAMEPLAY_COMPONENT_AABB_TREE( float margin );
    
    void Update();
    void Reset();

    void Remove( GAMEPLAY_COMPONENT_ENTITY * entity );
    void Insert( GAMEPLAY_COMPONENT_ENTITY * entity );
    void Insert( GAMEPLAY_COMPONENT_ENTITY * entity, float margin );

    void QueryTopToBottom( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback );
    void QueryBottomToTop( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback );
    
    inline void SetFrontToBack( bool front_to_back ) { FrontToBack = front_to_back; }
    
    private :
    
    void InsertBackToFront( GAMEPLAY_COMPONENT_AABB_NODE * node );

    void Insert( GAMEPLAY_COMPONENT_AABB_NODE * node, GAMEPLAY_COMPONENT_AABB_NODE ** parent );
    
    GAMEPLAY_COMPONENT_AABB_NODE
        * Root;
    bool
        FrontToBack;
    float
        Margin;
    std::list< GAMEPLAY_COMPONENT_AABB_NODE * >
        InvalidNodesList;

XS_CLASS_END

#endif /* AABBTree_hpp */
