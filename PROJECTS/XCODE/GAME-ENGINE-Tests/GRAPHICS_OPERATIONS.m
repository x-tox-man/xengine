//
//  GRAPHICS_OPERATIONS.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_RAY.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_SHAPE.h"
#include "CORE_DATA_STREAM.h"
#include "TestClass.h"
#include "TestClass2.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "ScriptEntity.h"
#include "RESOURCE.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_ATLAS_COMPILER.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_FONT.h"
#include "GRAPHIC_GLYPH.h"
#include "FONT_EDITOR.h"
#include "RESOURCE_CONTAINER.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_WINDOW_OSX_TEST.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GAMEPLAY_SCENE.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"
#include "GRAPHIC_MATERIAL_COLLECTION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

@interface GRAPHICS_OPERATIONS : XCTestCase

@end

@implementation GRAPHICS_OPERATIONS {
    CORE_FILESYSTEM file_system;
    GRAPHIC_WINDOW_OSX_TEST * Window;
    GRAPHIC_CAMERA
        * Camera;
    GRAPHIC_RENDER_TARGET
        RenderTarget;
}


- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    file_system.Initialize( "/Users/c.bernard/DEVELOP/PROJECTS/game-engine/RESOURCES/" );
    
    CORE_FILESYSTEM::SetDefaultFilesystem( file_system );
    
    Window = new GRAPHIC_WINDOW_OSX_TEST();
    
    CORE_APPLICATION::SetApplicationInstance( *(new CORE_APPLICATION ));
    CORE_APPLICATION::GetApplicationInstance().SetApplicationWindow( *Window );
    
    Window->SetHeight( 768 );
    Window->SetWidth( 1024 );
    
    Window->Initialize();
    Window->EnableBackgroundContext( true );
    
    CORE_MATH_QUATERNION lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    RenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    
    delete Window;
}

-(void) testRenderCubeAt00 {
    
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    CubeEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CubeObject->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), options, CubeEffect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderCubeAt00-rs" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

-(void)testRenderTexturedQuad {
    
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    CubeEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL( "game-controller" ) );
    
    CubeObject->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 1.0f ));
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), options, CubeEffect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderTexturedQuad-rs" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

GRAPHIC_OBJECT_ANIMATED * CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
    GRAPHIC_OBJECT_ANIMATED * animated_object = GRAPHIC_MESH_MANAGER::GetInstance().LoadObjectAnimated( object_path, 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    animated_object->SetAnimationController( new GRAPHIC_MESH_ANIMATION_CONTROLLER );
    
    for (int i = 0; i < animated_object->GetMeshTable().size(); i++ ) {
        
        char temp_path[128];
        
        strcpy(temp_path, animation_path.GetPath() );
        
        char buff[2];
        
        sprintf(buff, "%d", i);
        strcat( temp_path, buff );
        
        CORE_FILESYSTEM_PATH path( temp_path );
        
        animated_object->GetAnimationController()->Load( path );
        
        animated_object->GetAnimationController()->GetAnimation( i )->Initialize( animated_object->GetJointTable(), 0);
    }
    
    animated_object->GetAnimationController()->Initialize();
    
    return animated_object;
}

-(void) testRenderSimpleMesh {
    
    Window->EnableBackgroundContext( true );
    
    GRAPHIC_OBJECT::PTR AnimatedObject = GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath( "Ironman" , "smx", "MODELS" ), 1337, GRAPHIC_MESH_TYPE_ModelResource );
    
    auto Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BasicGeometryShader"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
    options;
    
    Effect->Initialize( AnimatedObject->GetShaderBindParameter() );
    Effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CORE_MATH_QUATERNION lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    lookat.RotateX(45.0f);
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    AnimatedObject->Render(GRAPHIC_RENDERER::GetInstance(), options, Effect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderSimpleMesh-rs" , "png", "" ) );
    
    RenderTarget.Discard();
}

