//
//  GRAPHIC_OBJECT_ANIMATED.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_ANIMATED__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_ANIMATED__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_OBJECT_ANIMATED, GRAPHIC_OBJECT )

    GRAPHIC_OBJECT_ANIMATED();
    virtual ~GRAPHIC_OBJECT_ANIMATED();

    virtual void Render( GRAPHIC_RENDERER & renderer ) override;

    inline GRAPHIC_MESH_ANIMATION_CONTROLLER * GetAnimationController() { return AnimationController; };
    inline void SetAnimationController( GRAPHIC_MESH_ANIMATION_CONTROLLER * animation ) { AnimationController = animation; };

private:

    GRAPHIC_MESH_ANIMATION_CONTROLLER
        * AnimationController;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_ANIMATED__) */
