//
//  GRAPHIC_MESH.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_MESH_ANIMATION.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_MESH_POLYGON_RENDER_MODE.h"
#include "GRAPHIC_MESH_SURFACE_RENDER_MODE.h"
#include "CORE_MATH_SHAPE_BOX.h"
#include "CORE_MATH_SHAPE_SPHERE.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH )

public:

    XS_DEFINE_SERIALIZABLE

    GRAPHIC_MESH();
    ~GRAPHIC_MESH();

    inline CORE_DATA_BUFFER * GetVertexCoreBuffer() { if ( VertexCoreBuffer == NULL ) VertexCoreBuffer = new CORE_DATA_BUFFER(); return VertexCoreBuffer; }
    void SetVertexCoreBuffer( CORE_DATA_BUFFER * vertexCoreBuffer ) {
        
        if ( VertexCoreBuffer && VertexCoreBuffer != vertexCoreBuffer) {
            
            CORE_MEMORY_ObjectSafeDeallocation( VertexCoreBuffer);
        }
        
        VertexCoreBuffer = vertexCoreBuffer;
    }

    inline CORE_DATA_BUFFER * GetIndexCoreBuffer() { if ( IndexCoreBuffer == NULL ) IndexCoreBuffer = new CORE_DATA_BUFFER(); return  IndexCoreBuffer; }
    void SetIndexCoreBuffer( CORE_DATA_BUFFER * indexCoreBuffer ) {
        
        if ( IndexCoreBuffer ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( IndexCoreBuffer);
        }
        
        IndexCoreBuffer = indexCoreBuffer;
    }

    void CreateBuffers();
    void ApplyBuffers();
    void ReleaseBuffers();

    void ActivateBufferComponent( GRAPHIC_SHADER_BIND attribute );
    static int ComputeVertexStride(GRAPHIC_SHADER_BIND bind);

    inline void SetTexture( GRAPHIC_TEXTURE * texture) { Texture = texture; }
    inline void SetNormalTexture( GRAPHIC_TEXTURE * texture) { NormalTexture = texture; }
    inline GRAPHIC_TEXTURE * GetTexture() { return Texture; }
    inline GRAPHIC_TEXTURE * GetNormalTexture() { return NormalTexture; }

    inline const GRAPHIC_MESH_POLYGON_RENDER_MODE GetPolygonRenderMode() const { return PolygonRenderMode; }
    inline const GRAPHIC_MESH_SURFACE_RENDER_MODE GetSurfaceRenderMode() const { return SurfaceRenderMode; }

    inline void SetSurfaceRenderMode( GRAPHIC_MESH_SURFACE_RENDER_MODE mode) { SurfaceRenderMode = mode; }

    inline GRAPHIC_SHADER_BIND & GetVertexComponent() { return VertexComponent; }
    inline void SetPolygonRenderMode( const GRAPHIC_MESH_POLYGON_RENDER_MODE mode ) { PolygonRenderMode = mode; }
    inline CORE_MATH_MATRIX & GetTransform() { return Transform; }
    inline const CORE_MATH_MATRIX & GetTransform() const { return Transform; }
    inline void SetTransform( const CORE_MATH_MATRIX & matrix ) { Transform = matrix; }

    inline const CORE_MATH_SHAPE & GetBoundingShape() const { return BoundingShape; }
    inline CORE_MATH_SHAPE & GetBoundingShape() { return BoundingShape; }
    inline int GetVertexStride() const { return VertexStride; }
    inline GRAPHIC_MESH_POLYGON_RENDER_MODE GetPolygonRenderMode() { return PolygonRenderMode; }

    inline char * GetName() { return MeshName; }
    inline void SetName ( const char * name ) { CORE_DATA_COPY_STRING( MeshName, name ); }

    #if __COMPILE_WITH__COLLADA__

        typedef struct{
            int vertex_index;
            float position[4];
            float Normals[4];
            float UV0[2];
            float UV1[2];
            float joint_weights[3];
            float joint_index[3];
            float tangents[3];
            float binormal[3];
        } VERTEX_ELEMENT;

        VERTEX_ELEMENT * CurrenGeometrytTable;
        int CurrenGeometrytTableSize;
    #endif

private :

    CORE_DATA_BUFFER
        * VertexCoreBuffer,
        * IndexCoreBuffer;
    GRAPHIC_TEXTURE
        * Texture,
        * NormalTexture;
    GRAPHIC_SHADER_BIND
        VertexComponent;
    GRAPHIC_MESH_POLYGON_RENDER_MODE
        PolygonRenderMode;
    GRAPHIC_MESH_SURFACE_RENDER_MODE
        SurfaceRenderMode;
    CORE_MATH_MATRIX
        Transform;
    CORE_MATH_SHAPE
        BoundingShape;
    char
        MeshName[64];
    int
        VertexStride;

// :Hold the values for specific rendering systems

#if OPENGL4
    #include "GRAPHIC_MESH_OPENGL_2.h"
#elif OPENGLES2
    #include "GRAPHIC_MESH_OES2.h"
#elif X_VK
    #include "GRAPHIC_MESH_VK.h"
#elif DX11

#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH__) */
