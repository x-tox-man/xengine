//
//  GAMEPLAY_COMPONENT_ENTITY.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__

#define GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS 8
#define GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS 8

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"
#include "CORE_MATH_VECTOR.h"
#include "GAMEPLAY_COMPONENT_HANDLE.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "CORE_MATH_QUATERNION.h"

class GAMEPLAY_COMPONENT_POSITION;
class GAMEPLAY_COMPONENT_RENDER;
class GAMEPLAY_COMPONENT_PHYSICS;
class GAMEPLAY_COMPONENT_ANIMATION;

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_ENTITY )
    
    GAMEPLAY_COMPONENT_ENTITY() :
        SubComponent( this ),
        Components(),
        Parent( NULL ),
        ChildEntities() {
        
        for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++ ) {
            
            ChildEntities[ i ] = NULL;
        }
    }
    
    GAMEPLAY_COMPONENT_ENTITY( GAMEPLAY_COMPONENT_ENTITY * subclass ) :
        SubComponent( subclass ),
        Components(),
        Parent( NULL ),
        ChildEntities() {
        
            for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++ ) {
                
                ChildEntities[ i ] = NULL;
            }
        }
    
    virtual ~GAMEPLAY_COMPONENT_ENTITY() {
        
    }

    XS_DEFINE_SERIALIZABLE

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT_ENTITY );

    GAMEPLAY_COMPONENT_POSITION * GetComponentPosition() {
        
        return ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    }
    
    GAMEPLAY_COMPONENT_RENDER * GetComponentRender() {
        
        return ( GAMEPLAY_COMPONENT_RENDER * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    }
    
    GAMEPLAY_COMPONENT_PHYSICS * GetComponentPhysics() {
        
        return ( GAMEPLAY_COMPONENT_PHYSICS * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    }
    
    GAMEPLAY_COMPONENT_ANIMATION * GetComponentAnimation() {
        
        return ( GAMEPLAY_COMPONENT_ANIMATION * )GetComponent( GAMEPLAY_COMPONENT_TYPE_Animation );
    }

    void SetCompononent( GAMEPLAY_COMPONENT_HANDLE component, int component_index ) {
        
        Components[ component_index ] = component;
    }

    inline void SetChild( GAMEPLAY_COMPONENT_ENTITY * entity, int index ) {
        
        ChildEntities[ index ] = entity;
        entity->SetParent( this );
    }

    virtual GAMEPLAY_COMPONENT_ENTITY * Clone() const {
        
        return new GAMEPLAY_COMPONENT_ENTITY();
    }

public:

    inline GAMEPLAY_COMPONENT * GetComponent( int component_index ) { return Components[ component_index ].GetComponent(); }
    inline const GAMEPLAY_COMPONENT_HANDLE & GetComponentHandle( int component_index ) const { return Components[ component_index ]; }
    inline GAMEPLAY_COMPONENT_HANDLE & GetComponentHandle( int component_index ) { return Components[ component_index ]; }
    inline GAMEPLAY_COMPONENT_ENTITY_HANDLE & GetHandle() { return Handle; }
    inline GAMEPLAY_COMPONENT_ENTITY * GetChild( int child_index ) { return ChildEntities[ child_index ]; }

    void SetPosition( const CORE_MATH_VECTOR & position );
    void SetPositionOffset( const CORE_MATH_VECTOR & offset );
    void SetOrientation( const CORE_MATH_QUATERNION & orientation );

    inline GAMEPLAY_COMPONENT_ENTITY * GetParent() const { return Parent; }
    inline void SetParent( GAMEPLAY_COMPONENT_ENTITY * parent ) { Parent = parent; }

    void PatchMemory( int index, GAMEPLAY_COMPONENT * component ) {
        
        Components[ index ].SetComponent( component->GetComponentAt( Components[ index ].GetIndex(), Components[ index ].GetOffset() + 1 ) );
    }

    virtual void CollidesWith( GAMEPLAY_COMPONENT_ENTITY * other );

private:

    GAMEPLAY_COMPONENT_ENTITY
        * SubComponent;
    GAMEPLAY_COMPONENT_HANDLE
        Components[ GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS ];
    GAMEPLAY_COMPONENT_ENTITY_HANDLE
        Handle;
    GAMEPLAY_COMPONENT_ENTITY
        * Parent,
        * ChildEntities[ GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS ];

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__) */
