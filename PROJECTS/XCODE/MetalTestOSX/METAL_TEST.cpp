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
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "CORE_DATA_JSON.h"

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
    
    bool create_object = false;
    
    if ( !create_object ) {
        Container.Load( CORE_FILESYSTEM_PATH::FindFilePath( "containertest2" , "rs", "" ) );
    }
    
    GetGame().GetScene().InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    GetGame().GetScene().InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    GetGame().GetScene().InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_LIGHTING );
    GetGame().GetScene().InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    GetGame().GetScene().InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    ((GAMEPLAY_COMPONENT_SYSTEM_RENDERER::PTR) GetGame().GetScene().GetRenderableSystemTable()[0])->SetMask( GAMEPLAY_COMPONENT_SYSTEM_MASK_Opaque );
    ((GAMEPLAY_COMPONENT_SYSTEM_RENDERER::PTR) GetGame().GetScene().GetRenderableSystemTable()[1])->SetMask( GAMEPLAY_COMPONENT_SYSTEM_MASK_Transparent );
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    //CORE_HELPERS_CALLBACK_2<int, int> resizeCallback( &Wrapper2<METAL_TEST, int, int, &METAL_TEST::OnScreenResized>, this );
    
    SphereObject = new GRAPHIC_OBJECT_SHAPE_SPHERE( 5 );
    SphereObject->InitializeShape();
    
    ConeObject = RESOURCE<GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER>::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "cone" ),  CORE_FILESYSTEM_PATH::FindFilePath("cone", "smx", "MODELS" ) );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    
    // Do any additional setup after loading the view.
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( false );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    auto tex_normal = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    
    StaticObject = RESOURCE<GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER>::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "StaticObject" ), CORE_FILESYSTEM_PATH::FindFilePath( "flat" , "smx", "MODELS" ) );
    
    {
        Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        
        Effect->Initialize( StaticObject->GetShaderBindParameter() );
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
        mat->SetTexture(GRAPHIC_SHADER_PROGRAM::NormalTexture, new GRAPHIC_TEXTURE_BLOCK( tex_normal ) );
        
        Effect->SetMaterial( mat );
    }
    
    {
        EffectDeferred = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShaderDeferred"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderDeferred" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        ShadowMapEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShadowmapEffect"), CORE_FILESYSTEM_PATH::FindFilePath( "ShadowmapEffect" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        //ShadowMapEffect->Initialize( StaticObject->GetShaderBindParameter() );
        EffectDeferred->Initialize( StaticObject->GetShaderBindParameter() );
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::NormalTexture, new GRAPHIC_TEXTURE_BLOCK( tex_normal ) );
        
        Effect->SetMaterial( mat );
        
        CreateStaticObject( create_object, StaticObject, EffectDeferred, mat );
    }
    
    {
        AnimatedEffectDeferred = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::AnimatedObject"), CORE_FILESYSTEM_PATH::FindFilePath( "AnimationShaderDeferred" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        AnimatedShadowMapEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::AnimatedShadowMapObject"), CORE_FILESYSTEM_PATH::FindFilePath( "AnimationShadowMapShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        
        NakedGirlObject = CreateAnimatedObject( create_object, CORE_FILESYSTEM_PATH::FindFilePath( "Dying" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "Running" , "acbx", "MODELS" ));
        //NakedGirlObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00.DE_Lingerie00_Skeleto" , "abx", "MODELS" ));
        
        AnimatedShadowMapEffect->Initialize( NakedGirlObject->GetShaderBindParameter() );
        AnimatedEffectDeferred->Initialize( NakedGirlObject->GetShaderBindParameter() );
    }
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1000.0f, GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight(), CORE_MATH_VECTOR( 0.0f,32.0f, -200.0f, 1.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis, 65.0f );
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    PrimaryRenderTarget.Initialize( GetApplicationWindow().GetWidth(),GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    FinalRenderTarget.Initialize( GetApplicationWindow().GetWidth(),GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, false, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    BloomRenderTarget.Initialize( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() / 1, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    PrimaryRenderTarget.Discard();
    
    PlanObject.InitializeShape();
    
    {
        DefaultTechnique.RenderTarget = &PrimaryRenderTarget;
        DefaultTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
        DefaultTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    }
    
    
    {
        FinalTechnique.RendererCallback.Connect( &Wrapper2<METAL_TEST, GRAPHIC_RENDERER &, int, &METAL_TEST::RenderFinalFrameBuffer>, this );
        FinalTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    }
    
    {
        TransparentTechnique.RenderTarget = &PrimaryRenderTarget;
        TransparentTechnique.SetTransparentMask( GAMEPLAY_COMPONENT_SYSTEM_MASK_Transparent );
        TransparentTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
        DefaultTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    }
    {
        CascadeShadowMapTechnique.CascadeCount = 3;
        CascadeShadowMapTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
        
        for ( int i = 0; i < METAL_TEST_MAX_SHAWOW_CASCADE; i ++ ) {
            
            CascadeShadowMapTechnique.ShadowMapRenderTarget[ i ] = new GRAPHIC_RENDER_TARGET;
            CascadeShadowMapTechnique.ShadowMapRenderTarget[ i ]->InitializeDepthTexture( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
        }
        
        CascadeShadowMapTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
        CascadeShadowMapTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    }
    
    {
        DeferredShadingTechnique.PlanObject = &PlanObject;
        DeferredShadingTechnique.FinalRenderTarget = &PrimaryRenderTarget;
        DeferredShadingTechnique.SphereObject = SphereObject;
        DeferredShadingTechnique.ConeObject = ConeObject;
        DeferredShadingTechnique.RendererCallback.Connect( &Wrapper2<GAMEPLAY_GAME, GRAPHIC_RENDERER &, int, &GAMEPLAY_GAME::Render>, &GetGame() );
        //DeferredShadingTechnique.RenderTarget = defered_tr;
        DeferredShadingTechnique.ConfigureGBufferBeforeInit( GRAPHIC_RENDERER::GetInstance(), GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_ALL );
        DeferredShadingTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    }
    
    {
        BloomTechnique.PlanObject = &PlanObject;
        BloomTechnique.TextureBlock = new GRAPHIC_TEXTURE_BLOCK();
        BloomTechnique.TextureBlock2 = new GRAPHIC_TEXTURE_BLOCK();
        BloomTechnique.PrimaryRenderTarget = &PrimaryRenderTarget;
        BloomTechnique.FinalRenderTarget = &FinalRenderTarget;
        BloomTechnique.BloomRenderTarget = &BloomRenderTarget;
        BloomTechnique.SetBlurPassCount( 3 );
    }
    
    {
        SSAOTechnique.PlanObject = &PlanObject;
        SSAOTechnique.SourceRenderTarget = DeferredShadingTechnique.RenderTarget;
        SSAOTechnique.RenderTarget = &FinalRenderTarget;
        SSAOTechnique.FinalRenderTarget = DeferredShadingTechnique.RenderTarget;
        SSAOTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    }
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( true );
    UIEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    UIEffectColored = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderColored"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderColored" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
       
    UIEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    //UIEffectColored->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    auto mat2 = new GRAPHIC_MATERIAL;
    mat2->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( FinalRenderTarget.GetTargetTexture( 0 ) ) );
       
    UIEffect->SetMaterial( mat2 );
    
    GRAPHIC_SYSTEM::SetRendersOnScreen( false );
    
    for (int blur_index = 1; blur_index < 4 ; blur_index++ ) {
        
        int blur_factor = (blur_index*blur_index);
        
        auto rt1 = new GRAPHIC_RENDER_TARGET;
        rt1->Initialize( GetApplicationWindow().GetWidth() / (blur_factor), GetApplicationWindow().GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        auto rt2 = new GRAPHIC_RENDER_TARGET;
        rt2->Initialize( GetApplicationWindow().GetWidth() / (blur_factor), GetApplicationWindow().GetHeight() / (blur_factor), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
        
        BloomTechnique.GaussianRenderTarget1Table[ blur_index - 1 ] = rt1;
        BloomTechnique.GaussianRenderTarget2Table[ blur_index - 1 ] = rt2;
    }
    
    BloomTechnique.Initialize( GRAPHIC_RENDERER::GetInstance() );
    
    DirectionalLight = new GRAPHIC_SHADER_LIGHT;
    
    CORE_MATH_VECTOR diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    CORE_MATH_VECTOR direction(0.0f, -1.0f, 1.0f, 0.0f);
    direction.Normalize();
    
    DirectionalLight->InitializeDirectional( diffuse, direction, 0.5f, 0.5f);
    
    CORE_MATH_VECTOR diffuse_1(1.0f, 0.0, 0.0, 1.0f);
    CORE_MATH_VECTOR diffuse_2(0.0f, 0.0f, 0.9f, 1.0f);
    
    CORE_MATH_VECTOR direction_1;
    CORE_MATH_VECTOR direction_2;
    
    CORE_MATH_VECTOR point1_position(-10.0f, -16.0f, -10.0f, 1.0f);
    CORE_MATH_VECTOR point2_position(10.0f, -16.0f, -10.0f, 1.0f);
    
    GRAPHIC_SHADER_LIGHT p_light1;
    p_light1.InitializePoint(diffuse_1, point1_position, 0.00032f, 0.5f, 0.009f, 1.0f, 1.0f);
    
    GRAPHIC_SHADER_LIGHT p_light2;
    p_light2.InitializePoint(diffuse_2, point2_position, 0.00032f, 0.5f, 0.009f, 1.0f, 1.0f);
    
    GRAPHIC_SHADER_LIGHT s_light1;
    s_light1.InitializeSpot(diffuse_1, point1_position, direction_1, 0.00032f, 0.00015f, 0.0009f, 0.01f, 1.0f, 1.0f );
    
    GRAPHIC_SHADER_LIGHT s_light2;
    s_light2.InitializeSpot(diffuse_2, point2_position, direction_2, 0.00032f, 0.5f, 0.0009f, 0.00001f, 1.0f, 1.0f );
    
    AmbientLight = new GRAPHIC_SHADER_LIGHT;
    AmbientLight->InitializeAmbient( CORE_MATH_VECTOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.7f);
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_LIGHT >();
    entity->SetPosition( point1_position );
    entity->GetComponent<GAMEPLAY_COMPONENT_LIGHT>()->SetLight( p_light1 );
    GetGame().GetScene().GetUpdatableSystemTable()[2]->AddEntity( entity );
    
    entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_LIGHT >();
    entity->GetComponent<GAMEPLAY_COMPONENT_LIGHT>()->SetLight( p_light2 );
    entity->SetPosition( point2_position );
    GetGame().GetScene().GetUpdatableSystemTable()[2]->AddEntity( entity );
    
    CORE_MATH_MATRIX mm;
    mm.YRotate( M_PI_4 );
    CORE_MATH_QUATERNION q;
    q.FromMatrix( &mm[0] );
    
    entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION,  GAMEPLAY_COMPONENT_LIGHT >();
    entity->GetComponent<GAMEPLAY_COMPONENT_LIGHT>()->SetLight( s_light1 );
    entity->SetPosition( point1_position );
    entity->SetOrientation( q );
    GetGame().GetScene().GetUpdatableSystemTable()[2]->AddEntity( entity );
    
    entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_LIGHT >();
    entity->GetComponent<GAMEPLAY_COMPONENT_LIGHT>()->SetLight( s_light2 );
    entity->SetPosition( point2_position );
    entity->SetOrientation( -q );
    GetGame().GetScene().GetUpdatableSystemTable()[2]->AddEntity( entity );
    
    GRAPHIC_RENDERER::GetInstance().SetAmbientLight( AmbientLight );
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( DirectionalLight );
    
    RESOURCE_CONTAINER
        container;
    
    auto proxy = new RESOURCE_PROXY;
    proxy->SetResource( StaticObject );
    proxy->SetType( RESOURCE_TYPE_ModelResource );
    
    container.AddResource( proxy, StaticObject->GetIdentifier() );
    container.Save( CORE_FILESYSTEM_PATH::FindFilePath( "containertest" , "rs", "" ) );
    
    /*RESOURCE_CONTAINER
        container2;
    
    container2.Load( CORE_FILESYSTEM_PATH::FindFilePath( "containertest" , "rs", "" ) );*/
    
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 0, -5.0f );
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 1, 10.0f );
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 2, 100.0f );
    GRAPHIC_RENDERER::GetInstance().SetCascadeEnd( 3, 1000.0f );
    
    CreateGround( create_object );
    //CreateWater( create_object );
    
    if ( create_object ) {
        
        GetGame().GetScene().SaveTo(CORE_FILESYSTEM_PATH::FindFilePath("test", "rs", "") );
        
        Container.Save( CORE_FILESYSTEM_PATH::FindFilePath( "containertest2" , "rs", "" ) );
    }
    else {
        GetGame().GetScene().LoadFrom(CORE_FILESYSTEM_PATH::FindFilePath("test", "rs", "") );
    }
    
    
    GRAPHIC_UI_SYSTEM::GetInstance().Initialize();
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
    GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(CreateFrame(), "main");
}

void METAL_TEST::Finalize() {
    
}

void METAL_TEST::Update( float time_step ) {
    
    static float angle = 0.0f;
    angle += time_step *M_PI_4;
    m1.XRotate(time_step * M_PI_2 );
    m2.XRotate(time_step * M_PI_4 );
    
    CORE_MATH_VECTOR direction(0.0f, -1.0f, 2.0f, 0.0f);
    direction.Normalize();
    
    //WaterEffect->GetProgram().GetShaderAttribute(GRAPHIC_SHADER_PROGRAM::TimeModulator ).AttributeValue.Value.FloatValue += time_step;
    
    CORE_MATH_MATRIX m;
    
    m.YRotate( angle );
    
    CORE_MATH_VECTOR vv = direction * m;
    CORE_MATH_VECTOR vv2 = CORE_MATH_VECTOR::ZAxis * m;
    
    Camera->UpdateCamera(Camera->GetPosition(), vv2 );
    
    memcpy( (void*) DirectionalLight->InternalLight.Directional.Direction, (void*) &vv[0], 16);
    
    CascadeShadowMapTechnique.UpdateCameras( -vv, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    //CascadeShadowMapTechnique.UpdateCameras( CORE_MATH_VECTOR( 0.0f, -8.0f, 4.0f, 1.0f) , CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GetGame().Update( time_step );
    GRAPHIC_UI_SYSTEM::GetInstance().Update( time_step );
}

void METAL_TEST::Render() {
    
    GRAPHIC_RENDERER
        & renderer = GRAPHIC_RENDERER::GetInstance();
    
    //TODO: NOT COOL !
    Update( 0.017f );
    //TODO: SCENE TECHNIQUE => DEPENDS ON A SCENE TO WORK

    SSAOTechnique.SSAOEffect->SetCamera( Camera );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );

    CascadeShadowMapTechnique.ApplyFirstPass( renderer );
    CascadeShadowMapTechnique.ApplySecondPass( renderer );
    
    renderer.SetNumCascade( 3 );
    DeferredShadingTechnique.ApplyFirstPass( renderer );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    
    SSAOTechnique.ApplyFirstPass( renderer );
    DeferredShadingTechnique.SetPreviousCamera( Camera );
    DeferredShadingTechnique.ApplySecondPass( renderer );
    
    /*renderer.SetNumCascade( 0 );
    PrimaryRenderTarget.Clear();
    renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    renderer.DisableDepthTest();
    renderer.DisableStencilTest();
    renderer.SetShadowMappingEnabled( false );
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    TransparentTechnique.ApplyFirstPass( renderer );
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );*/
    
    renderer.SetNumCascade( 0 );
    renderer.DisableBlend();
    renderer.DisableDepthTest();
    renderer.DisableStencilTest();
    
    //DefaultTechnique.ApplyFirstPass( renderer );
    
    renderer.SetNumCascade( 0 );
    //POST PROCESS
    BloomTechnique.ApplyFirstPass( renderer );
    FinalTechnique.ApplyFirstPass( renderer );
}

void METAL_TEST::RenderFinalFrameBuffer( GRAPHIC_RENDERER & renderer, int dummy ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    auto block = new GRAPHIC_TEXTURE_BLOCK();
    
    block->SetTexture( FinalRenderTarget.GetTargetTexture( 0 ) );
    
    auto mat = new GRAPHIC_MATERIAL;
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, block );
    UIEffect->SetMaterial( mat );
    
    PlanObject.Render( renderer, options, UIEffect );
    
    renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    GRAPHIC_UI_SYSTEM::GetInstance().Render( renderer );
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
    
    NakedGirlObject->Render( renderer, options, AnimatedEffectDeferred );
    
    options.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    //options.SetOrientation( q2 );
    //StaticObject->Render( renderer, options, Effect );
}

