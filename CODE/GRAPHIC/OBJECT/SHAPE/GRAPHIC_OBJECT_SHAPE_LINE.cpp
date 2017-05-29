//
//  GRAPHIC_OBJECT_SHAPE_LINE.cpp
//  GAME-ENGINE-REBORN
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
        
        Vertices[8] = 0.0f;
        Vertices[9] = 0.0f;
        Vertices[10] = 1.0f;
        Vertices[11] = 1.0f;
        
        Vertices[12] = 1.0f;
        Vertices[13] = 1.0f;
        Vertices[14] = 1.0f;
        Vertices[15] = 1.0f;
}

GRAPHIC_OBJECT_SHAPE_LINE::~GRAPHIC_OBJECT_SHAPE_LINE() {

    CORE_MEMORY_ObjectSafeDeallocation( ShaderPositions );
}

void GRAPHIC_OBJECT_SHAPE_LINE::InitializeShape() {
    
    static unsigned int index_data[] = { 0, 1 };
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( 2 * sizeof(unsigned int), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 2 * 8 * sizeof(float), 0, (void*) Vertices );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    mesh->CreateBuffers();
    mesh->SetPolygonRenderMode( GRAPHIC_MESH_POLYGON_RENDER_MODE_Line );
    
    AddNewMesh( mesh );
}

CORE_HELPERS_IDENTIFIER GRAPHIC_OBJECT_SHAPE_LINE::ShaderLineGeometry( "geometryPosition" );
