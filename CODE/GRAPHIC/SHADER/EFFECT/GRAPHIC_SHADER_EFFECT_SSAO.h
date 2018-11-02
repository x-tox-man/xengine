//
//  GRAPHIC_SHADER_EFFECT_SSAO.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/07/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_EFFECT_SSAO_hpp
#define GRAPHIC_SHADER_EFFECT_SSAO_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_CAMERA.h"

#define SSAO_MAX_KERNEL     128
#define SSAO_MAX_ROTATIONS  16

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT_SSAO, GRAPHIC_SHADER_EFFECT )

    GRAPHIC_SHADER_EFFECT_SSAO( GRAPHIC_SHADER_EFFECT::PTR effect );
    virtual ~GRAPHIC_SHADER_EFFECT_SSAO();

    virtual void Apply( GRAPHIC_RENDERER & ) override;
    virtual void BindAttributes() override;

    inline void SetSampleRad( float rad ) { SampleRad = rad; }
    inline void SetCamera( GRAPHIC_CAMERA::PTR camera ) { Camera = camera; }

private:

    void GenerateSSAOKernel();

    float
        SSAOKernel[ SSAO_MAX_KERNEL * 4 ],
        SampleRad;
    GRAPHIC_CAMERA::PTR
        Camera;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock;
    GRAPHIC_TEXTURE::PTR
        Texture;

XS_CLASS_END

#endif /* GRAPHIC_SHADER_EFFECT_SSAO_hpp */
