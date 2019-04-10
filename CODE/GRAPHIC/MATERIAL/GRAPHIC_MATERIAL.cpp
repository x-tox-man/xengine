//
//  GRAPHIC_MATERIAL.cpp
//  GAME-ENGINE
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
#include "CORE_DATA_JSON.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_DATA_TYPES.h"

typedef std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_TEXTURE_BLOCK * > TEX_TAB_TYPE;

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT(GRAPHIC_TEXTURE_BLOCK *, CORE_HELPERS_IDENTIFIER)

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MATERIAL )
    XS_DEFINE_ClassMember( "Name", std::string, Name )
    XS_DEFINE_ClassMember( "Diffuse", CORE_HELPERS_COLOR, Diffuse )
    XS_DEFINE_ClassMember( "TextureTable", TEX_TAB_TYPE, TextureTable )
    XS_DEFINE_ClassMember( "DepthIsEnabled", bool, DepthIsEnabled )
    XS_DEFINE_ClassMember( "CubeMapIsEnabled", bool, CubeMapIsEnabled )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL() :
    GR_M_ANCESTOR_TYPE(),
    Name(),
    Diffuse( CORE_COLOR_White ),
    TextureTable(),
    DepthIsEnabled( false ),
    CubeMapIsEnabled( false ),
    Specular( CORE_COLOR_White ),
    Ambient( CORE_COLOR_White ),
    SpecularIntensity( 1.0f ),
    Shininess( 1.0f ) {
    
}

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL( const GRAPHIC_MATERIAL & other ) :
    GR_M_ANCESTOR_TYPE(),
    Name( other.Name ),
    Diffuse( other.Diffuse ),
    TextureTable( other.TextureTable ),
    DepthIsEnabled( other.DepthIsEnabled ),
    CubeMapIsEnabled( other.CubeMapIsEnabled ),
    Specular( other.Specular ),
    Ambient( other.Ambient ),
    SpecularIntensity( other.SpecularIntensity ),
    Shininess( other.Shininess ) {
    
}

GRAPHIC_MATERIAL::GRAPHIC_MATERIAL( const char * image_path ) :
    Name( image_path ),
    Diffuse( CORE_COLOR_White ),
    TextureTable(),
    DepthIsEnabled( false ),
    CubeMapIsEnabled( false ),
    Specular( CORE_COLOR_White ),
    Ambient( CORE_COLOR_White ),
    SpecularIntensity( 1.0f ),
    Shininess( 1.0f ) {
    
#if DEBUG
    assert( strlen( image_path ) < 256 - 11 );
#endif
        
    char image_path_1[256], image_path_2[256], image_normal[256];
    
    sprintf(image_path_1, "%s1", image_path);
    image_path_2[0] = '\0';
    image_normal[0] = '\0';
        
    TryAndFillFor( image_path, "png", GRAPHIC_SHADER_PROGRAM::ColorTexture );
    TryAndFillFor( image_path_1, "png", GRAPHIC_SHADER_PROGRAM::ColorTexture1 );
    TryAndFillFor( image_path_2, "png", GRAPHIC_SHADER_PROGRAM::ColorTexture2 );
    TryAndFillFor( image_normal, "png", GRAPHIC_SHADER_PROGRAM::NormalTexture );
        
    //TODO : other images
}

GRAPHIC_MATERIAL::~GRAPHIC_MATERIAL() {
    
    TextureTable.clear();
}

void GRAPHIC_MATERIAL::Apply( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader, bool does_lighting, bool does_texturing ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & color_attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::GeometryColor );
    
    if ( renderer.IsColorEnabled() && color_attribute.AttributeIndex != 0 ) {
        
        GRAPHIC_SYSTEM_ApplyVector( color_attribute.AttributeIndex, 1,  &Diffuse[0] )
    }
    
    if ( does_texturing ) {
        
        ApplyTexture( shader );
    }
    
    if ( does_lighting ) {
        
        ApplyLights( shader, renderer );
    }
    
    GRAPHIC_SHADER_ATTRIBUTE & camera_world_position_attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::CameraWorldPosition );
    
    if ( camera_world_position_attribute.AttributeIndex != 0 ) {
        
        GRAPHIC_SYSTEM::ApplyShaderAttributeVector( &renderer.GetCamera()->GetPosition()[0], camera_world_position_attribute );
    }
    
    GRAPHIC_SHADER_ATTRIBUTE & attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::LightSpecularPower );
    
    if ( attribute.AttributeIndex != 0 ) {
        
        GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( 0.99f, attribute );
        GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( SpecularIntensity, shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MaterialSpecularIntensity ) );
    }
}

