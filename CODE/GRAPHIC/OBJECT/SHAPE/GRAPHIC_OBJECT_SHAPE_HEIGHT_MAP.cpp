//
//  GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.cpp
//  GAME-ENGINE
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
    HeightScale( 1.0f ),
    Length( lenght ) {
    
        ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
        ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
        ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Texcoord0 );
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP() :
    GRAPHIC_OBJECT_SHAPE() {
    
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::~GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP() {
    
} 

void GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::InitializeShape() {
    
    float *vertex_data = (float *) CORE_MEMORY_ALLOCATOR_Allocate( 10 * sizeof( float ) * XWidth * YWidth );
    int * index_data = (int *) CORE_MEMORY_ALLOCATOR_Allocate( 6 * sizeof(int)* (XWidth) * (YWidth));
    
    int height_offset_index = 0;
    
    int offset = 0;
    
    for ( int j = 0; j < YWidth; j++ ) {
        
        for ( int i = 0; i < XWidth; i++ ) {
            
            float height_offset = 0.0f;
            
            switch ( 1 ) {
                case 1:
                    
                    height_offset = *(((uint8_t *) Heights+ height_offset_index) ) ;
                    //printf("%d\t", height_offset );
                    
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
            
            float temp[] = { i * Length,  j * Length, height_offset * HeightScale,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, (float)(i / (float)(XWidth - 1)), (float)(j / (float)(YWidth - 1)) };
            //float temp[] = { i * Length, 0.0f,  j * Length ,  1.0f,       0.0f, 1.0f, 0.0f, 1.0f, };
            
            memcpy( (void*)(vertex_data+offset), temp, 10 * sizeof( float ) );
            
            offset +=10;
            height_offset_index++;
        }
    }
    
    //printf("\n\n\n");
    
    offset=0;
        
    for ( int j = 0; j < YWidth; j++ ) {
        
        for ( int i = 0; i < XWidth; i++ ) {
            int base = i*XWidth + j;
            int base2 = (i+1)*XWidth +j;
            int ind_temp[] = {base , base +1, base2+1, base2+1, base2, base};
            
            memcpy( (void*)(index_data+ offset), ind_temp, 6 * sizeof( int ) );
            
            offset+=6;
        }
    }
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Position );
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Normal );
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Texcoord0 );
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( 6 * sizeof(int)* (XWidth) * (YWidth), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 10 * sizeof( float ) * XWidth * YWidth, 0, (void*) vertex_data );
    
    CORE_MEMORY_ALLOCATOR_Free( vertex_data );
    CORE_MEMORY_ALLOCATOR_Free( index_data );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    mesh->GetBoundingShape().SetType( CORE_MATH_SHAPE_TYPE_Sphere );
    mesh->GetBoundingShape().SetHalfDiagonal( CORE_MATH_VECTOR( XWidth * Length, YWidth * Length, Length, 0.0f));
    
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
}
