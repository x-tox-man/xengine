//
//  GRAPHIC_MESH_SUB_SKELETON.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_SUB_SKELETON__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_SUB_SKELETON__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_MESH_ANIMATION_JOINT.h"
#include "CORE_HELPERS_SCALAR.h"

XS_CLASS_BEGIN( GRAPHIC_MESH_SUB_SKELETON )

    GRAPHIC_MESH_SUB_SKELETON();
    ~GRAPHIC_MESH_SUB_SKELETON();

    XS_DEFINE_SERIALIZABLE

    void Initialize( const std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & table );

    void print();
    
    GRAPHIC_MESH_SUB_SKELETON *
        SubSkelettonTable;
    GRAPHIC_MESH_ANIMATION_JOINT *
        Joint;
    int
        JointIndex,
        ChildCount;
    CORE_SCALAR
        Transform;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_SUB_SKELETON__) */
