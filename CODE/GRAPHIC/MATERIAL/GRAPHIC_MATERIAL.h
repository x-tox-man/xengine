//
//  GRAPHIC_MATERIAL.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MATERIAL_h
#define GRAPHIC_MATERIAL_h

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"

XS_CLASS_BEGIN( GRAPHIC_MATERIAL )

GRAPHIC_MATERIAL();
~GRAPHIC_MATERIAL();

GRAPHIC_MATERIAL(const char * image_path, const char * effect_name, const GRAPHIC_SHADER_BIND bind);

void Apply( GRAPHIC_RENDERER & renderer );
void Discard( GRAPHIC_RENDERER & renderer );

GRAPHIC_TEXTURE_BLOCK * GetTexture() {return Texture; }
void SetTexture( GRAPHIC_TEXTURE_BLOCK * texture ) {Texture = texture; }

GRAPHIC_SHADER_EFFECT * GetEffect() {return Effect; }
void SetEffect( GRAPHIC_SHADER_EFFECT * effect ) {Effect = effect; }

private:

GRAPHIC_TEXTURE_BLOCK * Texture;
GRAPHIC_SHADER_EFFECT * Effect;

XS_CLASS_END

#endif /* GRAPHIC_MATERIAL_hpp */
