//
//  GLOBAL_RESOURCES.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GLOBAL_RESOURCES.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_APPLICATION.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GLOBAL_RESOURCES::GLOBAL_RESOURCES() :
    ComponentIndex( 0 ),
    ResourceObject( NULL ),
    ChrisObject( NULL ) {
    
}

GLOBAL_RESOURCES::~GLOBAL_RESOURCES() {
    
}

void GLOBAL_RESOURCES::Initialize( GAMEPLAY_SCENE * scene ) {
    
    UITextureAtlas.Load(
        CORE_FILESYSTEM_PATH::FindFilePath( "atlas_test", "iax", "TEXTURES" ),
        CORE_FILESYSTEM_PATH::FindFilePath( "atlas_test", "png", "TEXTURES" ));
    GRAPHIC_SHADER_EFFECT::PTR
        ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) ),
        ui_colored_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderColored"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderColored" , "vsh", "OPENGL2" ) );
    
    UIPlanObject = new GRAPHIC_OBJECT_SHAPE_PLAN;
    UIPlanObjectColorOnly = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    ui_textured_shader_effect->Initialize( UIPlanObject->GetShaderBindParameter() );
    UIPlanObject->InitializeShape();
    
    ui_colored_shader_effect->Initialize( UIPlanObjectColorOnly->GetShaderBindParameter() );
    UIPlanObjectColorOnly->InitializeShape();
    
    UIFrameTextureBlock = new GRAPHIC_TEXTURE_BLOCK;
    
    UIFrameTextureBlock->SetTexture( CreateTextureFromImagePath("frameBorder") );
    UIFrameTextureBlock->Initialize();
    
    FrameRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    
    FrameRenderStyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    FrameRenderStyle->SetDecoratingShape( CreateFrameBorder( 11.0f / 400.0f, 11.0f / 200.0f, ui_textured_shader_effect) );
    FrameRenderStyle->SetDecoratingTextureBlock( UIFrameTextureBlock );
    FrameRenderStyle->SetShape(UIPlanObjectColorOnly);
    
    CellRenderStyle= new GRAPHIC_UI_RENDER_STYLE;
    
    CellRenderStyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    CellRenderStyle->SetDecoratingShape( CreateFrameBorder( 11.0f / 500.0f, 11.0f / 32.0f, ui_textured_shader_effect ) );
    CellRenderStyle->SetDecoratingTextureBlock( UIFrameTextureBlock );
    CellRenderStyle->SetShape(UIPlanObjectColorOnly);

    PageFrameRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    
    PageFrameRenderStyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    PageFrameRenderStyle->SetDecoratingShape( CreateFrameBorder( 11.0f / 600.0f, 11.0f / 300.0f, ui_textured_shader_effect ) );
    PageFrameRenderStyle->SetDecoratingTextureBlock( UIFrameTextureBlock );
    PageFrameRenderStyle->SetShape(UIPlanObjectColorOnly);
    
    InitializeFromApplicationRefactor( scene );
}

