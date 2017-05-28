//
//  GRAPHIC_MATERIAL_RESOURCE_LOADER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MATERIAL_RESOURCE_LOADER_hpp
#define GRAPHIC_MATERIAL_RESOURCE_LOADER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"

class GRAPHIC_MATERIAL;

typedef RESOURCE_LOADER< GRAPHIC_MATERIAL > GRAPHIC_MATERIAL_ANCESTOR_LOADER_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_MATERIAL_RESOURCE_LOADER, GRAPHIC_MATERIAL_ANCESTOR_LOADER_TYPE )

    GRAPHIC_MATERIAL_RESOURCE_LOADER();
    virtual ~GRAPHIC_MATERIAL_RESOURCE_LOADER();

    virtual GRAPHIC_MATERIAL * Load( const CORE_FILESYSTEM_PATH & file,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty );


    virtual GRAPHIC_MATERIAL * Load( CORE_DATA_STREAM & stream ,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty);

    virtual void ReloadResource( GRAPHIC_MATERIAL * resource_to_reload );

    #if ASSET_COMPILER
        virtual void CompileResource( const CORE_FILESYSTEM_PATH & source_file, const CORE_FILESYSTEM_PATH & destination_file );
    #endif

private:

    GRAPHIC_MATERIAL * LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad );

XS_CLASS_END

#endif /* GRAPHIC_MATERIAL_RESOURCE_LOADER_hpp */
