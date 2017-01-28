//
//  RESOURCE_IMAGE_PNG_LOADER.h
//  GAME-ENGINE-REBORN
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
#include "RESOURCE_IMAGE.h"
#include "CORE_FILESYSTEM.h"

#include <png.h>

XS_CLASS_BEGIN_WITH_ANCESTOR(RESOURCE_IMAGE_PNG_LOADER, RESOURCE_LOADER)

RESOURCE_IMAGE_PNG_LOADER() : RESOURCE_LOADER() {};

virtual RESOURCE * Load( CORE_FILESYSTEM_FILE & file );
virtual RESOURCE * Load( const void * memory );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_LOADER__) */
