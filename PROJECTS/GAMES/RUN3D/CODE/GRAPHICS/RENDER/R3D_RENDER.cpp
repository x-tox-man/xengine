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

R3D_RENDER::R3D_RENDER() :
    Lookat(),
    Camera( NULL ),
    RenderTargetCamera( NULL ),
    InterfaceCamera( NULL ),
    Directional(),
    Ambient(),
    PlanObject(),
    PrimaryRenderTarget(),
    FinalRenderTarget(),
    LightRenderTarget(),
    SpecularRenderTarget(),
    GaussianRenderTarget1(),
    GaussianRenderTarget2(),
    BloomRenderTarget(),
    TextureBlock( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock2( new GRAPHIC_TEXTURE_BLOCK() ),
    TextureBlock3(new GRAPHIC_TEXTURE_BLOCK() ),
    HorizontalBlurEffect(),
    VerticalBlurEffect(),
    CombineBloomEffect() {
    
}

void R3D_RENDER::Initialize() {
    
    CORE_MATH_VECTOR
        position(10.0f, 15.0f, 64.0f, 1.0f);
    CORE_MATH_QUATERNION
        lookat;
    
    lookat.RotateX(M_PI_2);
    
    auto Window = &R3D_APP_PTR->GetApplicationWindow();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), position, Lookat );
    
    CORE_MATH_QUATERNION
        interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        render_target_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    interface_lookat.RotateX( M_PI_2 );
    interface_lookat.RotateX( M_PI_2 );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight() ) );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f), interface_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    Directional.InitializeDirectional( CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 0.0f), 1.0f, 1.0f);
    Ambient.InitializeAmbient(CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), 0.5f, 0.0f );
    
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( &Directional );
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( &Directional );
    
    HorizontalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::HZBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianHorrizontalBlurPostProcess" , "", "OPENGL2" ) ) );
    
    VerticalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::VBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianVerticalBlurPostProcess" , "", "OPENGL2" ) ) );
    
    CombineBloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::CombineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenCombinePostProcess" , "", "OPENGL2" ) ) );
    
     BloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "", "OPENGL2" ) ) );
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    BloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    HorizontalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    VerticalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CombineBloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    PrimaryRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, false, 0 );
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    
    PrimaryRenderTarget.Discard();
    GaussianRenderTarget1.Discard();
    GaussianRenderTarget2.Discard();
    BloomRenderTarget.Discard();
    FinalRenderTarget.Discard();
    
    PlanObject.InitializeShape();
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, render_target_lookat );
    
#if DEBUG
    TOOLS_DEBUG_DRAW::Instance = new TOOLS_DEBUG_DRAW;
#endif
}

void R3D_RENDER::Render( GRAPHIC_RENDERER & renderer ) {
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    interface_lookat.Normalize();
    
    auto Window = &R3D_APP_PTR->GetApplicationWindow();
    
    {
        Camera->ActivateForRender();
        renderer.SetCamera( Camera );
        
        GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
        
#if PLATFORM_OSX
        PrimaryRenderTarget.Apply();
#endif
#if PLATFORM_IOS || PLATFORM_ANDROID
        renderer.SetLightingIsEnabled( false );
#else
        renderer.SetLightingIsEnabled( true );
#endif
        Lookat.Normalize();
        
        GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_LessOrEqual, true, 0.0f, 1.0f);
        R3D_APP_PTR->GetGame().Render( renderer );
        
        GRAPHIC_PARTICLE_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
        
#if DEBUG
        renderer.SetLightingIsEnabled( false );
        Camera->GetFustrum().DebugDraw( *Camera);
        renderer.SetLightingIsEnabled( true );
#endif
    
        renderer.SetLightingIsEnabled( false );
        
        GRAPHIC_SYSTEM::DisableDepthTest();
        renderer.SetCamera( InterfaceCamera );
        GRAPHIC_UI_SYSTEM::GetInstance().Render( renderer );
#if PLATFORM_OSX
        PrimaryRenderTarget.Discard();
#endif
    }
    
#if PLATFORM_OSX
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        BloomEffect->SetMaterial( mat );
        
        BloomRenderTarget.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, BloomEffect );
        BloomRenderTarget.Discard();
    }
    
    {
        TextureBlock->SetTexture( BloomRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        HorizontalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget1.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, HorizontalBlurEffect );
        GaussianRenderTarget1.Discard();
    }
    
    {
        TextureBlock->SetTexture( GaussianRenderTarget1.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        VerticalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget2.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, VerticalBlurEffect );
        GaussianRenderTarget2.Discard();
    }
    
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        TextureBlock2->SetTexture( GaussianRenderTarget2.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock2 );
        CombineBloomEffect->SetMaterial( mat );
        
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, CombineBloomEffect );
    }
#endif
    
    auto detect = ((GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION *) R3D_APP_PTR->GetGame().GetScene().GetUpdatableSystemTable()[4]);
    
    //detect->DebugDrawWorld();
}
