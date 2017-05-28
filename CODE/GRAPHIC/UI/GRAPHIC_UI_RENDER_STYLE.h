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
#include "CORE_HELPERS_COLOR.h"

XS_CLASS_BEGIN( GRAPHIC_UI_RENDER_STYLE )

    GRAPHIC_UI_RENDER_STYLE();
    GRAPHIC_UI_RENDER_STYLE( GRAPHIC_OBJECT_SHAPE * shape, GRAPHIC_SHADER_EFFECT * effect, const CORE_HELPERS_COLOR & color, GRAPHIC_OBJECT_SHAPE * decorating_shape = NULL, GRAPHIC_SHADER_EFFECT * decorating_effect = NULL );
    ~GRAPHIC_UI_RENDER_STYLE();

    void Apply( GRAPHIC_RENDERER & renderer, const GRAPHIC_UI_PLACEMENT & placement, float opacity );

    inline void SetShape( GRAPHIC_OBJECT_SHAPE * shape ) { Shape = shape; }
    inline void SetDecoratingShape( GRAPHIC_OBJECT_SHAPE * shape ) { DecoratingShape = shape; }

    inline void SetEffect( GRAPHIC_SHADER_EFFECT * effect ) { Effect = effect; }
    inline void SetDecoratingEffect( GRAPHIC_SHADER_EFFECT * effect ) { DecoratingEffect = effect; }

    void SetColor( const CORE_HELPERS_COLOR & color ) { Color = color; }

    inline GRAPHIC_OBJECT * GetShape() { return Shape; }
    inline GRAPHIC_OBJECT * GetDecoratingShape() { return DecoratingShape; }

    inline GRAPHIC_SHADER_EFFECT * GetEffect() { return Effect; }
    inline GRAPHIC_SHADER_EFFECT * GetDecoratingEffect() { return DecoratingEffect; }

private :

    CORE_HELPERS_COLOR
        Color;
    GRAPHIC_SHADER_EFFECT
        * Effect,
        * DecoratingEffect;
    GRAPHIC_OBJECT_SHAPE
        * Shape,
        * DecoratingShape;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__) */
