//
//  GRAPHIC_RENDER_TECHNIQUE_SSAO.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/07/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDER_TECHNIQUE_SSAO.h"

GRAPHIC_RENDER_TECHNIQUE_SSAO::GRAPHIC_RENDER_TECHNIQUE_SSAO() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    Material(),
    MaterialBlur(),
    PlanObject( NULL ),
    TextureBlock1( NULL ),
    SourceRenderTarget( NULL ),
    SSAOEffect( NULL ),
    SimpleBlurEffect( NULL ) {
    
}

GRAPHIC_RENDER_TECHNIQUE_SSAO::~GRAPHIC_RENDER_TECHNIQUE_SSAO() {
    
}

void GRAPHIC_RENDER_TECHNIQUE_SSAO::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    //SSAOEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SSAOEffect" ), CORE_FILESYSTEM_PATH::FindFilePath( "SSAOEffect", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    SSAOEffect = new GRAPHIC_SHADER_EFFECT_SSAO( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SSAOEffect"), CORE_FILESYSTEM_PATH::FindFilePath( "SSAOEffect" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    SSAOEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    SimpleBlurEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SimpleBlur"), CORE_FILESYSTEM_PATH::FindFilePath( "SimpleBlur" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    SimpleBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    SimpleBlurEffect->BindAttributes();
}

void GRAPHIC_RENDER_TECHNIQUE_SSAO::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    RenderTarget->BindForWriting();
    
    SourceRenderTarget->BindForReading();
    SourceRenderTarget->SetReadBuffer( 0 );
    renderer.SetLightingIsEnabled( false );
    TextureBlock1 = new GRAPHIC_TEXTURE_BLOCK();
    TextureBlock1->SetTexture( SourceRenderTarget->GetTargetTexture( 0 ) );
    
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock1 ) ;
    SSAOEffect->SetMaterial( &Material );

    
    PlanObject->Render( renderer, option, SSAOEffect );
    
    RenderTarget->Discard();
    SourceRenderTarget->Discard();

    {
        RenderTarget->BindForReading();
        RenderTarget->SetReadBuffer( 0 );
        TextureBlock1->SetTexture( RenderTarget->GetTargetTexture( 0 ) );
        MaterialBlur.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock1 );
        SimpleBlurEffect->SetMaterial( &MaterialBlur );
        
        {
            static int acc = 0;
            acc++;
            
            if ( acc % 30 == 0 ) {
                
                acc = 0;

                GRAPHIC_TEXTURE * texture2 = RenderTarget->GetTargetTexture( 0 );
                texture2->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "GRAPHIC_RENDER_TECHNIQUE_SSAO2", "png", "" ) );
            }
        }
        
        FinalRenderTarget->BindForWriting();
        GRAPHIC_SYSTEM::DisableBlend();

        GRAPHIC_SYSTEM::DisableDepthTest();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, SimpleBlurEffect );
        
        FinalRenderTarget->BindForReading();
        FinalRenderTarget->SetReadBuffer( 4 );
        
        {
            static int acc = 0;
            acc++;
            
            if ( acc % 30 == 0 ) {
                
                acc = 0;
                
                GRAPHIC_TEXTURE * texture2 = FinalRenderTarget->GetTargetTexture( 4 );
                texture2->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "GRAPHIC_RENDER_TECHNIQUE_SSAO4", "png", "" ) );
            }
        }
        
        RenderTarget->Discard();
        FinalRenderTarget->Discard();
    }
    
    renderer.SetLightingIsEnabled( true );
}

void GRAPHIC_RENDER_TECHNIQUE_SSAO::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    
}
