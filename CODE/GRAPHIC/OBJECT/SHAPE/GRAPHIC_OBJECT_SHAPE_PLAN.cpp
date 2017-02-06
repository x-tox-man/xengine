//
//  GRAPHIC_OBJECT_SHAPE_PLAN.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_MEMORY.h"

#include <math.h>

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"

#define unit_s 0.5f // -0.5 to  0.5 makes 1.0f lenght

static float Static_PlanVertexData[] = {
    -unit_s,  unit_s, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         0.0f, 0.0f,
    unit_s,  unit_s, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         1.0f, 0.0f,
    unit_s, -unit_s, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         1.0f, 1.0f,
    -unit_s, -unit_s, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         0.0f, 1.0f,
};

GRAPHIC_OBJECT_SHAPE_PLAN::GRAPHIC_OBJECT_SHAPE_PLAN() :
    GRAPHIC_OBJECT_SHAPE() {
    
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Texcoord0 );
}

GRAPHIC_OBJECT_SHAPE_PLAN::~GRAPHIC_OBJECT_SHAPE_PLAN() {

}

void GRAPHIC_OBJECT_SHAPE_PLAN::InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader ) {
    
    static unsigned int index_data[] = { 0, 1, 2, 2, 3, 0 };
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Position );
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Normal );
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Texcoord0 );
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    PlanVertexData = (float * ) CORE_MEMORY_ALLOCATOR_Allocate( sizeof(float) * 40 );
    memcpy(PlanVertexData, Static_PlanVertexData, sizeof(float) * 40 );
    
    unsigned int * temp_ptr = (unsigned int *) CORE_MEMORY_ALLOCATOR_Allocate( 6 * sizeof( unsigned int ) )
    memcpy(temp_ptr, index_data, 6 * sizeof( unsigned int ) );
    
    index_buffer->InitializeWithMemory( 6 * sizeof( unsigned int ), 0, ( void * ) temp_ptr );
    vertex_buffer->InitializeWithMemory( 4 * 10 * sizeof( float ), 0, ( void * ) PlanVertexData );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
    
    SetShaderForMesh( mesh, shader );
}

void GRAPHIC_OBJECT_SHAPE_PLAN::Render( GRAPHIC_RENDERER & renderer ) {
    
    if ( renderer.GetPassIndex() >= ShaderTable.size() ) {
        
        return;
    }
    
    CORE_MATH_MATRIX
        object_matrix,result;
    
    if( TextureBlock ) {
        
        //TODO: seulement si TextureBlock offset est différent!
        UpdateVertexData( PlanVertexData, *TextureBlock );
    }
    
    GetMeshTable()[ 0 ]->GetVertexCoreBuffer().InitializeWithMemory( 4 * 10 * sizeof( float ), 0, ( void * ) PlanVertexData );
    
    GRAPHIC_SYSTEM::UpdateVertexBuffer( GetMeshTable()[0], GetMeshTable()[ 0 ]->GetVertexCoreBuffer() );
    
    GetShaderTable()[ 0 ]->Enable();
        
    GRAPHIC_SHADER_ATTRIBUTE * attr = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    GRAPHIC_SHADER_ATTRIBUTE * texture = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture );
    GRAPHIC_SHADER_ATTRIBUTE * depth = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture );

    GLOBAL_IDENTITY_MATRIX( attr->AttributeValue.Value.FloatMatrix4x4 );
    
    static float angle = M_PI;
    
    object_matrix.Scale( ScaleFactor[0], ScaleFactor[1], ScaleFactor[2] );
    object_matrix.XRotate( angle );
    //object_matrix.ZRotate( angle );
    object_matrix.Translate( GetPosition() );
    
    result = renderer.GetCamera().GetProjectionMatrix();
    result *= renderer.GetCamera().GetViewMatrix();
    result *= object_matrix;
    
    GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    
    //LOCAL_MULTIPLY_MATRIX( attr->AttributeValue.Value.FloatMatrix4x4 , translation );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    int texture_index = 0;
    
    if( TextureBlock ) {
        
        TextureBlock->Apply( texture_index++, texture->AttributeIndex );
    }
    
    if ( SecondTextureBlock ) {
        
        GRAPHIC_SHADER_ATTRIBUTE * texture_2 = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture1 );
        
        SecondTextureBlock->Apply( texture_index++, texture_2->AttributeIndex );
    }
    
    if ( ThirdTextureBlock ) {
        
        GRAPHIC_SHADER_ATTRIBUTE * texture_3 = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture2 );
        
        SecondTextureBlock->Apply( texture_index++, texture_3->AttributeIndex );
    }
    
    if ( depth->AttributeIndex > 0 ) {
        
        TextureBlock->ApplyDepth( texture_index++, depth->AttributeIndex );
    }
    
    GRAPHIC_SHADER_ATTRIBUTE & color = GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::GeometryColor );
                                            
                                            
    GFX_CHECK( glUniform4fv(
              color.AttributeIndex,
              1,
              (const GLfloat * )&color.AttributeValue.Value.FloatArray4 ); )
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        attr->AttributeIndex,
        1,
        0,
        (const GLfloat * )&result[0]);
    
    // TODO : improve efficiency with uniform shader attribute handling
    if ( Effect ) {
        
        Effect->Apply();
    }

    GetMeshTable()[ 0 ]->ApplyBuffers();
    
    if( TextureBlock ) {
        
        TextureBlock->Discard();
    }
    
    GetShaderTable()[ 0 ]->Disable();
    
    GRAPHIC_SYSTEM::DisableBlend();
}

void GRAPHIC_OBJECT_SHAPE_PLAN::UpdateVertexData( float * PlanVertexData, const GRAPHIC_TEXTURE_BLOCK & block ) {
    
    PlanVertexData[8] = block.GetOffset()[0];
    PlanVertexData[9] = block.GetOffset()[1];
    
    PlanVertexData[18] = (block.GetOffset()[0] + block.GetSize()[0]);
    PlanVertexData[19] = block.GetOffset()[1];
    
    PlanVertexData[28] = (block.GetOffset()[0] + block.GetSize()[0]);
    PlanVertexData[29] = (block.GetOffset()[1] + block.GetSize()[1]);
    
    PlanVertexData[38] = block.GetOffset()[0];
    PlanVertexData[39] = (block.GetOffset()[1] + block.GetSize()[1]);;
}
