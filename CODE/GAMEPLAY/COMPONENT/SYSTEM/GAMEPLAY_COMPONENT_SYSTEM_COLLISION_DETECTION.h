//
//  GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_UNIQUE.h"
#if DEBUG
    #include "TOOL_BULLET_GL_DEBUGGER.h"
#endif

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
    #include "btMultiBodyConstraintSolver.h"
#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step ) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

    inline void SetGravity( const CORE_MATH_VECTOR & gravity ) { Gravity = gravity; }
    inline void SetRenderer( GRAPHIC_RENDERER * renderer ) { Renderer = renderer; }

    #ifdef __BULLET_PHYSICS__
        void SetCollisionFilter( btOverlapFilterCallback * callback );

        btDiscreteDynamicsWorld * GetDynamicsWorld() { return DynamicsWorld; }

        inline void SetNearCallback( btNearCallback callback ) {
            
            NearCallback = callback;
            HasNearCallback = true;
        }

    #endif

    virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) override {
        
        CORE_RUNTIME_Abort();
    }
    void AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity, int group, int mask );
    void AddStaticEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity, int group, int mask );

    void DebugDrawWorld();

private :

    GRAPHIC_RENDERER
        * Renderer;
    CORE_MATH_VECTOR
        Gravity;
    bool
        HasNearCallback;

#ifdef __BULLET_PHYSICS__
    btDiscreteDynamicsWorld
        * DynamicsWorld;
    btNearCallback
        NearCallback;

    #if DEBUG
        TOOL_BULLET_GL_DEBUGGER
            Debugger;
    #endif
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__) */
