//
//  GRAPHIC_TEXTURE_BLOCK.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_TEXTURE_BLOCK )
    XS_DEFINE_ClassMember( CORE_MATH_VECTOR , Offset )
    XS_DEFINE_ClassMember( CORE_MATH_VECTOR , Size )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_TEXTURE_BLOCK::GRAPHIC_TEXTURE_BLOCK() :
    Offset( CORE_MATH_VECTOR::Zero ),
    Size( CORE_MATH_VECTOR::One ) {
    
}

GRAPHIC_TEXTURE_BLOCK::~GRAPHIC_TEXTURE_BLOCK() {

}

void GRAPHIC_TEXTURE_BLOCK::Initialize() {
    
}

void GRAPHIC_TEXTURE_BLOCK::Apply( int texture_index, int shader_texture_attribute_index ) {
    
    //TODO : less dirty
    if ( Texture->GetDepthTextureHandle() > 0 ) {
        
        Texture->ApplyDepth( texture_index, shader_texture_attribute_index );
    }
    else {
        Texture->Apply( texture_index, shader_texture_attribute_index );
    }
}

void GRAPHIC_TEXTURE_BLOCK::ApplyDepth( int texture_index, int shader_texture_attribute_index ) {
    
    Texture->ApplyDepth( texture_index, shader_texture_attribute_index );
}


void GRAPHIC_TEXTURE_BLOCK::Discard() {
    
    Texture->Discard();
}