//
//  RESOURCE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE__
#define __GAME_ENGINE_REBORN__RESOURCE__

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_TYPE.h"
#include "CORE_HELPERS_FACTORY.h"
#include "CORE_HELPER_UNIQUE_IDENTIFIER.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN( RESOURCE )

RESOURCE();

CORE_HELPERS_FACTORY_Define( RESOURCE, RESOURCE_TYPE )

public :

inline const CORE_HELPERS_IDENTIFIER & GetIdentifier() const { return Identifier; }
inline void SetIdentifier( const CORE_HELPERS_IDENTIFIER & identifier ) { Identifier = identifier; }

private :

CORE_HELPERS_IDENTIFIER Identifier;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE__) */
