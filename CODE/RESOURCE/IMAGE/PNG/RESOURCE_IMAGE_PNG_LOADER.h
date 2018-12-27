//
//  RESOURCE_IMAGE_PNG_LOADER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_LOADER__
#define __GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_LOADER__

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_FILESYSTEM.h"

#include <png.h>

class RESOURCE_IMAGE;

typedef RESOURCE_LOADER< RESOURCE_IMAGE > RESOURCE_LOADER_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR(RESOURCE_IMAGE_PNG_LOADER, RESOURCE_LOADER_TYPE )

    RESOURCE_IMAGE_PNG_LOADER();
    virtual ~RESOURCE_IMAGE_PNG_LOADER();

    virtual RESOURCE_IMAGE * Load( const CORE_FILESYSTEM_PATH & file, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty );

    virtual RESOURCE_IMAGE * Load( CORE_DATA_STREAM & stream, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty);

    virtual void ReloadResource( RESOURCE_IMAGE * resource_to_reload );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_LOADER__) */
