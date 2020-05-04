//
//  GAMEPLAY_COMPONENT_ENTITY.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GAMEPLAY_COMPONENT_ENTITY )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( GAMEPLAY_COMPONENT_POSITION::PTR, GAMEPLAY_COMPONENT_ENTITY , GetComponentPosition )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( GAMEPLAY_COMPONENT_RENDER::PTR, GAMEPLAY_COMPONENT_ENTITY , GetComponentRender)
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( GAMEPLAY_COMPONENT_PHYSICS::PTR, GAMEPLAY_COMPONENT_ENTITY , GetComponentPhysics)
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GAMEPLAY_COMPONENT_ENTITY, SetPosition, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GAMEPLAY_COMPONENT_ENTITY, SetOrientation, const CORE_MATH_QUATERNION & )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_COMPONENT_ENTITY )

//XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY )
//XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY * )

GAMEPLAY_COMPONENT_ENTITY::GAMEPLAY_COMPONENT_ENTITY( const GAMEPLAY_COMPONENT_ENTITY & other ) :
    Handle(),
    Parent( other.GetParent() ),
    Childs(),
    ComponentCount( 0 ) {
}

void GAMEPLAY_COMPONENT_ENTITY::Scale( float scale ) {
    
    GAMEPLAY_COMPONENT_RENDER * render_component = (GAMEPLAY_COMPONENT_RENDER *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render_component->SetScaleFactor( scale );
    
    if ( render_component ) {
        
        render_component->GetAABBNode().GetBox().SetHalfDiagonal( render_component->GetAABBNode().GetBox().GetHalfDiagonal() * scale );
    }
}

void GAMEPLAY_COMPONENT_ENTITY::Resize( const CORE_MATH_VECTOR & size ) {
    
    GAMEPLAY_COMPONENT_RENDER * render_component = (GAMEPLAY_COMPONENT_RENDER *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    float scale = ( (render_component->GetAABBNode().GetBox().GetHalfDiagonal() *2).ComputeSquareLength() / size.ComputeSquareLength() );
    
    assert( scale > 0 );
    
    render_component->SetScaleFactor( scale );
    
    if ( render_component ) {
        
        render_component->GetAABBNode().GetBox().SetHalfDiagonal( size * 0.5f );
    }
}

void GAMEPLAY_COMPONENT_ENTITY::SetPosition( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_COMPONENT_POSITION * position_component = (GAMEPLAY_COMPONENT_POSITION *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    GAMEPLAY_COMPONENT_PHYSICS * physics_component = (GAMEPLAY_COMPONENT_PHYSICS *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    GAMEPLAY_COMPONENT_RENDER * render_component = (GAMEPLAY_COMPONENT_RENDER *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    position_component->SetPosition( position );
    
    if ( physics_component ) {
        
        physics_component->ForcePosition( position );
    }
    
    if ( render_component ) {
        
        render_component->GetAABBNode().GetBox().SetPosition( position );
    }

    /*for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++ ) {
        
        if ( ChildEntities[ i ] ) {
            
            ChildEntities[ i ]->SetPosition( position );
        }
    }*/
}

void GAMEPLAY_COMPONENT_ENTITY::SetPositionOffset( const CORE_MATH_VECTOR & offset ) {
    
    GAMEPLAY_COMPONENT_POSITION * position_component = (GAMEPLAY_COMPONENT_POSITION *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPositionOffset( offset );
    
    CORE_RUNTIME_Abort();
}

void GAMEPLAY_COMPONENT_ENTITY::SetOrientation( const CORE_MATH_QUATERNION & orientation ) {
    
    GAMEPLAY_COMPONENT_POSITION * position_component = (GAMEPLAY_COMPONENT_POSITION *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    GAMEPLAY_COMPONENT_PHYSICS * physics_component = (GAMEPLAY_COMPONENT_PHYSICS *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    position_component->SetOrientation( orientation );
    
    if ( physics_component) {
        
        physics_component->SetOrientation( orientation );
    }
    
    /*for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++ ) {
        
        if ( ChildEntities[ i ] ) {
            
            ChildEntities[ i ]->SetOrientation(q);
        }
    }*/
}

void GAMEPLAY_COMPONENT_ENTITY::CollidesWith( GAMEPLAY_COMPONENT_ENTITY * other ) {
    
}
