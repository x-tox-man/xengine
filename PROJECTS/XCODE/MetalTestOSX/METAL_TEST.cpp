//
//  METAL_TEST.cpp
//  MetalTestOSX
//
//  Created by Christophe Bernard on 16/10/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "METAL_TEST.h"
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "RESOURCE_PROXY.h"

METAL_TEST::METAL_TEST() :
    CORE_APPLICATION(),
    PlanObject(),
    PrimaryRenderTarget(),
    CascadeShadowMapTechnique(),
    DeferredShadingTechnique(),
    m1(),
    m2() {
    
    SetApplicationInstance( *this );
        
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
    
    GetGame().GetScene().InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    GetGame().GetScene().InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    GetGame().GetScene().InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    ((GAMEPLAY_COMPONENT_SYSTEM_RENDERER::PTR) GetGame().GetScene().GetRenderableSystemTable()[0])->SetMask( GAMEPLAY_COMPONENT_SYSTEM_MASK_Opaque );
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    //CORE_HELPERS_CALLBACK_2<int, int> resizeCallback( &Wrapper2<METAL_TEST, int, int, &METAL_TEST::OnScreenResized>, this );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    
    // Do any additional setup after loading the view.
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( false );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    
    StaticObject = RESOURCE<GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER>::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "StaticObject" ), CORE_FILESYSTEM_PATH::FindFilePath( "spaceship" , "smx", "MODELS" ) );
    
    {
        Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        
        Effect->Initialize( StaticObject->GetShaderBindParameter() );
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
        
        Effect->SetMaterial( mat );
    }
    
    {
        AnimatedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::AnimatedObject"), CORE_FILESYSTEM_PATH::FindFilePath( "AnimationShaderDeferred" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        AnimatedShadowMapEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::AnimatedShadowMapObject"), CORE_FILESYSTEM_PATH::FindFilePath( "AnimationShadowMapShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        
        NakedGirlObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "Dying" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "Dying.VoidPirateController" , "abx", "MODELS" ));
        //NakedGirlObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00.DE_Lingerie00_Skeleto" , "abx", "MODELS" ));
        
        AnimatedShadowMapEffect->Initialize( NakedGirlObject->GetShaderBindParameter() );
        AnimatedEffect->Initialize( NakedGirlObject->GetShaderBindParameter() );
    }
    
    
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
    DefaultTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
    DefaultTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    //FinalTechnique.RenderTarget = &PrimaryRenderTarget;
    FinalTechnique.RendererCallback.Connect( &Wrapper2<METAL_TEST, GRAPHIC_RENDERER &, int, &METAL_TEST::RenderFinalFrameBuffer>, this );
    FinalTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    BloomTechnique.PlanObject = &PlanObject;
    BloomTechnique.TextureBlock = new GRAPHIC_TEXTURE_BLOCK();
    BloomTechnique.TextureBlock2 = new GRAPHIC_TEXTURE_BLOCK();
    BloomTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    //BloomTechnique.FinalRenderTarget = &FinalRenderTarget;
    BloomTechnique.BloomRenderTarget = &BloomRenderTarget;
    BloomTechnique.SetBlurPassCount( 3 );
    
    CascadeShadowMapTechnique.CascadeCount = 3;
    CascadeShadowMapTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
    
    for ( int i = 0; i < METAL_TEST_MAX_SHAWOW_CASCADE; i ++ ) {
        
        CascadeShadowMapTechnique.ShadowMapRenderTarget[ i ] = new GRAPHIC_RENDER_TARGET;
        CascadeShadowMapTechnique.ShadowMapRenderTarget[ i ]->InitializeDepthTexture( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    }
    
    CascadeShadowMapTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
    //CascadeShadowMapTechnique.RendererCallback1.Connect( &Wrapper1<METAL_TEST, GRAPHIC_RENDERER &, &METAL_TEST::RenderTechnique>, this );
    CascadeShadowMapTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    
    DeferredShadingTechnique.PlanObject = &PlanObject;
    DeferredShadingTechnique.FinalRenderTarget = &PrimaryRenderTarget;
    //DeferredShadingTechnique.SphereObject = &SphereObject;
    //DeferredShadingTechnique.ConeObject = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "cone" ) )->GetResource< GRAPHIC_OBJECT >();
    DeferredShadingTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
    //DeferredShadingTechnique.RenderTarget = defered_tr;
    DeferredShadingTechnique.ConfigureGBufferBeforeInit( GRAPHIC_RENDERER::GetInstance(), GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_ALL );
    DeferredShadingTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    
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
    //GRAPHIC_RENDERER::GetInstance().SetSpotLight( SpotLightTwo, 1 );v
    
    RESOURCE_CONTAINER
        container;
    
    auto proxy = new RESOURCE_PROXY;
    proxy->SetResource( StaticObject );
    proxy->SetType( RESOURCE_TYPE_ModelResource );
    container.AddResource( proxy, StaticObject->GetIdentifier() );
    container.Save( CORE_FILESYSTEM_PATH::FindFilePath( "containertest" , "rs", "" ) );
    
    RESOURCE_CONTAINER
        container2;
    
    container2.Load( CORE_FILESYSTEM_PATH::FindFilePath( "containertest" , "rs", "" ) );
    
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 0, -5.0f );
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 1, 50.0f );
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 2, 55.0f );
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 3, 1500.0f );
}

