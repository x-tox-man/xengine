//
//  RESOURCE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GLOBAL_RESOURCES.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_FONT_MANAGER.h"

GLOBAL_RESOURCES::GLOBAL_RESOURCES() {
}

GLOBAL_RESOURCES::~GLOBAL_RESOURCES() {
}

void GLOBAL_RESOURCES::Initialize() {
    
    DirectionalLight = new GRAPHIC_SHADER_LIGHT;
    
    CORE_MATH_VECTOR diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    CORE_MATH_VECTOR direction(0.0f, -1.0f, 0.0f, 1.0f);
    
    DirectionalLight->InitializeDirectional( diffuse, direction, 0.5f, 0.5f);
    
    CORE_MATH_VECTOR diffuse_1(0.9f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR diffuse_2(0.0f, 0.0f, 0.9f, 1.0f);
    
    CORE_MATH_VECTOR direction_1(0.0f, 1.0f, 0.0f, 0.0f);
    CORE_MATH_VECTOR direction_2(0.0f, -1.0f, 0.0f, 0.0f);
    
    CORE_MATH_VECTOR point1_position(-10.0f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR point2_position(10.0f, 0.0f, 0.0f, 1.0f);
    
    PointLightOne = new GRAPHIC_SHADER_LIGHT;
    PointLightOne->InitializePoint(diffuse_1, point1_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    PointLightTwo = new GRAPHIC_SHADER_LIGHT;
    PointLightTwo->InitializePoint(diffuse_2, point2_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    SpotLightOne = new GRAPHIC_SHADER_LIGHT;
    SpotLightOne->InitializeSpot(diffuse_1, point1_position, direction_1, 0.1f, 0.2f, 0.4f, 0.001f, 1.0f, 1.0f );
    
    SpotLightTwo = new GRAPHIC_SHADER_LIGHT;
    SpotLightTwo->InitializeSpot(diffuse_2, point2_position, direction_2, 0.1f, 0.2f, 0.9f, 0.1f, 1.0f, 1.0f );
    
    GRAPHIC_FONT_MANAGER::GetInstance().LoadFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ), CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "fxb", "FONTS/" ), CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "png", "FONTS/" ) );
}

GRAPHIC_TEXTURE * GLOBAL_RESOURCES::CreateTextureFromImagePath(const char * image_path) {
    
    auto image = RESOURCE_IMAGE::LoadResourceForPath( image_path, CORE_FILESYSTEM_PATH::FindFilePath( image_path, "png", "TEXTURES" ) );
    
    return image->CreateTextureObject( false );
}

GRAPHIC_TEXTURE_BLOCK * GLOBAL_RESOURCES::CreateTextureBlockFromImagePath(const char * image_path) {
    GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK();
    
    tb->SetTexture(CreateTextureFromImagePath( image_path ) );
    
    return tb;
}

GRAPHIC_OBJECT_SHAPE_PLAN * GLOBAL_RESOURCES::CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect ) {

    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = new GRAPHIC_OBJECT_SHAPE_PLAN();
    shape->InitializeShape( &effect->GetProgram() );
    
    return shape;
}
