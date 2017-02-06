//
//  GRAPHIC_OBJECT_ANIMATED.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "GRAPHIC_MESH.h"

GRAPHIC_OBJECT_ANIMATED::GRAPHIC_OBJECT_ANIMATED() {


}

GRAPHIC_OBJECT_ANIMATED::~GRAPHIC_OBJECT_ANIMATED() {

}

void GRAPHIC_OBJECT_ANIMATED::Render( GRAPHIC_RENDERER & renderer ) {
    
    if ( renderer.GetPassIndex() >= ShaderTable.size() ) {
        
        return;
    }
    
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader = ShaderTable[ renderer.GetPassIndex() ];
    
    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            object_matrix, result;
        
        shader->Enable();
        
        // TODO: refactor :
        if ( renderer.GetPassIndex() == 0 ) {
            GRAPHIC_SYSTEM::ApplyLightDirectional( renderer.GetDirectionalLight(), *shader->GetProgram() ) ;
            
            GRAPHIC_SYSTEM::ApplyLightPoint( renderer.GetPointLight(0), *shader->GetProgram(), 0 ) ;
            GRAPHIC_SYSTEM::ApplyLightPoint( renderer.GetPointLight(1), *shader->GetProgram(), 1 ) ;
            
            GRAPHIC_SYSTEM::ApplyLightSpot( renderer.GetSpotLight(0), *shader->GetProgram(), 0 ) ;
            GRAPHIC_SYSTEM::ApplyLightSpot( renderer.GetSpotLight(1), *shader->GetProgram(), 1 ) ;
        }
        
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
        GRAPHIC_SHADER_ATTRIBUTE * attrModel = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelViewMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * attrSkinningMatrixTable = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::SkinningMatrixTable );
        GRAPHIC_SHADER_ATTRIBUTE * attrBindShapeMatrix = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::AttrBindShapeMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * texture = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture );
        GRAPHIC_SHADER_ATTRIBUTE * normal_texture = &shader->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::NormalTexture );
        
        if ( MeshTable[i]->GetTexture() != NULL && renderer.GetPassIndex() == 0 ) {
            
            MeshTable[i]->GetTexture()->Apply( 0, texture->AttributeIndex );
        }
        
        if ( MeshTable[i]->GetNormalTexture() != NULL && renderer.GetPassIndex() == 0 ) {
            
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
        
        GRAPHIC_SYSTEM_ApplyMatrix(attr->AttributeIndex, 1, 0, &result[0])
        GRAPHIC_SYSTEM_ApplyMatrix(attrModel->AttributeIndex, 1, 0, &object_matrix[0])
        
        {
            float * float_matrix_array = AnimationController->GetCurrentSkinningForAnimation( i );
            
            int size = (int) AnimationController->GetAnimation(i)->GetJointTable().size() * 16 * sizeof( float );
            //Hardcoded from shader
            int max_size = 4 * 16 *128;
            
            float * float_matrix_array_copy = (float*) malloc( max_size );
            
            memcpy(float_matrix_array_copy, float_matrix_array, size);
            
            float * ptr = (float*) AnimationController->GetAnimation( i )->GetInverseBindMatrixes().getpointerAtIndex(0, 0);
            
            int offset = 0;
            
            for (int mi = 0; mi < AnimationController->GetAnimation( i )->GetJointTable().size(); mi++ ) {
                
                GLOBAL_MULTIPLY_MATRIX(float_matrix_array_copy + offset, ptr + offset );
                
                offset += 16;
            }
            
            GRAPHIC_SYSTEM_ApplyMatrix(attrSkinningMatrixTable->AttributeIndex, 128, 0, float_matrix_array_copy)
            GRAPHIC_SYSTEM_ApplyMatrix(attrBindShapeMatrix->AttributeIndex, 1, 0, AnimationController->GetAnimation( i )->GetBindShapeMatrix().Value.FloatMatrix4x4)
            
            free(float_matrix_array_copy);
        }
        
        MeshTable[ i ]->ApplyBuffers();
        
        shader->Disable();
        
        if ( MeshTable[i]->GetTexture() != NULL && renderer.GetPassIndex() == 0 ) {
            
            MeshTable[i]->GetTexture()->Discard();
        }
        
        if ( MeshTable[i]->GetNormalTexture() != NULL && renderer.GetPassIndex() == 0 ) {
            
            MeshTable[i]->GetNormalTexture()->Discard();
        }
    }
}
