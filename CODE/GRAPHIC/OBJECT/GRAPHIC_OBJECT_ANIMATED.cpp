//
//  GRAPHIC_OBJECT_ANIMATED.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "GRAPHIC_MESH.h"

GRAPHIC_OBJECT_ANIMATED::GRAPHIC_OBJECT_ANIMATED() :
    GRAPHIC_OBJECT(),
    AnimationController( NULL ) {


}

GRAPHIC_OBJECT_ANIMATED::~GRAPHIC_OBJECT_ANIMATED() {

}

void GRAPHIC_OBJECT_ANIMATED::Render( GRAPHIC_RENDERER & renderer, const GRAPHIC_OBJECT_RENDER_OPTIONS & options, GRAPHIC_SHADER_EFFECT * effect ) {
    
    effect->Apply( renderer );
    
    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            result;
        
        GRAPHIC_SHADER_ATTRIBUTE * mvp_matrix = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * attrModel = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelViewMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * attrSkinningMatrixTable = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::SkinningMatrixTable );
        GRAPHIC_SHADER_ATTRIBUTE * attrBindShapeMatrix = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::AttrBindShapeMatrix );
        
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        
        CompteModelViewProjection( options, MeshTable[i]->GetTransform(), renderer, result );
        
        GRAPHIC_SYSTEM_ApplyMatrix(mvp_matrix->AttributeIndex, 1, 0, &result[0])
        
        {
            float * float_matrix_array = AnimationController->GetCurrentSkinningForAnimation( i );
            
            int size = (int) AnimationController->GetAnimation(i)->GetJointTable().size() * 16 * sizeof( float );
            //Hardcoded from shader
            int max_size = 4 * 16 *128;
            
            float * float_matrix_array_copy = (float*) CORE_MEMORY_ALLOCATOR_Allocate( max_size );
            
            memcpy(float_matrix_array_copy, float_matrix_array, size);
            
            float * ptr = (float*) AnimationController->GetAnimation( i )->GetInverseBindMatrixes().getpointerAtIndex(0, 0);
            
            int offset = 0;
            
            for (int mi = 0; mi < AnimationController->GetAnimation( i )->GetJointTable().size(); mi++ ) {
                
                GLOBAL_MULTIPLY_MATRIX(float_matrix_array_copy + offset, ptr + offset );
                
                offset += 16;
            }
            
            GRAPHIC_SYSTEM_ApplyMatrix(attrSkinningMatrixTable->AttributeIndex, 128, 0, float_matrix_array_copy)
            GRAPHIC_SYSTEM_ApplyMatrix(attrBindShapeMatrix->AttributeIndex, 1, 0, AnimationController->GetAnimation( i )->GetBindShapeMatrix().Value.FloatMatrix4x4)
            
            CORE_MEMORY_ALLOCATOR_Free(float_matrix_array_copy);
        }
        
        MeshTable[ i ]->ApplyBuffers();
        
        effect->Discard();
    }
}
