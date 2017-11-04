//
//  R3D_UI_FRAME.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 2/11/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_UI_FRAME.h"
#include "GRAPHIC_UI_HELPER.h"

R3D_UI_FRAME::R3D_UI_FRAME() :
    GRAPHIC_UI_FRAME() {
    
}

R3D_UI_FRAME::~R3D_UI_FRAME() {
    
}

void R3D_UI_FRAME::Initialize() {
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        texture_identifier( "frameBorder3" );
    
    GRAPHIC_TEXTURE::LoadResourceForPath( texture_identifier, CORE_FILESYSTEM_PATH::FindFilePath( "frameBorder3", "png", "TEXTURES" ) );
                                              
    GetPlacement().SetSize( CORE_MATH_VECTOR( 512.0f, 256.0f ) );
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f), "frameBorder3" );
    GRAPHIC_UI_FRAME::Initialize();
}
