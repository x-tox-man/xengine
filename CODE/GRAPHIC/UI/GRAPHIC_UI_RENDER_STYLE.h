//
//  GRAPHIC_UI_RENDER_STYLE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__
#define __GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_UI_PLACEMENT.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_HELPERS_COLOR.h"

XS_CLASS_BEGIN( GRAPHIC_UI_RENDER_STYLE )

    GRAPHIC_UI_RENDER_STYLE();
    GRAPHIC_UI_RENDER_STYLE( GRAPHIC_OBJECT_SHAPE * shape, GRAPHIC_SHADER_EFFECT * effect, const CORE_HELPERS_COLOR & color = CORE_COLOR_White, GRAPHIC_OBJECT_SHAPE * decorating_shape = NULL, GRAPHIC_SHADER_EFFECT * decorating_effect = NULL );
    ~GRAPHIC_UI_RENDER_STYLE();

    void Apply( GRAPHIC_RENDERER & renderer, const GRAPHIC_UI_PLACEMENT & placement );

    inline void SetShape( GRAPHIC_OBJECT_SHAPE * shape ) { Shape = shape; }
    inline void SetDecoratingShape( GRAPHIC_OBJECT_SHAPE * shape ) { DecoratingShape = shape; }

    inline void SetEffect( GRAPHIC_SHADER_EFFECT * effect ) { Effect = effect; }
    inline void SetDecoratingEffect( GRAPHIC_SHADER_EFFECT * effect ) { DecoratingEffect = effect; }

    inline void SetMaterial( GRAPHIC_MATERIAL * material ) { Material = material; }
    inline void SetDecoratingMaterial( GRAPHIC_MATERIAL * material ) { DecoratingMaterial = material; }

    inline GRAPHIC_MATERIAL * GetMaterial() { return Material; }
    inline const GRAPHIC_MATERIAL * GetMaterial() const { return Material; }

    inline GRAPHIC_MATERIAL * GetDecoratingMaterial() { return DecoratingMaterial; }
    inline const GRAPHIC_MATERIAL * GetDecoratingMaterial() const { return DecoratingMaterial; }

    inline GRAPHIC_OBJECT * GetShape() { return Shape; }
    inline GRAPHIC_OBJECT * GetDecoratingShape() { return DecoratingShape; }

    inline GRAPHIC_SHADER_EFFECT * GetEffect() { return Effect; }
    inline GRAPHIC_SHADER_EFFECT * GetDecoratingEffect() { return DecoratingEffect; }

private :

    GRAPHIC_MATERIAL
        * Material,
        * DecoratingMaterial;
    GRAPHIC_SHADER_EFFECT
        * Effect,
        * DecoratingEffect;
    GRAPHIC_OBJECT_SHAPE
        * Shape,
        * DecoratingShape;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_RENDER_STYLE__) */