-(void) testRenderAnimatedMesh {
    
    auto AnimatedObject = new GRAPHIC_OBJECT_ANIMATED;
    
    Window->EnableBackgroundContext( true );
    
    auto Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ObjectShader"), CORE_FILESYSTEM_PATH::FindFilePath( "Shader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    AnimatedObject = CreateAnimatedObject( CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" ), CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00.DE_Lingerie00_Skeleto" , "abx", "MODELS" ) );
    
    Effect->Initialize( AnimatedObject->GetShaderBindParameter() );
    
    Effect->GetMaterialCollection()->LoadMaterialForName( "DE_Lingerie00_Body" );
    Effect->GetMaterialCollection()->LoadMaterialForName( "DE_Lingerie00_Hands" );
    Effect->GetMaterialCollection()->LoadMaterialForName( "DE_Lingerie00_Feet" );
    Effect->GetMaterialCollection()->LoadMaterialForName( "DE_Lingerie00_Hair" );
    Effect->GetMaterialCollection()->LoadMaterialForName( "DE_Lingerie00_Face" );
    
    CORE_MATH_QUATERNION lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    lookat.RotateX(M_PI_4);
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    AnimatedObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    for (int i = 0; i < 60; i++) {
        
        AnimatedObject->GetAnimationController()->Update( 0.033f );
    }
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    AnimatedObject->Render(GRAPHIC_RENDERER::GetInstance(), options, Effect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderAnimatedMesh-rs" , "png", "" ) );
    
    RenderTarget.Discard();
}

-(void)testRenderText {
    
    GRAPHIC_TEXT * text_shape = new GRAPHIC_TEXT;
    
    GRAPHIC_FONT_MANAGER::GetInstance().LoadFont(
                                                 CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ),
                                                 CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "fxb", "FONTS/" ),
                                                 CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "png", "FONTS/" ) );
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    auto Effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
    options;
    
    Effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    text_shape->InitializeShape();
    text_shape->Initialize( L"Hello", *font, 1.0f, &Effect->GetProgram() );
    
    CORE_MATH_MATRIX rotation_mat;
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    //Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), lookat );
    Camera = new GRAPHIC_CAMERA_ORTHOGONAL( 10.0f, -10.0f, 1024.0f, 768.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    text_shape->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    Effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    Effect->GetMaterialCollection()->GetDefaultMaterial()->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( font->GetTexture() ) );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    text_shape->Render(GRAPHIC_RENDERER::GetInstance(), options, Effect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderText-rs" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

-(void)testRenderScene {
    
    //----------------- Base setup -----------------
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
    options;
    
    CubeEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CubeObject->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    
    
    //----------------- Scene setup -----------------
    GAMEPLAY_SCENE * scene = new GAMEPLAY_SCENE();
    
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    
    scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * rd = (GAMEPLAY_COMPONENT_SYSTEM_RENDERER*) scene->GetRenderableSystemTable()[0];
    
    rd->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER>();
    
    RESOURCE_PROXY effect( CubeEffect );
    RESOURCE_PROXY object( CubeObject );
    
    auto render = component_entity->GetComponentRender();
    render->SetEffect( effect );
    render->SetObject( object );
    
    scene->GetRenderableSystemTable()[0]->AddEntity( component_entity->GetHandle(), component_entity );
    
    RenderTarget.Apply();
    
    scene->Update( 0.033f );
    scene->Render( GRAPHIC_RENDERER::GetInstance(), GAMEPLAY_COMPONENT_SYSTEM_MASK_ );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderScene" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

-(void)testRenderSceneAfterSerializatrion {
    
    //----------------- Camera setup -----------------
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    //----------------- Object setup -----------------
    auto object = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    object->InitializeShape();
    
    auto effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    effect->Initialize( object->GetShaderBindParameter() );
    effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    RESOURCE_CONTAINER * container = new RESOURCE_CONTAINER();
    
    container->AddResource(new RESOURCE_PROXY( object ), CORE_HELPERS_UNIQUE_IDENTIFIER("GRAPHIC_OBJECT_SHAPE_CUBE" ) );
    container->AddResource(new RESOURCE_PROXY( effect ), effect->GetIdentifier() );
    
    //----------------- Scene setup -----------------
    GAMEPLAY_SCENE * scene = new GAMEPLAY_SCENE();
    
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    
    scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * rd = (GAMEPLAY_COMPONENT_SYSTEM_RENDERER*) scene->GetRenderableSystemTable()[0];
    
    rd->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity<GAMEPLAY_COMPONENT_ENTITY>();
    
    GAMEPLAY_COMPONENT_HANDLE position_handle, render_handle;
    
    position_handle.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( position_handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION * ) position_handle.GetComponent();
    pos->InitializeObservable();
    pos->SetPosition( CORE_MATH_VECTOR( 1.0f, 0.0f, 0.0f, 1.0f ) );
    
    RESOURCE_PROXY effect_proxy( effect );
    effect_proxy.SetIdentifier(effect->GetIdentifier());
    
    RESOURCE_PROXY object_proxy( object );
    object_proxy.SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER("GRAPHIC_OBJECT_SHAPE_CUBE" ) );
    
    render_handle.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( effect_proxy );
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( object_proxy );
    
    component_entity->SetCompononent( render_handle, GAMEPLAY_COMPONENT_TYPE_Render );
    
    rd->AddEntity( component_entity->GetHandle(), component_entity );
    
    scene->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath("scene-test-2", "scx", "") );
    
    scene->Clear();
    
    /*#error "TODO implement" // TODO: Fix memory placement for all objects (ex resource proxy must not be valid anymore
    scene->LoadFrom( CORE_FILESYSTEM_PATH::FindFilePath("scene-test-2", "scx", "") );
    
    RenderTarget.Apply();
    
    //scene->Update( 0.033f );
    scene->Render( GRAPHIC_RENDERER::GetInstance() );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderSceneAfterSerialization" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );*/
}

