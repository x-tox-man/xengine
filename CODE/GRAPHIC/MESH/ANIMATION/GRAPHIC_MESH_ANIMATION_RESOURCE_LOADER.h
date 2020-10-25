//
//  GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/07/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER_hpp
#define GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"

class GRAPHIC_MESH_ANIMATION;

typedef RESOURCE_LOADER< GRAPHIC_MESH_ANIMATION > GRAPHIC_MESH_ANIMATION_ANCESTOR_LOADER_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER, GRAPHIC_MESH_ANIMATION_ANCESTOR_LOADER_TYPE )

    GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER();
    virtual ~GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER();

    virtual GRAPHIC_MESH_ANIMATION * Load( const CORE_FILESYSTEM_PATH & file, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty );


    virtual GRAPHIC_MESH_ANIMATION * Load( CORE_DATA_STREAM & stream, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty);

    virtual void ReloadResource( GRAPHIC_MESH_ANIMATION * resource_to_reload );

    #if ASSET_COMPILER
        virtual void CompileResource( const CORE_FILESYSTEM_PATH & source_file, const CORE_FILESYSTEM_PATH & destination_file );
    #endif

private:

    GRAPHIC_MESH_ANIMATION * LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad );

XS_CLASS_END

#endif /* GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER_hpp */