void GLOBAL_RESOURCES::InitializeFromApplicationRefactor(GAMEPLAY_SCENE * scene ) {
    
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 1" );
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    
    SERVICE_LOGGER_Error( "Trying to load resource 1" );
    ChrisObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "Chris" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "Chris.geom-chris-base-skin1" , "abx", "MODELS" ));
    
    NakedGirlObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00.DE_Lingerie00_Skeleto" , "abx", "MODELS" ));
    
    Moulin = GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath( "MoulinNoAnim" , "smx", "MODELS" ), 1337, GRAPHIC_MESH_TYPE_ModelResource);
    
    SERVICE_LOGGER_Error( "loaded resource 1" );
    
    GRAPHIC_SHADER_EFFECT::PTR effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::Default"), CORE_FILESYSTEM_PATH::FindFilePath( "Shader" , "vsh", "OPENGL2" ) );
    
    GRAPHIC_SHADER_EFFECT::PTR effect_shadow_map = GRAPHIC_SHADER_EFFECT::LoadEffectWithVertexAndFragmentPath(
        CORE_FILESYSTEM_PATH::FindFilePath( "ShaderShadowMap" , "vsh", "OPENGL2" ),
        CORE_FILESYSTEM_PATH::FindFilePath( "ShadowMapEffect" , "fsh", "OPENGL2" ),
        CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShadowMapShader"));
    
    GRAPHIC_SHADER_EFFECT::PTR BasicEffectShadowMap = GRAPHIC_SHADER_EFFECT::LoadEffectWithVertexAndFragmentPath(
        CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometrySMShader" , "vsh", "OPENGL2" ),
        CORE_FILESYSTEM_PATH::FindFilePath( "ShadowMapEffect" , "fsh", "OPENGL2" ),
        CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BaicShadowMapShader"));
    
    GRAPHIC_SHADER_EFFECT::PTR basic_geometry_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", "OPENGL2" ) );
    
    basic_geometry_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    BasicEffectShadowMap->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    
    RESOURCE_IMAGE * image = NULL;
    
    image = RESOURCE_IMAGE::LoadResourceForPath( "HANDS_DE_GL_N_00", CORE_FILESYSTEM_PATH::FindFilePath( "HANDS_DE_GL_N_00", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[0]->SetTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HEAD_DE_FC_N_05", CORE_FILESYSTEM_PATH::FindFilePath( "HEAD_DE_FC_N_05", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[1]->SetTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HEAD_DE_FC_N_05", CORE_FILESYSTEM_PATH::FindFilePath( "HEAD_DE_FC_N_05", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[2]->SetTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "FEET_DE_FT_N_00", CORE_FILESYSTEM_PATH::FindFilePath( "FEET_DE_FT_N_00", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[3]->SetTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HEAD_DE_FC_N_05", CORE_FILESYSTEM_PATH::FindFilePath( "HEAD_DE_FC_N_05", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[4]->SetTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HAIR_CO_HR_N_24", CORE_FILESYSTEM_PATH::FindFilePath( "HAIR_CO_HR_N_24", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[5]->SetTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HANDS_DE_GL_N_00_NR", CORE_FILESYSTEM_PATH::FindFilePath( "HANDS_DE_GL_N_00_NR", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[0]->SetNormalTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HEAD_DE_FC_N_05_NR", CORE_FILESYSTEM_PATH::FindFilePath( "HEAD_DE_FC_N_05_NR", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[1]->SetNormalTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "BODY_DE_BD_N_00_NR", CORE_FILESYSTEM_PATH::FindFilePath( "BODY_DE_BD_N_00_NR", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[2]->SetNormalTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "FEET_DE_FT_N_00_NR", CORE_FILESYSTEM_PATH::FindFilePath( "FEET_DE_FT_N_00_NR", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[3]->SetNormalTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HEAD_DE_FC_N_05_NR", CORE_FILESYSTEM_PATH::FindFilePath( "HEAD_DE_FC_N_05_NR", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[4]->SetNormalTexture( image->CreateTextureObject( true ) );
    
    image=RESOURCE_IMAGE::LoadResourceForPath( "HAIR_CO_HR_N_24_NR", CORE_FILESYSTEM_PATH::FindFilePath( "HAIR_CO_HR_N_24_NR", "png", "MODEL_TEXTURES" ) );
    NakedGirlObject->GetMeshTable()[5]->SetNormalTexture( image->CreateTextureObject( true ) );
    
    effect->Initialize( NakedGirlObject->GetMeshTable()[0]->GetVertexComponent() );
    effect_shadow_map->Initialize( NakedGirlObject->GetMeshTable()[0]->GetVertexComponent() );
    
    NakedGirlObject->SetShaderForMesh( NULL, &effect->GetProgram() );
    NakedGirlObject->SetShaderForMesh( NULL, &effect_shadow_map->GetProgram() );
    
    ChrisObject->SetShaderForMesh( NULL, &effect->GetProgram() );
    ChrisObject->SetShaderForMesh( NULL, &effect_shadow_map->GetProgram() );
    
    GRAPHIC_SHADER_EFFECT::PTR plane_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "ShaderColor" , "vsh", "OPENGL2" ) );
    GRAPHIC_SHADER_EFFECT::PTR line_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::LineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "LineShader" , "vsh", "OPENGL2" ) );
    
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 55" );
    
    PlanObject = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    EffectPlan = new GRAPHIC_OBJECT_SHAPE_PLAN;
    CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
    SphereObject = new GRAPHIC_OBJECT_SHAPE_SPHERE;
    Line = new GRAPHIC_OBJECT_SHAPE_LINE;
    
    RESOURCE_IMAGE * height_map = (RESOURCE_IMAGE*) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath("heightmap", "png", "MAP" ) );
    
    float * heights = (float * ) height_map->GetImageRawData();
    height_map->SetImageRawData( NULL );
    
    HeightMapObject = new GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( heights, height_map->GetImageInfo().Width, height_map->GetImageInfo().Height, 2.0f );
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 56" );
    
    CORE_MEMORY_ObjectSafeDeallocation( height_map);
    
    plane_shader_effect->Initialize( PlanObject->GetShaderBindParameter() );
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 57" );
    
    line_shader_effect->Initialize( PlanObject->GetShaderBindParameter() );
    
    HeightMapObject->InitializeShape( &basic_geometry_effect->GetProgram() );
    HeightMapObject->SetShaderForMesh(NULL, BasicEffectShadowMap->GetProgram().GetProgram());
    CubeObject->InitializeShape( &plane_shader_effect->GetProgram() );
    CubeObject->SetShaderForMesh(NULL, &BasicEffectShadowMap->GetProgram());
    Line->InitializeShape( &line_shader_effect->GetProgram() );
    
    PlanObject->InitializeShape( &BlurEffect->GetProgram() );
    
    Moulin->SetShaderForMesh( NULL, &basic_geometry_effect->GetProgram() );
    
    CORE_MEMORY_ALLOCATOR_Free( heights );
    
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2" );
    
#if PLATFORM_WINDOWS || PLATFORM_OSX
    ShadowMapRenderTarget.InitializeDepthTexture( 1024, 1024, GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    
    const GRAPHIC_WINDOW & window = CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow();
    
    PrimaryRenderTarget.Initialize( window.GetWidth(), window.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1 );
    GaussianRenderTarget.Initialize( window.GetWidth(), window.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1 );
    BloomRenderTarget.Initialize( window.GetWidth()/8, window.GetHeight() /8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1 );
    
    PrimaryRenderTarget.Discard();
    GaussianRenderTarget.Discard();
    BloomRenderTarget.Discard();
    
    BlurEffect = (GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR ) GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SpeedBlur"), CORE_FILESYSTEM_PATH::FindFilePath( "FullScreenSpeedBlurShader" , "", "OPENGL2" ) );
    BloomEffect = (GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR ) GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "", "OPENGL2" ) );
    HorizontalBlurEffect = (GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR ) GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::HZBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianHorrizontalBlurPostProcess" , "", "OPENGL2" ) );
    VerticalBlurEffect = (GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR ) GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::VBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianVerticalBlurPostProcess" , "", "OPENGL2" ) );
    CombineBloomEffect = (GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::PTR ) GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::CombineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenCombinePostProcess" , "", "OPENGL2" ) );
    
    BlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    BloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    HorizontalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    VerticalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CombineBloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    EffectPlan->InitializeShape( &BloomEffect->GetProgram() );
    
    EffectPlan->SetEffect( BloomEffect );
    EffectPlan->SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
    EffectPlan->SetScaleFactor( CORE_MATH_VECTOR( 1024.0f, 768.0f, 0.0f, 1.0f ) );
    
    TextureBlock = new GRAPHIC_TEXTURE_BLOCK;
    TextureBlock->SetOffset(CORE_MATH_VECTOR::Zero );
    TextureBlock->SetSize( CORE_MATH_VECTOR::One );
    TextureBlock->SetTexture( PrimaryRenderTarget.TargetTexture );
    
    EffectPlan->SetTextureBlock( TextureBlock );
    
    AlternateTextureBlock = new GRAPHIC_TEXTURE_BLOCK;
    AlternateTextureBlock->SetOffset(CORE_MATH_VECTOR::Zero );
    AlternateTextureBlock->SetSize( CORE_MATH_VECTOR::One );
    AlternateTextureBlock->SetTexture( GaussianRenderTarget.TargetTexture );
    
#endif
    
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.1" );
    
    BasicGeometryEffect = ( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR )  GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderPoNoUVTaBi"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", "OPENGL2" ) );
    
    BasicGeometryEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.14" );
    component_entity2 = CreateMesh( CORE_FILESYSTEM_PATH::FindFilePath("T_34_85", "smx", "MODELS" ) ,&BasicGeometryEffect->GetProgram(), CORE_MATH_VECTOR( 5.0f,0.0f,.0f,0.0f ), scene);
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.14" );
    CreateMesh( CORE_FILESYSTEM_PATH::FindFilePath("thor", "smx", "MODELS" ) ,&BasicGeometryEffect->GetProgram(), CORE_MATH_VECTOR( 10.0f,0.0f,.0f,0.0f ), scene);
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.15" );
    CreateMesh( CORE_FILESYSTEM_PATH::FindFilePath("cyl", "smx", "MODELS" ) ,&BasicGeometryEffect->GetProgram(), CORE_MATH_VECTOR( 15.0f,0.0f,.0f,0.0f ), scene);
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.16" );
    CreateMesh( CORE_FILESYSTEM_PATH::FindFilePath("mesh2", "smx", "MODELS" ) ,&BasicGeometryEffect->GetProgram(), CORE_MATH_VECTOR( 20.0f,0.0f,.0f,0.0f ), scene);
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.17" );
    CreateMesh( CORE_FILESYSTEM_PATH::FindFilePath("untitled", "smx", "MODELS" ) ,&BasicGeometryEffect->GetProgram(), CORE_MATH_VECTOR( 25.0f,0.0f,.0f,0.0f ), scene);
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.18" );
    CreateMesh( CORE_FILESYSTEM_PATH::FindFilePath("Ironman", "smx", "MODELS" ) ,&BasicGeometryEffect->GetProgram(), CORE_MATH_VECTOR( 30.0f,0.0f,.0f,0.0f ), scene);
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.19" );
    RESOURCE_IMAGE::FlushCache();
    
    SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 2.2" );
    
    GRAPHIC_PARTICLE_MANAGER * man = new GRAPHIC_PARTICLE_MANAGER();
    GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * emiter = new GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL( "smoke", "BasicParticleShader", GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    emiter->Initialize(200, 5.0f, material );
    
    GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_v = new GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_g = new GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>( 9.81f);
    
    emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_g) );
    emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_v) );
    
    man->AddEmiter(*((GRAPHIC_PARTICLE_EMITER_BASE_CLASS *)emiter));
    
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().AddManager(*man);
    
    DirectionalLight = new GRAPHIC_SHADER_LIGHT;
    
    CORE_MATH_VECTOR diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    CORE_MATH_VECTOR direction(0.0f, -1.0f, 0.0f, 1.0f);
    
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
    
    CreateGround( scene );
    CreateChris( scene );
    CreateNakedGirl( scene );
    CreateMoulin( scene );
    
}

