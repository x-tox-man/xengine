//
//  AABBNode.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef AABBNode_hpp
#define AABBNode_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GRAPHIC_CAMERA.h"
#include "CORE_HELPERS_CALLBACK.h"

class GAMEPLAY_COMPONENT_ENTITY;

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_AABB_NODE )
    
    GAMEPLAY_COMPONENT_AABB_NODE( float margin );
    
    void Remove( GAMEPLAY_COMPONENT_ENTITY * entity );
    
    bool Finalize();

    void Update( std::list< GAMEPLAY_COMPONENT_AABB_NODE * > & invalid_nodes );
    
    inline void UpdateCenterAndExtent() {
        
        if ( Left ) Box.AggregateWithBox( Left->Box );
        if ( Right ) Box.AggregateWithBox( Right->Box );
        
        BoxWithMargin.SetPosition( Box.GetPosition() );
        BoxWithMargin.SetHalfDiagonal( Box.GetHalfDiagonal() +CORE_MATH_VECTOR( Margin, Margin, Margin, 0.0f ) );
    }
    
    inline bool IsLeaf() const {
        
        return Entity != NULL;
    }
    
    void QueryTopToBottom( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback );
    void QueryBottomToTop( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback );

    void RenderFrontToBack( CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback );
    
    void InsertFrontToBack( GAMEPLAY_COMPONENT_AABB_NODE * node );
    void InsertBackToFront( GAMEPLAY_COMPONENT_AABB_NODE * node );
    inline GAMEPLAY_COMPONENT_ENTITY * GetEntity() { return Entity; }
    inline void SetEntity( GAMEPLAY_COMPONENT_ENTITY * entity ) { Entity = entity; }
    inline CORE_MATH_SHAPE & GetBox() { return Box; }
    inline CORE_MATH_SHAPE & GetBoxWithMargin() { return BoxWithMargin; }
    inline float GetMargin() const { return Margin; }

GAMEPLAY_COMPONENT_AABB_NODE
    * Left,
    * Right,
    * ZOrderLeft,
    * ZOrderRight;

private:
    
    CORE_MATH_SHAPE
        Box,
        BoxWithMargin;
    GAMEPLAY_COMPONENT_ENTITY
        * Entity;
    float
        Margin;

XS_CLASS_END

#endif /* AABBNode_hpp */
