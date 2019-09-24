//
//  GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_RENDERER__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_RENDERER__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_AABB_TREE.h"
#include "GAMEPLAY_COMPONENT_AABB_NODE.h"
#include "GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_RENDERER, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_RENDERER();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_RENDERER();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step ) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

    virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) override;
    virtual void RemoveEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) override;

    void RenderFrontToBack( GAMEPLAY_COMPONENT_AABB_NODE * node );

    void SetRenderer( GRAPHIC_RENDERER * renderer ) { Renderer = renderer; }

    virtual void Clear() override {
        
        EntitiesTable.clear();
        Tree.Reset();
    }

    inline void SetCustomRenderComponentIndex( int index ) { CustomRenderComponentIndex = index; }

private :

    GRAPHIC_RENDERER
        * Renderer;
    GAMEPLAY_COMPONENT_AABB_TREE
        Tree;
    int
        CustomRenderComponentIndex;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_RENDERER__) */
