//
//  R3D_RENDER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_RENDER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "TOOLS_DEBUG_DRAW.h"
#include "APPLICATION_CONFIGURATION.h"
#include "APPLICATION_IDENTITY_MANAGER.h"

R3D_RENDER::R3D_RENDER() :
    Lookat(),
    Camera( NULL ),
    RenderTargetCamera( NULL ),
    InterfaceCamera( NULL ),
    Directional(),
    Ambient(),
    PlanObject(),
    SphereObject( 5 ),
    PrimaryRenderTarget(),
    FinalRenderTarget(),
    LightRenderTarget(),
    SpecularRenderTarget(),
    BloomRenderTarget(),
    ShadowMapRenderTarget1(),
    ShadowMapRenderTarget2(),
    ShadowMapRenderTarget3(),
    TextureBlock1( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock2( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock3( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock4( new GRAPHIC_TEXTURE_BLOCK() ),
    SpeedBlurTechnique(),
    BloomTechnique(),
    CascadeShadowMapTechnique(),
    DeferredShadingTechnique(),
    SSAOTechnique() {
    
}

void R3D_RENDER::Initialize() {
    
    CORE_MATH_VECTOR
        position(0.0f, 0.0f, 1.0f, 1.0f);
    CORE_MATH_QUATERNION
        render_target_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    auto Window = &R3D_APP_PTR->GetApplicationWindow();
    GRAPHIC_RENDERER::GetInstance().Resize( Window->GetWidth(), Window->GetHeight() );
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 150.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), position, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight() ) );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f, -2.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    CORE_MATH_MATRIX
        m;
    
    m.XRotate( -M_PI_4 );
    m.YRotate( -M_PI_4 );
    
    Directional.InitializeDirectional( CORE_MATH_VECTOR(1.0f, 1.0f, 1.0f, 1.0f), CORE_MATH_VECTOR::ZAxis * m, 1.0f, 1.0f);
    Ambient.InitializeAmbient(CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), 1.0f, 1.0f );
    
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( &Directional );
    
    int divider = APPLICATION_CONFIGURATION_OPTIONS::GetInstance().GetGraphicsOptionRenderTargetResolutionDivider();
    
    PrimaryRenderTarget.Initialize( Window->GetWidth() / divider, Window->GetHeight() / divider, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
#if OPENGL4
    
    BloomRenderTarget.Initialize( Window->GetWidth() / 1, Window->GetHeight() / 1, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    ShadowMapRenderTarget1.InitializeDepthTexture( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    ShadowMapRenderTarget2.InitializeDepthTexture( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    ShadowMapRenderTarget3.InitializeDepthTexture( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
#endif
    
    PrimaryRenderTarget.Discard();
    
#if OPENGL4
    BloomRenderTarget.Discard();
    FinalRenderTarget.Discard();
    ShadowMapRenderTarget1.Discard();
    ShadowMapRenderTarget2.Discard();
    ShadowMapRenderTarget3.Discard();
#endif
    
    PlanObject.InitializeShape();
    SphereObject.InitializeShape();
    
    SpeedBlurTechnique.PlanObject = &PlanObject;
    SpeedBlurTechnique.TextureBlock = TextureBlock1;
    SpeedBlurTechnique.TextureBlock2 = TextureBlock2;
    SpeedBlurTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    SpeedBlurTechnique.FinalRenderTarget = &FinalRenderTarget;
    SpeedBlurTechnique.RendererCallback.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderOpaqueScene>, this );
    SpeedBlurTechnique.RendererCallback1.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderOpaqueScene>, this );
    SpeedBlurTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    BloomTechnique.PlanObject = &PlanObject;
    BloomTechnique.TextureBlock = TextureBlock1;
    BloomTechnique.TextureBlock2 = TextureBlock2;
    BloomTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    BloomTechnique.FinalRenderTarget = NULL;//&FinalRenderTarget;
    BloomTechnique.BloomRenderTarget = &BloomRenderTarget;
    BloomTechnique.SetBlurPassCount( 3 );
    
    for (int blur_index = 1; blur_index < 4 ; blur_index++ ) {
        
        int blur_factor = (blur_index*blur_index);
        
        auto rt1 = new GRAPHIC_RENDER_TARGET;
        rt1->Initialize( Window->GetWidth() / (blur_factor), Window->GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        auto rt2 = new GRAPHIC_RENDER_TARGET;
        rt2->Initialize( Window->GetWidth() / (blur_factor), Window->GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        
        BloomTechnique.GaussianRenderTarget1Table[ blur_index - 1 ] = rt1;
        BloomTechnique.GaussianRenderTarget2Table[ blur_index - 1 ] = rt2;
    }
    BloomTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    auto defered_tr = new GRAPHIC_RENDER_TARGET;
    defered_tr->Initialize(Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    DeferredShadingTechnique.PlanObject = &PlanObject;
    DeferredShadingTechnique.FinalRenderTarget = &PrimaryRenderTarget;
    DeferredShadingTechnique.SphereObject = &SphereObject;
    DeferredShadingTechnique.ConeObject = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "cone" ) )->GetResource< GRAPHIC_OBJECT >();
    DeferredShadingTechnique.RendererCallback.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderOpaqueScene>, this );
    DeferredShadingTechnique.RenderTarget = defered_tr;
    DeferredShadingTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    SSAOTechnique.PlanObject = &PlanObject;
    SSAOTechnique.TextureBlock1 = TextureBlock1;
    SSAOTechnique.SourceRenderTarget = DeferredShadingTechnique.RenderTarget;
    SSAOTechnique.RenderTarget = &FinalRenderTarget;
    SSAOTechnique.FinalRenderTarget = DeferredShadingTechnique.RenderTarget;
    SSAOTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    CascadeShadowMapTechnique.CascadeCount = 3;
    CascadeShadowMapTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    CascadeShadowMapTechnique.ShadowMapRenderTarget[0] = &ShadowMapRenderTarget1;
    CascadeShadowMapTechnique.ShadowMapRenderTarget[1] = &ShadowMapRenderTarget2;
    CascadeShadowMapTechnique.ShadowMapRenderTarget[2] = &ShadowMapRenderTarget3;
    CascadeShadowMapTechnique.RendererCallback.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderOpaqueScene>, this );
    CascadeShadowMapTechnique.RendererCallback1.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderOpaqueScene>, this );
    CascadeShadowMapTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    TransparentTechnique.RendererCallback.Connect(
        &Wrapper1<
            R3D_RENDER,
            GRAPHIC_RENDERER &,
            &R3D_RENDER::RenderSceneTransparentWithParticles>,
        this );
    
    TransparentTechnique.RenderTarget = &PrimaryRenderTarget;
    TransparentTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
#if DEBUG
    TOOLS_DEBUG_DRAW::Instance = new TOOLS_DEBUG_DRAW;
    DebugRenderActive = false;
#endif
    
    auto light = new GRAPHIC_SHADER_LIGHT;
    light->InitializeAmbient( CORE_COLOR_White, 0.2f, 0.2f );
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( light );
}

