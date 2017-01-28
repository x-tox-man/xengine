//
//  GRAPHIC_PARTICLE_SYSTEM.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 7/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_SYSTEM_hpp
#define GRAPHIC_PARTICLE_SYSTEM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_PARTICLE_MANAGER.h"
#include "GRAPHIC_CAMERA_BILLBOARD.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_PARTICLE.h"

XS_CLASS_BEGIN( GRAPHIC_PARTICLE_SYSTEM )
    XS_DEFINE_UNIQUE( GRAPHIC_PARTICLE_SYSTEM )

    void Update(float time_step, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat);
    void Render( GRAPHIC_RENDERER & renderer );

    void AddManager( GRAPHIC_PARTICLE_MANAGER & manager );

private:

std::vector<GRAPHIC_PARTICLE_MANAGER *> ManagerTable;

    
XS_CLASS_END

#endif /* GRAPHIC_PARTICLE_SYSTEM_hpp */
