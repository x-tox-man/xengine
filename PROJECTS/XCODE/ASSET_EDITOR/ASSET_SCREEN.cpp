//
//  ASSET_SCREEN.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "ASSET_SCREEN.h"
#include "CORE_APPLICATION.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "CORE_PARALLEL_TASK.h"
#include "CORE_PARALLEL.h"

ASSET_SCREEN::ASSET_SCREEN() :
    Atlas(),
    Font() {
    
}

ASSET_SCREEN::~ASSET_SCREEN() {
    
}

void ASSET_SCREEN::Initialize() {
    
    SetIdentifier( CORE_HELPERS_IDENTIFIER( "BaseScreen" ) );
}

void ASSET_SCREEN::LoadAtlas( const char * atlas_path, const char * image_path) {
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
            CORE_FILESYSTEM_PATH
                image_file_path( image_path ),
                atlas_file_path( atlas_path );
    
            Atlas.Load(atlas_file_path, image_file_path);
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

GRAPHIC_TEXTURE * ASSET_SCREEN::CreateTextureFromImagePath( const char * image_path ) {

    return GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( image_path ), CORE_FILESYSTEM_PATH::FindFilePath( image_path, "png", "TEXTURES" ) );
}

GRAPHIC_OBJECT_SHAPE_PLAN * ASSET_SCREEN::CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect ) {
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = new GRAPHIC_OBJECT_SHAPE_PLAN();
    shape->InitializeShape();
    
    return shape;
}

void ASSET_SCREEN::LoadFont( const char * font_path, const char * font_image_path ) {
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
            Font.Load( font_path, font_image_path );
    
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}
