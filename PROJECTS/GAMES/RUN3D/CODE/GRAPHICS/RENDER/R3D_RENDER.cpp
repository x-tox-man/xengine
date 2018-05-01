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
#include "CORE_MATH.h"

R3D_RENDER::R3D_RENDER() :
    Lookat(),
    CascadeProjectionInfo(),
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
    ShadowMapRenderTarget1(),
    ShadowMapRenderTarget2(),
    ShadowMapRenderTarget3(),
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
    
    LightShadowCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 200.0f, -200.0f, 2.0f, 2.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 9.0f, 0.0f), rt_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( &Directional );
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( &Directional );

#if OPENGL4
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
    
    int divider = APPLICATION_CONFIGURATION_OPTIONS::GetInstance().GetGraphicsOptionRenderTargetResolutionDivider();
    
    PrimaryRenderTarget.Initialize( Window->GetWidth() / 2, Window->GetHeight() / 2, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 0 );
    
#if OPENGL4
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    ShadowMapRenderTarget1.InitializeDepthTexture( 1024, 1024, GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
    ShadowMapRenderTarget2.InitializeDepthTexture( 1024, 1024, GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
    ShadowMapRenderTarget3.InitializeDepthTexture( 1024, 1024, GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
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
    
    #if OPENGL4
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

    #if OPENGL4
    {
        GRAPHIC_RENDERER::GetInstance().SetPassIndex( 1 );
        {
            bool screenshots = false;
            if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_M ) ) {
                screenshots = true;
            }
            LightShadowCamera->UpdateCamera( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition() + CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 1.0f ), CORE_MATH_QUATERNION() );
            
            CalculateCascadeOrthoProjection();

            //LightShadowCamera->Reset( CascadeProjectionInfo[0].Near, CascadeProjectionInfo[ 0 ].Far, fabs(CascadeProjectionInfo[ 0 ].Left ) + fabs( CascadeProjectionInfo[ 0 ].Right ), fabs( CascadeProjectionInfo[ 0 ].Top ) + fabs( CascadeProjectionInfo[ 0 ].Bottom ), R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition() + CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 1.0f ), CORE_MATH_QUATERNION() );
            GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera );

            ShadowMapRenderTarget1.Apply();
            R3D_APP_PTR->GetGame()->Render( renderer );
            
            if ( screenshots ) {
                
                GRAPHIC_TEXTURE * texture2 = ShadowMapRenderTarget1.GetTargetTexture();
                texture2->SaveDepthTo(CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth1" , "png", "" ));
            }
            
            ShadowMapRenderTarget1.Discard();
            glClear( GL_DEPTH_BUFFER_BIT );

            LightShadowCamera->Reset( CascadeProjectionInfo[ 1 ].Near, CascadeProjectionInfo[ 1 ].Far, fabs( CascadeProjectionInfo[ 1 ].Left ) + fabs( CascadeProjectionInfo[ 1 ].Right ), fabs( CascadeProjectionInfo[ 1 ].Top ) + fabs( CascadeProjectionInfo[ 1 ].Bottom ), R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition() + CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 1.0f ), CORE_MATH_QUATERNION() );
            ShadowMapRenderTarget2.Apply();
            R3D_APP_PTR->GetGame()->Render( renderer );

            if ( screenshots ) {

                GRAPHIC_TEXTURE * texture2=ShadowMapRenderTarget1.GetTargetTexture();
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth2", "png", "" ) );
            }
            ShadowMapRenderTarget2.Discard();
            glClear( GL_DEPTH_BUFFER_BIT );

            LightShadowCamera->Reset( CascadeProjectionInfo[ 2 ].Near, CascadeProjectionInfo[ 2 ].Far, fabs( CascadeProjectionInfo[ 2 ].Left ) + fabs( CascadeProjectionInfo[ 2 ].Right ), fabs( CascadeProjectionInfo[ 2 ].Top ) + fabs( CascadeProjectionInfo[ 2 ].Bottom ), R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition() + CORE_MATH_VECTOR( 0.0f, 0.0f, 1.0f, 1.0f ), CORE_MATH_QUATERNION() );
            ShadowMapRenderTarget3.Apply();
            R3D_APP_PTR->GetGame()->Render( renderer );
            if ( screenshots ) {

                GRAPHIC_TEXTURE * texture2=ShadowMapRenderTarget1.GetTargetTexture();
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth3", "png", "" ) );
            }
            ShadowMapRenderTarget3.Discard();
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
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( ShadowMapRenderTarget1.GetTargetTexture() );
#endif
            PrimaryRenderTarget.Apply();
            GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
            
            Lookat.Normalize();
            
            R3D_APP_PTR->GetGame()->Render( renderer );
            GRAPHIC_PARTICLE_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
            
#if DEBUG
            renderer.SetLightingIsEnabled( false );
            Camera->GetFustrum().DebugDraw( *Camera);
            renderer.SetLightingIsEnabled( true );
            
            if ( DebugRenderActive ) {
                auto detect = ((GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION *) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[4]);
                
                detect->DebugDrawWorld();
            }
#endif
            
            PrimaryRenderTarget.Discard();
            
            GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( NULL );
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( NULL );
        }
        
        renderer.SetLightingIsEnabled( false );
