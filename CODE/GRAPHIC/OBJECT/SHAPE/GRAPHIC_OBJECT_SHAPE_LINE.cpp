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

}

void GRAPHIC_OBJECT_SHAPE_LINE::InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader ) {
    
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
    
    SetShaderForMesh( mesh, shader );
    
    GetShaderTable()[0]->GetProgram()->BindAttribute(*ShaderPositions, ShaderLineGeometry );
}

void GRAPHIC_OBJECT_SHAPE_LINE::Render( const GRAPHIC_RENDERER & renderer ) {
    
    if ( renderer.GetPassIndex() >= ShaderTable.size() ) {
        
        return;
    }

    CORE_MATH_MATRIX
        object_matrix, result;
    
    GetShaderTable()[ 0 ]->Enable();
    
    GRAPHIC_SHADER_ATTRIBUTE * attr = &GetShaderTable()[0]->getShaderAttribute(GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[0] = Position[0];
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[1] = 0.0f;
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[2] = 0.0f;
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[3] = 1.0f;
    
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[4] = Target[0] * 5000.0f;
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[5] = Target[1] * 5000.0f;
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[6] = Target[2] * 5000.0f;
    ShaderPositions->AttributeValue.Value.FloatMatrix4x4[7] = 1.0f;
    
    CORE_MATH_MATRIX temp( CORE_MATH_MATRIX::Identity );
    temp = renderer.GetCamera().GetViewMatrix();
    temp *= object_matrix;
    
    glEnable(GL_BLEND);
    GFX_CHECK( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); )
    
    //LOCAL_MULTIPLY_MATRIX( attr->AttributeValue.Value.FloatMatrix4x4 , translation );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    result = renderer.GetCamera().GetProjectionMatrix();
    result *= renderer.GetCamera().GetViewMatrix();
    result *= object_matrix;
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        attr->AttributeIndex,
        1,
        0,
        (const GLfloat * )&result[0]);
    
    GFX_CHECK( glUniform4fv(
        ShaderPositions->AttributeIndex,
        4,
        (const GLfloat * )&ShaderPositions->AttributeValue.Value.FloatMatrix4x4[0]); )

    GetMeshTable()[ 0 ]->ApplyBuffers();
    GetShaderTable()[ 0 ]->Disable();
    
    glDisable(GL_BLEND);
}

CORE_HELPERS_IDENTIFIER GRAPHIC_OBJECT_SHAPE_LINE::ShaderLineGeometry( "geometryPosition" );
