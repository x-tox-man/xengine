//
//  UI_BASE_BUTTON.cpp
//  Run3d
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_BASE_BUTTON.h"
#include "GRAPHIC_UI_HELPER.h"
#include "GRAPHIC_UI_SYSTEM.h"

UI_BASE_BUTTON::UI_BASE_BUTTON() :
    GRAPHIC_UI_FRAME(),
    Title( L"Test\0" ) {

}

void UI_BASE_BUTTON::Initialize() {
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        texture_identifier( "frameBorder3" );
    
    GRAPHIC_UI_FRAME::Initialize();
    
    GRAPHIC_TEXTURE::LoadResourceForPath( texture_identifier, CORE_FILESYSTEM_PATH::FindFilePath( "frameBorder3", "png", "TEXTURES" ) );
    
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.0f, 0.0f, 0.0f, 0.0f ), "frameBorder3" );
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.6f, 0.6f, 0.6f, 0.5f ), "frameBorder3", 2 );
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.7f, 0.7f, 0.7f, 0.5f ), "frameBorder3", 4 );
    
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetDecoratingMaterial()->GetDiffuse()[0] = 0.7f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetDecoratingMaterial()->GetDiffuse()[1] = 0.7f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetDecoratingMaterial()->GetDiffuse()[2] = 0.7f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetDecoratingMaterial()->GetDiffuse()[3] = 0.7f;
    
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered )->GetDecoratingMaterial()->GetDiffuse()[0] = 0.8f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered )->GetDecoratingMaterial()->GetDiffuse()[1] = 0.8f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered )->GetDecoratingMaterial()->GetDiffuse()[2] = 0.8f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered )->GetDecoratingMaterial()->GetDiffuse()[3] = 0.8f;
    
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed )->GetDecoratingMaterial()->GetDiffuse()[0] = 0.9f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed )->GetDecoratingMaterial()->GetDiffuse()[1] = 0.9f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed )->GetDecoratingMaterial()->GetDiffuse()[2] = 0.9f;
    GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed )->GetDecoratingMaterial()->GetDiffuse()[3] = 0.9f;
    
    auto text = GRAPHIC_UI_HELPER::CreateTextElement( CORE_HELPERS_IDENTIFIER( "Texttest" ), Title.GetString() );
    text->Initialize();
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    AddObject( text );
}
