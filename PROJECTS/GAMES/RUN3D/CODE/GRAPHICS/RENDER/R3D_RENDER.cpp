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
#include "GRAPHIC_PARTICLE_SYSTEM.h"
#include "TOOLS_DEBUG_DRAW.h"
#include "APPLICATION_CONFIGURATION.h"

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
    GaussianRenderTarget1(),
    GaussianRenderTarget2(),
    BloomRenderTarget(),
    ShadowMapRenderTarget1(),
    ShadowMapRenderTarget2(),
    ShadowMapRenderTarget3(),
    TextureBlock1( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock2( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock3(new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock4( new GRAPHIC_TEXTURE_BLOCK() ),
    SpeedBlurTechnique(),
    BloomTechnique(),
    CascadeShadowMapTechnique(),
    DeferredShadingTechnique(),
    SSAOTechnique() {
    
}

void R3D_RENDER::Initialize() {
    
    CORE_MATH_VECTOR
        position(10.0f, 15.0f, 64.0f, 1.0f);
    CORE_MATH_QUATERNION
        interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        render_target_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    lookat.RotateX(M_PI_2);
    
    auto Window = &R3D_APP_PTR->GetApplicationWindow();
    GRAPHIC_RENDERER::GetInstance().Resize( Window->GetWidth(), Window->GetHeight() );
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1500.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), position, Lookat );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight() ) );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f), interface_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    Directional.InitializeDirectional( CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), CORE_MATH_VECTOR( 0.0f, 0.0f, -1.0f, 0.0f), 1.0f, 1.0f);
    Ambient.InitializeAmbient(CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), 0.5f, 0.0f );
    
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( &Directional );
    
    int divider = APPLICATION_CONFIGURATION_OPTIONS::GetInstance().GetGraphicsOptionRenderTargetResolutionDivider();
    
    PrimaryRenderTarget.Initialize( Window->GetWidth() / divider, Window->GetHeight() / divider, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
#if OPENGL4
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    ShadowMapRenderTarget1.InitializeDepthTexture( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    ShadowMapRenderTarget2.InitializeDepthTexture( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    ShadowMapRenderTarget3.InitializeDepthTexture( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
#endif
    
    PrimaryRenderTarget.Discard();
    
#if OPENGL4
    GaussianRenderTarget1.Discard();
    GaussianRenderTarget2.Discard();
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
    SpeedBlurTechnique.RendererCallback.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderScene>, this );
    SpeedBlurTechnique.RendererCallback1.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderSceneWithParticles>, this );
    SpeedBlurTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    BloomTechnique.PlanObject = &PlanObject;
    BloomTechnique.TextureBlock = TextureBlock1;
    BloomTechnique.TextureBlock2 = TextureBlock2;
    BloomTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    BloomTechnique.FinalRenderTarget = NULL;//&FinalRenderTarget;
    BloomTechnique.BloomRenderTarget = &BloomRenderTarget;
    BloomTechnique.GaussianRenderTarget1 = &GaussianRenderTarget1;
    BloomTechnique.GaussianRenderTarget2 = &GaussianRenderTarget2;
    BloomTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    DeferredShadingTechnique.PlanObject = &PlanObject;
    DeferredShadingTechnique.FinalRenderTarget = &PrimaryRenderTarget;
    DeferredShadingTechnique.SphereObject = &SphereObject;
    DeferredShadingTechnique.RendererCallback.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderScene>, this );
    DeferredShadingTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    SSAOTechnique.PlanObject = &PlanObject;
    SSAOTechnique.TextureBlock1 = TextureBlock1;
    SSAOTechnique.SourceRenderTarget = &DeferredShadingTechnique.RenderTarget;
    SSAOTechnique.RenderTarget = &FinalRenderTarget;
    SSAOTechnique.FinalRenderTarget = &DeferredShadingTechnique.RenderTarget;
    SSAOTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );

    CORE_MATH_QUATERNION q;
    
    //q.RotateX( M_PI_2 );
    //q.RotateY( M_PI_2 * 0.05f );
    q.Normalize();
    
    CascadeShadowMapTechnique.CascadeCount = 3;
    CascadeShadowMapTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    CascadeShadowMapTechnique.ShadowMapRenderTarget1 = &ShadowMapRenderTarget1;
    CascadeShadowMapTechnique.ShadowMapRenderTarget2 = &ShadowMapRenderTarget2;
    CascadeShadowMapTechnique.ShadowMapRenderTarget3 = &ShadowMapRenderTarget3;
    CascadeShadowMapTechnique.LightSourcePose.SetPosition( CORE_MATH_VECTOR::One );
    CascadeShadowMapTechnique.LightSourcePose.SetOrientation( q );
    CascadeShadowMapTechnique.RendererCallback.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderScene>, this );
    CascadeShadowMapTechnique.RendererCallback1.Connect( &Wrapper1<R3D_RENDER, GRAPHIC_RENDERER &, &R3D_RENDER::RenderSceneWithParticles>, this );
    CascadeShadowMapTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, render_target_lookat );
    
#if DEBUG
    TOOLS_DEBUG_DRAW::Instance = new TOOLS_DEBUG_DRAW;
    DebugRenderActive = false;
#endif
    
    auto light = new GRAPHIC_SHADER_LIGHT;
    light->InitializeAmbient( CORE_COLOR_White, 0.2f, 0.2f );
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( light );
}

void R3D_RENDER::RenderScene( GRAPHIC_RENDERER & renderer ) {
    
    R3D_APP_PTR->GetGame()->Render( renderer );
}

void R3D_RENDER::RenderSceneWithParticles( GRAPHIC_RENDERER & renderer ) {
    
    R3D_APP_PTR->GetGame()->Render( renderer );
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
}

void R3D_RENDER::Render( GRAPHIC_RENDERER & renderer ) {

#if OPENGL4
    static CORE_MATH_VECTOR
        color( 0.0f, 0.0f, 0.0f, 1.0f );
    
    GRAPHIC_SYSTEM::SetClearColor( color );
    CascadeShadowMapTechnique.LightSourcePose.SetPosition( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition() );
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
    BloomTechnique.ApplyFirstPass( renderer );
    SpeedBlurTechnique.ApplySecondPass( renderer );
#else
    {
        GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
        
        UIShaderTextured = GRAPHIC_SHADER_EFFECT::GetResourceForIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured") );
        
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        UIShaderTextured->SetMaterial( mat );
        
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, UIShaderTextured );
        
        delete mat;
    }
#endif
    
    GRAPHIC_SYSTEM::DisableDepthTest();
    renderer.SetCamera( InterfaceCamera );
    GRAPHIC_UI_SYSTEM::GetInstance().Render( renderer );
}
