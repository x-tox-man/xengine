//
//  GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 25/10/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"

GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT() {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetSahderBind();
    Material = effect->GetMaterial();
}

GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::~GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR() {

}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::SampleOffsetsIdentifier( "SampleOffsets" ),
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::SampleWeightsIdentifier( "SampleWeights" );
