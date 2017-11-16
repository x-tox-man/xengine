//
//  GRAPHIC_PARTICLE_RENDERER_OPENGL.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_RENDERER_OPENGL_h
#define GRAPHIC_PARTICLE_RENDERER_OPENGL_h

public :

void Render( std::array< __PARTICLE_TYPE__, __ARRAY_SIZE__ > & particle_table, GRAPHIC_SHADER_EFFECT * effect, GRAPHIC_RENDERER & renderer, int first_index, int last_index ) {
    
    //TODO:
    renderer.SetLightingIsEnabled( false );
    VertexBuffer->InitializeWithMemory( 8 * sizeof(float) * __ARRAY_SIZE__, 0, (void*) &particle_table[0] );
    GRAPHIC_SYSTEM::UpdateVertexBuffer(&Mesh, *VertexBuffer);
    
    effect->Apply( renderer );
    
    GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    
    CORE_MATH_MATRIX result = renderer.GetCamera().GetProjectionMatrix();
    result *= renderer.GetCamera().GetViewMatrix();
    
    GRAPHIC_SHADER_ATTRIBUTE & attr = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    GRAPHIC_SYSTEM_ApplyMatrix( attr.AttributeIndex, 1, 0, &result[0])
    
    int vertex_offset = 0;
    GRAPHIC_SHADER_BIND component = Mesh.GetVertexComponent();
    int stride = Mesh.GetVertexStride();
    
    if ( component & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Position, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*) 0); )
        
        vertex_offset += 4;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Normal, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    
    if ( first_index < last_index ) {
        
        GFX_CHECK( glPointSize(10.0f); )
        GFX_CHECK( glBindVertexArray(Mesh.GetVertexArrays() ); )
        GFX_CHECK( glDrawArrays(GL_POINTS, first_index, (last_index - (first_index+1))); )
    }
    else if ( last_index > first_index ){
        
        GFX_CHECK( glPointSize(10.0f); )
        GFX_CHECK( glBindVertexArray(Mesh.GetVertexArrays() ); )
        GFX_CHECK( glDrawArrays(GL_POINTS, last_index, (__ARRAY_SIZE__ - 1) - last_index); )
        GFX_CHECK( glDrawArrays(GL_POINTS, 0, first_index); )
    }
    
    renderer.SetLightingIsEnabled( true );
}

private :

GRAPHIC_MESH
    Mesh;
CORE_DATA_BUFFER
    * IndexBuffer,
    * VertexBuffer;

void InternalInitialize( GRAPHIC_SHADER_EFFECT * effect ) {
    
    IndexBuffer = new CORE_DATA_BUFFER;
    VertexBuffer = new CORE_DATA_BUFFER;
    
    //TODO : refactor
    Mesh.ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    Mesh.ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    
    VertexBuffer->InitializeWithMemory( 0 * sizeof(float) * __ARRAY_SIZE__, 0, (void*) NULL );
    
    Mesh.SetVertexCoreBuffer( VertexBuffer );
    
    Mesh.CreateBuffers();
}

#endif /* GRAPHIC_PARTICLE_RENDERER_OPENGL_h */
