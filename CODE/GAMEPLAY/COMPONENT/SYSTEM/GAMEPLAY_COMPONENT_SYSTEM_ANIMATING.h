//
//  GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_ANIMATING__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_ANIMATING__

#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_MESH_ANIMATION.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_ANIMATING, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_ANIMATING();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_ANIMATING();

    virtual void Initialize() override;
    virtual void Update( float time_step) override;
    virtual void Render() override;
    virtual void Finalize() override;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_ANIMATING__) */
