//
//  GRAPHIC_MESH.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"
#include "CORE_MEMORY.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH )
    XS_DEFINE_ClassMember( "VertexCoreBuffer", CORE_DATA_BUFFER, VertexCoreBuffer )
    XS_DEFINE_ClassMember( "IndexCoreBuffer", CORE_DATA_BUFFER, IndexCoreBuffer )
    XS_DEFINE_ClassMember( "VertexComponent", GRAPHIC_SHADER_BIND, VertexComponent )
    XS_DEFINE_ClassMember( "PolygonRenderMode", GRAPHIC_MESH_POLYGON_RENDER_MODE, PolygonRenderMode )
    XS_DEFINE_ClassMember( "SurfaceRenderMode", GRAPHIC_MESH_SURFACE_RENDER_MODE, SurfaceRenderMode )
    XS_DEFINE_ClassMember( "VertexStride", int, VertexStride )
    XS_DEFINE_ClassMember( "Transform", CORE_MATH_MATRIX, Transform )
    XS_DEFINE_ClassMember( "BoundingShape", CORE_MATH_SHAPE, BoundingShape )
    XS_DEFINE_ClassMember( "MeshName", std::string, MeshName )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH * )

GRAPHIC_MESH::GRAPHIC_MESH() :
    VertexCoreBuffer( NULL ),
    IndexCoreBuffer( NULL ),
    Texture( NULL ),
    NormalTexture( NULL ),
    VertexComponent( GRAPHIC_SHADER_BIND_None ),
    VertexStride( 0 ),
    PolygonRenderMode( GRAPHIC_MESH_POLYGON_RENDER_MODE_TriangleList ),
    SurfaceRenderMode( GRAPHIC_MESH_SURFACE_RENDER_MODE_Wireframe ),
    Transform()
    #if X_VK
    , Buffer(),
    Memory(),
    BufferInfo()
    #endif
    {
        
        GLOBAL_IDENTITY_MATRIX( &Transform[0] );
        
        #if __COMPILE_WITH__COLLADA__
        
            CurrenGeometrytTable = NULL;
        #endif
}

GRAPHIC_MESH::GRAPHIC_MESH(const GRAPHIC_MESH & other ) {
    
}

GRAPHIC_MESH::~GRAPHIC_MESH() {

    CORE_MEMORY_ObjectSafeDeallocation( VertexCoreBuffer );
    CORE_MEMORY_ObjectSafeDeallocation( IndexCoreBuffer );
    CORE_MEMORY_ObjectSafeDeallocation( Texture );
    CORE_MEMORY_ObjectSafeDeallocation( NormalTexture );
}

int GRAPHIC_MESH::ComputeVertexStride(GRAPHIC_SHADER_BIND bind) {
    
    int stride = 0;
    
    if ( bind & GRAPHIC_SHADER_BIND_Position ) {
        
        stride += 4;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Normal ) {
        
        stride += 4;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        stride += 2;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Tangents ) {
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        stride += 3;
    }
    
    return stride;
}

void GRAPHIC_MESH::ActivateBufferComponent( GRAPHIC_SHADER_BIND attribute ) {
    
    VertexComponent = (GRAPHIC_SHADER_BIND ) (VertexComponent | attribute);
    
    if ( attribute & GRAPHIC_SHADER_BIND_Position ) {
        
        VertexStride += 4;
    }
    
    if ( attribute & GRAPHIC_SHADER_BIND_Normal ) {
        
        VertexStride += 4;
    }
    
    if ( attribute & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        VertexStride += 2;
    }
    
    if ( attribute & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        VertexStride += 3;
    }
    
    if ( attribute & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        VertexStride += 3;
    }
    
    if ( attribute & GRAPHIC_SHADER_BIND_Tangents ) {
        
        VertexStride += 3;
    }
    
    if ( attribute & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        VertexStride += 3;
    }
}

void GRAPHIC_MESH::CreateBuffers()
{
    if ( VertexCoreBuffer == NULL ) {
        
        VertexCoreBuffer = new CORE_DATA_BUFFER();
    }
    
    if ( IndexCoreBuffer == NULL ) {
        
        IndexCoreBuffer = new CORE_DATA_BUFFER();
    }

    // Create Vertex Array Object
    GRAPHIC_SYSTEM::CreateVertexBuffer(*this);
    GRAPHIC_SYSTEM::CreateIndexBuffer(*this);
}

void GRAPHIC_MESH::ApplyBuffers() {
    
    GRAPHIC_SYSTEM::ApplyBuffers(*this);
}

void GRAPHIC_MESH::ReleaseBuffers() {
    
    GRAPHIC_SYSTEM::ReleaseBuffers(*this);
}
