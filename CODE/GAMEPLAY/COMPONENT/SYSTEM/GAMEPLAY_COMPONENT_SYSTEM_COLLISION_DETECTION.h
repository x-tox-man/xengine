//
//  GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h
//  GAME-ENGINE-REBORN
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

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION();

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;
    virtual void Render() override;
    virtual void Finalize() override;

    void SetRenderer( GRAPHIC_RENDERER * renderer ) { Renderer = renderer; }

    #ifdef __BULLET_PHYSICS__
        btDiscreteDynamicsWorld * GetDynamicsWorld() { return DynamicsWorld; }
    #endif

    virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY * entity ) override;

private :

    GRAPHIC_RENDERER
        * Renderer;

#ifdef __BULLET_PHYSICS__
    btDiscreteDynamicsWorld * DynamicsWorld;
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__) */
