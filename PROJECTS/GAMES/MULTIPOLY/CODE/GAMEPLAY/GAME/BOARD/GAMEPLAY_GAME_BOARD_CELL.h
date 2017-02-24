//
//  GAMEPLAY_GAME_BOARD_CELL.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_GAME_BOARD_CELL_hpp
#define GAMEPLAY_GAME_BOARD_CELL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_MATH_QUATERNION.h"
#include "GAMEPLAY_PLAYER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_GAME_BOARD_CELL, GAMEPLAY_COMPONENT_ENTITY)

    GAMEPLAY_GAME_BOARD_CELL();
    ~GAMEPLAY_GAME_BOARD_CELL();

    void Initialize(
                    const CORE_MATH_VECTOR & position,
                    const CORE_MATH_VECTOR & size,
                    const CORE_MATH_QUATERNION & orientation,
                    GAMEPLAY_SCENE * scene,
                    GRAPHIC_TEXTURE_BLOCK * block,
                    bool is_corner );

private:

    GAMEPLAY_COMPONENT_ENTITY * CreateThisComponent(
        //const CORE_FILESYSTEM_PATH & path,
        GRAPHIC_OBJECT_SHAPE_PLAN::PTR object,
        GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
        const CORE_MATH_VECTOR & position,
        const CORE_MATH_QUATERNION & orientation,
        const CORE_MATH_VECTOR & size,
        GAMEPLAY_SCENE * scene );

    std::vector< GAMEPLAY_PLAYER * >
        ThisCellPlayerTable;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_BOARD_CELL_hpp */
