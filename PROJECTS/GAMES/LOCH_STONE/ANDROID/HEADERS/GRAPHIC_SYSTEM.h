//
//  GRAPHIC_SYSTEM.h
//  GAME-ENGINE-REBORN
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

class GRAPHIC_TEXTURE;

XS_CLASS_BEGIN( GRAPHIC_SYSTEM )

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

static void CreateTexture( GRAPHIC_TEXTURE * texture, void * texture_data );
static void ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index );
static void DiscardTexture( GRAPHIC_TEXTURE * texture );

static void SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SYSTEM__) */