void METAL_TEST::Finalize() {
    
}

void METAL_TEST::Update( float time_step ) {
    
    static float angle = 0.0f;
    angle += time_step *M_PI_4;
    m1.XRotate(time_step * M_PI_2 );
    m2.XRotate(time_step * M_PI_4 );
    
    CORE_MATH_VECTOR direction(1.0f, 0.0f, 0.0f, 0.0f);
    
    CORE_MATH_MATRIX m;
    
    m.YRotate( angle );
    
    CORE_MATH_VECTOR vv = direction * m;
    
    memcpy( (void*) DirectionalLight->InternalLight.Directional.Direction, (void*) &vv[0], 16);
    
    //CascadeShadowMapTechnique.UpdateCameras( - vv, vv, CORE_MATH_VECTOR::YAxis );
    CascadeShadowMapTechnique.UpdateCameras( CORE_MATH_VECTOR( 0.0f, -8.0f, 4.0f, 1.0f) , CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GetGame().Update( time_step );
}

void METAL_TEST::Render() {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    GRAPHIC_RENDERER
        & renderer = GRAPHIC_RENDERER::GetInstance();
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    //TODO: NOT COOL !
    Update( 0.0333333f );
    //TODO: SCENE TECHNIQUE => DEPENDS ON A SCENE TO WORK
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );

    CascadeShadowMapTechnique.ApplyFirstPass( renderer );
    CascadeShadowMapTechnique.ApplySecondPass( renderer );
    
    renderer.SetNumCascade( 0 );
    DeferredShadingTechnique.ApplyFirstPass( renderer );
    
    //renderer.SetCamera( RenderTargetCamera );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    
    //SSAOTechnique.ApplyFirstPass( renderer );
    DeferredShadingTechnique.ApplySecondPass( renderer );
    
    renderer.SetNumCascade( 0 );
    renderer.DisableBlend();
    //DefaultTechnique.ApplyFirstPass( renderer );
    
    renderer.SetNumCascade( 0 );
    //POST PROCESS
    //BloomTechnique.ApplyFirstPass( renderer );
    FinalTechnique.ApplyFirstPass( renderer );
}

void METAL_TEST::RenderFinalFrameBuffer( GRAPHIC_RENDERER & renderer, int dummy ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    auto block = new GRAPHIC_TEXTURE_BLOCK();
    
    block->SetTexture( PrimaryRenderTarget.GetTargetTexture( 0 ) );
    
    auto mat = new GRAPHIC_MATERIAL;
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, block );
    UIEffect->SetMaterial( mat );
    
    PlanObject.Render( renderer, options, UIEffect );
}

void METAL_TEST::RenderTechnique( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    CORE_MATH_QUATERNION
        q1,q2;
    
    //q1.FromMatrix( m1.GetRow(0) );
    //q2.FromMatrix( m2.GetRow(0) );
    //q1.RotateX(45.0f);
    
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

GRAPHIC_OBJECT * METAL_TEST::CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
    GRAPHIC_OBJECT * animated_object = RESOURCE<GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER>::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "NakedGirlObject" ), object_path );
    
    animated_object->SetAnimationController( new GRAPHIC_MESH_ANIMATION_CONTROLLER );
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    
    for (int i = 0; i < animated_object->GetMeshTable().size(); i++ ) {
        
        char
            temp_path[256];
        
        strcpy(temp_path, animation_path.GetPath() );
        
        char buff[2];
        
        sprintf(buff, "%d", i);
        strcat( temp_path, buff );
        
        CORE_FILESYSTEM_PATH path( temp_path );
        
        animated_object->GetAnimationController()->Load( path );
        
        
        //animated_object->GetAnimationController()->GetAnimation( i )->Initialize( animated_object->GetJointTable(), 0);
        
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
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_ANIMATION, GAMEPLAY_COMPONENT_RENDER >();
    
    CORE_MATH_QUATERNION
        q1;
    
    //q1.RotateX(45.0f);
    
    entity->SetPosition( CORE_MATH_VECTOR( 0.0f,0.0f,-50.0f,0.0f) );
    entity->SetOrientation( q1 );
    
    auto proxy = new RESOURCE_PROXY;
    
    proxy = new RESOURCE_PROXY;
    proxy->SetResource( animated_object );

    entity->GetComponentRender()->SetObject( *proxy );

    proxy = new RESOURCE_PROXY;
    proxy->SetResource( AnimatedEffect );
    entity->GetComponentRender()->SetEffect( *proxy );
    
    proxy = new RESOURCE_PROXY;
    proxy->SetResource( AnimatedShadowMapEffect );
    entity->GetComponentRender()->SetShadowMapEffectProxy( *proxy );
    
    proxy = new RESOURCE_PROXY;
    proxy->SetResource( collection );
    entity->GetComponentRender()->SetMaterialCollection( *proxy );
    
    entity->GetComponentAnimation()->SetAnimation( *animated_object->GetAnimationController() );
    
    //TODO: fix this index bullshit
    GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( entity );
    GetGame().GetScene().GetUpdatableSystemTable()[1]->AddEntity( entity );
    GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( entity );
    
    return animated_object;
}
