//
//  POPUP.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 26/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "POPUP.h"
#include "GLOBAL_RESOURCES.h"

POPUP::POPUP() {
    
}

POPUP::~POPUP() {
    
}

void POPUP::Initialize() {
    
    auto renderstyle = new GRAPHIC_UI_RENDER_STYLE;
    
    GRAPHIC_SHADER_EFFECT::PTR
        ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"),
                                                       CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) ),
        ui_colored_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderColored"),
                                                                              CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderColored" , "vsh", "OPENGL2" ) );
    
    auto plan_color = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    ui_colored_shader_effect->Initialize( plan_color->GetShaderBindParameter() );
    plan_color->InitializeShape( &ui_colored_shader_effect->GetProgram() );
    
    renderstyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    renderstyle->SetDecoratingShape( GLOBAL_RESOURCES::CreateFrameBorder( 11.0f / GetSize().X(), 11.0f / GetSize().Y(), ui_textured_shader_effect ) );
    
    ui_textured_shader_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    plan_color->InitializeShape( &ui_colored_shader_effect->GetProgram() );
    
    auto tb = new GRAPHIC_TEXTURE_BLOCK;
    
    tb->SetTexture( GLOBAL_RESOURCES::CreateTextureFromImagePath("frameBorder") );
    tb->Initialize();
    
    renderstyle->SetDecoratingTextureBlock( tb );
    renderstyle->SetShape( plan_color );
    
    SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, renderstyle );
}