void GRAPHIC_MATERIAL::ApplyTexture( GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader ) {
    
    std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_TEXTURE_BLOCK * >::iterator it = TextureTable.begin();
    
    int texture_index = 0;
    
    while ( it != TextureTable.end() ) {
        
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

void GRAPHIC_MATERIAL::ApplyLights( GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader, GRAPHIC_RENDERER & renderer ) {
    
    if ( renderer.IsDeferredLightingEnabled() ) {
        if ( renderer.GetDeferredSpotIndex() > -1 ) {
            
            GRAPHIC_SYSTEM::ApplyLightSpot( *renderer.GetSpotLight( renderer.GetDeferredSpotIndex() ), *shader->GetProgram(), 0 ) ;
        }
        else if ( renderer.GetDeferredPointIndex() > -1 ) {
            
            GRAPHIC_SYSTEM::ApplyLightPoint( *renderer.GetPointLight( renderer.GetDeferredPointIndex() ), *shader->GetProgram(), 0 ) ;
        }
    }
    else if ( renderer.IsLightingEnabled() ) {
        
        if ( renderer.GetDirectionalLight() != NULL ) {
            GRAPHIC_SYSTEM::ApplyLightDirectional( *renderer.GetDirectionalLight(), *shader->GetProgram() ) ;
        }
        
        if ( renderer.GetAmbientLight() != NULL) {
            
            GRAPHIC_SYSTEM::ApplyLightAmbient( *renderer.GetAmbientLight(), *shader->GetProgram() ) ;
        }
        
        if ( ! renderer.IsDeferredLightingEnabled() ) {
            
            /*if ( renderer.GetPointLight( 0 ) != NULL) {

                GRAPHIC_SYSTEM::ApplyLightPoint( *renderer.GetPointLight(0), *shader->GetProgram(), 0 ) ;
            }

            if ( renderer.GetPointLight( 1 ) != NULL) {

                GRAPHIC_SYSTEM::ApplyLightPoint( *renderer.GetPointLight(1), *shader->GetProgram(), 1 ) ;
            }
            if ( renderer.GetSpotLight( 0 ) != NULL) {

                GRAPHIC_SYSTEM::ApplyLightSpot( *renderer.GetSpotLight(0), *shader->GetProgram(), 0 ) ;
            }
            if ( renderer.GetSpotLight( 1 ) != NULL) {

                GRAPHIC_SYSTEM::ApplyLightSpot( *renderer.GetSpotLight(1), *shader->GetProgram(), 1 ) ;
            }*/
        }
    }
}

void GRAPHIC_MATERIAL::Discard( GRAPHIC_RENDERER & renderer ) {
    
}

void GRAPHIC_MATERIAL::TryAndFillFor( const char * file_path, const char * extension, const CORE_HELPERS_IDENTIFIER & identifier ) {
    if ( strlen( file_path ) == 0 ) {
        
        return;
    }
    
    CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath(file_path, extension, "TEXTURES");
    CORE_FILESYSTEM_FILE file( path );
    
    if ( file.OpenOutput() ) {
        
        file.Close();
        
#if DEBUG
        assert( strlen(file_path) + strlen(extension) < 32 );
#endif
        
        char id[128];
        CORE_DATA_COPY_STRING( id, file_path );
        id[ strlen( file_path ) ] = 0;
        CORE_DATA_STRING_CONCAT( id, extension );
        
        GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK( GRAPHIC_TEXTURE::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( id ), path ));

        SetTexture( identifier, tb );
    }
}
