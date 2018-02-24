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
    LightShadowCamera( NULL ),
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
        interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        render_target_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        rt_lookat( 0.0f, 0.0f, 0.0f, 1.0f ),
        lookat;
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    lookat.RotateX(M_PI_2);
    
    auto Window = &R3D_APP_PTR->GetApplicationWindow();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1500.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), position, Lookat );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight() ) );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f), interface_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    Directional.InitializeDirectional( CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 0.0f), 1.0f, 1.0f);
    Ambient.InitializeAmbient(CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), 0.5f, 0.0f );
    
    LightShadowCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 2.0f, -2.0f, 2.0f, 2.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 9.0f, 0.0f), rt_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( &Directional );
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( &Directional );
#if PLATFORM_OSX
    HorizontalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::HZBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianHorrizontalBlurPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    VerticalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::VBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianVerticalBlurPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    CombineBloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::CombineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenCombinePostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    SpeedBlurEffect = new GRAPHIC_SHADER_EFFECT_SPEEDBLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::FullScreenSpeedBlurShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "FullScreenSpeedBlurShader", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    BloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    ((GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR)BloomEffect)->BindAttributes();
    HorizontalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    HorizontalBlurEffect->BindAttributes();
    VerticalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    VerticalBlurEffect->BindAttributes();
    CombineBloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CombineBloomEffect->BindAttributes();
    SpeedBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    ((GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR) SpeedBlurEffect)->BindAttributes();
#endif
    PrimaryRenderTarget.Initialize( Window->GetWidth() / 2, Window->GetHeight() / 2, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 0 );
    
#if PLATFORM_OSX
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    ShadowMapRenderTarget.InitializeDepthTexture( 1024, 1024, GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
#endif
    
    PrimaryRenderTarget.Discard();
    
#if PLATFORM_OSX
    GaussianRenderTarget1.Discard();
    GaussianRenderTarget2.Discard();
    BloomRenderTarget.Discard();
    FinalRenderTarget.Discard();
#endif
    
    PlanObject.InitializeShape();
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, render_target_lookat );
    
#if DEBUG
    TOOLS_DEBUG_DRAW::Instance = new TOOLS_DEBUG_DRAW;
    DebugRenderActive = false;
#endif
    
    auto light = new GRAPHIC_SHADER_LIGHT;
    light->InitializeAmbient( CORE_COLOR_White, 0.2f, 0.2f );
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( light );
}

void R3D_RENDER::Render( GRAPHIC_RENDERER & renderer ) {
    
    CORE_MATH_QUATERNION
        interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    static CORE_MATH_VECTOR old_p;
    
    #if PLATFORM_OSX
    {
        CORE_MATH_MATRIX
        current_mat( &Camera->GetProjectionMatrix()[0] );
        CORE_MATH_MATRIX
        inv( CORE_MATH_MATRIX::Identity );
        
        current_mat *= Camera->GetViewMatrix();
        current_mat.GetInverse( inv );
        
        memcpy(
               (void*) SpeedBlurEffect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::InverseCurrentModelViewIdentifier ).AttributeValue.Value.FloatMatrix4x4,
               (void*) &inv[0],
               16* sizeof(float) );
    }
    #endif
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    interface_lookat.Normalize();

    #if PLATFORM_OSX
    {
        GRAPHIC_RENDERER::GetInstance().SetPassIndex( 1 );
        {
            LightShadowCamera->UpdateCamera( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition() + CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 1.0f ), CORE_MATH_QUATERNION() );
            
            GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera );

            ShadowMapRenderTarget.Apply();
            R3D_APP_PTR->GetGame()->Render( renderer );
            
            if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_M ) ) {
                
                GRAPHIC_TEXTURE * texture2 = ShadowMapRenderTarget.GetTargetTexture();
                texture2->SaveDepthTo(CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth" , "png", "" ));
            }
            
            ShadowMapRenderTarget.Discard();
        }
    #endif
        
        GRAPHIC_RENDERER::GetInstance().SetPassIndex( 0 );
        {
            Camera->ActivateForRender();
            renderer.SetCamera( Camera );
            
#if PLATFORM_IOS || PLATFORM_ANDROID
            renderer.SetLightingIsEnabled( false );
#else
            renderer.SetLightingIsEnabled( true );
            GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera(LightShadowCamera);
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( ShadowMapRenderTarget.GetTargetTexture() );
#endif
            PrimaryRenderTarget.Apply();
            GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
            
            Lookat.Normalize();
            
            R3D_APP_PTR->GetGame()->Render( renderer );
            
            GRAPHIC_PARTICLE_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
            
            PrimaryRenderTarget.Discard();
            
            GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( NULL );
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( NULL );
        }
        
#if DEBUG
        renderer.SetLightingIsEnabled( false );
        Camera->GetFustrum().DebugDraw( *Camera);
        renderer.SetLightingIsEnabled( true );
        
        if ( DebugRenderActive ) {
            auto detect = ((GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION *) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[4]);
            
            detect->DebugDrawWorld();
        }
#endif
        
        renderer.SetLightingIsEnabled( false );
#if PLATFORM_OSX
    }
#endif
    
#if PLATFORM_OSX && 0
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        BloomEffect->SetMaterial( mat );
        
        BloomRenderTarget.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, BloomEffect );
        BloomRenderTarget.Discard();
        delete mat;
    }
    
    {
        TextureBlock->SetTexture( BloomRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        HorizontalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget1.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, HorizontalBlurEffect );
        GaussianRenderTarget1.Discard();
        delete mat;
    }
    
    {
        TextureBlock->SetTexture( GaussianRenderTarget1.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        VerticalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget2.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, VerticalBlurEffect );
        GaussianRenderTarget2.Discard();
        delete mat;
    }
    
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        TextureBlock2->SetTexture( GaussianRenderTarget2.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock2 );
        CombineBloomEffect->SetMaterial( mat );
        
        FinalRenderTarget.Apply();
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, CombineBloomEffect );
        FinalRenderTarget.Discard();
        
        delete mat;
    }
    
    CORE_MATH_VECTOR delta_position = Camera->GetPosition() - old_p;
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::ViewRayIdentifier ).AttributeValue.Value.FloatArray4,
           (void*) &delta_position[0],
           4* sizeof(float) );
    
    {
        TextureBlock->SetTexture( FinalRenderTarget.GetTargetTexture() );
        TextureBlock2->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::DepthTexture, TextureBlock2 );
        SpeedBlurEffect->SetMaterial( mat );
        
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, SpeedBlurEffect );
        
        delete mat;
    }
#else
    {
        GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
        auto last_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        last_effect->SetMaterial( mat );
        
        PlanObject.Render( GRAPHIC_RENDERER::GetInstance(), option, last_effect );
        
        delete mat;
    }
#endif
    
    GRAPHIC_SYSTEM::DisableDepthTest();
    renderer.SetCamera( InterfaceCamera );
    GRAPHIC_UI_SYSTEM::GetInstance().Render( renderer );
    
    #if PLATFORM_OSX
    {
        CORE_MATH_MATRIX previous_mat( &Camera->GetProjectionMatrix()[0] );
        
        previous_mat *= Camera->GetViewMatrix();
        
        memcpy(
               (void*) SpeedBlurEffect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PreviousModelViewProjectionIdentifier ).AttributeValue.Value.FloatMatrix4x4,
               (void*) &previous_mat[0],
               16* sizeof(float) );
    }
    
    old_p = Camera->GetPosition();
    #endif
    
}

