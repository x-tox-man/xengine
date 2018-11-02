//
//  GRAPHIC_SHADER_EFFECT_SSAO.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/07/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_SSAO.h"
#include "RESOURCE_IMAGE.h"

GRAPHIC_SHADER_EFFECT_SSAO::GRAPHIC_SHADER_EFFECT_SSAO( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT(),
    SSAOKernel(),
    SampleRad( 0.1f ),
    Camera() {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetShaderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_SSAO::~GRAPHIC_SHADER_EFFECT_SSAO() {
    
}

void GRAPHIC_SHADER_EFFECT_SSAO::BindAttributes() {
    
    GRAPHIC_SHADER_EFFECT::BindAttributes();
    
    GenerateSSAOKernel();
}

void GRAPHIC_SHADER_EFFECT_SSAO::Apply( GRAPHIC_RENDERER & renderer ) {
    
    CORE_MATH_MATRIX
        mv,
        inv,
        id;
    
    GetMaterial()->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture5, TextureBlock );
    GRAPHIC_SHADER_EFFECT::Apply( renderer );
    
    GRAPHIC_SHADER_ATTRIBUTE & ssao_kernel = Program.getShaderAttribute( GRAPHIC_SHADER_PROGRAM::SSAOKernel );
    GRAPHIC_SHADER_ATTRIBUTE & ssao_sample_rad = Program.getShaderAttribute( GRAPHIC_SHADER_PROGRAM::SSAOSampleRad );
    GRAPHIC_SHADER_ATTRIBUTE & proj = Program.getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ProjectionMatrix );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeVectorTable( SSAOKernel, SSAO_MAX_KERNEL, ssao_kernel );
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( SampleRad, ssao_sample_rad );
    
    mv = Camera->GetProjectionMatrix() * Camera->GetViewMatrix();// * inv;
    GRAPHIC_SYSTEM_ApplyMatrix(proj.AttributeIndex, 1, 1, &mv[0] );
}

void GRAPHIC_SHADER_EFFECT_SSAO::GenerateSSAOKernel() {
    
    srand( (unsigned int) clock() );
    
    for (int i = 0; i < SSAO_MAX_KERNEL; i++ ) {
        
        float scale = 1.0f - ((float)i / (float)(SSAO_MAX_KERNEL));
        scale = (0.1f + 0.9f * scale * scale);

        SSAOKernel[ i * 4 + 0 ] = ( ( ( rand() %2000) * 0.001f ) -1.0f ) * scale;
        SSAOKernel[ i * 4 + 1 ] = ( ( ( rand() %2000) * 0.001f ) -1.0f ) * scale;
        SSAOKernel[ i * 4 + 2 ] = ( ( ( rand() %2000) * 0.001f ) -1.0f ) * scale;
        SSAOKernel[ i * 4 + 3 ] = 1.0f;
    }
    float * noise = (float*) malloc( sizeof(float) * SSAO_MAX_ROTATIONS * 4);
    
    for (unsigned int i = 0; i < 16; i++)
    {
        noise[ i * 4 + 0 ] = ( ( ( rand() %2000) * 0.001f ) -1.0f );
        noise[ i * 4 + 1 ] = ( ( ( rand() %2000) * 0.001f ) -1.0f );
        noise[ i * 4 + 2 ] = ( ( ( rand() %2000) * 0.001f ) -1.0f );
        noise[ i * 4 + 3 ] = 1.0f;
    }
    
    RESOURCE_IMAGE image;
    
    image.SetImageRawData( noise );
    image.GetImageInfo().Height = 4;
    image.GetImageInfo().Width = 4;
    image.GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;
    
    Texture = image.CreateTextureObject( false );
    GRAPHIC_SYSTEM::SetTextureOptions(Texture, GRAPHIC_TEXTURE_FILTERING_Nearest, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
    TextureBlock = new GRAPHIC_TEXTURE_BLOCK( Texture );
}
