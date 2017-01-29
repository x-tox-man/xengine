//
//  GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_MESH_ANIMATION.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING();

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;
    virtual void Render() override;
    virtual void Finalize() override;

    void SetFirstMeshAnimation( GRAPHIC_MESH_ANIMATION * animation ) { First = animation; }
    void SetSecondMeshAnimation( GRAPHIC_MESH_ANIMATION * animation ) { Second = animation; }

private :

    GRAPHIC_MESH_ANIMATION
        * First,
        * Second;
    GRAPHIC_MESH_ANIMATION
        BlendedAnimation;


XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING__) */
