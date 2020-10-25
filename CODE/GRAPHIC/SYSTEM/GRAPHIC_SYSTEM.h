//
//  GRAPHIC_SYSTEM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SYSTEM__
#define __GAME_ENGINE_REBORN__GRAPHIC_SYSTEM__

#include "CORE_HELPERS_CLASS.h"

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_COMPARE_OPERATION.h"
#include "GRAPHIC_SYSTEM_BLEND_OPERATION.h"
#include "GRAPHIC_SYSTEM_POLYGON_FILL_MODE.h"
#include "GRAPHIC_POLYGON_FACE.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "CORE_PARALLEL_LOCK_MUTEX.h"
#include "CORE_HELPERS_COLOR.h"
#include "GRAPHIC_TEXTURE_FILTERING.h"
#include "GRAPHIC_TEXTURE_WRAP.h"
#include "GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE.h"
#include "GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION.h"
#include "GRAPHIC_SYSTEM_BLEND_EQUATION.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"

class GRAPHIC_TEXTURE;
class GRAPHIC_RENDER_TARGET;
class GRAPHIC_SHADER_LIGHT;
class GRAPHIC_SHADER_PROGRAM;
class GRAPHIC_SHADER_ATTRIBUTE;
class GRAPHIC_MESH;
class GRAPHIC_RENDERER;
class GRAPHIC_MATERIAL;

XS_CLASS_BEGIN( GRAPHIC_SYSTEM )

    ~GRAPHIC_SYSTEM();

    static void Initialize( const char * app_name, int app_version );
    static void Finalize();

    static void EnableScissor( bool enable, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );
    static void SetScissorRectangle(float x, float y, float width, float height, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );

    static void EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );
    static void DisableBlend( void * __GRAPHIC_SYSTEM_CONTEXT = NULL);
    static void SetBlendFunction( const GRAPHIC_SYSTEM_BLEND_EQUATION equation, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );

    static void EnableStencilTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, int ref, unsigned int mask, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );
    static void DisableStencil( void * __GRAPHIC_SYSTEM_CONTEXT = NULL );
    static void SetStencilOperation( const GRAPHIC_POLYGON_FACE face, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_fail, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_pass, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_and_depth_fail, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );

    static void EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin = 0.0f, float range_end = 1.0f, void * __GRAPHIC_SYSTEM_CONTEXT = NULL );
    static void DisableDepthTest( void * __GRAPHIC_SYSTEM_CONTEXT = NULL );

    static void EnableAlpha( void * __GRAPHIC_SYSTEM_CONTEXT = NULL );
    static void DisableAlpha( void * __GRAPHIC_SYSTEM_CONTEXT = NULL );

    static void EnableBackfaceCulling( const GRAPHIC_POLYGON_FACE face );
    static void DisableFaceCulling();

    static void UpdateVertexBuffer( GRAPHIC_MESH * mesh, CORE_DATA_BUFFER & data );

    static void ReleaseTexture( GRAPHIC_TEXTURE * texture );

    static void CreateTexture( GRAPHIC_TEXTURE * texture );
    static void CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type );
    static void CreateTexture( GRAPHIC_TEXTURE * texture, CORE_DATA_BUFFER & texture_data, bool generate_mipmap );
    static void CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data );
    static void ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index );
    static void ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index );
    static void DiscardTexture( GRAPHIC_TEXTURE * texture );
    static void SetTextureOptions( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_FILTERING filtering, GRAPHIC_TEXTURE_WRAP wrap, const CORE_HELPERS_COLOR & color );

    static void CreateFrameBuffer( GRAPHIC_RENDER_TARGET * target, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode );
    static void CreateDepthBuffer( GRAPHIC_RENDER_TARGET * target, int width, int height );

    static void SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode );

    static void ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program );
    static void ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program );
    static void ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index );
    static void ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index );

    static void ApplyShaderAttributeVector( GRAPHIC_RENDERER & renderer, const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute );
    static void ApplyShaderAttributeVectorTable( GRAPHIC_RENDERER & renderer, const float * vector, int size, GRAPHIC_SHADER_ATTRIBUTE & attribute );
    static void ApplyShaderAttributeFloat( GRAPHIC_RENDERER & renderer, const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute );
    static void ApplyShaderAttributeMatrix( GRAPHIC_RENDERER & renderer, const float * matrixs, GRAPHIC_SHADER_ATTRIBUTE & attribute );

    static void CreateVertexBuffer( GRAPHIC_MESH & mesh );
    static void CreateIndexBuffer( GRAPHIC_MESH & mesh );
    static void ReleaseBuffers(GRAPHIC_MESH &mesh);
    static void ApplyBuffers( GRAPHIC_RENDERER & renderer, GRAPHIC_MESH &mesh);
    static const char * GetShaderDirectoryPath() { return ShaderDirectoryPath; }
    static void SetClearColor( CORE_HELPERS_COLOR & color ) { ClearColor = color; }

    static void Clear();
    static void ClearFrambufferDepth( float default_depth );
    static void ClearFrambufferColor();
    static void ClearFrambufferStencil();

    static void BeginRendering();
    static void EndRendering();

    static void EnableDefaultFrameBuffer();
    static void DisableDefaultFrameBuffer();

    static void ApplyMaterial( const GRAPHIC_MATERIAL & material );

    // TODO: Remove this hack
    static bool RendersOnScreen() { return ItRenderOnScreen; }
    static void SetRendersOnScreen( bool on_screen ) { ItRenderOnScreen = on_screen; }

#if X_METAL

    static void BeginMtlFrame();
    static void EndMtlFrame();
    static void * CreateMtlVertexDescriptor( GRAPHIC_SHADER_BIND bind);
    static void * CreateMetalFunction( const char * function_name );
    static void InitializeMetal( void * view );
    static void * GetMtlView();
    static void * CreateMetalPipelineState( void * descriptor, GRAPHIC_SHADER_PROGRAM & program );
    static void EnableMtlPipelineState( void * pipeline_state );
    static void * CreateMetalDynamicUniformBuffer( unsigned long size );
    static void EnableMtlUniforms( void * buffer, uint32_t offset, uint32_t size );
    static void * GetMtlBufferPointer( void * buffer );
    static void * CreateMtlTextureFromDescriptor( void * descriptor );
    static void * CreateMtlRenderEncoder( void * descriptor );
    static void MtlReleasePipelineState( void * state );
    static void * GetCachedStateFromRenderer( GRAPHIC_RENDERER &, GRAPHIC_SHADER_PROGRAM * );
    static void * MtlGetCachedStencilStateFromRenderer( GRAPHIC_RENDERER & );
#endif

    static CORE_PARALLEL_LOCK_MUTEX
        GraphicSystemLock;
    static const char *
        ShaderDirectoryPath;
    static CORE_HELPERS_COLOR
        ClearColor;
    static bool
        ItRenderOnScreen;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SYSTEM__) */
