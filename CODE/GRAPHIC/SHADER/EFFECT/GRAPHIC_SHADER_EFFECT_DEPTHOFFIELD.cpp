//
//  GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD::GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD() {
    
}

GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD::~GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD() {

}


void GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD::Apply( GRAPHIC_RENDERER & renderer, bool does_lighting, bool does_texturing ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer, does_lighting, does_texturing );
}
