//
//  GRAPHIC_MESH_OPENGL2_MEMBERS.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 18/07/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#if OPENGL2PLUS

#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_BIND.h"

void GRAPHIC_MESH::CreateBuffers()
{
    // Create Vertex Array Object
    
    GFX_CHECK( glGenBuffers( 1, &VertexBuffer); )
    GFX_CHECK( glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer); )
    GFX_CHECK( glBufferData( GL_ARRAY_BUFFER, VertexCoreBuffer->getsize(), VertexCoreBuffer->getpointerAtIndex((unsigned int)0), GL_STATIC_DRAW ); )
    
    GFX_CHECK( glGenBuffers( 1, &IndexBuffer); )
    GFX_CHECK( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer); )
    GFX_CHECK( glBufferData( GL_ELEMENT_ARRAY_BUFFER, IndexCoreBuffer->getsize(), IndexCoreBuffer->getpointerAtIndex((unsigned int)0), GL_STATIC_DRAW ); )
    
    VertexArrays = (GLuint*) malloc(sizeof(GLuint));
    GFX_CHECK( glGenVertexArrays(1, VertexArrays); )
    GFX_CHECK( glBindVertexArray(*VertexArrays); )
    
    int vertex_offset = 0;
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_Position ) {

        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGL3_Position); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Position, 4, GL_FLOAT, GL_FALSE, VertexStride* sizeof(GLfloat), (void*)vertex_offset); )
        
        vertex_offset += 4;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGL3_Normal); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Normal, 4, GL_FLOAT, GL_FALSE, VertexStride* sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0); )
        GFX_CHECK( glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0, 2, GL_FLOAT, GL_FALSE, VertexStride* sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 2;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGL3_SkinWeight); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_SkinWeight, 3, GL_FLOAT, GL_FALSE, VertexStride* sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGL3_JointIndices); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_JointIndices, 3, GL_INT, GL_FALSE, VertexStride* sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat)));
                  )
        
        vertex_offset += 3;
    }
}

void GRAPHIC_MESH::ApplyBuffers() {

    GFX_CHECK( glBindVertexArray(*VertexArrays); )
    GFX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer); )
    
    int vertex_offset = 0;
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Position, 4, GL_FLOAT, GL_FALSE, VertexStride * sizeof(GLfloat), (void*) 0); )
        
        vertex_offset += 4;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Normal, 4, GL_FLOAT, GL_FALSE, VertexStride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        GFX_CHECK( glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0, 2, GL_FLOAT, GL_FALSE, VertexStride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 2;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_SkinWeight, 3, GL_FLOAT, GL_FALSE, VertexStride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
    
    if ( VertexComponent & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGL3_JointIndices, 3, GL_INT, GL_FALSE, VertexStride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
    
    //GFX_CHECK( glBindBuffer(GL_ARRAY_BUFFER, 0); )
    
    GFX_CHECK( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer) ; )
     
    GFX_CHECK( glDrawElements(
        GRAPHIC_MESH_POLYGON_RENDER_MODE_GetForOpengl3( PolygonRenderMode ),      // mode
        IndexCoreBuffer->getsize() / 4,    // count
        GL_UNSIGNED_INT,   // type
        (void*)0); )
}

void GRAPHIC_MESH::ReleaseBuffers()
{
    GFX_CHECK( glDeleteBuffers(getIndexCoreBuffer().getsize(), &IndexBuffer); )
    GFX_CHECK( glDeleteBuffers(getVertexCoreBuffer().getsize(), &VertexBuffer); )
    
    GFX_CHECK( glDisableVertexAttribArray( GRAPHIC_SHADER_BIND_OPENGL3_Position ); )
    GFX_CHECK( glDisableVertexAttribArray( GRAPHIC_SHADER_BIND_OPENGL3_Normal ); )
    GFX_CHECK( glDisableVertexAttribArray( GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0 ); )
    GFX_CHECK( glDisableVertexAttribArray( GRAPHIC_SHADER_BIND_OPENGL3_JointIndices ); )
    GFX_CHECK( glDisableVertexAttribArray( GRAPHIC_SHADER_BIND_OPENGL3_SkinWeight ); )
}

#endif