void R3D_RENDER::RenderOpaqueScene( GRAPHIC_RENDERER & renderer ) {
    
    R3D_APP_PTR->GetGame()->Render( renderer, GAMEPLAY_COMPONENT_SYSTEM_MASK_Opaque );
}

void R3D_RENDER::RenderSceneTransparentWithParticles( GRAPHIC_RENDERER & renderer ) {
    
    renderer.SetCamera(Camera);
    renderer.SetNumCascade( 0 );
    renderer.SetPassIndex( 0 );
    
    DeferredShadingTechnique.RenderTarget->BindForReading();
    PrimaryRenderTarget.CopyDepthFrom( *DeferredShadingTechnique.RenderTarget );
    /*static int t = 0;
    t++;
    if( t % 120 == 1) {
        PrimaryRenderTarget.BindForReading();
        PrimaryRenderTarget.GetTargetTexture( 0 )->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "test-depth" , "png", "" ) );
    }*/
    
    //GRAPHIC_PARTICLE_SYSTEM::GetInstance().Render( renderer );
    R3D_APP_PTR->GetGame()->Render( renderer, GAMEPLAY_COMPONENT_SYSTEM_MASK_Transparent );
    
    renderer.SetCamera(RenderTargetCamera);
}

void R3D_RENDER::Render( GRAPHIC_RENDERER & renderer ) {


    static auto cam = new GRAPHIC_CAMERA_ORTHOGONAL;
    
    if ( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer() ) {
        
        CORE_MATH_MATRIX
            m;
        
        m.XRotate( -M_PI_4 );
        m.YRotate( -M_PI_2 );
        
        CascadeShadowMapTechnique.UpdateCameras( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition()+ CORE_MATH_VECTOR( 0.0f, 1.0f), CORE_MATH_VECTOR::ZAxis * m, CORE_MATH_VECTOR::YAxis * m );
        cam->InitWithViewProj( CascadeShadowMapTechnique.LightShadowCamera[0]->GetViewMatrix(), CascadeShadowMapTechnique.LightShadowCamera[0]->GetProjectionMatrix() );
    }
    
#if OPENGL4
    static CORE_MATH_VECTOR
        color( 0.0f, 0.0f, 0.0f, 1.0f );
    
    GRAPHIC_SYSTEM::SetClearColor( color );
    
    static int acc = 0;
    acc++;
    
    /*if (acc > 200 ) {
        acc = 0;
    }
    else if ( acc > 100 ) {
        Camera = cam;
    }
    else
    {
        static GRAPHIC_CAMERA * bk_camera = Camera;
    
        Camera = bk_camera;
    }*/
    
    renderer.SetCamera( Camera );
    SSAOTechnique.SSAOEffect->SetCamera( Camera );
    DeferredShadingTechnique.GameCamera = Camera;
    
    SpeedBlurTechnique.ApplyFirstPass( renderer );
    CascadeShadowMapTechnique.ApplyFirstPass( renderer );
    CascadeShadowMapTechnique.ApplySecondPass( renderer );
    DeferredShadingTechnique.ApplyFirstPass( renderer );
    
    renderer.SetNumCascade( 0 );
    renderer.SetCamera( RenderTargetCamera );
    
    SSAOTechnique.ApplyFirstPass( renderer );
    DeferredShadingTechnique.ApplySecondPass( renderer );
    TransparentTechnique.ApplyFirstPass( renderer );
    BloomTechnique.ApplyFirstPass( renderer );
    
    //SpeedBlurTechnique.ApplySecondPass( renderer );
#else
    {
        renderer.SetCamera(Camera);
        renderer.SetNumCascade( 0 );
        RenderSceneWithParticles( renderer );
        /*GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
        
        UIShaderTextured = GRAPHIC_SHADER_EFFECT::GetResourceForIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured") );
        
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        UIShaderTextured->SetMaterial( mat );
        
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, UIShaderTextured );
        
        delete mat;*/
    }
#endif
    
    renderer.SetCamera( InterfaceCamera );
    GRAPHIC_UI_SYSTEM::GetInstance().Render( renderer );
    
    renderer.SetCamera( Camera );
    //CascadeShadowMapTechnique.DebugFustrum( renderer );
}
