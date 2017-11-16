//
//  GRAPHIC_PARTICLE_MANAGER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_MANAGER_hpp
#define GRAPHIC_PARTICLE_MANAGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_EMITER.h"

XS_CLASS_BEGIN( GRAPHIC_PARTICLE_MANAGER )

GRAPHIC_PARTICLE_MANAGER();
~GRAPHIC_PARTICLE_MANAGER();

void Update(float time_step);
void Render( GRAPHIC_RENDERER & renderer );

void AddEmiter( GRAPHIC_PARTICLE_EMITER_BASE_CLASS & emiter );

private :

std::vector<GRAPHIC_PARTICLE_EMITER_BASE_CLASS *> EmitersTable;

XS_CLASS_END

#endif /* GRAPHIC_PARTICLE_MANAGER_hpp */
