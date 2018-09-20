//
//  GRAPHIC_RENDERER_TECHNIQUE_BLOOM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE_BLOOM.h"

GRAPHIC_RENDERER_TECHNIQUE_BLOOM::GRAPHIC_RENDERER_TECHNIQUE_BLOOM() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    Material(),
    PlanObject( NULL ),
    TextureBlock( NULL ),
    TextureBlock2( NULL ),
    PrimaryRenderTarget( NULL ),
    FinalRenderTarget( NULL ),
    HorizontalBlurEffect( NULL ),
    VerticalBlurEffect( NULL ),
    CombineBloomEffect( NULL ) {
    
}
GRAPHIC_RENDERER_TECHNIQUE_BLOOM::~GRAPHIC_RENDERER_TECHNIQUE_BLOOM() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE_BLOOM::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    HorizontalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::HZBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianHorrizontalBlurPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    VerticalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::VBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianVerticalBlurPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    CombineBloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::CombineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenCombinePostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    ((GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR)BloomEffect)->BindAttributes();
    HorizontalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    HorizontalBlurEffect->BindAttributes();
    VerticalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    VerticalBlurEffect->BindAttributes();
    CombineBloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CombineBloomEffect->BindAttributes();
}

void GRAPHIC_RENDERER_TECHNIQUE_BLOOM::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    {
        Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock ) ;
        TextureBlock->SetTexture( PrimaryRenderTarget->GetTargetTexture( 0 ) );
        
        BloomEffect->SetMaterial( &Material );
        
        BloomRenderTarget->Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, BloomEffect );
        BloomRenderTarget->Discard();
    }
    
    {
        TextureBlock->SetTexture( BloomRenderTarget->GetTargetTexture( 0 ) );
        
        Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        HorizontalBlurEffect->SetMaterial( &Material );
        
        GaussianRenderTarget1->Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, HorizontalBlurEffect );
        GaussianRenderTarget1->Discard();
    }
    
    {
        TextureBlock->SetTexture( GaussianRenderTarget1->GetTargetTexture( 0 ) );
        
        Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        VerticalBlurEffect->SetMaterial( &Material );
        
        GaussianRenderTarget2->Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, VerticalBlurEffect );
        GaussianRenderTarget2->Discard();
    }
    
    {
        TextureBlock->SetTexture( PrimaryRenderTarget->GetTargetTexture( 0 ) );
        TextureBlock2->SetTexture( GaussianRenderTarget2->GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock2 );
        CombineBloomEffect->SetMaterial( mat );
        
        FinalRenderTarget->Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, CombineBloomEffect );
        FinalRenderTarget->Discard();
        
        delete mat;
    }
}

void GRAPHIC_RENDERER_TECHNIQUE_BLOOM::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
}
