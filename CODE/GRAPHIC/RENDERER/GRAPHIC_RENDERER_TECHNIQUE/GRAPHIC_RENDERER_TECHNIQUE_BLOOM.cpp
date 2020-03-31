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
    BlurPassCount( 1 ),
    Material(),
    PlanObject( NULL ),
    TextureBlock( NULL ),
    TextureBlock2( NULL ),
    PrimaryRenderTarget( NULL ),
    HorizontalBlurEffect( NULL ),
    VerticalBlurEffect( NULL ),
    CombineBloomEffect( NULL ) {
    
    for (int i = 0; i < GRAPHIC_RENDERER_TECHNIQUE_BLOOM_MAX_BLUR; i++ ) {
        
        GaussianRenderTarget1Table[ i ] = NULL;
        GaussianRenderTarget2Table[ i ] = NULL;
    }
}

GRAPHIC_RENDERER_TECHNIQUE_BLOOM::~GRAPHIC_RENDERER_TECHNIQUE_BLOOM() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE_BLOOM::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    HorizontalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::HZBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianHorrizontalBlurPostProcess" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    VerticalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::VBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianVerticalBlurPostProcess" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    CombineBloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::CombineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenCombinePostProcess" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    ((GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR)BloomEffect)->BindAttributes();
    HorizontalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    HorizontalBlurEffect->BindAttributes();
    VerticalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    VerticalBlurEffect->BindAttributes();
    CombineBloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CombineBloomEffect->BindAttributes();

    // -- BEGIN OF SPECIFIC METAL CODE
    //GaussianRenderTarget2Table[0]->SetTextureLoadMode( GRAPHIC_STEXTURE_LOAD_MODE_Keep );
    // -- END OF SPECIFIC METAL CODE
    
    renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    
    GaussianRenderTarget2Table[0]->EnableTextureBlending();

    //VerticalBlurEffect->EnableBlending( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
}

void GRAPHIC_RENDERER_TECHNIQUE_BLOOM::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    renderer.DisableDepthTest();
    
    GaussianRenderTarget2Table[0]->Clear();
    
    {
        PrimaryRenderTarget->BindForReading();
        PrimaryRenderTarget->SetReadBuffer( 0 );
        
        
        /*{
            static int acc = 0;
            acc++;
            
            if ( acc % 30 == 0 ) {
                
                acc = 0;
                
                GRAPHIC_TEXTURE * texture2 = PrimaryRenderTarget->GetTargetTexture( 0 );
                //texture2->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "GRAPHIC_RENDER_TECHNIQUE_BeforeBloom", "png", "" ) );
            }
        }*/
        
        TextureBlock->SetTexture( PrimaryRenderTarget->GetTargetTexture( 0 ) );
        Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock ) ;
        
        BloomEffect->SetMaterial( &Material );
        
        BloomRenderTarget->BindForWriting();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, BloomEffect );
        BloomRenderTarget->Discard();
        
        /*{
            static int acc = 0;
            acc++;
            
            if ( acc % 30 == 0 ) {
                
                acc = 0;
                
                BloomRenderTarget->BindForReading();
                BloomRenderTarget->SetReadBuffer( 0 );
                
                GRAPHIC_TEXTURE * texture2 = BloomRenderTarget->GetTargetTexture( 0 );
                //texture2->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "GRAPHIC_RENDER_TECHNIQUE_Bloom", "png", "" ) );
            }
        }*/
    }
    
    for (int blur_pass_index = BlurPassCount -1; blur_pass_index >= 0; blur_pass_index-- ) {
        
        {
            BloomRenderTarget->BindForReading();
            BloomRenderTarget->SetReadBuffer( 0 );
            TextureBlock->SetTexture( BloomRenderTarget->GetTargetTexture( 0 ) );
            
            Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
            HorizontalBlurEffect->SetMaterial( &Material );
            HorizontalBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeValue.Value.FloatArray2[0] = (blur_pass_index + 1) * (blur_pass_index + 1 );
            HorizontalBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeValue.Value.FloatArray2[1] = (blur_pass_index + 1) * (blur_pass_index + 1 );
            
            GaussianRenderTarget1Table[blur_pass_index]->BindForWriting();
            PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, HorizontalBlurEffect );
            
            /*{
                static int acc = 0;
                acc++;

                if ( acc % 30 == 0 ) {

                     acc = 0;

                     GaussianRenderTarget1Table[blur_pass_index]->BindForReading();
                     GaussianRenderTarget1Table[blur_pass_index]->SetReadBuffer( 0 );

                     GRAPHIC_TEXTURE * texture2 = GaussianRenderTarget1Table[blur_pass_index]->GetTargetTexture( 0 );
                     //texture2->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "GRAPHIC_RENDER_TECHNIQUE_Gaussian", "png", "" ) );
                }
            }*/
            GaussianRenderTarget1Table[blur_pass_index]->Discard();
        }
        
        {
            GaussianRenderTarget1Table[blur_pass_index]->BindForReading();
            GaussianRenderTarget1Table[blur_pass_index]->SetReadBuffer( 0 );
            TextureBlock->SetTexture( GaussianRenderTarget1Table[blur_pass_index]->GetTargetTexture( 0 ) );
            
            Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
            VerticalBlurEffect->SetMaterial( &Material );
            VerticalBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeValue.Value.FloatArray2[0] = (blur_pass_index + 1) * (blur_pass_index + 1 );
            VerticalBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeValue.Value.FloatArray2[1] = (blur_pass_index + 1) * (blur_pass_index + 1 );
            
            GaussianRenderTarget2Table[0]->BindForWriting();
            PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, VerticalBlurEffect );
            
            /*{
                static int acc = 0;
                acc++;
                
                if ( acc % 30 == 0 ) {
                    
                    acc = 0;
                    
                    GaussianRenderTarget2Table[blur_pass_index]->BindForReading();
                    GaussianRenderTarget2Table[blur_pass_index]->SetReadBuffer( 0 );
                    
                    GRAPHIC_TEXTURE * texture2 = GaussianRenderTarget2Table[blur_pass_index]->GetTargetTexture( 0 );
                    //texture2->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "GRAPHIC_RENDER_TECHNIQUE_Gaussian2", "png", "" ) );
                }
            }*/
            GaussianRenderTarget2Table[0]->Discard();
        }
    }
    
    {
        PrimaryRenderTarget->BindForReading();
        GaussianRenderTarget2Table[0]->BindForReading();
        
        TextureBlock->SetTexture( PrimaryRenderTarget->GetTargetTexture( 0 ) );
        TextureBlock2->SetTexture( GaussianRenderTarget2Table[0]->GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock2 );
        CombineBloomEffect->SetMaterial( mat );
        
        if ( FinalRenderTarget != NULL )
            FinalRenderTarget->BindForWriting();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, CombineBloomEffect );
        
        if ( FinalRenderTarget != NULL )
            FinalRenderTarget->Discard();
        
        delete mat;
    }
}

void GRAPHIC_RENDERER_TECHNIQUE_BLOOM::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
}
