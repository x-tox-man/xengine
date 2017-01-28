//
//  GRAPHIC_UI_RENDER_STYLE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__
#define __GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_UI_PLACEMENT.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"

XS_CLASS_BEGIN( GRAPHIC_UI_RENDER_STYLE )

GRAPHIC_UI_RENDER_STYLE();

void Apply( const GRAPHIC_RENDERER & renderer, const GRAPHIC_UI_PLACEMENT & placement );

void SetShape( GRAPHIC_OBJECT_SHAPE * shape ) { Shape = shape; }
void SetColor( const CORE_MATH_VECTOR & color ) { Color = color; }
void SetTextureBlock( GRAPHIC_TEXTURE_BLOCK * texture_block ) { TextureBlock = texture_block; }

GRAPHIC_OBJECT * GetShape() { return Shape; }
const CORE_MATH_VECTOR & GetColor() { return Color; }
GRAPHIC_TEXTURE_BLOCK * GetTextureBlock( GRAPHIC_TEXTURE_BLOCK * texture_block ) { return TextureBlock; }
const GRAPHIC_TEXTURE_BLOCK * GetTextureBlock() const { return TextureBlock; }

private :

CORE_MATH_VECTOR
    Color;
GRAPHIC_OBJECT_SHAPE
    * Shape;
GRAPHIC_TEXTURE_BLOCK
    * TextureBlock;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__) */
