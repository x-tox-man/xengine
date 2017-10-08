//
//  GRAPHIC_MATERIAL_COLLECTION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/07/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MATERIAL_COLLECTION.h"

typedef std::map<std::string, GRAPHIC_MATERIAL::PTR> MAT_TAB_STRING;

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( GRAPHIC_MATERIAL::PTR, std::string)

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MATERIAL_COLLECTION )
    XS_DEFINE_ClassMember( MAT_TAB_STRING, MaterialTable )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MATERIAL_COLLECTION::GRAPHIC_MATERIAL_COLLECTION() :
    MaterialTable() {
    
}

GRAPHIC_MATERIAL_COLLECTION::~GRAPHIC_MATERIAL_COLLECTION() {
    
}

void GRAPHIC_MATERIAL_COLLECTION::SetMaterialForName( GRAPHIC_MATERIAL::PTR material, const char * name ) {
    
    MaterialTable[ std::string( name ) ] = material;
}

GRAPHIC_MATERIAL::PTR GRAPHIC_MATERIAL_COLLECTION::GetMaterialForName( std::string & name ) {
    
    return MaterialTable[ std::string( name ) ];
}

void GRAPHIC_MATERIAL_COLLECTION::LoadMaterialForName( const char * name ) {
    //Android will not like this
    GRAPHIC_MATERIAL::PTR material = new GRAPHIC_MATERIAL;
    SetMaterialForName( material, name );
    
    char normal_name[256], tesselation_name[256];
    
    strcpy(normal_name, name);
    strcat(normal_name, "-normal");
    strcpy(tesselation_name, name);
    strcat(tesselation_name, "-tesselation");
    
    
    CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath(name, "png", "TEXTURES" );
    
    auto texture = GRAPHIC_TEXTURE::LoadResourceForPath( name, CORE_FILESYSTEM_PATH::FindFilePath( name, "png", "TEXTURES" ) );
    auto texture_normal = GRAPHIC_TEXTURE::LoadResourceForPath( normal_name, CORE_FILESYSTEM_PATH::FindFilePath( normal_name, "png", "TEXTURES" ) );
    auto texture_tesselation = GRAPHIC_TEXTURE::LoadResourceForPath( tesselation_name, CORE_FILESYSTEM_PATH::FindFilePath( tesselation_name, "png", "TEXTURES" ) );
    
    if ( texture ) {
        
        material->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( texture ) );
    }
    
    if ( texture_normal ) {
        
        material->SetTexture(GRAPHIC_SHADER_PROGRAM::NormalTexture, new GRAPHIC_TEXTURE_BLOCK( texture_normal ) );
    }
    
    if ( texture_tesselation ) {
    
        material->SetTexture(GRAPHIC_SHADER_PROGRAM::TesselationTexture, new GRAPHIC_TEXTURE_BLOCK( texture_tesselation ) );
    }
}

void GRAPHIC_MATERIAL_COLLECTION::Apply( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader ) {
    
    MaterialTable.begin()->second->Apply(renderer, shader );
}

void GRAPHIC_MATERIAL_COLLECTION::SetDiffuse( const CORE_HELPERS_COLOR & color ) {
    std::map<std::string, GRAPHIC_MATERIAL::PTR>::iterator it = MaterialTable.begin();
    
    while( it != MaterialTable.end() ) {
        
        it->second->SetDiffuse( color );
        it++;
    }
}

std::string GRAPHIC_MATERIAL_COLLECTION::DefaultMaterialName = std::string( "DefaultMaterial" );