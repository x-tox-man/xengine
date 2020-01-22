//
//  GRAPHIC_OBJECT_ANIMATED.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_OBJECT_ANIMATED::GRAPHIC_OBJECT_ANIMATED() :
    GRAPHIC_OBJECT(),
    AnimationController( NULL ) {


}

GRAPHIC_OBJECT_ANIMATED::~GRAPHIC_OBJECT_ANIMATED() {

}

void GRAPHIC_OBJECT_ANIMATED::Render( GRAPHIC_RENDERER & renderer, const GRAPHIC_OBJECT_RENDER_OPTIONS & options, GRAPHIC_SHADER_EFFECT * effect ) {
    
    const int max_size = 4 * 16 *128;
    float float_matrix_array_copy_base[6][3][max_size];
    static int ii = 0;

    for ( size_t i = 0; i < MeshTable.size() ; i++ ) {
        
        CORE_MATH_MATRIX
            result,
            object;
        
        float * float_matrix_array_copy = float_matrix_array_copy_base[i][ii];
        
        effect->Apply( renderer, GetMaterialName(i, effect), renderer.IsLightingEnabled(), options.IsTexturingEnabled() );
        
        GRAPHIC_SHADER_ATTRIBUTE & mvp_matrix = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & model_matrix = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & view_matrix = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::ViewMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & time_mod = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::TimeModulator );
        GRAPHIC_SHADER_ATTRIBUTE & projection_matrix = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::ProjectionMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & attrSkinningMatrixTable = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::SkinningMatrixTable );
        GRAPHIC_SHADER_ATTRIBUTE & attrBindShapeMatrix = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::AttrBindShapeMatrix );

        ComputeModelViewProjection( options, MeshTable[i]->GetTransform(), renderer, result, object );
        
        effect->UpdateMatrix( renderer, mvp_matrix, &result[0] );
        effect->UpdateMatrix( renderer, projection_matrix, &renderer.GetCamera()->GetProjectionMatrix()[0]);
        effect->UpdateMatrix( renderer, model_matrix, &object[0]);
        effect->UpdateMatrix( renderer, view_matrix, &renderer.GetCamera()->GetViewMatrix()[0]);
        effect->UpdateFloat( renderer, time_mod, time_mod.AttributeValue.Value.FloatValue );
        
        {
            //
            float * float_matrix_array = AnimationController->GetCurrentSkinningForAnimation( (int) i );
            
            size_t size = (int) AnimationController->GetAnimation( (int) i)->GetJointTable().size() * 16 * sizeof( float );
            //Hardcoded from shader

            memcpy((void*) float_matrix_array_copy, (void*) float_matrix_array, size );

            float * ptr = (float*) AnimationController->GetAnimation( (int)i )->GetInverseBindMatrixes().getpointerAtIndex(0, 0);

            int offset = 0;

            for ( size_t mi = 0; mi < AnimationController->GetAnimation( (int)i )->GetJointTable().size(); mi++ ) {
                
                GLOBAL_MULTIPLY_MATRIX(float_matrix_array_copy + offset, ptr + offset );
                
                offset += 16;
            }
            
#if OPENGL4
            GRAPHIC_SYSTEM_ApplyMatrix( attrSkinningMatrixTable.AttributeIndex, 64, 0, float_matrix_array_copy )
#else
            //Only for METAL
            attrSkinningMatrixTable.AttributeIndex = 0;
            attrSkinningMatrixTable.AttributeOffset = 9;

            
            renderer.BufferPassIndex = i;
            
            effect->UpdateFloatArray(renderer, attrSkinningMatrixTable, 64*16, float_matrix_array_copy );
#endif
 
            effect->UpdateMatrix(renderer, attrBindShapeMatrix, AnimationController->GetAnimation( (int) i )->GetBindShapeMatrix().Value.FloatMatrix4x4);
        }

        GRAPHIC_SHADER_ATTRIBUTE * depth[3];

        depth[0] = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture );
        depth[1] = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture1 );
        depth[2] = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture2 );
        
        for ( int cascade_index = 0; cascade_index < renderer.GetNumCascade(); cascade_index++ ) {
            
            CORE_MATH_MATRIX
                depthMVP,
                depthBias;

            GRAPHIC_SHADER_ATTRIBUTE & shadowmap_mvp = effect->GetProgram().GetShaderAttribute( renderer.GetShadowMapMVPName( cascade_index ) );
            GRAPHIC_SHADER_ATTRIBUTE & end_clip_space = effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::CascadeEndClipSpace );
            
            //Depth Textures are always last
            renderer.GetDepthTexture( cascade_index )->ApplyDepth(effect->GetMaterial()->GetTextureCount() + cascade_index , depth[cascade_index]->AttributeIndex );
            
            static const CORE_MATH_MATRIX
                biasMatrix(
                    0.5f, 0.0f, 0.0f, 0.5f,
                    0.0f, 0.5f, 0.0f, 0.5f,
                    0.0f, 0.0f, 0.5f, 0.5f,
                    0.0f, 0.0f, 0.0f, 1.0f );
            
            depthMVP = renderer.GetShadowMapCamera( cascade_index ).GetProjectionMatrix() * renderer.GetShadowMapCamera( cascade_index ).GetViewMatrix() * object;
            
            depthBias = biasMatrix * depthMVP;
            
            float cascade_end[8];
            
            for (int ci = 0; ci < renderer.GetNumCascade(); ci++) {
                
                CORE_MATH_VECTOR vvv( 0.0f, 0.0f, renderer.GetCascadeEnd( ci + 1 ), 0.0f ), vres;
                
                vres = renderer.GetCamera()->GetProjectionMatrix() * vvv;
                
                cascade_end[ci] = -vres.Z();//Why is it negative? -> Bullshit in matrix vect mul
            }
            
            effect->UpdateMatrix( renderer, shadowmap_mvp, &depthBias[0] );
            effect->UpdateFloatArray( renderer, end_clip_space, renderer.GetNumCascade(), cascade_end );
        }
        
        MeshTable[ i ]->ApplyBuffers( renderer );
    }
    
    ii = (ii + 1) % 3;
    
    effect->Discard();
    
    
    //
    //
    //
    
    /*effect->Apply( renderer, options.IsTexturingEnabled(), true );
    
    for ( size_t i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            result,
            object;
        
        effect->SelectMaterial( MeshTable[i]->GetName() );
        
        GRAPHIC_SHADER_ATTRIBUTE * mvp_matrix = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * attrModel = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * attrSkinningMatrixTable = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::SkinningMatrixTable );
        GRAPHIC_SHADER_ATTRIBUTE * attrBindShapeMatrix = &effect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::AttrBindShapeMatrix );
        
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        
        ComputeModelViewProjection( options, MeshTable[i]->GetTransform(), renderer, result, object );
        
        GRAPHIC_SYSTEM_ApplyMatrix(mvp_matrix->AttributeIndex, 1, 0, &result[0])
        
        float * float_matrix_array = AnimationController->GetCurrentSkinningForAnimation( i );
        
        int size = (int) AnimationController->GetAnimation(i)->GetJointTable().size() * 16 * sizeof( float );
        //Hardcoded from shader
        int max_size = 4 * 16 *128;
        
        float * float_matrix_array_copy = (float*) CORE_MEMORY_ALLOCATOR_Allocate( max_size );
        
        memcpy(float_matrix_array_copy, float_matrix_array, size);
        //memset(float_matrix_array_copy, 0, size );
        
        float * ptr = (float*) AnimationController->GetAnimation( i )->GetInverseBindMatrixes().getpointerAtIndex(0, 0);
        
        int offset = 0;
        
        for ( size_t mi = 0; mi < AnimationController->GetAnimation( i )->GetJointTable().size(); mi++ ) {
            
            GLOBAL_MULTIPLY_MATRIX(float_matrix_array_copy + offset, ptr + offset );
            
            offset += 16;
        }
        
        GRAPHIC_SYSTEM_ApplyMatrix( attrSkinningMatrixTable->AttributeIndex, 128, 0, float_matrix_array_copy )
        GRAPHIC_SYSTEM_ApplyMatrix(attrBindShapeMatrix->AttributeIndex, 1, 1, AnimationController->GetAnimation( i )->GetBindShapeMatrix().Value.FloatMatrix4x4)
        
        MeshTable[ i ]->ApplyBuffers( renderer );
        
        CORE_MEMORY_ALLOCATOR_Free(float_matrix_array_copy);
        
        effect->Discard();
    }*/
}
