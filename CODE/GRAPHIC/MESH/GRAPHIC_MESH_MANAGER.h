//
//  GRAPHIC_MESH_MANAGER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_MANAGER__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_MANAGER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT.h"
#include "CORE_FILESYSTEM.h"

class GRAPHIC_OBJECT_ANIMATED;

enum GRAPHIC_MESH_TYPE {
    GRAPHIC_MESH_TYPE_None = 0,
    GRAPHIC_MESH_TYPE_OpenCollada,
    GRAPHIC_MESH_TYPE_ModelResource,
    GRAPHIC_MESH_TYPE_Count
};

XS_CLASS_BEGIN( GRAPHIC_MESH_MANAGER )

    XS_DEFINE_UNIQUE( GRAPHIC_MESH_MANAGER )

    ~GRAPHIC_MESH_MANAGER();
    
    GRAPHIC_OBJECT * LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad );
    GRAPHIC_OBJECT_ANIMATED * LoadObjectAnimated( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad );

    void GetMesh( int meshIdentifier );

    void Compile( const CORE_FILESYSTEM_PATH & path, const CORE_FILESYSTEM_PATH & destination_path, const int meshIdentifier, int meshTypeToLoad );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_MANAGER__) */
