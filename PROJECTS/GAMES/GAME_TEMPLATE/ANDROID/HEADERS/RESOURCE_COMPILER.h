//
//  RESOURCE_COMPILER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE_COMPILER__
#define __GAME_ENGINE_REBORN__RESOURCE_COMPILER__

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN( RESOURCE_COMPILER )

RESOURCE_COMPILER();

void Compile( const char * file_path );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_COMPILER__) */
