//
//  ASSET_SCREEN.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "ASSET_SCREEN.h"
#include "RESOURCE_IMAGE.h"

ASSET_SCREEN::ASSET_SCREEN() {
    
}

ASSET_SCREEN::~ASSET_SCREEN() {
    
}

void ASSET_SCREEN::Initialize() {
    
}

GRAPHIC_TEXTURE * ASSET_SCREEN::CreateTextureFromImagePath( const char * image_path ) {

    auto image = RESOURCE_IMAGE::LoadResourceForPath( image_path, CORE_FILESYSTEM_PATH::FindFilePath( image_path, "png", "IMAGES" ) );

    return image->CreateTextureObject( false );
}

GRAPHIC_OBJECT_SHAPE_PLAN * ASSET_SCREEN::CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect ) {
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = new GRAPHIC_OBJECT_SHAPE_PLAN();
    shape->InitializeShape( &effect->GetProgram() );
    
    return shape;
}
