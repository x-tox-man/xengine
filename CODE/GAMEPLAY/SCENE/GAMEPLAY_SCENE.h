//
//  GAMEPLAY_SCENE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_SCENE__
#define __GAME_ENGINE_REBORN__GAMEPLAY_SCENE__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

XS_CLASS_BEGIN( GAMEPLAY_SCENE )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_SCENE );

    GAMEPLAY_SCENE();
    ~GAMEPLAY_SCENE();

    static void Ping();

    void Update( float time_step );
    void Render();

    std::vector< GAMEPLAY_COMPONENT_SYSTEM * > & GetUpdatableSystemTable() { return UpdatableSystemTable; };
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * > & GetRenderableSystemTable() { return RenderableSystemTable; };

    void InsertUpdatableSystem( GAMEPLAY_COMPONENT_SYSTEM * system );
    void InsertRenderableSystem( GAMEPLAY_COMPONENT_SYSTEM * system );

    std::vector< GAMEPLAY_COMPONENT_SYSTEM * > UpdatableSystemTable;
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * > RenderableSystemTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_SCENE__) */