void GLOBAL_RESOURCES::Finalize() {
    
    UITextureAtlas.Finalize();
    
    CORE_MEMORY_ObjectSafeDeallocation( UIPlanObject );
    CORE_MEMORY_ObjectSafeDeallocation( FrameRenderStyle );
    CORE_MEMORY_ObjectSafeDeallocation( CellRenderStyle );
    CORE_MEMORY_ObjectSafeDeallocation( PageFrameRenderStyle );
    
    NakedGirlObject->Release();
    CubeObject->Release();
    HeightMapObject->Release();
    SphereObject->Release();
    Line->Release();
    PlanObject->Release();
    EffectPlan->Release();
    
    RESOURCE_IMAGE::FlushCache();
    GRAPHIC_SHADER_EFFECT::FlushCache();
    
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[0]->GetTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[1]->GetTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[2]->GetTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[3]->GetTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[4]->GetTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[5]->GetTexture() );
    
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[0]->GetNormalTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[1]->GetNormalTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[2]->GetNormalTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[3]->GetNormalTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[4]->GetNormalTexture() );
    GRAPHIC_SYSTEM::ReleaseTexture( NakedGirlObject->GetMeshTable()[5]->GetNormalTexture() );
    
    CORE_MEMORY_ObjectSafeDeallocation( NakedGirlObject );
    CORE_MEMORY_ObjectSafeDeallocation( PlanObject);
    CORE_MEMORY_ObjectSafeDeallocation( EffectPlan );
    CORE_MEMORY_ObjectSafeDeallocation( CubeObject );
    CORE_MEMORY_ObjectSafeDeallocation( HeightMapObject );
    CORE_MEMORY_ObjectSafeDeallocation( SphereObject );
    
    CORE_MEMORY_ObjectSafeDeallocation( Line );
    
    CORE_MEMORY_ObjectSafeDeallocation( DirectionalLight );
    CORE_MEMORY_ObjectSafeDeallocation( PointLightOne );
    CORE_MEMORY_ObjectSafeDeallocation( PointLightTwo);
    CORE_MEMORY_ObjectSafeDeallocation( SpotLightOne );
    CORE_MEMORY_ObjectSafeDeallocation( SpotLightTwo );
}

