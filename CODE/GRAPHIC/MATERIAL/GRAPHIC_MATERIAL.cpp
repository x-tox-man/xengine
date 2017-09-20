//
//  GRAPHIC_MATERIAL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "CORE_DATA_STREAM.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"

typedef std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_TEXTURE_BLOCK * > TEX_TAB_TYPE;

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT(GRAPHIC_TEXTURE_BLOCK *, CORE_HELPERS_IDENTIFIER)

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MATERIAL )
    XS_DEFINE_ClassMember( std::string, Name )
    XS_DEFINE_ClassMember( CORE_HELPERS_COLOR, Diffuse )
    XS_DEFINE_ClassMember( TEX_TAB_TYPE, TextureTable )
    XS_DEFINE_ClassMember( bool, DepthIsEnabled )
    XS_DEFINE_ClassMember( bool, CubeMapIsEnabled )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL() :
    Name(),
    Diffuse( CORE_COLOR_White ),
    TextureTable(),
    DepthIsEnabled( false ),
    CubeMapIsEnabled( false )
{
    
}

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL( const char * image_path ) :
    Name( image_path ),
    Diffuse( CORE_COLOR_White ),
    TextureTable(),
    DepthIsEnabled( false ),
    CubeMapIsEnabled( false ) {
    
#if DEBUG
    assert( strlen( image_path ) < 256 - 11 );
#endif
        
    char image_path_1[256], image_path_2[256], image_normal[256];
    
    sprintf(image_path_1, "%s1", image_path);
        
    TryAndFillFor( image_path, "png", GRAPHIC_SHADER_PROGRAM::ColorTexture );
    TryAndFillFor( image_path_1, "png", GRAPHIC_SHADER_PROGRAM::ColorTexture1 );
    TryAndFillFor( image_path_2, "png", GRAPHIC_SHADER_PROGRAM::ColorTexture2 );
    TryAndFillFor( image_normal, "png", GRAPHIC_SHADER_PROGRAM::NormalTexture );
        
    //TODO : other images
}

GRAPHIC_MATERIAL::~GRAPHIC_MATERIAL() {
    
}

void GRAPHIC_MATERIAL::Apply( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & color_attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::GeometryColor );
    
    if ( renderer.IsColorEnabled() && Diffuse[3] > 0.0f ) {
        GRAPHIC_SYSTEM_ApplyVector( color_attribute.AttributeIndex, 1, (const GLfloat * ) &Diffuse[0] )
    }
    
    ApplyTexture( shader );
    
    if ( renderer.GetDirectionalLight() != NULL ) {
        GRAPHIC_SYSTEM::ApplyLightDirectional( *renderer.GetDirectionalLight(), *shader->GetProgram() ) ;
        
        GRAPHIC_SYSTEM::ApplyLightPoint( *renderer.GetPointLight(0), *shader->GetProgram(), 0 ) ;
        GRAPHIC_SYSTEM::ApplyLightPoint( *renderer.GetPointLight(1), *shader->GetProgram(), 1 ) ;
        
        GRAPHIC_SYSTEM::ApplyLightSpot( *renderer.GetSpotLight(0), *shader->GetProgram(), 0 ) ;
        GRAPHIC_SYSTEM::ApplyLightSpot( *renderer.GetSpotLight(1), *shader->GetProgram(), 1 ) ;
        
        GRAPHIC_SHADER_ATTRIBUTE & camera_world_position_attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::CameraWorldPosition );
        
        if ( camera_world_position_attribute.AttributeIndex != 0 ) {
            
            GRAPHIC_SYSTEM::ApplyShaderAttributeVector( &renderer.GetCamera().GetPosition()[0], camera_world_position_attribute );
        }
        
        GRAPHIC_SHADER_ATTRIBUTE & attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::LightSpecularPower );
        
        if ( attribute.AttributeIndex != 0 ) {
            
            GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( 0.99f, attribute );
            GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( 0.9f, shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MaterialSpecularIntensity ) );
        }
    }
}

void GRAPHIC_MATERIAL::ApplyTexture( GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader ) {
    
    std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_TEXTURE_BLOCK * >::iterator it = TextureTable.begin();
    
    int texture_index = 0;
    
    while (it != TextureTable.end()) {
        
        GRAPHIC_SHADER_ATTRIBUTE & attribute = shader->getShaderAttribute( it->first );
        
        if ( it->first == GRAPHIC_SHADER_PROGRAM::DepthTexture ) {
            it->second->ApplyDepth(texture_index++, attribute.AttributeIndex );
        }
        else {
            
            it->second->Apply(texture_index++, attribute.AttributeIndex );
        }
        
        it++;
    }
}

void GRAPHIC_MATERIAL::Discard( GRAPHIC_RENDERER & renderer ) {
    
}

void GRAPHIC_MATERIAL::TryAndFillFor( const char * file_path, const char * extension, const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath(file_path, extension, "TEXTURES");
    CORE_FILESYSTEM_FILE file( path );
    
    if ( file.OpenOutput() ) {
        
        file.Close();
        
#if DEBUG
        assert( strlen(file_path) + strlen(extension) < 32 );
#endif
        
        char * id = ( char * ) malloc( strlen(file_path) + strlen(extension));
        strcpy(id, file_path );
        id[strlen(file_path)] = 0;
        strcat(id, extension );
        
        GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK( GRAPHIC_TEXTURE::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER(), path ));

        SetTexture( identifier, tb );
    }
}
