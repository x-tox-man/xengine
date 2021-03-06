//
//  GRAPHIC_FONT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_FONT.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "GRAPHIC_GLYPH.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_FONT )
    XS_DEFINE_ClassMember( "GlyphTable", GLYPH_TABLE, GlyphTable )
    XS_DEFINE_ClassMemberArray( "Name", char , Name, (size_t)256 )
    XS_DEFINE_ClassMember( "Size", int, Size )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_FONT::GRAPHIC_FONT() :
    Name(),
    Size( 0 ),
    GlyphTable(),
    Texture() {
    
    CORE_DATA_COPY_STRING( Name, "HELLO" );
}

GRAPHIC_FONT::~GRAPHIC_FONT() {
    
    if ( Texture ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( Texture );
    }
}

void GRAPHIC_FONT::Initialize() {
    
}

void GRAPHIC_FONT::Load( const CORE_FILESYSTEM_PATH & font_path, const CORE_FILESYSTEM_PATH & image_path ) {
    
    CORE_FILESYSTEM_FILE file( font_path );
    RESOURCE_IMAGE_PNG_LOADER loader;
    
    
    file.OpenOutput();
    int size = file.GetSize();
    CORE_DATA_STREAM stream( size );
    
    stream.Open();
    
    file.OutputBytes( stream.GetMemoryBuffer(), size );
    
    XS_CLASS_SERIALIZER< GRAPHIC_FONT, CORE_DATA_STREAM >::Serialize<std::false_type>( "font", *this, stream );
    
    stream.Close();
    stream.ResetOffset();
    
    auto img  = (RESOURCE_IMAGE*) loader.Load( image_path );
    
    Texture = img->CreateTextureObject( true );
    
    CORE_MEMORY_ObjectSafeDeallocation( img );
}
