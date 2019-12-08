//
//  METAL_TEST.cpp
//  MetalTestOSX
//
//  Created by Christophe Bernard on 16/10/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "METAL_TEST.h"

METAL_TEST::METAL_TEST() :
    CORE_APPLICATION(),
    DefaultFileystem(),
    PlanObject(),
    PrimaryRenderTarget(),
    m1(),
    m2() {
    
    SetApplicationInstance( *this );
        
        SERVICE_LOGGER_Error( "ALL APP create 1" );
            
        #if PLATFORM_OSX
            DefaultFileystem.Initialize( "/Users/c.bernard/Library/Containers/cbe.MetalTestOSX/Data/RESOURCES/" );
        #elif PLATFORM_IOS
            DefaultFileystem.Initialize( "None" );
        #elif PLATFORM_ANDROID
            //DefaultFileystem.Initialize( "None" );
        #elif PLATFORM_WINDOWS
            DefaultFileystem.Initialize( "C:\\Users\\X\\Documents\\game-engine-clean\\RESOURCES\\" );
        #endif
            
        CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
}

METAL_TEST::~METAL_TEST() {
    
}

void METAL_TEST::Initialize() {
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    //CORE_HELPERS_CALLBACK_2<int, int> resizeCallback( &Wrapper2<METAL_TEST, int, int, &METAL_TEST::OnScreenResized>, this );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    
    // Do any additional setup after loading the view.
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( false );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    
    AnimatedObject = GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath( "spaceship" , "smx", "MODELS" ), 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    Effect->Initialize( AnimatedObject->GetShaderBindParameter() );
    auto mat = new GRAPHIC_MATERIAL;
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    Effect->SetMaterial( mat );
    
    Camera = new GRAPHIC_CAMERA( 0.01f, 10.0f, GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, -0.1f, 1.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis, 45.0f );
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    PrimaryRenderTarget.Initialize( GetApplicationWindow().GetWidth(),GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    FinalRenderTarget.Initialize( GetApplicationWindow().GetWidth(),GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    BloomRenderTarget.Initialize( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() / 1, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    PrimaryRenderTarget.Discard();
    
    PlanObject.InitializeShape();
    
    //DefaultTechnique.PlanObject = &PlanObject;
    //DefaultTechnique.TextureBlock = TextureBlock1;
    DefaultTechnique.RenderTarget = &PrimaryRenderTarget;
    DefaultTechnique.RendererCallback.Connect( &Wrapper1<METAL_TEST, GRAPHIC_RENDERER &, &METAL_TEST::RenderTechnique>, this );
    DefaultTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    FinalTechnique.RendererCallback.Connect( &Wrapper1<METAL_TEST, GRAPHIC_RENDERER &, &METAL_TEST::RenderFinalFrameBuffer>, this );
    FinalTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    BloomTechnique.PlanObject = &PlanObject;
    BloomTechnique.TextureBlock = new GRAPHIC_TEXTURE_BLOCK();
    BloomTechnique.TextureBlock2 = new GRAPHIC_TEXTURE_BLOCK();
    BloomTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    BloomTechnique.FinalRenderTarget = &FinalRenderTarget;
    BloomTechnique.BloomRenderTarget = &BloomRenderTarget;
    BloomTechnique.SetBlurPassCount( 3 );
    
    for (int blur_index = 1; blur_index < 4 ; blur_index++ ) {
        
        int blur_factor = (blur_index*blur_index);
        
        auto rt1 = new GRAPHIC_RENDER_TARGET;
        rt1->Initialize( GetApplicationWindow().GetWidth() / (blur_factor), GetApplicationWindow().GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        auto rt2 = new GRAPHIC_RENDER_TARGET;
        rt2->Initialize( GetApplicationWindow().GetWidth() / (blur_factor), GetApplicationWindow().GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        
        BloomTechnique.GaussianRenderTarget1Table[ blur_index - 1 ] = rt1;
        BloomTechnique.GaussianRenderTarget2Table[ blur_index - 1 ] = rt2;
        
        // TODO: Refactor
        if( blur_index == 1 ) {
            
            GRAPHIC_SYSTEM::SetRendersOnScreen( true );
            UIEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::Uitextured"), CORE_FILESYSTEM_PATH::FindFilePath( "Uitextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
               
            UIEffect->Initialize( AnimatedObject->GetShaderBindParameter() );
            auto mat2 = new GRAPHIC_MATERIAL;
            mat2->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( rt2->GetTargetTexture( 0 ) ) );
               
            UIEffect->SetMaterial( mat2 );
            
            GRAPHIC_SYSTEM::SetRendersOnScreen( false );
        }
    }
    
    BloomTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
}

void METAL_TEST::Finalize() {
    
}

void METAL_TEST::Update( float time_step ) {
    
    m1.XRotate(time_step * M_PI_2 );
    m2.XRotate(time_step * M_PI_4 );
}

void METAL_TEST::Render() {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    Update( 0.016777f );
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    DefaultTechnique.ApplyFirstPass( GRAPHIC_RENDERER::GetInstance() );
    BloomTechnique.ApplyFirstPass( GRAPHIC_RENDERER::GetInstance() );
    FinalTechnique.ApplyFirstPass( GRAPHIC_RENDERER::GetInstance() );
    
    //RenderTechnique( GRAPHIC_RENDERER::GetInstance() );
}

void METAL_TEST::RenderFinalFrameBuffer( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    PlanObject.Render(GRAPHIC_RENDERER::GetInstance(), options, UIEffect );
}

void METAL_TEST::RenderTechnique( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    CORE_MATH_QUATERNION q1,q2;
    
    q1.FromMatrix( m1.GetRow(0) );
    q2.FromMatrix( m2.GetRow(0) );
    
    GRAPHIC_RENDERER::GetInstance().SetNumCascade( 0 );
    GRAPHIC_RENDERER::GetInstance().GetCamera()->ActivateForRender();
    
    GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_FrontAndBack );
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetOrientation( q1 );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    AnimatedObject->Render( renderer, options, Effect );
    
    renderer.SetCamera( RenderTargetCamera );
    
    /*options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetOrientation( q2 );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    AnimatedObject->Render( renderer, options, Effect );*/
}
