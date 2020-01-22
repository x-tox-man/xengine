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
        
        CORE_MATH_MATRIX m1, m2, rs;
        m1[0] = 1.177f;
        m1[5] = 1.570f;
        m1[10] = -1.001f;
        m1[11] = -1.0f;
        m1[14] = -0.1001f;
        m1[15] = -0.0f;
        
        m2[14] = -8.0f;
        
        rs = m1 * m2;
        
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
    
    StaticObject = GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath( "spaceship" , "smx", "MODELS" ), 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    Effect->Initialize( StaticObject->GetShaderBindParameter() );
    auto mat = new GRAPHIC_MATERIAL;
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    Effect->SetMaterial( mat );
    
    AnimatedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::AnimatedObject"), CORE_FILESYSTEM_PATH::FindFilePath( "AnimationShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    NakedGirlObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00.DE_Lingerie00_Skeleto" , "abx", "MODELS" ));
    
    AnimatedEffect->Initialize( NakedGirlObject->GetShaderBindParameter() );
    
    Camera = new GRAPHIC_CAMERA( 0.1f, 100.0f, GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR( 0.0f, -8.0f, -25.0f, 1.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis, 65.0f );
    
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
    
    DirectionalLight = new GRAPHIC_SHADER_LIGHT;
    
    CORE_MATH_VECTOR diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    CORE_MATH_VECTOR direction(1.0f, 0.0f, 0.0f, 0.0f);
    
    DirectionalLight->InitializeDirectional( diffuse, direction, 0.5f, 0.5f);
    
    CORE_MATH_VECTOR diffuse_1(0.9f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR diffuse_2(0.0f, 0.0f, 0.9f, 1.0f);
    
    CORE_MATH_VECTOR direction_1(0.0f, 1.0f, 0.0f, 0.0f);
    CORE_MATH_VECTOR direction_2(0.0f, -1.0f, 0.0f, 0.0f);
    
    CORE_MATH_VECTOR point1_position(-10.0f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR point2_position(10.0f, 0.0f, 0.0f, 1.0f);
    
    PointLightOne = new GRAPHIC_SHADER_LIGHT;
    PointLightOne->InitializePoint(diffuse_1, point1_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    PointLightTwo = new GRAPHIC_SHADER_LIGHT;
    PointLightTwo->InitializePoint(diffuse_2, point2_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    SpotLightOne = new GRAPHIC_SHADER_LIGHT;
    SpotLightOne->InitializeSpot(diffuse_1, point1_position, direction_1, 0.1f, 0.2f, 0.4f, 0.001f, 1.0f, 1.0f );
    
    SpotLightTwo = new GRAPHIC_SHADER_LIGHT;
    SpotLightTwo->InitializeSpot(diffuse_2, point2_position, direction_2, 0.1f, 0.2f, 0.9f, 0.1f, 1.0f, 1.0f );
    AmbientLight = new GRAPHIC_SHADER_LIGHT;
    AmbientLight->InitializeAmbient( CORE_MATH_VECTOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.7f);
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( AmbientLight );
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( DirectionalLight );
    //GRAPHIC_RENDERER::GetInstance().SetPointLight( PointLightOne, 0 );
    //GRAPHIC_RENDERER::GetInstance().SetPointLight( PointLightTwo, 1 );
    //GRAPHIC_RENDERER::GetInstance().SetSpotLight( SpotLightOne, 0 );
    //GRAPHIC_RENDERER::GetInstance().SetSpotLight( SpotLightTwo, 1 );
}

void METAL_TEST::Finalize() {
    
}

void METAL_TEST::Update( float time_step ) {
    
    static float angle = 0.0f;
    angle += time_step *M_PI_4;
    m1.XRotate(time_step * M_PI_2 );
    m2.XRotate(time_step * M_PI_4 );
    
    if ( time_step + NakedGirlObject->GetAnimationController()->GetCurrentTimeFrame() < NakedGirlObject->GetAnimationController()->GetAnimation( 0 )->GetJointTable()[0]->GetDuration() ) {
        
        NakedGirlObject->GetAnimationController()->Update( time_step );
    }
    else {
        
        NakedGirlObject->GetAnimationController()->Reset();
    }
    
    CORE_MATH_VECTOR direction(1.0f, 0.0f, 0.0f, 0.0f);
    
    CORE_MATH_MATRIX m;
    
    m.YRotate( angle );
    
    CORE_MATH_VECTOR vv = direction * m;
    
    memcpy( (void*) DirectionalLight->InternalLight.Directional.Direction, (void*) &vv[0], 16);
}

void METAL_TEST::Render() {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    Update( 0.0333333f );
    
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
    CORE_MATH_QUATERNION
        q1,q2;
    
    //q1.FromMatrix( m1.GetRow(0) );
    //q2.FromMatrix( m2.GetRow(0) );
    q1.RotateX(45.0f);
    
    GRAPHIC_RENDERER::GetInstance().SetNumCascade( 0 );
    renderer.SetCamera( Camera );
    GRAPHIC_RENDERER::GetInstance().GetCamera()->ActivateForRender();
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetOrientation( q1 );
    
    NakedGirlObject->Render( renderer, options, AnimatedEffect );
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    //options.SetOrientation( q2 );
    //StaticObject->Render( renderer, options, Effect );
}

GRAPHIC_OBJECT_ANIMATED * METAL_TEST::CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
    GRAPHIC_OBJECT_ANIMATED * animated_object = GRAPHIC_MESH_MANAGER::GetInstance().LoadObjectAnimated( object_path, 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    animated_object->SetAnimationController( new GRAPHIC_MESH_ANIMATION_CONTROLLER );
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    
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
        
        auto mat = new GRAPHIC_MATERIAL;
        
        auto image = RESOURCE_IMAGE::LoadResourceForPath( animated_object->GetMeshTable()[i]->GetName(), CORE_FILESYSTEM_PATH::FindFilePath( animated_object->GetMeshTable()[i]->GetName(), "png", "TEXTURES_BASE" ) );
        
        if ( image == NULL ) {
            
            auto mat2 = collection->GetMaterialForName( "DE_Lingerie00_Face" );
            collection->SetMaterialForName(mat2, animated_object->GetMeshTable()[i]->GetName() );
            
            continue;
        }
        
        mat->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( image->CreateTextureObject( true ) ) );
        
        char normal_texture_name[128];
        
        CORE_DATA_COPY_STRING( normal_texture_name, animated_object->GetMeshTable()[i]->GetName() );
        CORE_DATA_STRING_CONCAT( normal_texture_name, "-normal" );
        
        image=RESOURCE_IMAGE::LoadResourceForPath( normal_texture_name, CORE_FILESYSTEM_PATH::FindFilePath( normal_texture_name, "png", "TEXTURES_BASE" ) );
        mat->SetTexture(GRAPHIC_SHADER_PROGRAM::NormalTexture, new GRAPHIC_TEXTURE_BLOCK( image->CreateTextureObject( true ) ) );
        
        collection->SetMaterialForName(mat, animated_object->GetMeshTable()[i]->GetName() );
    }
    
    animated_object->GetAnimationController()->Initialize();
    AnimatedEffect->SetMaterialCollection( collection );
    
    return animated_object;
}