GRAPHIC_OBJECT * METAL_TEST::CreateAnimatedObject( bool create_object, const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
    GRAPHIC_OBJECT * animated_object = RESOURCE<GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER>::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "NakedGirlObject" ), object_path );
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT_ANIMATION >();
    
    //animated_object->SetAnimationController( new GRAPHIC_MESH_ANIMATION_CONTROLLER );
    
    auto animation_collection = GRAPHIC_MESH_ANIMATION_COLLECTION::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "NakedGirlObjectAnimation" ), animation_path );
    
    entity->GetComponent<GAMEPLAY_COMPONENT_ANIMATION>()->SetAnimationResource( *Container.AddResource( animation_collection ) );
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    collection->SetIdentifier( "AnimatedModelMaterialCollection" );
    
    GRAPHIC_MATERIAL_COLLECTION::GetResourceCache()->SetResourceForIdentifier(collection,  CORE_HELPERS_UNIQUE_IDENTIFIER( "AnimatedModelMaterialCollection" ) );
    
    for (int i = 0; i < animated_object->GetMeshTable().size(); i++ ) {
        
        /*char
            temp_path[256];
        
        strcpy(temp_path, animation_path.GetPath() );
        
        char buff[2];
        
        sprintf(buff, "%d", i);
        strcat( temp_path, buff );
        
        CORE_FILESYSTEM_PATH path( temp_path );
        auto animation = GRAPHIC_MESH_ANIMATION::LoadResourceForPath( "animation", path);
        
        RESOURCE_PROXY anim_proxy;
        
        anim_proxy.SetResource( animation );
        
        entity->GetComponent<GAMEPLAY_COMPONENT_ANIMATION>()->SetAnimationResource( anim_proxy );
        
        //animated_object->GetAnimationController()->Load( path );
        //animated_object->GetAnimationController()->GetAnimation( i )->Initialize( animated_object->GetJointTable(), 0);*/
        
        auto mat = new GRAPHIC_MATERIAL;
        
        auto image = RESOURCE_IMAGE::LoadResourceForPath( animated_object->GetMeshTable()[i]->GetName(), CORE_FILESYSTEM_PATH::FindFilePath( animated_object->GetMeshTable()[i]->GetName(), "png", "TEXTURES" ) );
        
        if ( image == NULL ) {
            
            auto mat2 = collection->GetMaterialForName( "DE_Lingerie00_Face" );
            collection->SetMaterialForName(mat2, animated_object->GetMeshTable()[i]->GetName() );
            
            continue;
        }
        
        mat->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( image->CreateTextureObject( true ) ) );
        
        char normal_texture_name[128];
        
        CORE_DATA_COPY_STRING( normal_texture_name, animated_object->GetMeshTable()[i]->GetName() );
        CORE_DATA_STRING_CONCAT( normal_texture_name, "-normal" );
        
        image=RESOURCE_IMAGE::LoadResourceForPath( normal_texture_name, CORE_FILESYSTEM_PATH::FindFilePath( normal_texture_name, "png", "TEXTURES" ) );
        mat->SetTexture(GRAPHIC_SHADER_PROGRAM::NormalTexture, new GRAPHIC_TEXTURE_BLOCK( image->CreateTextureObject( true ) ) );
        
        collection->SetMaterialForName(mat, animated_object->GetMeshTable()[i]->GetName() );
    }
    
    CORE_MATH_QUATERNION
        q1;
    
    //q1.RotateX(45.0f);
    
    if ( create_object ) {
    
        entity->SetPosition( CORE_MATH_VECTOR( 0.0f,0.0f,-10.0f,0.0f) );
        entity->SetOrientation( q1 );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( *Container.AddResource( animated_object ) );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( *Container.AddResource( AnimatedEffectDeferred ) );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetShadowMapEffectProxy( *Container.AddResource( AnimatedShadowMapEffect ) );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetMaterialCollection( *Container.AddResource( collection ) );
        
        //TODO: fix this index bullshit
        GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( entity );
        GetGame().GetScene().GetUpdatableSystemTable()[1]->AddEntity( entity );
        GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( entity );
        
        entity->Scale( 1.6f);
        
        for( int i = 0; i < 100; i++ ) {
            
            auto clone = GAMEPLAY_COMPONENT_MANAGER::GetInstance().Clone( entity );
            clone->Reset();
            clone->SetPosition( CORE_MATH_VECTOR( -150.0f + i *30.0,0.0f,-10.0f,0.0f) );
            
            clone->GetComponent<GAMEPLAY_COMPONENT_ANIMATION>()->SetSpeed( 0.1f *i );
            GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( clone );
            GetGame().GetScene().GetUpdatableSystemTable()[1]->AddEntity( clone );
            GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( clone );
        }
    }
    
    return animated_object;
}

