//
//  GRAPHIC_OBJECT_SHAPE_CUBE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include <math.h>

#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"

#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SYSTEM.h"

#define unit_s 1.0f

GRAPHIC_OBJECT_SHAPE_CUBE::GRAPHIC_OBJECT_SHAPE_CUBE() :
    GRAPHIC_OBJECT_SHAPE() {
    
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
}

GRAPHIC_OBJECT_SHAPE_CUBE::~GRAPHIC_OBJECT_SHAPE_CUBE() {

}

void GRAPHIC_OBJECT_SHAPE_CUBE::InitializeShape() {
    
    static unsigned int index_data[] = {
        0, 3, 2, 2, 1, 0,
        6, 7, 4, 4, 5, 6,
        6, 5, 1, 1, 2, 6,
        7, 3, 0, 0, 4, 7,
        0, 1, 5, 5, 4, 0,
        7, 6, 2, 2, 3, 7
    };
    
    static float vertex_data[] = {
        -unit_s,  unit_s,  unit_s,  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
         unit_s,  unit_s,  unit_s,  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
         unit_s, -unit_s,  unit_s,  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        -unit_s, -unit_s,  unit_s,  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        
        -unit_s,  unit_s,  -unit_s, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
         unit_s,  unit_s,  -unit_s, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
         unit_s, -unit_s,  -unit_s, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        -unit_s, -unit_s,  -unit_s, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    };
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( 36 * sizeof(unsigned int), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 8 * 8 * sizeof(float), 0, (void*) vertex_data );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
}

void GRAPHIC_OBJECT_SHAPE_CUBE::UpdateGeometry( const CORE_MATH_VECTOR & center, const CORE_MATH_VECTOR & extent ) {
    
    float vertex_data[] = {
        
        - extent.X(),   extent.Y(),    extent.Z(),  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
          extent.X(),   extent.Y(),    extent.Z(),  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
          extent.X(), - extent.Y(),    extent.Z(),  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        - extent.X(), - extent.Y(),    extent.Z(),  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        
        - extent.X(),   extent.Y(),  - extent.Z(), 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
          extent.X(),   extent.Y(),  - extent.Z(), 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
          extent.X(), - extent.Y(),  - extent.Z(), 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        - extent.X(), - extent.Y(),  - extent.Z(), 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    };
    
    GetMeshTable()[ 0 ]->GetVertexCoreBuffer()->InitializeWithMemory( 8 * 8 * sizeof(float), 0, (void*) vertex_data );
    GRAPHIC_SYSTEM::UpdateVertexBuffer( GetMeshTable()[ 0 ], *GetMeshTable()[ 0 ]->GetVertexCoreBuffer() );
}
