//
//  GRAPHIC_MESH.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_MEMORY.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH )
    XS_DEFINE_ClassMember( CORE_DATA_BUFFER, VertexCoreBuffer )
    XS_DEFINE_ClassMember( CORE_DATA_BUFFER, IndexCoreBuffer )
    XS_DEFINE_ClassMember( GRAPHIC_SHADER_BIND, VertexComponent )
    XS_DEFINE_ClassMember( GRAPHIC_MESH_POLYGON_RENDER_MODE, PolygonRenderMode )
    XS_DEFINE_ClassMember( GRAPHIC_MESH_SURFACE_RENDER_MODE, SurfaceRenderMode )
    XS_DEFINE_ClassMember( int, VertexStride )
    XS_DEFINE_ClassMember( CORE_MATH_MATRIX, Transform )
    XS_DEFINE_ClassMember( CORE_MATH_SHAPE, BoundingShape)
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH * )

GRAPHIC_MESH::GRAPHIC_MESH() :
    VertexCoreBuffer(),
    IndexCoreBuffer(),
    Texture( NULL ),
    NormalTexture( NULL ),
    VertexComponent( GRAPHIC_SHADER_BIND_None ),
    VertexStride( 0 ),
    PolygonRenderMode( GRAPHIC_MESH_POLYGON_RENDER_MODE_TriangleList ),
    SurfaceRenderMode( GRAPHIC_MESH_SURFACE_RENDER_MODE_Solid ),
    Transform(){
        
        GLOBAL_IDENTITY_MATRIX( &Transform[0] );
        
        #if __COMPILE_WITH__COLLADA__
        
            CurrenGeometrytTable = NULL;
        #endif
    
    VertexCoreBuffer = new CORE_DATA_BUFFER();
    IndexCoreBuffer = new CORE_DATA_BUFFER();
}

GRAPHIC_MESH::GRAPHIC_MESH(const GRAPHIC_MESH & other ) {
    
}

GRAPHIC_MESH::~GRAPHIC_MESH() {

    CORE_MEMORY_ObjectSafeDeallocation( VertexCoreBuffer );
    CORE_MEMORY_ObjectSafeDeallocation( IndexCoreBuffer );
    CORE_MEMORY_ObjectSafeDeallocation( Texture );
    CORE_MEMORY_ObjectSafeDeallocation( NormalTexture );
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
