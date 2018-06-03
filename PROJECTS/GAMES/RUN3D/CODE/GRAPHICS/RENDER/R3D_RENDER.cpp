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
    LightShadowCamera(),
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
    
    Directional.InitializeDirectional( CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), CORE_MATH_VECTOR( 0.0f, 0.0f, -1.0f, 0.0f), 1.0f, 1.0f);
    Ambient.InitializeAmbient(CORE_MATH_VECTOR(0.7f, 0.7f, 0.7f, 1.0f), 0.5f, 0.0f );
    
    LightShadowCamera[0] = new GRAPHIC_CAMERA_ORTHOGONAL( 0.1f, 10.0f, 4.0f, 4.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 9.0f, 0.0f), rt_lookat );
    LightShadowCamera[1] = new GRAPHIC_CAMERA_ORTHOGONAL( 0.1f, 10.0f, 4.0f, 4.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 9.0f, 0.0f), rt_lookat );
    LightShadowCamera[2] = new GRAPHIC_CAMERA_ORTHOGONAL( 0.1f, 10.0f, 4.0f, 4.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 9.0f, 0.0f), rt_lookat );
    
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
    
    PrimaryRenderTarget.Initialize( Window->GetWidth() / divider, Window->GetHeight() / divider, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 0 );
    
#if OPENGL4
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
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
    
    renderer.SetNumCascade( 0 );

    #if OPENGL4
    {
        GRAPHIC_RENDERER::GetInstance().SetPassIndex( 1 );
        {
            bool screenshots = false;
            if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_M ) ) {
                screenshots = true;
            }
            
            CORE_MATH_QUATERNION q;
            
            //q.RotateX( M_PI_2 * 0.12f );
            q.RotateY( M_PI_2 * 0.33f );
            q.Normalize();
            
            LightShadowCamera[0]->UpdateCamera( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition(), q );
            LightShadowCamera[1]->UpdateCamera( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition(), q );
            LightShadowCamera[2]->UpdateCamera( R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition(), q );
            
            CalculateCascadeOrthoProjection( renderer );
            
            LightShadowCamera[0]->InitOrthoProjTransform(CascadeProjectionInfo[ 0 ].Left, CascadeProjectionInfo[ 0 ].Right, CascadeProjectionInfo[ 0 ].Bottom, CascadeProjectionInfo[ 0 ].Top, CascadeProjectionInfo[ 0 ].Near, CascadeProjectionInfo[ 0 ].Far );
            GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[0] );

            ShadowMapRenderTarget1.Apply();
            GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
            glClearDepth( 0.0f );
            glClear( GL_DEPTH_BUFFER_BIT );
            R3D_APP_PTR->GetGame()->Render( renderer );
            
            if ( screenshots ) {
                
                GRAPHIC_TEXTURE * texture2 = ShadowMapRenderTarget1.GetTargetTexture();
                texture2->SaveDepthTo(CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth1" , "png", "" ));
            }
            ShadowMapRenderTarget1.Discard();
            
            LightShadowCamera[1]->InitOrthoProjTransform(CascadeProjectionInfo[ 1 ].Left, CascadeProjectionInfo[ 1 ].Right, CascadeProjectionInfo[ 1 ].Bottom, CascadeProjectionInfo[ 1 ].Top, CascadeProjectionInfo[ 1 ].Near, CascadeProjectionInfo[ 1 ].Far );
            GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[1] );
            
            ShadowMapRenderTarget2.Apply();
            GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
            glClearDepth( 0.0f );
            glClear( GL_DEPTH_BUFFER_BIT );
            R3D_APP_PTR->GetGame()->Render( renderer );

            if ( screenshots ) {

                GRAPHIC_TEXTURE * texture2=ShadowMapRenderTarget2.GetTargetTexture();
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth2", "png", "" ) );
            }
            ShadowMapRenderTarget2.Discard();

            LightShadowCamera[2]->InitOrthoProjTransform(CascadeProjectionInfo[ 2 ].Left, CascadeProjectionInfo[ 2 ].Right, CascadeProjectionInfo[ 2 ].Bottom, CascadeProjectionInfo[ 2 ].Top, CascadeProjectionInfo[ 2 ].Near, CascadeProjectionInfo[ 2 ].Far );
            GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[2] );
            
            ShadowMapRenderTarget3.Apply();
            GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
            glClearDepth( 0.0f );
            glClear( GL_DEPTH_BUFFER_BIT );
            R3D_APP_PTR->GetGame()->Render( renderer );
            if ( screenshots ) {

                GRAPHIC_TEXTURE * texture2=ShadowMapRenderTarget3.GetTargetTexture();
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
            
            GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( 0, LightShadowCamera[ 0 ] );
            GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( 1, LightShadowCamera[ 1 ] );
            GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( 2, LightShadowCamera[ 2 ]);
            
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 0, ShadowMapRenderTarget1.GetTargetTexture() );
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 1, ShadowMapRenderTarget2.GetTargetTexture() );
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 2, ShadowMapRenderTarget3.GetTargetTexture() );
#endif
            PrimaryRenderTarget.Apply();
            GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
            
            Lookat.Normalize();
            
            renderer.SetNumCascade( NUM_CASCADES );
            R3D_APP_PTR->GetGame()->Render( renderer );
            renderer.SetNumCascade( 0 );
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
            
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 0, NULL );
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 1, NULL );
            GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 2, NULL );
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

