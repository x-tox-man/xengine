//
//  GRAPHIC_OBJECT_SHAPE_AXIS.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#define AXIS_UNIT 1.0f

#include <math.h>

#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT_SHAPE_AXIS.h"
#include "GRAPHIC_SHADER_PROGRAM.h"

GRAPHIC_OBJECT_SHAPE_AXIS::GRAPHIC_OBJECT_SHAPE_AXIS( float position[ 4 ], CORE_MATH_QUATERNION & orientation ) {
    
}

GRAPHIC_OBJECT_SHAPE_AXIS::~GRAPHIC_OBJECT_SHAPE_AXIS() {

}

void GRAPHIC_OBJECT_SHAPE_AXIS::InitializeShape() {
    
    static unsigned int index_data[] = { 0, 1, 0, 2, 0, 3 };
    
    static float vertex_data[] = {
        0.0f,       0.0f,       0.0f,       1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        AXIS_UNIT,  0.0f,       0.0f,       1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        0.0f,       AXIS_UNIT,  0.0f,       1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
        0.0f,       0.0f,       AXIS_UNIT,  1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    };
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( 6 * sizeof(unsigned int), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 4 * 8 * sizeof(float), 0, (void*) vertex_data );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
}

/*void GRAPHIC_OBJECT_SHAPE_AXIS::Render( GRAPHIC_RENDERER & renderer, const GRAPHIC_OBJECT_RENDER_OPTIONS & options, GRAPHIC_SHADER_EFFECT * effect ) {
    
    if ( renderer.GetPassIndex() >= ShaderTable.size() ) {
        
        return;
    }
    
    GetShaderTable()[ 0 ]->Enable();
    
    GRAPHIC_SHADER_ATTRIBUTE * attr = &GetShaderTable()[0]->GetShaderAttribute(GRAPHIC_SHADER_PROGRAM::ProjectionMatrix );
    GRAPHIC_SHADER_ATTRIBUTE * attrModel = &GetShaderTable()[0]->GetShaderAttribute(GRAPHIC_SHADER_PROGRAM::ModelMatrix );
    
    GLOBAL_IDENTITY_MATRIX(attr->AttributeValue.Value.FloatMatrix4x4);
    
    static float angle = M_PI;
    
    angle += 0.015f;
    
    static float depth = 0.0f;
    
    depth += 1.15f;
    
    float rotation[16];
    
    GLOBAL_IDENTITY_MATRIX(rotation);
    
    rotation[0] = cosf(angle);
    rotation[1] = 0.0f;
    rotation[2] = -sinf(angle);
    rotation[3] = 0.0f;
    
    rotation[4] = 0.0f;
    rotation[5] = 1.0f;
    rotation[6] = 0.0f;
    rotation[7] = 0.0f;
    
    rotation[8] = sinf(angle);
    rotation[9] = 0.0f;
    rotation[10] = cosf(angle);
    rotation[11] = 0.0f;
    
    rotation[12] = 0.0f;
    rotation[13] = 0.0f;
    rotation[14] = 0.0f;
    rotation[15] = 1.0f;
    
    float rotation2[16];
    
    GLOBAL_IDENTITY_MATRIX(rotation2);
    
    float translation[16];
    
    GLOBAL_IDENTITY_MATRIX(translation);
    
    translation[0] = 1.0f;
    translation[1] = 0.0f;
    translation[2] = 0.0f;
    translation[3] = 0.0f;
    
    translation[4] = 0.0f;
    translation[5] = 1.0f;
    translation[6] = 0.0f;
    translation[7] = 0.0f;
    
    translation[8] = 0.0f;
    translation[9] = 0.0f;
    translation[10] = 1.0f;
    translation[11] = -1.0f;
    
    translation[12] = 0.0f;
    translation[13] = 0.0f;
    translation[14] = 0.0f;
    translation[15] = 1.0f;
    
    float rotation3[16];
    
    
    //reverse the camera (this is lookat)
    GLOBAL_IDENTITY_MATRIX(rotation3);
    
    GLOBAL_MULTIPLY_MATRIX( rotation, rotation2  );
    GLOBAL_MULTIPLY_MATRIX( translation, rotation  );
    GLOBAL_MULTIPLY_MATRIX( rotation3, translation  );
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        attr->AttributeIndex,
        1,
        0,
        (const GLfloat * )&renderer.GetCamera()->GetProjectionMatrix()[0]);
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        attrModel->AttributeIndex,
        1,
        0,
        (const GLfloat * )rotation3);
    
    
    GetMeshTable()[ 0 ]->ApplyBuffers();
    GetShaderTable()[ 0 ]->Disable();
}*/

#undef AXIS_UNIT
