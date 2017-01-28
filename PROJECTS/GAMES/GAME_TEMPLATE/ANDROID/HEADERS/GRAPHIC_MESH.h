//
//  GRAPHIC_MESH.h
//  GAME-ENGINE-REBORN
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
#include "GRAPHIC_MESH_POLYGON_RENDER_MODE.h"
#include "GRAPHIC_MESH_SURFACE_RENDER_MODE.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH )

public:

    XS_DEFINE_SERIALIZABLE

    GRAPHIC_MESH();

    CORE_DATA_BUFFER & getVertexCoreBuffer() { return *VertexCoreBuffer; }
    void setVertexCoreBuffer( CORE_DATA_BUFFER * vertexCoreBuffer ) { VertexCoreBuffer = vertexCoreBuffer; }

    CORE_DATA_BUFFER & getIndexCoreBuffer() { return *IndexCoreBuffer; }
    void setIndexCoreBuffer( CORE_DATA_BUFFER * indexCoreBuffer ) { IndexCoreBuffer = indexCoreBuffer; }

    void CreateBuffers();
    void ApplyBuffers();
    void ReleaseBuffers();
    void ActivateBufferComponent( GRAPHIC_SHADER_BIND attribute );

    void SetTexture( GRAPHIC_TEXTURE * texture) { Texture = texture; }
    GRAPHIC_TEXTURE * GetTexture() { return Texture; }

    const GRAPHIC_MESH_POLYGON_RENDER_MODE GetPolygonRenderMode() const { return PolygonRenderMode; }
    const GRAPHIC_MESH_SURFACE_RENDER_MODE GetSurfaceRenderMode() const { return SurfaceRenderMode; }

    GRAPHIC_SHADER_BIND & GetVertexComponent() { return VertexComponent; }
    void SetPolygonRenderMode( const GRAPHIC_MESH_POLYGON_RENDER_MODE mode ) { PolygonRenderMode = mode; }

private :

    CORE_DATA_BUFFER * VertexCoreBuffer;
    CORE_DATA_BUFFER * IndexCoreBuffer;

    GRAPHIC_TEXTURE * Texture;

    GRAPHIC_SHADER_BIND VertexComponent;

    GRAPHIC_MESH_POLYGON_RENDER_MODE PolygonRenderMode;
    GRAPHIC_MESH_SURFACE_RENDER_MODE SurfaceRenderMode;

    int VertexStride;

// :Hold the values for specific rendering systems

#if OPENGL2PLUS
    #include "GRAPHIC_MESH_OPENGL2.h"
#elif OPENGLES2
    #include "GRAPHIC_MESH_OPENGLES2.h"
#elif DX11

#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH__) */