void R3D_RENDER::CalculateCascadeOrthoProjection( GRAPHIC_RENDERER & renderer )
{

    CORE_MATH_MATRIX
        view_matrix = Camera->GetViewMatrix(),
        inverse_view_matrix;

    renderer.SetCascadeEnd( 0, 0.0f );
    renderer.SetCascadeEnd( 1, 1.0f );
    renderer.SetCascadeEnd( 2, 8.0f );
    renderer.SetCascadeEnd( 3, Camera->GetFar() );

    float screen_width = R3D_APP_PTR->GetApplicationWindow().GetWidth();
    float screen_height = R3D_APP_PTR->GetApplicationWindow().GetHeight();

    view_matrix.GetInverse( inverse_view_matrix );

    CORE_MATH_MATRIX LightM =LightShadowCamera[0]->GetViewMatrix();

    float aspect_ratio = screen_height / screen_width;
    float tanHalfHFOV = tanf( CORE_MATH_ToRadians( Camera->GetFov() / 2.0f ) );
    float tanHalfVFOV = tanf( CORE_MATH_ToRadians( ( Camera->GetFov() * aspect_ratio ) / 2.0f ) );

    for ( int i=0; i < NUM_CASCADES; i++ ) {
        float xn = renderer.GetCascadeEnd( i ) * tanHalfHFOV;
        float xf = renderer.GetCascadeEnd( i + 1 ) * tanHalfHFOV;
        float yn = renderer.GetCascadeEnd( i ) * tanHalfVFOV;
        float yf = renderer.GetCascadeEnd( i + 1 ) * tanHalfVFOV;

        CORE_MATH_VECTOR frustum_corners[ NUM_FRUSTUM_CORNERS ]={
            // near face
            CORE_MATH_VECTOR( xn, yn, renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( -xn, yn, renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( xn, -yn, renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( -xn, -yn, renderer.GetCascadeEnd( i ), 1.0 ),

            // far face
            CORE_MATH_VECTOR( xf, yf, renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( -xf, yf, renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( xf, -yf, renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( -xf, -yf, renderer.GetCascadeEnd( i + 1 ), 1.0 )
        };
        //What we see above matches step #1 of the description in the background section on how to calculate the orthographic projections for the cascades.The frustumCorners array is populated with the eight corners of each cascade in view space.Note that since the field of view is provided only for the horizontal axis we have to extrapolate it for the vertical axis( e.g, if the horizontal field of view is 90 degrees and the window has a width of 1000 and a height of 500 the vertical field of view will be only 45 degrees ).

        CORE_MATH_VECTOR frustum_corners_l[ NUM_FRUSTUM_CORNERS ];

        float minX= 1000000000.0f;
        float maxX= -1000000000.0f;
        float minY= 1000000000.0f;
        float maxY = -1000000000.0f;
        float minZ = 1000000000.0f;
        float maxZ= -1000000000.0f;

        for ( int j=0; j < NUM_FRUSTUM_CORNERS; j++ ) {

            // Transform the frustum coordinate from view to world space
            const CORE_MATH_VECTOR vW = ::operator*( frustum_corners[ j ], inverse_view_matrix );
            //const CORE_MATH_VECTOR vW2 = ::operator*( frustum_corners[ j ], inverse_view_matrix );

            // Transform the frustum coordinate from world to light space
            frustum_corners_l[ j ] = ::operator*( vW, LightM );

            minX=fmin( minX, frustum_corners_l[ j ].X() );
            maxX=fmax( maxX, frustum_corners_l[ j ].X() );
            minY=fmin( minY, frustum_corners_l[ j ].Y() );
            maxY=fmax( maxY, frustum_corners_l[ j ].Y() );
            minZ=fmin( minZ, frustum_corners_l[ j ].Z() );
            maxZ=fmax( maxZ, frustum_corners_l[ j ].Z() );
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
