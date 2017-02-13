//
//  GRAPHIC_OBJECT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include <math.h>

#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_OBJECT )
    XS_DEFINE_ClassMember( std::vector< GRAPHIC_MESH * > , MeshTable )
    XS_DEFINE_ClassMember( std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>, JointTable )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_OBJECT::GRAPHIC_OBJECT() :
    MeshTable(),
    ShaderTable(),
    JointTable(),
    Position(),
    ScaleFactor( CORE_MATH_VECTOR::One),
    Orientation()
#if __COMPILE_WITH__COLLADA__
    ,AnimationTable()
#endif
{
    
    JointTable.resize(0);
        
    Position[0] = 0.0f;
    Position[1] = -10.0f;
    Position[2] = 15.0f;
}

GRAPHIC_OBJECT::~GRAPHIC_OBJECT() {
    
    Release();
    
    for( int i = 0; i < MeshTable.size(); i++ ) {

        CORE_MEMORY_ObjectSafeDeallocation( MeshTable[ i ] );
    }

    for ( int i=0; i < JointTable.size(); i++ ) {

        CORE_MEMORY_ObjectSafeDeallocation( JointTable[ i ] );
    }
    
    #if __COMPILE_WITH__COLLADA__
        for ( int i = 0; i < AnimationTable.size(); i++ ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( AnimationTable[ i ] );
        }
    #endif
}

void GRAPHIC_OBJECT::AddNewMesh( GRAPHIC_MESH * mesh ) {
    
    MeshTable.push_back(mesh);
}

void GRAPHIC_OBJECT::SetShaderForMesh( GRAPHIC_MESH * meshToBind, GRAPHIC_SHADER_PROGRAM::PTR shader ) {
    
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader_proxy = new GRAPHIC_SHADER_PROGRAM_DATA_PROXY;
    
    shader_proxy->Initialize( shader );
    
    ShaderTable.push_back( shader_proxy );
}

void GRAPHIC_OBJECT::SetShaderForMesh( GRAPHIC_MESH * meshToBind, GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader ) {
    
    ShaderTable.push_back( shader );
}

void GRAPHIC_OBJECT::BindShader() {
    
}

void GRAPHIC_OBJECT::Render( GRAPHIC_RENDERER & renderer ) {
    
    if( renderer.GetPassIndex() >= ShaderTable.size() )
        return;
    
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader = ShaderTable[ renderer.GetPassIndex() ];

    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            object_matrix,
            scaling_matrix,
            result;

        shader->Enable();
        GRAPHIC_SYSTEM::ApplyLightDirectional( renderer.GetDirectionalLight(), *shader->GetProgram() ) ;
        
        GRAPHIC_SYSTEM::ApplyLightPoint( renderer.GetPointLight(0), *shader->GetProgram(), 0 ) ;
        GRAPHIC_SYSTEM::ApplyLightPoint( renderer.GetPointLight(1), *shader->GetProgram(), 1 ) ;
        
        GRAPHIC_SYSTEM::ApplyLightSpot( renderer.GetSpotLight(0), *shader->GetProgram(), 0 ) ;
        GRAPHIC_SYSTEM::ApplyLightSpot( renderer.GetSpotLight(1), *shader->GetProgram(), 1 ) ;

        GRAPHIC_SHADER_ATTRIBUTE & camera_world_position_attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::CameraWorldPosition );
        
        if ( camera_world_position_attribute.AttributeIndex != 0 ) {
            
            GRAPHIC_SYSTEM::ApplyShaderAttributeVector( &renderer.GetCamera().GetPosition()[0], camera_world_position_attribute );
        }
        
        GRAPHIC_SHADER_ATTRIBUTE & attribute = shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::LightSpecularPower );
        
        if ( attribute.AttributeIndex != 0 ) {
            
            GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( 0.99f, attribute );
            GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( 0.9f, shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MaterialSpecularIntensity ) );
        }
        
        GRAPHIC_SHADER_ATTRIBUTE * attr = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * texture = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture );
        GRAPHIC_SHADER_ATTRIBUTE * normal_texture = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::NormalTexture );
        
        if ( MeshTable[i]->GetTexture() != NULL  ) {
            
            MeshTable[i]->GetTexture()->Apply( 0, texture->AttributeIndex );
        }
        
        if ( MeshTable[i]->GetNormalTexture() != NULL  ) {
            
            MeshTable[i]->GetNormalTexture()->Apply( 1, normal_texture->AttributeIndex );
        }
        
        GLOBAL_IDENTITY_MATRIX(attr->AttributeValue.Value.FloatMatrix4x4);
        
        object_matrix.Translate( Position );
        
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        
        if ( !MeshTable[i]->GetTransform().IsIdentity() ) {
            
            object_matrix *= MeshTable[i]->GetTransform();
        }
        
        result = renderer.GetCamera().GetProjectionMatrix();
        result *= renderer.GetCamera().GetViewMatrix();
        result *= object_matrix;
        
        //---------------
        //MVPmatrix = projection * view * model; // Remember : inverted !
        
        GRAPHIC_SYSTEM_ApplyMatrix(attr->AttributeIndex, 1, 0, &result[0])
        
        MeshTable[ i ]->ApplyBuffers();
        
        shader->Disable();
        
        if ( MeshTable[i]->GetTexture() != NULL  ) {
         
            MeshTable[i]->GetTexture()->Discard();
        }
        
        if ( MeshTable[i]->GetNormalTexture() != NULL  ) {
            
            MeshTable[i]->GetNormalTexture()->Discard();
        }
    }
}

void GRAPHIC_OBJECT::Release() {
    
    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        MeshTable[i]->ReleaseBuffers();
    }
}
