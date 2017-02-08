//
//  GRAPHIC_FONT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_FONT.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_STREAM.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "GRAPHIC_GLYPH.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_FONT )
    XS_DEFINE_ClassMember( GLYPH_TABLE, GlyphTable )
    XS_DEFINE_ClassMemberArray( char , (char **) &Name, (int) strlen(Name) )
    XS_DEFINE_ClassMember( int, Size )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_FONT::GRAPHIC_FONT() :
    Name( NULL ),
    Size( 0 ),
    GlyphTable(),
    Texture() {
    
    Name = (char*) malloc((int) strlen("NONAME\0") );
    strcpy(Name, "NONAME\0");
}

GRAPHIC_FONT::~GRAPHIC_FONT() {
    
    if ( Name ) {
        
        free(Name);
        Name = NULL;
    }
    
    if ( Texture ) {
        
        delete Texture;
        Texture = NULL;
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
    
    XS_CLASS_SERIALIZER< GRAPHIC_FONT >::Serialize<std::false_type>( *this, stream );
    
    stream.Close();
    stream.ResetOffset();
    
    Texture = ((RESOURCE_IMAGE*) loader.Load( image_path ))->CreateTextureObject( true );
}
