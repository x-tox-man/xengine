//
//  GRAPHIC_TEXTURE_BLOCK.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"
#include "GRAPHIC_TEXTURE_LOADER.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_TEXTURE_BLOCK )
    XS_DEFINE_ClassMember( "Offset", CORE_MATH_VECTOR, Offset )
    XS_DEFINE_ClassMember( "Size", CORE_MATH_VECTOR, Size )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_TEXTURE_BLOCK::GRAPHIC_TEXTURE_BLOCK() :
    Texture( NULL ),
    Offset( CORE_MATH_VECTOR::Zero ),
    Size( CORE_MATH_VECTOR::One ) {
    
}

GRAPHIC_TEXTURE_BLOCK::GRAPHIC_TEXTURE_BLOCK( GRAPHIC_TEXTURE * texture ) :
    Texture( texture ),
    Offset( CORE_MATH_VECTOR::Zero ),
    Size( CORE_MATH_VECTOR::One ){
    
}

GRAPHIC_TEXTURE_BLOCK::GRAPHIC_TEXTURE_BLOCK( const char * texture_name ) :
    Texture(),
    Offset( CORE_MATH_VECTOR::Zero ),
    Size( CORE_MATH_VECTOR::One ){
    
    CORE_HELPERS_UNIQUE_IDENTIFIER id(texture_name );
    Texture = GRAPHIC_TEXTURE::LoadResourceForPath(texture_name, CORE_FILESYSTEM_PATH::FindFilePath(texture_name, ".png", "TEXTURE"));
}

GRAPHIC_TEXTURE_BLOCK::~GRAPHIC_TEXTURE_BLOCK() {

    if ( Texture ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( Texture );
    }
}

void GRAPHIC_TEXTURE_BLOCK::Initialize() {
    
}

void GRAPHIC_TEXTURE_BLOCK::Apply( int texture_index, int shader_texture_attribute_index ) {
    
    Texture->Apply( texture_index, shader_texture_attribute_index );
}

void GRAPHIC_TEXTURE_BLOCK::ApplyDepth( int texture_index, int shader_texture_attribute_index ) {
    
    Texture->ApplyDepth( texture_index, shader_texture_attribute_index );
}


void GRAPHIC_TEXTURE_BLOCK::Discard() {
    
    Texture->Discard();
}
