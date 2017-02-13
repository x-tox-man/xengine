//
//  GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_MESH.h"

#include <math.h>

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MEMORY.h"

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( const void * heights, int x_width, int y_width, float lenght ) :
    GRAPHIC_OBJECT_SHAPE(),
    Heights(heights),
    XWidth(x_width),
    YWidth(y_width),
    Length( lenght ) {
    
        ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
        ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP() :
    GRAPHIC_OBJECT_SHAPE() {
    
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::~GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP() {
    
} 

void GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader ) {
    
    float *vertex_data = (float *) CORE_MEMORY_ALLOCATOR_Allocate( 8 * sizeof( float ) * XWidth * YWidth );
    int * index_data = (int *) CORE_MEMORY_ALLOCATOR_Allocate( 6 * sizeof(int)* (XWidth-1) * (YWidth-1));
    
    int height_offset_index = 0;
    
    int offset = 0;
    
    for ( int j = 0; j < YWidth; j++ ) {
        
        for ( int i = 0; i < XWidth; i++ ) {
            
            float height_offset = 0.0f;
            
            switch ( 1 ) {
                case 1:
                    
                    height_offset = *(((uint8_t *) Heights+ height_offset_index) ) ;
                    
                    break;
                    
                /*case 2:
                    
                    //const float height_offset = *Heights + test;
                    break;
                    
                case 4:
                    
                    //const float height_offset = *Heights + test;
                    break;
                    
                default:
                    CORE_RUNTIME_Abort();
                    
                    break;*/
            }
            
            float temp[] = { i * Length,  j * Length, height_offset / 10.0f ,  1.0f,       0.0f, 1.0f, 0.0f, 1.0f, };
            //float temp[] = { i * Length, 0.0f,  j * Length ,  1.0f,       0.0f, 1.0f, 0.0f, 1.0f, };
            
            memcpy( (void*)(vertex_data+offset), temp, 8 * sizeof( float ) );
            
            offset +=8;
            height_offset_index++;
        }
    }
    
    offset=0;
        
    for ( int j = 0; j < YWidth-1; j++ ) {
        
        for ( int i = 0; i < XWidth-1; i++ ) {
            int base = i*XWidth + j;
            int base2 = (i+1)*XWidth +j;
            int ind_temp[] = {base , base +1, base2+1, base2+1, base2, base};
            
            memcpy( (void*)(index_data+ offset), ind_temp, 6 * sizeof( int ) );
            
            offset+=6;
        }
    }
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( 6 * sizeof(int)* (XWidth-1) * (YWidth-1), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 8 * sizeof( float ) * XWidth * YWidth, 0, (void*) vertex_data );
    
    CORE_MEMORY_ALLOCATOR_Free( vertex_data );
    CORE_MEMORY_ALLOCATOR_Free( index_data );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
    
    SetShaderForMesh( mesh, shader );
}

void GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::Render( GRAPHIC_RENDERER & renderer ) {

    CORE_MATH_MATRIX
        object_matrix,
        depthBias;
    
    if ( renderer.GetPassIndex() >= ShaderTable.size() ) {
        
        return;
    }
        
    GetShaderTable()[ 0 ]->Enable();
    
    object_matrix.Translate( Position );
    
    if ( renderer.GetDepthTexture() ) {
        
        GRAPHIC_SHADER_ATTRIBUTE * depth = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture );
        
        if ( depth->AttributeIndex > 0 ) {
            
            GRAPHIC_SHADER_ATTRIBUTE * depthBiasAttr = &GetShaderTable()[0]->getShaderAttribute(GRAPHIC_SHADER_PROGRAM::ShadowMapMVP );
            
            renderer.GetDepthTexture()->ApplyDepth(0, depth->AttributeIndex );
            
            CORE_MATH_MATRIX biasMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                                        0.0f, 0.5f, 0.0f, 0.5f,
                                        0.0f, 0.0f, 0.5f, 0.5f,
                                        0.0f, 0.0f, 0.0f, 1.0f
                                 );
        
            CORE_MATH_MATRIX temp;
            
            depthBias =renderer.GetShadowMapCamera().GetProjectionMatrix();
            depthBias *= renderer.GetShadowMapCamera().GetViewMatrix();
            depthBias *= object_matrix;
            
            
            temp = depthBias;
            
            depthBias = biasMatrix * temp;
            
            GRAPHIC_SYSTEM_ApplyMatrix(
                depthBiasAttr->AttributeIndex,
                1,
                0,
                (const GLfloat * )&depthBias[0]);
        }
    }
        
    GRAPHIC_SHADER_ATTRIBUTE * attr = &GetShaderTable()[0]->getShaderAttribute(GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    
    CORE_MATH_MATRIX result;
    
    object_matrix.SetIdentity();
    object_matrix.Translate( Position );
    
    result = renderer.GetCamera().GetProjectionMatrix();
    result *= renderer.GetCamera().GetViewMatrix();
    result *= object_matrix;
    
    
    //LOCAL_MULTIPLY_MATRIX( attr->AttributeValue.Value.FloatMatrix4x4 , translation );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        attr->AttributeIndex,
        1,
        0,
        (const GLfloat * )&result[0]);    

    GetMeshTable()[ 0 ]->ApplyBuffers();
    GetShaderTable()[ 0 ]->Disable();
}
