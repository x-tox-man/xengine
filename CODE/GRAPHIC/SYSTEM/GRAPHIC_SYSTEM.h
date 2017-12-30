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
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "CORE_PARALLEL_LOCK_MUTEX.h"
#include "CORE_HELPERS_COLOR.h"

class GRAPHIC_TEXTURE;
class GRAPHIC_RENDER_TARGET;
class GRAPHIC_SHADER_LIGHT;
class GRAPHIC_SHADER_PROGRAM;
class GRAPHIC_SHADER_ATTRIBUTE;
class GRAPHIC_MESH;

XS_CLASS_BEGIN( GRAPHIC_SYSTEM )

~GRAPHIC_SYSTEM();

static void EnableScissor( bool enable );
static void SetScissorRectangle(float x, float y, float width, float height);

static void EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination );
static void DisableBlend();

static void EnableStencilTest();
static void DisableStencil();

static void EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin, float range_end );
static void DisableDepthTest();

static void EnableAlpha();
static void DisableAlpha();

static void EnableBackfaceCulling();
static void DisableFaceCulling();

static void UpdateVertexBuffer( GRAPHIC_MESH * mesh, CORE_DATA_BUFFER & data );

static void ReleaseTexture( GRAPHIC_TEXTURE * texture );

static void CreateTexture( GRAPHIC_TEXTURE * texture );
static void CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type );
static void CreateTexture( GRAPHIC_TEXTURE * texture, const void * texture_data, bool generate_mipmap );
static void CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data );
static void ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index );
static void ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index );
static void DiscardTexture( GRAPHIC_TEXTURE * texture );

static void SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode );

static void ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program );
static void ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program );
static void ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index );
static void ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index );

static void ApplyShaderAttributeVector( const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute );
static void ApplyShaderAttributeFloat( const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute );
static void ApplyShaderAttributeMatrix( const float * matrixs, GRAPHIC_SHADER_ATTRIBUTE & attribute );

static void CreateVertexBuffer( GRAPHIC_MESH & mesh );
static void CreateIndexBuffer( GRAPHIC_MESH & mesh );
static void ReleaseBuffers(GRAPHIC_MESH &mesh);
static void ApplyBuffers(GRAPHIC_MESH &mesh);
static const char * GetShaderDirectoryPath() { return ShaderDirectoryPath; }
static void SetClearColor( CORE_HELPERS_COLOR & color ) { ClearColor = color; }

static CORE_PARALLEL_LOCK_MUTEX
    GraphicSystemLock;
static const char *
    ShaderDirectoryPath;
static CORE_HELPERS_COLOR
    ClearColor;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SYSTEM__) */
