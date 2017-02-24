//
//  SPLASH.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "SPLASH.h"
#include "GRAPHIC_UI_HELPER.h"
#include "GLOBAL_RESOURCES.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "MAIN_MENU_PAGE.h"

SPLASH::SPLASH() :
    AccumulatedTime(0.0f){
    
}

SPLASH::~SPLASH() {
    
}

void SPLASH::Initialize() {
    
    auto * base_screen = new GRAPHIC_UI_ELEMENT();
    auto * background_base_screen = new GRAPHIC_UI_ELEMENT();
    auto render_style = new GRAPHIC_UI_RENDER_STYLE;
    auto render_style_background = new GRAPHIC_UI_RENDER_STYLE;
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("UIBaseShader"),
                                                             CORE_FILESYSTEM_PATH::FindFilePath("UIShaderTextured", "vsh", "OPENGL2"));
    auto shader_colored = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("UIBaseShader"),
                                                             CORE_FILESYSTEM_PATH::FindFilePath("UIShaderColored", "vsh", "OPENGL2"));
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = GLOBAL_RESOURCES::CreateUIPlanShape( shader );
    shader->Initialize( shape->GetShaderBindParameter() );
    
    render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    render_style->SetShape( GLOBAL_RESOURCES::CreateUIPlanShape( shader ) );
    render_style->SetTextureBlock( GLOBAL_RESOURCES::CreateTextureBlockFromImagePath( "splash" ) );
    
    render_style_background->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    render_style_background->SetShape( GLOBAL_RESOURCES::CreateUIPlanShape( shader_colored ) );
    
    //Uncomment for debugging  Shadow texture :
    //GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK;
    //tb->SetTexture( ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetShadowMapRenderTarget().TargetTexture );
    //default_render_style->SetTextureBlock( tb );
    
    base_screen->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, render_style );
    base_screen->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, render_style );
    base_screen->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, render_style );
    
    background_base_screen->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, render_style_background );
    background_base_screen->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, render_style_background );
    background_base_screen->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, render_style_background );
    
    base_screen->GetPlacement().Initialize( &GetPlacement(),
                                                  CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
                                                  CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                  GRAPHIC_UI_Center );
    
    background_base_screen->GetPlacement().Initialize( &GetPlacement(),
                                           CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
                                           CORE_MATH_VECTOR( 12800.0f, 12800.0f, 0.0f, 1.0f ),
                                           GRAPHIC_UI_Center );
    
    AddObject( background_base_screen );
    AddObject( base_screen );
}

void SPLASH::Update( const float step ) {
    
    if ( AccumulatedTime < 2.0f ) {
        
        AccumulatedTime += step;
        
        if ( AccumulatedTime >= 2.0f ) {
            
            AccumulatedTime = 2.0f;
            
            APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync< MAIN_MENU_PAGE >( "main_menu" );
        }
        
        SetOpacity( fmin( 2.0f - AccumulatedTime, 1.0f) );
    }
}