GRAPHIC_TEXTURE * GLOBAL_RESOURCES::CreateTextureFromImagePath(const char * image_path) {
    
    auto image = RESOURCE_IMAGE::LoadResourceForPath( image_path, CORE_FILESYSTEM_PATH::FindFilePath( image_path, "png", "TEXTURES" ) );
    
    return image->CreateTextureObject( false );
}

GRAPHIC_OBJECT_SHAPE_FRAME * GLOBAL_RESOURCES::CreateFrameBorder( float height, float width, GRAPHIC_SHADER_EFFECT::PTR shader ) {
    
    auto frame = new GRAPHIC_OBJECT_SHAPE_FRAME;
    
    frame->SetBorderSize( height, width);
    frame->InitializeShape( &shader->GetProgram() );
    
    return frame;
}

void GLOBAL_RESOURCES::CreateGround(GAMEPLAY_SCENE * scene) {
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    
    //should not be done like this
    
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject(  HeightMapObject );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( component_entity );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) scene->GetUpdatableSystemTable()[3];
    
    CORE_MATH_VECTOR position ( -256.0f, -60.0f, -256.0f, 1.0f );
    
    ( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapePlane( position );
    
    bullet_system->AddEntity(component_entity);
    
    component_entity->SetPosition( position );
}

void GLOBAL_RESOURCES::CreateNakedGirl(GAMEPLAY_SCENE * scene) {
    
    component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    component_entity->SetIndex( ComponentIndex++ );
    
    //should not be done like this
    
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Animation ), GAMEPLAY_COMPONENT_TYPE_Animation );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject( NakedGirlObject );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( component_entity );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) scene->GetUpdatableSystemTable()[3];
    GAMEPLAY_COMPONENT_SYSTEM_ANIMATING * animation_system = ( GAMEPLAY_COMPONENT_SYSTEM_ANIMATING * ) scene->GetUpdatableSystemTable()[1];
    
    CORE_MATH_VECTOR position ( 0.0f, 20.0f, 0.0f, 1.0f );
    
    ( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapeSphere( position );
    
    ( ( GAMEPLAY_COMPONENT_ANIMATION *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Animation))->SetAnimation( ((GRAPHIC_OBJECT_ANIMATED*) NakedGirlObject)->GetAnimationController() );
    
    bullet_system->AddEntity( component_entity );
    animation_system->AddEntity( component_entity );
    
    component_entity->SetPosition( position );
}

