//
//  GRAPHIC_OBJECT_SHAPE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_SHAPE.h"
#include "CORE_MEMORY.h"

GRAPHIC_OBJECT_SHAPE::GRAPHIC_OBJECT_SHAPE() :
    GRAPHIC_OBJECT(),
    TextureBlock( NULL ),
    SecondTextureBlock( NULL ),
    ThirdTextureBlock( NULL ),
    Effect( NULL ) {
    
}

GRAPHIC_OBJECT_SHAPE::~GRAPHIC_OBJECT_SHAPE() {
    
    //Deletion of textures and shaders must not be done here because it does not make sense
}

void GRAPHIC_OBJECT_SHAPE::InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader) {
    
}

void GRAPHIC_OBJECT_SHAPE::Render( GRAPHIC_RENDERER & renderer ) {
    
}

