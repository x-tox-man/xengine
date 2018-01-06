//
//  R3D_GAUGE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 5/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_GAUGE.h"
#include "GRAPHIC_UI_HELPER.h"
#include "GRAPHIC_UI_SYSTEM.h"

R3D_GAUGE::R3D_GAUGE() :
    GRAPHIC_UI_FRAME(),
    Percent( 1.0f ) {
    
}

void R3D_GAUGE::Initialize() {
    
    GetPlacement().SetSize( CORE_MATH_VECTOR( 256.0f, 1.0f) );
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        texture_identifier( "frame_gauge" );
    
    GRAPHIC_TEXTURE::LoadResourceForPath( texture_identifier, CORE_FILESYSTEM_PATH::FindFilePath( "frame_gauge", "png", "TEXTURES" ) );
    
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frame_gauge" );
    
    auto element = GRAPHIC_UI_HELPER::CreateElement( "BackButton" );
    element->GetPlacement().SetAnchor( GRAPHIC_UI_Left );
    element->GetPlacement().SetSize( CORE_MATH_VECTOR( 256.0f * Percent, 4.0f ) );
    GRAPHIC_UI_HELPER::CreateElementStyleWithContentColor(element, CORE_COLOR_Cyan );
    element->Initialize();
    
    AddObject( element );
    
    GRAPHIC_UI_FRAME::Initialize();
}
