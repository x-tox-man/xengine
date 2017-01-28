//
//  GRAPHIC_MESH_OPENGL2_MEMBERS.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 18/07/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_MEMORY.h"

void GRAPHIC_MESH::CreateBuffers()
{
    // Create Vertex Array Object
    GRAPHIC_SYSTEM::CreateVertexBuffer(*this);
    GRAPHIC_SYSTEM::CreateIndexBuffer(*this);
}

void GRAPHIC_MESH::ReleaseBuffers()
{
    GFX_CHECK( glDisableVertexAttribArray(GRAPHIC_SHADER_BIND_Position); )
    GFX_CHECK( glDeleteBuffers(GetIndexCoreBuffer().Getsize(), &IndexBuffer); )
    GFX_CHECK( glDeleteBuffers(GetVertexCoreBuffer().Getsize(), &VertexBuffer); )
}
