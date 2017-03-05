//
//  GRAPHIC_BACKGROUND.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 27/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GRAPHIC_BACKGROUND.h"
#include "GLOBAL_RESOURCES.h"

GRAPHIC_BACKGROUND::GRAPHIC_BACKGROUND() :
    GAMEPLAY_COMPONENT_ENTITY() {
    
}

GRAPHIC_BACKGROUND::~GRAPHIC_BACKGROUND() {
    
}

void GRAPHIC_BACKGROUND::Initialize( GAMEPLAY_SCENE * scene ) {
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("BackgroundShader"), CORE_FILESYSTEM_PATH::FindFilePath("UIShaderTextured", "vsh", "OPENGL2"));
    auto texture = GLOBAL_RESOURCES::CreateTextureBlockFromImagePath( "background_image" );
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = GLOBAL_RESOURCES::CreateUIPlanShape( shader );
    shader->Initialize( shape->GetShaderBindParameter() );
    shape->SetTextureBlock( texture );
    
    GLOBAL_RESOURCES::CreatePlanComponent(
        this,
        shape,
        &shader->GetProgram(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 1.0f ),
        CORE_MATH_QUATERNION(),
        CORE_MATH_VECTOR(1024.0f, 1024.0f),
        scene,
        CORE_HELPERS_CALLBACK_1<GAMEPLAY_COMPONENT_ENTITY *>() );
}
