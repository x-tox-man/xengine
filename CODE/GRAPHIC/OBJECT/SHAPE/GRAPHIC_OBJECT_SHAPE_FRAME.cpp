//
//  GRAPHIC_OBJECT_SHAPE_FRAME.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_SHAPE_FRAME.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_MEMORY.h"

#include <math.h>

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"

#define unit_s  0.5f
#define ot      0.33334f
#define tt      (2.0f * 0.33334f)

void Static_GetPlanVertexDataAdapted(float * destination, float base_x, float base_y, float half_size_x, float half_size_y, float u, float v ) {
    
    float vertex_data [] = {
        base_x - half_size_x,  base_y + half_size_y, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         u,     v, // top left
        base_x + half_size_x,  base_y + half_size_y, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         u+ ot, v, // top right
        base_x + half_size_x, base_y - half_size_y, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,          u+ ot, v +ot, // bottom right
        base_x - half_size_x, base_y - half_size_y, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,         u,     v +ot, // bottom left
    };
    
    memcpy((void*)destination, (void*)vertex_data, sizeof(float) * 40);
}

void Static_GetPlanIndexDataAdapted(unsigned int * base_index_data ) {
    
    unsigned int * data_offset = base_index_data;
    
    for (int i = 0; i < 8; i++ ) {
        unsigned int offset = (unsigned int) i * 4;
        unsigned int index_data[] = { 0+offset, 1+offset, 2+offset, 2+offset, 3+offset, 0+offset };
        
        memcpy((void*)data_offset, (void*)index_data, 6* sizeof(unsigned int));
        data_offset += 6;
    }
}

GRAPHIC_OBJECT_SHAPE_FRAME::GRAPHIC_OBJECT_SHAPE_FRAME() :
    GRAPHIC_OBJECT_SHAPE() {
    
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Texcoord0 );
}

GRAPHIC_OBJECT_SHAPE_FRAME::~GRAPHIC_OBJECT_SHAPE_FRAME() {

}

void GRAPHIC_OBJECT_SHAPE_FRAME::InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader ) {
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Position );
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Normal );
    mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Texcoord0 );
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    CreateVertexData();
    
    unsigned int * temp_ptr = (unsigned int *) CORE_MEMORY_ALLOCATOR_Allocate( 8 * 6 * sizeof( unsigned int ) )
    Static_GetPlanIndexDataAdapted(temp_ptr);
    
    index_buffer->InitializeWithMemory( 8 * 6 * sizeof( unsigned int ), 0, ( void * ) temp_ptr );
    vertex_buffer->InitializeWithMemory( 8 * 40 * sizeof( float ), 0, ( void * ) VertexData );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
    
    SetShaderForMesh( mesh, shader );
    
    free(temp_ptr);
}

void GRAPHIC_OBJECT_SHAPE_FRAME::Render( GRAPHIC_RENDERER & renderer ) {
    
    if ( renderer.GetPassIndex() >= ShaderTable.size() ) {
        
        return;
    }
    
    CORE_MATH_MATRIX
        object_matrix,result;
    
    //UpdateFrameVertexData( VertexData, *TextureBlock );
    
    //GetMeshTable()[ 0 ]->GetVertexCoreBuffer().InitializeWithMemory( 8 * 40  * sizeof( float ), 0, ( void * ) VertexData );
    
    //GRAPHIC_SYSTEM::UpdateVertexBuffer( GetMeshTable()[0], GetMeshTable()[ 0 ]->GetVertexCoreBuffer() );
    
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
    TextureBlock->Apply( texture_index++, texture->AttributeIndex );
    
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
    
    TextureBlock->Discard();
    
    GetShaderTable()[ 0 ]->Disable();
    
    GRAPHIC_SYSTEM::DisableBlend();
}

void GRAPHIC_OBJECT_SHAPE_FRAME::UpdateFrameVertexData( float * plan_vertex_data, const GRAPHIC_TEXTURE_BLOCK & block ) {
    
    VertexData[8] = block.GetOffset()[0];
    VertexData[9] = block.GetOffset()[1];
    
    VertexData[18] = (block.GetOffset()[0] + block.GetSize()[0]);
    VertexData[19] = block.GetOffset()[1];
    
    VertexData[28] = (block.GetOffset()[0] + block.GetSize()[0]);
    VertexData[29] = (block.GetOffset()[1] + block.GetSize()[1]);
    
    VertexData[38] = block.GetOffset()[0];
    VertexData[39] = (block.GetOffset()[1] + block.GetSize()[1]);;
}

void GRAPHIC_OBJECT_SHAPE_FRAME::CreateVertexData() {
    
    float * offset = NULL;
    VertexData = (float * ) CORE_MEMORY_ALLOCATOR_Allocate( sizeof(float) * 40 * 8 );
    offset = VertexData;
    
    float width_half_border_size = BorderWidth * 0.5f;
    float height_half_border_size = BorderHeight * 0.5f;
    
    //Top left
    Static_GetPlanVertexDataAdapted( offset, - unit_s - width_half_border_size, unit_s + height_half_border_size, width_half_border_size, height_half_border_size, 0.0f, 0.0f);
    offset = offset + 40;
    //Top
    Static_GetPlanVertexDataAdapted( offset, 0.0f, unit_s + height_half_border_size, unit_s, height_half_border_size, ot, 0.0f);
    offset = offset + 40;
    //Top right
    Static_GetPlanVertexDataAdapted( offset, unit_s + width_half_border_size, unit_s + height_half_border_size, width_half_border_size, height_half_border_size, tt, 0.0f);
    offset = offset + 40;
    //Right
    Static_GetPlanVertexDataAdapted( offset, unit_s + width_half_border_size, 0.0f, width_half_border_size, unit_s, tt, ot);
    offset = offset + 40;
    //Bottom Right
    Static_GetPlanVertexDataAdapted( offset, unit_s + width_half_border_size, - unit_s - height_half_border_size, width_half_border_size, height_half_border_size, tt, tt);
    offset = offset + 40;
    //Bottom
    Static_GetPlanVertexDataAdapted( offset, 0.0f, - unit_s - height_half_border_size , unit_s, height_half_border_size, ot, tt);
    offset = offset + 40;
    //Bottom Left
    Static_GetPlanVertexDataAdapted( offset, - unit_s - width_half_border_size, - unit_s - height_half_border_size, width_half_border_size, height_half_border_size, 0.0f, tt);
    offset = offset + 40;
    //Left
    Static_GetPlanVertexDataAdapted( offset, - unit_s - width_half_border_size, 0.0f, width_half_border_size, unit_s, 0.0f, ot);
}
