//
//  R3D_MENU_BACKGROUND.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 24/03/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef R3D_MENU_BACKGROUND_hpp
#define R3D_MENU_BACKGROUND_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_MATH_MATRIX.h"
#include "GAMEPLAY_HELPER.h"

XS_CLASS_BEGIN( R3D_MENU_BACKGROUND )

R3D_MENU_BACKGROUND() {
    
}

static GAMEPLAY_COMPONENT_ENTITY::PTR Create( const CORE_MATH_VECTOR & size );

XS_CLASS_END

#endif /* R3D_MENU_BACKGROUND_hpp */
