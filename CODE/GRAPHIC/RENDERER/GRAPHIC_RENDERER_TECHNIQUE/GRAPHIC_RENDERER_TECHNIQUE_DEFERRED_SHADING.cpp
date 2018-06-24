//
//  GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.h"

GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    Material(),
    PlanObject( NULL ),
    TextureBlock( NULL ),
    TextureBlock1( NULL ),
    TextureBlock2( NULL ),
    RenderTarget(),
    FinalRenderTarget( NULL ),
    AmbientDirectionalDefferedEffect( NULL ),
    SpotDeferredEffect( NULL ),
    PointDefferedEffect( NULL ) {
    
}

GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::~GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    RenderTarget.Initialize(renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 3, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_Write);
    
    AmbientDirectionalDefferedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredAmbiantAndDirectionnal" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredAmbiantAndDirectionnal", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    AmbientDirectionalDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    AmbientDirectionalDefferedEffect->BindAttributes();
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    renderer.GetCamera()->ActivateForRender();
    renderer.SetLightingIsEnabled( false );
    glClearDepth( 0.0f );
    glClear( GL_DEPTH_BUFFER_BIT );
    RenderTarget.BindForWriting();
    RenderTarget.Apply();
    RendererCallback( renderer );
    renderer.SetLightingIsEnabled( true );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    static int acc = 0;
    
    acc++;
    
    RenderTarget.BindForReading();
    
    if ( (acc % 33) == 0 ) {
     
        RenderTarget.SetReadBuffer( 0 );
        GRAPHIC_TEXTURE * texture2 = RenderTarget.GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING1" , "png", "" ));
        
        RenderTarget.SetReadBuffer( 1 );
        texture2 = RenderTarget.GetTargetTexture( 1 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING2" , "png", "" ));
        
        RenderTarget.SetReadBuffer( 2 );
        texture2 = RenderTarget.GetTargetTexture( 2 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING3" , "png", "" ));
     }
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );

    TextureBlock->SetTexture( RenderTarget.GetTargetTexture( 0 ) );
    TextureBlock1->SetTexture( RenderTarget.GetTargetTexture( 1 ) );
    TextureBlock2->SetTexture( RenderTarget.GetTargetTexture( 2 ) );
    RenderTarget.Discard();
    
    FinalRenderTarget->Apply();
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock1 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture2, TextureBlock2 ) ;
    
    AmbientDirectionalDefferedEffect->SetMaterial( &Material );
    
    glClearDepth( 0.0f );
    glClear( GL_DEPTH_BUFFER_BIT );
    glDisable( GL_DEPTH_TEST );
    renderer.SetLightingIsEnabled( true );
    PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, AmbientDirectionalDefferedEffect );
    renderer.SetLightingIsEnabled( false );
    
    if ( (acc % 33) == 0 ) {
        
        acc = 0;
        GRAPHIC_TEXTURE * texture2 = FinalRenderTarget->GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING4" , "png", "" ));
    }

    FinalRenderTarget->Discard();
}

