//
//  GAMEPLAY_COMPONENT_SYSTEM.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_SYSTEM )

GAMEPLAY_COMPONENT_SYSTEM();
virtual ~GAMEPLAY_COMPONENT_SYSTEM();

virtual void Initialize() = 0;

virtual void Update( float time_step ) = 0;
virtual void Render() = 0;

virtual void Finalize() = 0;

virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY * entity );
virtual void RemoveEntity( GAMEPLAY_COMPONENT_ENTITY * entity );

std::vector< GAMEPLAY_COMPONENT_ENTITY * > EntitiesVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__) */
