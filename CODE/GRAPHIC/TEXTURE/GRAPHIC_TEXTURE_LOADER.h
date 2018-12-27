//
//  GRAPHIC_TEXTURE_LOADER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_TEXTURE_LOADER_hpp
#define GRAPHIC_TEXTURE_LOADER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"

class GRAPHIC_TEXTURE;

typedef RESOURCE_LOADER< GRAPHIC_TEXTURE > GRAPHIC_TEXTURE_ANCESTOR_LOADER_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_TEXTURE_LOADER, GRAPHIC_TEXTURE_ANCESTOR_LOADER_TYPE )

    GRAPHIC_TEXTURE_LOADER();
    virtual ~GRAPHIC_TEXTURE_LOADER();

    virtual GRAPHIC_TEXTURE * Load( const CORE_FILESYSTEM_PATH & file, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty );


    virtual GRAPHIC_TEXTURE * Load( CORE_DATA_STREAM & stream, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty);

    virtual void ReloadResource( GRAPHIC_TEXTURE * resource_to_reload );

    #if ASSET_COMPILER
        virtual void CompileResource( const CORE_FILESYSTEM_PATH & source_file, const CORE_FILESYSTEM_PATH & destination_file );
    #endif

XS_CLASS_END

#endif /* GRAPHIC_TEXTURE_LOADER_hpp */
