//
//  GRAPHIC_TEXT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_MESH.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GRAPHIC_TEXT )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_TEXT, UpdateText, const char * )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GRAPHIC_TEXT )

GRAPHIC_TEXT::GRAPHIC_TEXT() {
    
}

GRAPHIC_TEXT::~GRAPHIC_TEXT() {

}

void GRAPHIC_TEXT::Initialize( const char * text, GRAPHIC_FONT & font, float size_factor, GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader, bool left_to_right ) {
    
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Texcoord0 );
    
    Font = &font;
    
    if( GetMeshTable().size() ) {
        
        delete GetMeshTable()[0];
        GetMeshTable().clear();
    }
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    AddNewMesh( mesh );
    
    SetShaderForMesh( mesh, shader );
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Texcoord0);
    
    TextSize = size_factor;
    
    Text = text;
    
    UpdateText( Text, TextSize );
}

void GRAPHIC_TEXT::Initialize( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader ) {
    
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Texcoord0 );
    
    if( GetMeshTable().size() ) {
        
        delete GetMeshTable()[0];
        GetMeshTable().clear();
    }
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    AddNewMesh( mesh );
    
    SetShaderForMesh( mesh, shader );
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Texcoord0);
    
    UpdateText( Text, TextSize );
}

void GRAPHIC_TEXT::Render( GRAPHIC_RENDERER & renderer ) {
    
    CORE_MATH_MATRIX
        object_matrix, result;
    
    GetShaderTable()[ 0 ]->Enable();
    
    GRAPHIC_SHADER_ATTRIBUTE * attr = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    GRAPHIC_SHADER_ATTRIBUTE * texture = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ColorTexture );
    GRAPHIC_SHADER_ATTRIBUTE * color = &GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::GeometryColor );
    
    object_matrix.Translate( GetPosition() );
    object_matrix.Scale( ScaleFactor[0], ScaleFactor[1], ScaleFactor[2] );
    
    
    result = renderer.GetCamera().GetProjectionMatrix();
    result *= renderer.GetCamera().GetViewMatrix();
    result *= object_matrix;
    
    GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    
    //LOCAL_MULTIPLY_MATRIX( attr->AttributeValue.Value.FloatMatrix4x4 , translation );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    TextureBlock->Apply( 0, texture->AttributeIndex );
    
    GRAPHIC_SYSTEM_ApplyMatrix(attr->AttributeIndex, 1, 0, &result[0])
    
    renderer.EnableColor(true);
    GFX_CHECK( glUniform4fv(
                  color->AttributeIndex,
                  1,
                  (const GLfloat * )&color->AttributeValue.Value.FloatArray4); )
    renderer.EnableColor(false);
    
    GetMeshTable()[ 0 ]->ApplyBuffers();
    
    TextureBlock->Discard();
    
    GetShaderTable()[ 0 ]->Disable();
    
    GRAPHIC_SYSTEM::DisableBlend();
}

void GRAPHIC_TEXT::UpdateText( const char * text, float size_factor, bool left_to_right ) {
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    int text_size = (int) strlen( text );
    
    float * vertex_data = (float *) CORE_MEMORY_ALLOCATOR::Allocate( 10 * sizeof( float ) * text_size * 4 );
    
    int * index_data = (int *) CORE_MEMORY_ALLOCATOR::Allocate( 6 * sizeof(int)* text_size );
    
    int offset = 0;
    
    float advance[2];
    
    advance[0] = 0.0f;
    advance[1] = 0.0f;
    
    float text_extent[2];
    
    text_extent[0] = 0.0f;
    text_extent[1] = 0.0f;
    
    float font_size = (float) Font->GetSize() * size_factor;
    
    for ( int i = 0; i < text_size; i++ ) {
        
        char current_char = text[i];
        GRAPHIC_GLYPH & current_glyph = Font->GetGlyphTable()[ current_char ];
        
        if ( current_char == '\n' || current_char == '\r' ) {
            
            advance[0] = 0.0f;
            advance[1] -= font_size;
            
            continue;
        }
        
        if ( current_char == ' ' ) {
            
            advance[0] += font_size / 2;
            
            continue;
        }
        
        advance[0] += current_glyph.Advance[2];
        advance[1] += current_glyph.Advance[3];
        
        float temp1[] = {
            
            advance[0], advance[1], 1.0f ,  1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, //Normal
            current_glyph.PaddingBounding[0] ,1 - current_glyph.PaddingBounding[1] //uv
        };
        
        memcpy( (void*)( vertex_data + offset), temp1, 10 * sizeof( float ) );
        
        offset +=10;
        
        float temp2[] = {
            advance[0] + current_glyph.Advance[0], advance[1],  1.0f ,  1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, //Normal
            current_glyph.PaddingBounding[0] + current_glyph.PaddingBounding[2], 1 - current_glyph.PaddingBounding[1] //uv
        };
        
        memcpy( (void*)( vertex_data + offset), temp2, 10 * sizeof( float ) );
        
        offset +=10;
        
        float temp3[] = {
            advance[0] + current_glyph.Advance[0], advance[1] - current_glyph.Advance[1],  1.0f ,  1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, //Normal
            current_glyph.PaddingBounding[0] + current_glyph.PaddingBounding[2], 1 - ( current_glyph.PaddingBounding[1] + current_glyph.PaddingBounding[3] ) //uv
        };
        
        memcpy( (void*)( vertex_data + offset), temp3, 10 * sizeof( float ) );
        
        offset +=10;
        
        float temp4[] = {
            advance[0], advance[1] - current_glyph.Advance[1],  1.0f ,  1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, //Normal
            current_glyph.PaddingBounding[0], 1 - ( current_glyph.PaddingBounding[1] + current_glyph.PaddingBounding[3] )//uv
        };
        
        memcpy( (void*)( vertex_data + offset), temp4, 10 * sizeof( float ) );
        
        offset += 10;
        
        advance[0] -= current_glyph.Advance[2];
        advance[1] -= current_glyph.Advance[3];
        
        advance[0] += current_glyph.Advance[0] + 1.0f;
        
        text_extent[0] += current_glyph.Advance[0];
    }
    
    offset = 0;
    
    for ( int base = 0; base < text_size; base++ ) {
        
        int i = base * 4;
        int ind_temp[] = { i, i + 1, i + 2, i + 2, i + 3, i };
        
        memcpy( (void*)(index_data + offset), ind_temp, 6 * sizeof( int ) );
        
        offset += 6;
    }
    
    index_buffer->InitializeWithMemory( 6 * sizeof(int) * text_size, 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( 10 * sizeof( float ) * text_size * 4, 0, (void*) vertex_data );
    
    GetMeshTable()[0]->SetIndexCoreBuffer( index_buffer );
    GetMeshTable()[0]->SetVertexCoreBuffer( vertex_buffer );
    
    GetMeshTable()[0]->CreateBuffers();
    
    CORE_MEMORY_ALLOCATOR_Free( vertex_data );
    CORE_MEMORY_ALLOCATOR_Free( index_data );
}
