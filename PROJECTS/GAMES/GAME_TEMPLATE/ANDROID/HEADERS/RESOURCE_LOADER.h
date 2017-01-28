//
//  RESOURCE_LOADER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE_LOADER__
#define __GAME_ENGINE_REBORN__RESOURCE_LOADER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "RESOURCE.h"

XS_CLASS_BEGIN(RESOURCE_LOADER)

RESOURCE_LOADER() {};

virtual RESOURCE * Load( const char * path );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_LOADER__) */