void METAL_TEST::CreateStaticObject( bool create_object, GRAPHIC_OBJECT * object, GRAPHIC_SHADER_EFFECT::PTR effect, GRAPHIC_MATERIAL * mat ) {
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    collection->SetIdentifier( "StaticObjectMaterialCollection" );
    collection->SetMaterialForName(mat, object->GetMeshTable()[0]->GetName() );
    GRAPHIC_MATERIAL_COLLECTION::GetResourceCache()->SetResourceForIdentifier(collection,  CORE_HELPERS_UNIQUE_IDENTIFIER( "StaticObjectMaterialCollection" ) );
    
    if (create_object ) {
        
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
        
        CORE_MATH_QUATERNION
            q1;
        
        q1.RotateX( 90.0f );
        
        entity->SetPosition( CORE_MATH_VECTOR( 0.0f,0.0f,-50.0f,0.0f) );
        entity->Scale( 10.0f);
        entity->SetOrientation( q1 );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( *Container.AddResource( object ) );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( *Container.AddResource( effect ) );
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetShadowMapEffectProxy( *Container.AddResource( ShadowMapEffect ) );
        
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetMaterialCollection( *Container.AddResource( collection ) );
        
        //TODO: fix this index bullshit
        GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( entity );
        GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( entity );
        
        auto clone = GAMEPLAY_COMPONENT_MANAGER::GetInstance().Clone( entity );
        
        clone->SetPosition( CORE_MATH_VECTOR( -5.0f,0.0f,-50.0f,0.0f) );
        GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( clone );
        GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( clone );
    }
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR METAL_TEST::Set3DHeighFieldObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    RESOURCE_IMAGE * height_map = (RESOURCE_IMAGE*) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath(identifier.GetIdentifier(), "png", "MAP" ) );
    
    float * heights = (float * ) height_map->GetImageRawData();
    
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR object = new GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( heights, height_map->GetImageInfo().Width, height_map->GetImageInfo().Height, 2.0f );
    object->SetHeightScale( 0.05f );
    object->InitializeShape();
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>();
    render->GetObject().SetResource( object );

    return object;
}


