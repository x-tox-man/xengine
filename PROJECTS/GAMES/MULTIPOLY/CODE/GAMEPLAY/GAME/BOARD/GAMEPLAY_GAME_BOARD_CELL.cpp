//
//  GAMEPLAY_GAME_BOARD_CELL.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GLOBAL_RESOURCES.h"

GAMEPLAY_GAME_BOARD_CELL::GAMEPLAY_GAME_BOARD_CELL() :
    GAMEPLAY_COMPONENT_ENTITY(),
    ThisCellPlayerTable(),
    Rule( NULL ) {
    
}

GAMEPLAY_GAME_BOARD_CELL::~GAMEPLAY_GAME_BOARD_CELL() {
    
}

void GAMEPLAY_GAME_BOARD_CELL::Initialize(
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_VECTOR & size,
    const CORE_MATH_QUATERNION & orientation,
    GAMEPLAY_SCENE * scene,
    GRAPHIC_TEXTURE_BLOCK * block,
    bool is_corner) {
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("CellShader"), CORE_FILESYSTEM_PATH::FindFilePath("UIShaderTextured", "vsh", "OPENGL2"));
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = GLOBAL_RESOURCES::CreateUIPlanShape( shader );
    shader->Initialize( shape->GetShaderBindParameter() );
    shape->SetTextureBlock( block );
    
    GLOBAL_RESOURCES::CreateThisComponent(
        this,
        shape,
        &shader->GetProgram(),
        position,
        orientation,
        size,
        scene);
}
