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
    
    PointDefferedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredPoint" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredPoint", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    SpotDeferredEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredSpot" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredSpot", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    AmbientDirectionalDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    AmbientDirectionalDefferedEffect->BindAttributes();
    
    PointDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    PointDefferedEffect->BindAttributes();
    
    SpotDeferredEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    SpotDeferredEffect->BindAttributes();
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
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    static int
        acc = 0;
        acc++;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    RenderTarget.BindForReading();
    
    //glEnable(GL_BLEND);
    //glBlendEquation(GL_FUNC_ADD);
    //glBlendFunc(GL_ONE, GL_ONE);
    
    glClear(GL_COLOR_BUFFER_BIT);

    TextureBlock->SetTexture( RenderTarget.GetTargetTexture( 0 ) );
    TextureBlock1->SetTexture( RenderTarget.GetTargetTexture( 1 ) );
    TextureBlock2->SetTexture( RenderTarget.GetTargetTexture( 2 ) );
    RenderTarget.SetReadBuffer( 0 );
    RenderTarget.SetReadBuffer( 1 );
    RenderTarget.SetReadBuffer( 2 );
    
    if ( (acc % 33) == 0 ) {
        
        GRAPHIC_TEXTURE * texture2 = RenderTarget.GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING1" , "png", "" ));
        texture2 = RenderTarget.GetTargetTexture( 1 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING2" , "png", "" ));
        texture2 = RenderTarget.GetTargetTexture( 2 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING3" , "png", "" ));
    }
    
    RenderTarget.Discard();
    
    FinalRenderTarget->Apply();
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock1 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture2, TextureBlock2 ) ;
    
    AmbientDirectionalDefferedEffect->SetMaterial( &Material );
    PointDefferedEffect->SetMaterial( &Material );
    SpotDeferredEffect->SetMaterial( &Material );
    
    glClearDepth( 0.0f );
    glClear( GL_DEPTH_BUFFER_BIT );
    glDisable( GL_DEPTH_TEST );
    renderer.SetLightingIsEnabled( true );
    PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, AmbientDirectionalDefferedEffect );
    /*renderer.SetDeferredLightingIsEnabled( true );
    ApplyPointLightPass( renderer );
    ApplySpotLightPass( renderer );
    renderer.SetDeferredLightingIsEnabled( false );*/
    renderer.SetLightingIsEnabled( false );
    
    if ( (acc % 33) == 0 ) {
        
        acc = 0;
        GRAPHIC_TEXTURE * texture2 = FinalRenderTarget->GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING4" , "png", "" ));
    }

    FinalRenderTarget->Discard();
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyPointLightPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    for (unsigned int i = 0 ; i < renderer.GetPointLightTable().size(); i++) {
        
        auto light = renderer.GetPointLightTable()[ i ];
        option.SetPosition( light->InternalLight.Point.Position );
        option.SetOrientation( CORE_MATH_QUATERNION() );
        
        float scale = CalculatePointLightSphereAndExtent( *light );
        
        option.SetScaleFactor(CORE_MATH_VECTOR( scale, scale, scale, 1.0f ) );
        
        renderer.SetDeferredPointIndex( i );
        SphereObject->Render( renderer, option, PointDefferedEffect );
    }
    
    renderer.SetDeferredPointIndex( -1 );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplySpotLightPass( GRAPHIC_RENDERER & renderer ) {
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    renderer.SetDeferredSpotIndex( -1 );
}

float GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::CalculatePointLightSphereAndExtent(const GRAPHIC_SHADER_LIGHT & light) {
    float MaxChannel = fmax(fmax(light.InternalLight.Point.Color[0], light.InternalLight.Point.Color[1]), light.InternalLight.Point.Color[2]);
    
    float ret = (- light.InternalLight.Point.Linear + sqrtf( light.InternalLight.Point.Linear * light.InternalLight.Point.Linear - 4 * light.InternalLight.Point.Exp * (light.InternalLight.Point.Exp - 256 * MaxChannel * light.InternalLight.Point.DiffuseIntensity)))
    /
    (2 * light.InternalLight.Point.Exp);
    
    return ret;
}