void GLOBAL_RESOURCES::CreateChris(GAMEPLAY_SCENE * scene) {
    
    component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    component_entity->SetIndex( ComponentIndex++ );
    
    //should not be done like this
    
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Animation ), GAMEPLAY_COMPONENT_TYPE_Animation );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject( ChrisObject );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( component_entity );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) scene->GetUpdatableSystemTable()[3];
    GAMEPLAY_COMPONENT_SYSTEM_ANIMATING * animation_system = ( GAMEPLAY_COMPONENT_SYSTEM_ANIMATING * ) scene->GetUpdatableSystemTable()[1];
    
    CORE_MATH_VECTOR position ( 0.0f, 10.0f, 0.0f, 1.0f );
    
    ( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapeSphere( position );
    
    ( ( GAMEPLAY_COMPONENT_ANIMATION *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Animation))->SetAnimation( ((GRAPHIC_OBJECT_ANIMATED*) ChrisObject)->GetAnimationController() );
    
    bullet_system->AddEntity( component_entity );
    animation_system->AddEntity( component_entity );
    
    component_entity->SetPosition( position );
}

void GLOBAL_RESOURCES::CreateMoulin(GAMEPLAY_SCENE * scene) {
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    component_entity->SetIndex( ComponentIndex++ );
    
    //should not be done like this
    
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject( Moulin );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( component_entity );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) scene->GetUpdatableSystemTable()[3];
    
    CORE_MATH_VECTOR position ( 1.0f, 0.0f, -5000.0f, 1.0f );
    
    ( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapeSphere( position );
    
    bullet_system->AddEntity(component_entity);
    
    component_entity->SetPosition( position );
}