void METAL_TEST::CreateGround( bool create_object ) {
    
    TerrainEffectDeferred = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicTerrainDeferred"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicTerrainDeferred" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color" ), CORE_FILESYSTEM_PATH::FindFilePath("map_color_0", "png", "MAP" ) );
    
    auto mat = new GRAPHIC_MATERIAL;

    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map_color_0" ), CORE_FILESYSTEM_PATH::FindFilePath("map_color_0", "png", "MAP" ) );
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color-rock" ), CORE_FILESYSTEM_PATH::FindFilePath("map-color-rock", "png", "TEXTURES" ) );
    GRAPHIC_SYSTEM::SetTextureOptions( text, GRAPHIC_TEXTURE_FILTERING_Linear, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture2, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color-sand" ), CORE_FILESYSTEM_PATH::FindFilePath("map-color-sand", "png", "TEXTURES" ) );
    GRAPHIC_SYSTEM::SetTextureOptions( text, GRAPHIC_TEXTURE_FILTERING_Linear, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture3, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color-grass" ), CORE_FILESYSTEM_PATH::FindFilePath("map-color-grass", "png", "TEXTURES" ) );
    GRAPHIC_SYSTEM::SetTextureOptions( text, GRAPHIC_TEXTURE_FILTERING_Linear, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture4, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    collection->SetMaterialForName( mat, GRAPHIC_SHADER_EFFECT::DefaultMaterialName );
    collection->SetIdentifier( "GroundMeshMaterialCollection" );
    GRAPHIC_MATERIAL_COLLECTION::GetResourceCache()->SetResourceForIdentifier(collection,  CORE_HELPERS_UNIQUE_IDENTIFIER( "GroundMeshMaterialCollection" ) );
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    RESOURCE_IMAGE * height_map = (RESOURCE_IMAGE*) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( CORE_HELPERS_UNIQUE_IDENTIFIER( "heightmap" ).GetIdentifier(), "png", "MAP" ) );
    
    float * heights = (float * ) height_map->GetImageRawData();
    
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR h_object = new GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( heights, height_map->GetImageInfo().Width, height_map->GetImageInfo().Height, 2.0f );
    h_object->SetHeightScale( 0.05f );
    h_object->InitializeShape();
    h_object->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "HeightMapObject" ) );
    GRAPHIC_OBJECT::GetResourceCache()->SetResourceForIdentifier( h_object,  CORE_HELPERS_UNIQUE_IDENTIFIER( "HeightMapObject" ) );
    
    TerrainEffectDeferred->Initialize( h_object->GetShaderBindParameter() );
    
    if ( create_object ) {
        
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
        
        GAMEPLAY_COMPONENT_RENDER::PTR render = entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>();

        //auto height_map_object = Set3DHeighFieldObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "heightmap" ) );
        
        GAMEPLAY_COMPONENT_RENDER::PTR render_c = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>();
        render_c->GetObject().SetResource( h_object );
        
        render->SetEffect( *Container.AddResource( TerrainEffectDeferred ) );
        render->SetMaterialCollection( *Container.AddResource( collection ) );
        
        entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetShadowMapEffectProxy( *Container.AddResource( ShadowMapEffect ) );
        
        CORE_MATH_VECTOR p( -((h_object->GetXWidth() - 1) * h_object->GetLength())*0.5f, -30.0f, -((h_object->GetYWidth()- 1) * h_object->GetLength())*0.5f, 1.0f );
        
        entity->SetPosition( p );
        entity->Scale( 100.0f );
        
        //GAMEPLAY_HELPER::AddStaticToPhysics( entity, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
        //GAMEPLAY_HELPER::AddToWorld( entity );
        
        //TODO: fix this index bullshit
        GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( entity );
        GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( entity );
    }
}