#if OPENGL4
    }
#endif
    
#if OPENGL4
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
    
    #if OPENGL4
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

void R3D_RENDER::CalculateCascadeOrthoProjection()
{

    CORE_MATH_MATRIX
        view_matrix = Camera->GetViewMatrix(),
        inverse_view_matrix;

    float
        cascade_end[ NUM_CASCADES + 1];

    cascade_end[ 0 ] = Camera->GetNear();
    cascade_end[ 1 ] = ( Camera->GetFar() - Camera->GetNear())* 0.33f;
    cascade_end[ 2 ] = ( Camera->GetFar() - Camera->GetNear())* 0.66f;
    cascade_end[ 3 ] = Camera->GetFar();

    float screen_width = R3D_APP_PTR->GetApplicationWindow().GetWidth();
    float screen_height = R3D_APP_PTR->GetApplicationWindow().GetHeight();

    view_matrix.GetInverse( inverse_view_matrix );

    CORE_MATH_MATRIX LightM =LightShadowCamera->GetViewMatrix();

    float aspect_ratio = screen_height / screen_width;
    float tanHalfHFOV = tanf( CORE_MATH_ToRadians( Camera->GetFov() / 2.0f ) );
    float tanHalfVFOV = tanf( CORE_MATH_ToRadians( ( Camera->GetFov() * aspect_ratio ) / 2.0f ) );

    for ( int i=0; i < NUM_CASCADES; i++ ) {
        float xn = cascade_end[ i ] * tanHalfHFOV;
        float xf = cascade_end[ i + 1 ] * tanHalfHFOV;
        float yn = cascade_end[ i ] * tanHalfVFOV;
        float yf = cascade_end[ i + 1 ] * tanHalfVFOV;

        CORE_MATH_VECTOR frustum_corners[ NUM_FRUSTUM_CORNERS ]={
            // near face
            CORE_MATH_VECTOR( xn, yn, cascade_end[ i ], 1.0 ),
            CORE_MATH_VECTOR( -xn, yn, cascade_end[ i ], 1.0 ),
            CORE_MATH_VECTOR( xn, -yn, cascade_end[ i ], 1.0 ),
            CORE_MATH_VECTOR( -xn, -yn, cascade_end[ i ], 1.0 ),

            // far face
            CORE_MATH_VECTOR( xf, yf, cascade_end[ i + 1 ], 1.0 ),
            CORE_MATH_VECTOR( -xf, yf, cascade_end[ i + 1 ], 1.0 ),
            CORE_MATH_VECTOR( xf, -yf, cascade_end[ i + 1 ], 1.0 ),
            CORE_MATH_VECTOR( -xf, -yf, cascade_end[ i + 1 ], 1.0 )
        };
        //What we see above matches step #1 of the description in the background section on how to calculate the orthographic projections for the cascades.The frustumCorners array is populated with the eight corners of each cascade in view space.Note that since the field of view is provided only for the horizontal axis we have to extrapolate it for the vertical axis( e.g, if the horizontal field of view is 90 degrees and the window has a width of 1000 and a height of 500 the vertical field of view will be only 45 degrees ).

        CORE_MATH_VECTOR frustum_corners_l[ NUM_FRUSTUM_CORNERS ];

        float minX= 1000000000.0f;
        float maxX= -1000000000.0f;
        float minY= 1000000000.0f;
        float maxY = -1000000000.0f;
        float minZ=1000000000.0f;
        float maxZ= -1000000000.0f;

        for ( int j=0; j < NUM_FRUSTUM_CORNERS; j++ ) {

            // Transform the frustum coordinate from view to world space
            const CORE_MATH_VECTOR vW = ::operator*(frustum_corners[ j ], inverse_view_matrix );

            // Transform the frustum coordinate from world to light space
            frustum_corners_l[ j ] = LightM * vW;

            minX=min( minX, frustum_corners_l[ j ].X() );
            maxX=max( maxX, frustum_corners_l[ j ].X() );
            minY=min( minY, frustum_corners_l[ j ].Y() );
            maxY=max( maxY, frustum_corners_l[ j ].Y() );
            minZ=min( minZ, frustum_corners_l[ j ].Z() );
            maxZ=max( maxZ, frustum_corners_l[ j ].Z() );
        }
        //The above code contains step #2 until #4. Each frustum corner coordinate is multiplied by the inverse view transform in order to bring it into world space.It is then multiplied by the light transform in order to move it into light space.We then use a series of min / max functions in order to find the size of the bounding box of the cascade in light space.

        CascadeProjectionInfo[ i ].Right=maxX;
        CascadeProjectionInfo[ i ].Left=minX;
        CascadeProjectionInfo[ i ].Bottom=minY;
        CascadeProjectionInfo[ i ].Top=maxY;
        CascadeProjectionInfo[ i ].Far=maxZ;
        CascadeProjectionInfo[ i ].Near=minZ;
    }
}