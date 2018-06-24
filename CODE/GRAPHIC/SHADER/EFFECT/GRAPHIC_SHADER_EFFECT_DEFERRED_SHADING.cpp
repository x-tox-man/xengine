//
//  GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING.h"

GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING::GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT() {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetShaderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING::~GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING() {
    
}

void GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING::Apply( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer );
}

void GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING::BindAttributes() {
    
    GRAPHIC_SHADER_EFFECT::BindAttributes();
}