-(void) testLighBlurEffect {
    
    GRAPHIC_OBJECT_SHAPE_PLAN
        * PlanObject = new GRAPHIC_OBJECT_SHAPE_PLAN;
    GRAPHIC_RENDER_TARGET
        PrimaryRenderTarget,
        FinalRenderTarget,
        LightRenderTarget,
        SpecularRenderTarget,
        GaussianRenderTarget1,
        GaussianRenderTarget2,
        BloomRenderTarget;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock = new GRAPHIC_TEXTURE_BLOCK,
        TextureBlock2 = new GRAPHIC_TEXTURE_BLOCK,
        TextureBlock3 = new GRAPHIC_TEXTURE_BLOCK;
    
    
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR BloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::BloomShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenBloomPostProcess" , "", "OPENGL2" ) ) );
    
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR HorizontalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::HZBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianHorrizontalBlurPostProcess" , "", "OPENGL2" ) ) );
    
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR VerticalBlurEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::VBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenGaussianVerticalBlurPostProcess" , "", "OPENGL2" ) ) );
    
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::PTR CombineBloomEffect = new GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::CombineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullscreenCombinePostProcess" , "", "OPENGL2" ) ) );
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    BloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    HorizontalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    VerticalBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CombineBloomEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );

    
    PrimaryRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    PrimaryRenderTarget.Discard();
    GaussianRenderTarget1.Discard();
    GaussianRenderTarget2.Discard();
    BloomRenderTarget.Discard();
    FinalRenderTarget.Discard();
    
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    interface_lookat.Normalize();
    
    PlanObject->InitializeShape();
    
    auto RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    {
        CubeObject->InitializeShape();
        CubeEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
        CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
        
        CORE_MATH_MATRIX rotation_mat;
        
        rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
        rotation_mat.XRotate(M_PI_2);
        
        CORE_MATH_QUATERNION lookat;
        
        lookat.FromMatrix( &rotation_mat[0] );
        lookat.Normalize();
        
        Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
        
        GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
        
        PrimaryRenderTarget.Apply();
        
        CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
        
        CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), option, CubeEffect );
        
        GRAPHIC_TEXTURE * texture = PrimaryRenderTarget.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-0" , "png", "" ) );
        
        PrimaryRenderTarget.Discard();
    }
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        BloomEffect->SetMaterial( mat );
        
        BloomRenderTarget.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, BloomEffect );
        
        GRAPHIC_TEXTURE * texture = BloomRenderTarget.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-1" , "png", "" ) );
        
        BloomRenderTarget.Discard();
    }
    
    {
        TextureBlock->SetTexture( BloomRenderTarget.GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        HorizontalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget1.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, HorizontalBlurEffect );
        
        GRAPHIC_TEXTURE * texture = GaussianRenderTarget1.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-2" , "png", "" ) );
        
        GaussianRenderTarget1.Discard();
    }
    
    {
        TextureBlock->SetTexture( GaussianRenderTarget1.GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        VerticalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget2.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, VerticalBlurEffect );
        
        GRAPHIC_TEXTURE * texture = GaussianRenderTarget2.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-3" , "png", "" ) );
        
        GaussianRenderTarget2.Discard();
    }
    
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture( 0 ) );
        TextureBlock2->SetTexture( GaussianRenderTarget2.GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock2 );
        CombineBloomEffect->SetMaterial( mat );
         
        FinalRenderTarget.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, CombineBloomEffect );
        
        GRAPHIC_TEXTURE * texture = FinalRenderTarget.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-combined" , "png", "" ) );
        
        FinalRenderTarget.Discard();
    }
}

