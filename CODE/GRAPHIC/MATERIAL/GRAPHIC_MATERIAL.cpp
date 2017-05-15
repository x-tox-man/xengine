//
//  GRAPHIC_MATERIAL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_DATA_STREAM.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE.h"

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL() {
    
}

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL(const char * image_path, const char * effect_name, const GRAPHIC_SHADER_BIND bind ) {
    
    Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::EffectNameToChange"), CORE_FILESYSTEM_PATH::FindFilePath( effect_name , "vsh", "OPENGL2" ) );
    
    Effect->Initialize(bind);
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    
    Texture = new GRAPHIC_TEXTURE_BLOCK();
    
    auto img = loader.Load(CORE_FILESYSTEM_PATH::FindFilePath( image_path , "png", "IMAGES" ));
    
    Texture->SetTexture( img->CreateTextureObject( false ) );
    
    delete img;
}

GRAPHIC_MATERIAL::~GRAPHIC_MATERIAL() {
    
}

void GRAPHIC_MATERIAL::Apply( GRAPHIC_RENDERER & renderer ) {
    Effect->Apply();
    int texture_index = Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture ).AttributeIndex;

    Texture->Apply(0, texture_index);
}

void GRAPHIC_MATERIAL::Discard( GRAPHIC_RENDERER & renderer ) {
    
}
