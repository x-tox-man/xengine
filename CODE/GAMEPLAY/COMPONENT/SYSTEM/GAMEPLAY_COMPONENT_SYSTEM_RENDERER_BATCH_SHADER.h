//
//  GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER_hpp
#define GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER_hpp

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

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER();

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
    inline void SetEffect( GRAPHIC_SHADER_EFFECT::PTR effect ) { Effect = effect; }

    private :

    GRAPHIC_RENDERER
        * Renderer;
    GAMEPLAY_COMPONENT_AABB_TREE
        Tree;
    GRAPHIC_SHADER_EFFECT::PTR
        Effect;
    int
        CustomRenderComponentIndex;
    GRAPHIC_SHADER_ATTRIBUTE::PTR
        MVPMatrix,
        ModelMatrix,
        ViewMatrix,
        TimeModulator,
        ProjectionMatrix,
        ShadowmapMVP,
        EndClipSpace;
    GRAPHIC_SHADER_ATTRIBUTE::PTR
        Depth[8];
    GRAPHIC_OBJECT_RENDER_OPTIONS
        Options,
        ParentOptions;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER_hpp */
