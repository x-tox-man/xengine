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

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_ANIMATED, GRAPHIC_OBJECT )

GRAPHIC_OBJECT_ANIMATED();

std::vector< GRAPHIC_MESH_ANIMATION *> & getAnimationControllerTable() { return AnimationControllerTable; }
std::vector< GRAPHIC_MESH_ANIMATION_JOINT *> & getJointTable() { return JointTable; }

std::vector< GRAPHIC_MESH_ANIMATION *>
    AnimationControllerTable;

//TODO: only for resource compiling target
std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>
    JointTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_ANIMATED__) */