-(void) testMotionBlurEffect {
    
    GRAPHIC_OBJECT_SHAPE_PLAN
        * PlanObject = new GRAPHIC_OBJECT_SHAPE_PLAN;
    GRAPHIC_RENDER_TARGET
        PrimaryRenderTarget,
        FinalRenderTarget;
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    PrimaryRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    PrimaryRenderTarget.Discard();
    FinalRenderTarget.Discard();
    
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR SpeedBlurEffect = new GRAPHIC_SHADER_EFFECT_SPEEDBLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::FullScreenSpeedBlurShader"), CORE_FILESYSTEM_PATH::FindFilePath( "FullScreenSpeedBlurShader" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    SpeedBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    interface_lookat.Normalize();
    
    PlanObject->InitializeShape();
    
    auto RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    CORE_MATH_QUATERNION v_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    v_lookat.Normalize();
    
    Camera->UpdateCamera( CORE_MATH_VECTOR( -10.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis );
    
    CORE_MATH_MATRIX previous_mat( &Camera->GetProjectionMatrix()[0] );
    
    previous_mat *= Camera->GetViewMatrix();
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::PreviousModelViewProjectionIdentifier ).AttributeValue.Value.FloatMatrix4x4,
           (void*) &previous_mat[0],
           16* sizeof(float) );

    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis );
    
    CORE_MATH_MATRIX current_mat( &Camera->GetProjectionMatrix()[0] );
    
    CORE_MATH_MATRIX inv( CORE_MATH_MATRIX::Identity );
    
    current_mat *= Camera->GetViewMatrix();
    current_mat.GetInverse( inv );
    
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::InverseCurrentModelViewIdentifier ).AttributeValue.Value.FloatMatrix4x4,
           (void*) &inv[0],
           16* sizeof(float) );
    
    {
        CubeObject->InitializeShape();
        CubeEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
        CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
        
        CORE_MATH_MATRIX rotation_mat;
        
        rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
        rotation_mat.XRotate(M_PI_2);
        
        CORE_MATH_QUATERNION lookat;
        
        lookat.FromMatrix( &rotation_mat[0] );
        lookat.Normalize();
        
        Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
        
        GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
        
        PrimaryRenderTarget.Apply();
        
        CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
        
        CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), option, CubeEffect );
        
        GRAPHIC_TEXTURE * texture = PrimaryRenderTarget.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testMotionBlurEffect-0" , "png", "" ) );
        
        PrimaryRenderTarget.Discard();
    }
    
    CORE_MATH_VECTOR deltaPosition = CORE_MATH_VECTOR( 10.0f, 0.0f, 0.0f, 0.0f);
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::ViewRayIdentifier ).AttributeValue.Value.FloatArray4,
           (void*) &deltaPosition[0],
           4* sizeof(float) );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    {
        GRAPHIC_TEXTURE_BLOCK::PTR tb = new GRAPHIC_TEXTURE_BLOCK();
        tb->SetTexture( PrimaryRenderTarget.GetTargetTexture( 0 ) );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, tb );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::DepthTexture, tb );
        SpeedBlurEffect->SetMaterial( mat );
        
        FinalRenderTarget.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, SpeedBlurEffect );
        
        GRAPHIC_TEXTURE * texture = FinalRenderTarget.GetTargetTexture( 0 );
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testMotionBlurEffect-Final" , "png", "" ) );
        
        FinalRenderTarget.Discard();
    }
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::PreviousModelViewProjectionIdentifier ).AttributeValue.Value.FloatMatrix4x4,
           (void*) &previous_mat[0],
           16* sizeof(float) );
}

