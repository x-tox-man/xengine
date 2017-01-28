//
//  GRAPHIC_OBJECT_SHAPE_FRAME.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_FRAME__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_FRAME__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_SHADER_BIND.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE_FRAME, GRAPHIC_OBJECT_SHAPE)

GRAPHIC_OBJECT_SHAPE_FRAME();

virtual void InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader );
virtual void Render( const GRAPHIC_RENDERER & renderer );

void SetBorderSize( const float boder_width, const float boder_height ) {
    BorderWidth = boder_width;
    BorderHeight = boder_height;
}

private :

void UpdateFrameVertexData( float * vertex_data, const GRAPHIC_TEXTURE_BLOCK & block );
void CreateVertexData();
float
    * VertexData;
float
    BorderWidth,
    BorderHeight;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_FRAME__) */
