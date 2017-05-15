//
//  GAMEPLAY_COMPONENT_ENTITY.h
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_ENTITY )

    GAMEPLAY_COMPONENT_ENTITY();
    ~GAMEPLAY_COMPONENT_ENTITY();

    inline void SetCompononent( GAMEPLAY_COMPONENT * component, int component_index ) {
        
        Components[ component_index ] = component;
    }

    inline void SetChild( GAMEPLAY_COMPONENT_ENTITY * entity, int index ) {
        
        ChildEntities[ index ] = entity;
    }

    inline GAMEPLAY_COMPONENT * GetComponent( int component_index ) { return Components[ component_index ]; }

    inline GAMEPLAY_COMPONENT_ENTITY * GetChild( int child_index ) { return ChildEntities[ child_index ]; }

    void SetPosition( const CORE_MATH_VECTOR & position );

    Scalar_SGet( int, Index )

private:

GAMEPLAY_COMPONENT
    * Components[ GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS ];
GAMEPLAY_COMPONENT_ENTITY
    * Parent,
    * ChildEntities[ GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS ];

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__) */
