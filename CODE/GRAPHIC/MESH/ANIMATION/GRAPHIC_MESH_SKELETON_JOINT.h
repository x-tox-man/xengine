//
//  GRAPHIC_MESH_SKELETON_JOINT.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_SKELETON_JOINT__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_SKELETON_JOINT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_SCALAR.h"

XS_CLASS_BEGIN( GRAPHIC_MESH_SKELETON_JOINT )

    GRAPHIC_MESH_SKELETON_JOINT();
    ~GRAPHIC_MESH_SKELETON_JOINT();

    XS_DEFINE_SERIALIZABLE

    inline void SetName( const char * name ) { CORE_DATA_COPY_STRING( Name, name); }
    inline char * GetName() { return Name; }

    void print( int level );

    int
        Index,
        ChildCount;
    CORE_SCALAR
        Transform;
    GRAPHIC_MESH_SKELETON_JOINT::PTR
        ChildJointTable;
    char
        Name[256];

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_SKELETON_JOINT__) */
