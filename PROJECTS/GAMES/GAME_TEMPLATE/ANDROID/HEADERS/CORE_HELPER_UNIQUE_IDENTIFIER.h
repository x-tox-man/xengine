//
//  CORE_HELPER_UNIQUE_IDENTIFIER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_HELPER_UNIQUE_IDENTIFIER__
#define __GAME_ENGINE_REBORN__CORE_HELPER_UNIQUE_IDENTIFIER__

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN( CORE_HELPER_UNIQUE_IDENTIFIER )

CORE_HELPER_UNIQUE_IDENTIFIER();

char * GetIdentifier() { return Identifier; }

void Generate();

private :

char Identifier[32];

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_HELPER_UNIQUE_IDENTIFIER__) */
