//
//  TERRAIN.hpp
//  Run3d
//
//  Created by Christophe Bernard on 12/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef TERRAIN_hpp
#define TERRAIN_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_MATH_MATRIX.h"
#include "GAMEPLAY_HELPER.h"

XS_CLASS_BEGIN( R3D_RENDERTERRAIN )

    R3D_RENDERTERRAIN() {
        
    }

    static GAMEPLAY_COMPONENT_ENTITY::PTR Create();

XS_CLASS_END

#endif /* TERRAIN_hpp */
