//
//  GRAPHIC_PARTICLE_RENDERER_OPENGL.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 20/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_RENDERER_OPENGL_h
#define GRAPHIC_PARTICLE_RENDERER_OPENGL_h

public :

void Render( std::array< __PARTICLE_TYPE__, __ARRAY_SIZE__ > & particle_table, GRAPHIC_MATERIAL & material, GRAPHIC_RENDERER & renderer ) {
    
    // normally : lock particle and transfert to geometry buffer
    //int decrement = particle_table.size();
    
    //PlanObject.SetTextureBlock(material.GetTexture());
    
    /*while ( decrement-- > 0 ) {
     
     PlanObject.SetPosition(particle_table[decrement].Position );
     PlanObject.SetOrientation(particle_table[decrement].Orientation );
     PlanObject.SetScaleFactor(CORE_MATH_VECTOR(1.0f,1.0f,0.0f,1.0f) );
     PlanObject.Render(renderer);
     }*/
    
    VertexBuffer->InitializeWithMemory( 10 * sizeof(float) * __ARRAY_SIZE__, 0, (void*) &particle_table[0] );
    GRAPHIC_SYSTEM::UpdateVertexBuffer(&Mesh, *VertexBuffer);
    
    material.Apply(renderer);
    
    //GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    
    CORE_MATH_MATRIX result = renderer.GetCamera().GetProjectionMatrix();
    result *= renderer.GetCamera().GetViewMatrix();
    
    GRAPHIC_SHADER_ATTRIBUTE * attr = &material.GetEffect()->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    GRAPHIC_SYSTEM_ApplyMatrix(attr->AttributeIndex, 1, 0, &result[0])
    
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
    
    if ( component & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        GFX_CHECK( glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 2;
    }
    
    //GFX_CHECK( glEnable( GL_PROGRAM_POINT_SIZE ); )
    GFX_CHECK( glPointSize(10.0f); )
    GFX_CHECK( glBindVertexArray(Mesh.GetVertexArrays() ); )
    GFX_CHECK( glDrawArrays(GL_POINTS, 0, __ARRAY_SIZE__); )
    
    material.Discard(renderer);
}

private :

GRAPHIC_OBJECT_SHAPE_PLAN PlanObject;
GRAPHIC_MESH Mesh;
CORE_DATA_BUFFER * IndexBuffer = new CORE_DATA_BUFFER;
CORE_DATA_BUFFER * VertexBuffer = new CORE_DATA_BUFFER;

void InternalInitialize( GRAPHIC_MATERIAL & material ) {
    
    PlanObject.InitializeShape(&material.GetEffect()->GetProgram());
    PlanObject.SetShaderForMesh(nullptr, material.GetEffect()->GetProgram().GetProgram());
    
    //TODO : refactor
    Mesh.ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    Mesh.ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    Mesh.ActivateBufferComponent(GRAPHIC_SHADER_BIND_PositionTexture);
    
    VertexBuffer->InitializeWithMemory( 0 * sizeof(float) * __ARRAY_SIZE__, 0, (void*) NULL );
    
    Mesh.SetVertexCoreBuffer( VertexBuffer );
    
    Mesh.CreateBuffers();
    //GRAPHIC_SYSTEM::
}

#endif /* GRAPHIC_PARTICLE_RENDERER_OPENGL_h */
