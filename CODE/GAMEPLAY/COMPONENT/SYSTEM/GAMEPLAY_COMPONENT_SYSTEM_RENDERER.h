//
//  GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_RENDERER, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_RENDERER();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_RENDERER();

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;
    virtual void Render() override;
    virtual void Finalize() override;

    void SetRenderer( GRAPHIC_RENDERER * renderer ) { Renderer = renderer; }

private :

    GRAPHIC_RENDERER
        * Renderer;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_RENDERER__) */
