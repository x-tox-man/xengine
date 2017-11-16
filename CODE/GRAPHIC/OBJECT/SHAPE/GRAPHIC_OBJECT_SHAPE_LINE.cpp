//
//  GRAPHIC_OBJECT_SHAPE_LINE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_SHAPE_LINE.h"

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"

GRAPHIC_OBJECT_SHAPE_LINE::GRAPHIC_OBJECT_SHAPE_LINE():
    GRAPHIC_OBJECT_SHAPE(),
    Vertices(),
    ShaderPositions( new GRAPHIC_SHADER_ATTRIBUTE() ){
    
        Vertices[0] = 10.0f;
        Vertices[1] = 0.0f;
        Vertices[2] = 0.0f;
        Vertices[3] = 1.0f;
        
        Vertices[4] = 0.0f;
        Vertices[5] = 0.0f;
        Vertices[6] = 0.0f;
        Vertices[7] = 1.0f;
}

GRAPHIC_OBJECT_SHAPE_LINE::~GRAPHIC_OBJECT_SHAPE_LINE() {

    CORE_MEMORY_ObjectSafeDeallocation( ShaderPositions );
}

void GRAPHIC_OBJECT_SHAPE_LINE::InitializeShape() {
    
    static unsigned int index_data[] = { 0, 1 };
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( 2 * sizeof(unsigned int), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 2 * 4 * sizeof(float), 0, (void*) Vertices );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    mesh->CreateBuffers();
    mesh->SetPolygonRenderMode( GRAPHIC_MESH_POLYGON_RENDER_MODE_Line );
    
    AddNewMesh( mesh );
}

void GRAPHIC_OBJECT_SHAPE_LINE::UpdateShape() {
    
    memcpy( (void*)GetMeshTable()[0]->GetVertexCoreBuffer()->getpointerAtIndex( 0 ), (void*)Vertices, 8* sizeof(float) );
    
    GRAPHIC_SYSTEM::UpdateVertexBuffer(GetMeshTable()[0], *GetMeshTable()[0]->GetVertexCoreBuffer());
}

CORE_HELPERS_IDENTIFIER GRAPHIC_OBJECT_SHAPE_LINE::ShaderLineGeometry( "geometryPosition" );