/*-(void) testShapeModelViewZSorting {
    
    GRAPHIC_CAMERA camera;
    AABBTree tree;
    CORE_MATH_QUATERNION q;
    AABBNodeFrontToBackFustrumCollider
        collider;
    
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
    options;
    
    CubeEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CubeObject->InitializeShape();
    
    CORE_HELPERS_CALLBACK_1< AABBNode * > callback( Wrapper1<AABBNodeFrontToBackFustrumCollider, AABBNode *, &AABBNodeFrontToBackFustrumCollider::Collide>, &collider );
    
    GAMEPLAY_COMPONENT_ENTITY
    * entity1 = new GAMEPLAY_COMPONENT_ENTITY,
    * entity2 = new GAMEPLAY_COMPONENT_ENTITY,
    * entity3 = new GAMEPLAY_COMPONENT_ENTITY;
    
    {
        GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r;
        RESOURCE_PROXY proxy;
        
        proxy.SetResource( CubeObject );
        
        handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
        handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
        
        entity1->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
        entity1->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
        entity1->SetPosition(CORE_MATH_VECTOR( -10.0f, 0.0f ) );
        
        GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity1->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        
        render->SetObject( proxy );
    }
    
    {
        GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r;
        RESOURCE_PROXY proxy;
        
        proxy.SetResource( CubeObject );
        
        handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
        handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
        
        entity2->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
        entity2->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
        entity2->SetPosition(CORE_MATH_VECTOR( 10.0f, 10.0f ) );
        
        GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity2->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        
        render->SetObject( proxy );
    }
    
    {
        GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r;
        RESOURCE_PROXY proxy;
        
        proxy.SetResource( CubeObject );
        
        handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
        handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
        
        entity3->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
        entity3->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
        entity3->SetPosition(CORE_MATH_VECTOR( -11.0f, 1.0f ) );
        
        GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity3->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        
        render->SetObject( proxy );
    }
    
    
    
    tree.Insert( entity1 );
    tree.Insert( entity2 );
    tree.Insert( entity3 );
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.YRotate( M_PI_2 );
    
    q.RotateY( M_PI_2 );
    q.FromMatrix( &rotation_mat[0] );
    
    camera.Reset(1.0f, 100.0f, 1024.0f, 768.0f, CORE_MATH_VECTOR( -4.0f, 1.0f, 0.0f, 1.0f), q );
    camera.ActivateForRender();
    
    tree.QueryTopToBottom( camera.GetFustrum(), callback );
    
    XCTAssert( collider.Amount == 2 );
}*/

-(void) testCameraXYZ {
    
    GRAPHIC_CAMERA camera;
    CORE_MATH_MATRIX mvp, object_matrix;
    camera.Reset( 1.0f, 150.0f, 1024.0f, 768.0f, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis,
          CORE_MATH_VECTOR::YAxis );
    
    CORE_MATH_VECTOR vector( 0.0f, 0.0f, -10.0f, 1.0f ), result;
    
    mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * object_matrix;
    result = mvp * vector;
}

-(void) testCameraXYZ2 {
    
    GRAPHIC_CAMERA camera;
    CORE_MATH_MATRIX mvp, object_matrix;
    camera.Reset( 1.0f, 150.0f, 1024.0f, 768.0f, CORE_MATH_VECTOR( 2.2f, -2.4f + 0.15f, -6.6f + 1.95f, 1.0f ), CORE_MATH_VECTOR::ZAxis,
                 CORE_MATH_VECTOR::YAxis );
    
    CORE_MATH_VECTOR vector( 2.2f, -2.4f, -6.6f, 1.0f ), result;
    
    mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * object_matrix;
    result = mvp * vector;
}

@end
