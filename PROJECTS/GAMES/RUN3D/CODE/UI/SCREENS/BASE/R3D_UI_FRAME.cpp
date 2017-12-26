//
//  R3D_UI_FRAME.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 2/11/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_UI_FRAME.h"
#include "GRAPHIC_UI_HELPER.h"
#include "GRAPHIC_UI_SYSTEM.h"

R3D_UI_FRAME::R3D_UI_FRAME() :
    GRAPHIC_UI_FRAME(),
    Presenter( NULL ),
    Borderless( false ) {
    
}

R3D_UI_FRAME::~R3D_UI_FRAME() {
    
}

void R3D_UI_FRAME::Initialize() {
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        texture_identifier( "frameBorder3" );
    
#if DEBUG
    if ( Presenter == NULL ) {
        
        abort();
    }
#endif
    
    GRAPHIC_TEXTURE::LoadResourceForPath( texture_identifier, CORE_FILESYSTEM_PATH::FindFilePath( "frameBorder3", "png", "TEXTURES" ) );
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() * 0.9f );
    
    if ( !Borderless ) {
        GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frameBorder3" );
    }
    
    GRAPHIC_UI_FRAME::Initialize();
}

