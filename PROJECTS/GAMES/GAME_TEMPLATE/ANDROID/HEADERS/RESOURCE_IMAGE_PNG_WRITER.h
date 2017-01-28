//
//  RESOURCE_IMAGE_PNG_WRITER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 14/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_WRITER__
#define __GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_WRITER__

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "RESOURCE_IMAGE.h"

#include <png.h>

XS_CLASS_BEGIN( RESOURCE_IMAGE_PNG_WRITER )

RESOURCE_IMAGE_PNG_WRITER() {};

bool Write( const char * path, RESOURCE_IMAGE * image );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_IMAGE_PNG_WRITER__) */