GAMEPLAY_COMPONENT_ENTITY * GLOBAL_RESOURCES::CreateMesh( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
    const CORE_MATH_VECTOR & position,
    GAMEPLAY_SCENE * scene ) {
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    component_entity->SetIndex( ComponentIndex++ );
    
    //should not be done like this
    
    GRAPHIC_OBJECT * object = GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( path, 0, GRAPHIC_MESH_TYPE_ModelResource );
    
    object->GetShaderTable().resize( 1 );
    object->GetShaderTable()[ 0 ] = program;
    
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject(  object );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( component_entity );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) scene->GetUpdatableSystemTable()[3];
    
    ( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapePlane( position );
    
    bullet_system->AddEntity(component_entity);
    
    component_entity->SetPosition( position );
    
    return component_entity;
}

GRAPHIC_OBJECT_ANIMATED * GLOBAL_RESOURCES::CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
    GRAPHIC_OBJECT_ANIMATED * animated_object = GRAPHIC_MESH_MANAGER::GetInstance().LoadObjectAnimated( object_path, 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    animated_object->SetAnimationController( new GRAPHIC_MESH_ANIMATION_CONTROLLER );
    
    for (int i = 0; i < animated_object->GetMeshTable().size(); i++ ) {
        
        char * temp_path = (char *) CORE_MEMORY_ALLOCATOR::Allocate(strlen( animation_path.GetPath() ) + 2 );
        
        strcpy(temp_path, animation_path.GetPath() );
        
        char buff[2];
        
        sprintf(buff, "%d", i);
        strcat( temp_path, buff );
        
        CORE_FILESYSTEM_PATH path( temp_path );
        
        animated_object->GetAnimationController()->Load( path );
        
        animated_object->GetAnimationController()->GetAnimation( i )->Initialize( animated_object->GetJointTable(), 0);
        
        CORE_MEMORY_ALLOCATOR_Free( temp_path );
    }
    
    animated_object->GetAnimationController()->Initialize();
    
    return animated_object;
}
