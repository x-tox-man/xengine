//
//  GRAPHIC_TEXTURE_ATLAS.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_FILESYSTEM_FILE.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_TEXTURE_ATLAS )
    XS_DEFINE_ClassMember( "TextureBlockTable", GRAPHIC_TEXTURE_ATLAS_BLOCK_TABLE, TextureBlockTable )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( GRAPHIC_TEXTURE_BLOCK, CORE_HELPERS_UNIQUE_IDENTIFIER )

GRAPHIC_TEXTURE_ATLAS::GRAPHIC_TEXTURE_ATLAS() :
    GRAPHIC_TEXTURE(),
    TextureBlockTable() {
    
}

GRAPHIC_TEXTURE_ATLAS::~GRAPHIC_TEXTURE_ATLAS() {
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER , GRAPHIC_TEXTURE_BLOCK >::iterator it = TextureBlockTable.begin();

    while ( it != TextureBlockTable.end() ) {
        
        it->second.SetTexture( NULL );
        
        it++;
    }
    
    TextureBlockTable.clear();
    
    
    GRAPHIC_TEXTURE::Finalize();
}

void GRAPHIC_TEXTURE_ATLAS::Initialize( const void * texture_data ) {
    
    GRAPHIC_TEXTURE::Initialize( texture_data, true );
}

void GRAPHIC_TEXTURE_ATLAS::Load( const CORE_FILESYSTEM_PATH & atlas_path, const CORE_FILESYSTEM_PATH & image_path ) {
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    
    GRAPHIC_TEXTURE_BLOCK * texture_block = new GRAPHIC_TEXTURE_BLOCK;
    GRAPHIC_TEXTURE * texture = NULL;
    
    RESOURCE_IMAGE * image = (RESOURCE_IMAGE*) loader.Load( image_path );
    
    GRAPHIC_SYSTEM::CreateTexture( this, image->GetImageRawData(), false );
    
    texture = image->CreateTextureObject( false );
    
    if ( texture != NULL ){
        
        CORE_FILESYSTEM_FILE file( atlas_path );
        
        texture_block->SetTexture( texture );
        
        file.OpenOutput();
        int size = file.GetSize();
        CORE_DATA_STREAM stream( size );
        
        stream.Open();
        
        file.OutputBytes( stream.GetMemoryBuffer(), size );
        
        XS_CLASS_SERIALIZER< GRAPHIC_TEXTURE_ATLAS, CORE_DATA_STREAM >::Serialize<std::false_type>( "atlas", *this, stream );
        
        stream.Close();
        stream.ResetOffset();
        
        std::map< CORE_HELPERS_UNIQUE_IDENTIFIER , GRAPHIC_TEXTURE_BLOCK >::iterator it = TextureBlockTable.begin();
        
        while ( it != TextureBlockTable.end() ) {
            
            it->second.SetTexture( texture );
            
            it++;
        }
        
        CORE_MEMORY_ObjectSafeDeallocation( image );
    }
    
    texture_block->SetTexture( NULL );
    CORE_MEMORY_ObjectSafeDeallocation( texture_block );
    
}

void GRAPHIC_TEXTURE_ATLAS::AddTexture( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_MATH_VECTOR & size, const CORE_MATH_VECTOR & offset ) {
    
    TextureBlockTable[ identifier ].SetTexture( new GRAPHIC_TEXTURE );
    TextureBlockTable[ identifier ].GetTexture()->SetTextureHandle( GetTextureHandle() );
    TextureBlockTable[ identifier ].GetTexture()->SetTextureInfo( GetTextureInfo() );
    
    TextureBlockTable[ identifier ].SetOffset( offset );
    TextureBlockTable[ identifier ].SetSize( size );
    
    TextureBlockTable[ identifier ];
}