void METAL_TEST::CreateWater( bool create_object ) {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
    
    auto mat = new GRAPHIC_MATERIAL;
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>();
    
    WaterEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::WaterAnimated"), CORE_FILESYSTEM_PATH::FindFilePath( "WaterAnimated" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    render->SetEffect( *Container.AddResource( WaterEffect ) );
    
    
    auto obj = RESOURCE<GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER>::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "flat_base" ),  CORE_FILESYSTEM_PATH::FindFilePath("flat_base", "smx", "MODELS" ) );
    
    render->SetObject( *Container.AddResource( obj ) );
    
    WaterEffect->Initialize( obj->GetShaderBindParameter() );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "water-0339" ), CORE_FILESYSTEM_PATH::FindFilePath("water-0339", "png", "TEXTURES" ) );
    GRAPHIC_SYSTEM::SetTextureOptions( text, GRAPHIC_TEXTURE_FILTERING_Linear, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "water-0339-normal" ), CORE_FILESYSTEM_PATH::FindFilePath("water-0339-normal", "png", "TEXTURES" ) );
    GRAPHIC_SYSTEM::SetTextureOptions( text, GRAPHIC_TEXTURE_FILTERING_Linear, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
    mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    collection->SetMaterialForName( mat, "Plane" );
    
    render->SetMaterialCollection( *Container.AddResource( collection ) );
    
    render->SetShadowMapEffectProxy( *Container.AddResource( ShadowMapEffect ) );
    
    CORE_MATH_QUATERNION orientation;
    orientation.RotateX( M_PI_2 );
    
    entity->SetOrientation( orientation );
    entity->SetPosition( CORE_MATH_VECTOR(0.0f, 10.0f, -50.0f, 1.0f ) );
    render->SetScaleFactor( 1000.0f);
    
    //TODO: fix this index bullshit
    GetGame().GetScene().GetUpdatableSystemTable()[0]->AddEntity( entity );
    GetGame().GetScene().GetRenderableSystemTable()[1]->AddEntity( entity );
}

