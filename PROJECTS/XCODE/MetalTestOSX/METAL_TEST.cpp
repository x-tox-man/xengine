//
//  METAL_TEST.cpp
//  MetalTestOSX
//
//  Created by Christophe Bernard on 16/10/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "METAL_TEST.h"
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"

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
    
    NakedGirlObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00.DE_Lingerie00_Skeleto" , "abx", "MODELS" ));
    
    Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    Effect->Initialize( AnimatedObject->GetShaderBindParameter() );
    auto mat = new GRAPHIC_MATERIAL;
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    Effect->SetMaterial( mat );
    
    AnimatedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::AnimatedObject"), CORE_FILESYSTEM_PATH::FindFilePath( "AnimationShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    AnimatedEffect->Initialize( NakedGirlObject->GetShaderBindParameter() );
    AnimatedEffect->SetMaterial( mat );
    
    Camera = new GRAPHIC_CAMERA( 0.01f, 1000.0f, GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis, 45.0f );
    
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
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( true );
    UIEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
       
    UIEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    auto mat2 = new GRAPHIC_MATERIAL;
    mat2->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( FinalRenderTarget.GetTargetTexture( 0 ) ) );
       
    UIEffect->SetMaterial( mat2 );
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( false );
    
    for (int blur_index = 1; blur_index < 4 ; blur_index++ ) {
        
        int blur_factor = (blur_index*blur_index);
        
        auto rt1 = new GRAPHIC_RENDER_TARGET;
        rt1->Initialize( GetApplicationWindow().GetWidth() / (blur_factor), GetApplicationWindow().GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        auto rt2 = new GRAPHIC_RENDER_TARGET;
        rt2->Initialize( GetApplicationWindow().GetWidth() / (blur_factor), GetApplicationWindow().GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        
        BloomTechnique.GaussianRenderTarget1Table[ blur_index - 1 ] = rt1;
        BloomTechnique.GaussianRenderTarget2Table[ blur_index - 1 ] = rt2;
    }
    
    BloomTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
}

void METAL_TEST::Finalize() {
    
}

void METAL_TEST::Update( float time_step ) {
    
    m1.XRotate(time_step * M_PI_2 );
    m2.XRotate(time_step * M_PI_4 );
    
    NakedGirlObject->GetAnimationController()->Update(time_step );
}

void METAL_TEST::Render() {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    Update( 0.016777f );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    DefaultTechnique.ApplyFirstPass( GRAPHIC_RENDERER::GetInstance() );
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    
    BloomTechnique.ApplyFirstPass( GRAPHIC_RENDERER::GetInstance() );
    FinalTechnique.ApplyFirstPass( GRAPHIC_RENDERER::GetInstance() );
}

void METAL_TEST::RenderFinalFrameBuffer( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    PlanObject.Render(GRAPHIC_RENDERER::GetInstance(), options, UIEffect );
}

void METAL_TEST::RenderTechnique( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    CORE_MATH_QUATERNION q1,q2;
    
    //q1.FromMatrix( m1.GetRow(0) );
    //q2.FromMatrix( m2.GetRow(0) );
    q1.RotateX(-90.0f);
    
    GRAPHIC_RENDERER::GetInstance().SetNumCascade( 0 );
    renderer.SetCamera( Camera );
    GRAPHIC_RENDERER::GetInstance().GetCamera()->ActivateForRender();
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    //options.SetOrientation( q1 );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    //AnimatedObject->Render( renderer, options, Effect );
    NakedGirlObject->Render( renderer, options, AnimatedEffect );
    
    /*options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetOrientation( q2 );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    AnimatedObject->Render( renderer, options, Effect );*/
}

GRAPHIC_OBJECT_ANIMATED * METAL_TEST::CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
    GRAPHIC_OBJECT_ANIMATED * animated_object = GRAPHIC_MESH_MANAGER::GetInstance().LoadObjectAnimated( object_path, 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    animated_object->SetAnimationController( new GRAPHIC_MESH_ANIMATION_CONTROLLER );
    
    for (int i = 0; i < animated_object->GetMeshTable().size(); i++ ) {
        
        char
            temp_path[128];
        
        strcpy(temp_path, animation_path.GetPath() );
        
        char buff[2];
        
        sprintf(buff, "%d", i);
        strcat( temp_path, buff );
        
        CORE_FILESYSTEM_PATH path( temp_path );
        
        animated_object->GetAnimationController()->Load( path );
        
        animated_object->GetAnimationController()->GetAnimation( i )->Initialize( animated_object->GetJointTable(), 0);
    }
    
    animated_object->GetAnimationController()->Initialize();
    animated_object->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    return animated_object;
}