GRAPHIC_UI_FRAME::PTR METAL_TEST::CreateFrame() {
    
    GRAPHIC_UI_FRAME::PTR frame = new GRAPHIC_UI_FRAME;
    auto button = new GRAPHIC_UI_ELEMENT;
    button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    button->GetPlacement().SetSize(CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    button->GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( -16.0f, 16.0f ) );
    
    button->Initialize();
    
    auto network_button = new GRAPHIC_UI_ELEMENT;
    network_button->GetPlacement().SetAnchor( GRAPHIC_UI_Center );
    network_button->GetPlacement().SetSize(CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    network_button->GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( .0f, -16.0f ) );
    
    network_button->Initialize();
    
    
    frame->AddObject( button );
    frame->AddObject( network_button );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "icn-modal-close" ), CORE_FILESYSTEM_PATH::FindFilePath( "icn-modal-close", "png", "TEXTURES_BASE" ) );
    
    auto mat = new GRAPHIC_MATERIAL;
    //mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ));
    
    auto style = new GRAPHIC_UI_RENDER_STYLE( &PlanObject , UIEffectColored );
    style->SetMaterial( mat );
    
    frame->Initialize();
    //frame->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, style  );
    frame->GetPlacement().SetSize( CORE_MATH_VECTOR( 0.1f, 0.1f ) );
    
    return frame;
}

