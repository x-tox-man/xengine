//
//  GRAPHICS_OPERATIONS.m
//  GAME-ENGINE-REBORN
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
    
    file_system.Initialize( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/" );
    
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
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR::Zero, lookat );
    
    RenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
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
    
    CubeEffect->Initialize( CubeObject->GetShaderBindParameter() );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CubeObject->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), lookat );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), options, CubeEffect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderCubeAt00-rs" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

-(void)testRenderTexturedQuad {
    
    auto CubeObject = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    auto CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    CubeEffect->Initialize( CubeObject->GetShaderBindParameter() );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL( "Create_Server_button" ) );
    
    CubeObject->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 1.0f ));
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), lookat );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), options, CubeEffect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderTexturedQuad-rs" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

GRAPHIC_OBJECT_ANIMATED * CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path ) {
    
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
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    AnimatedObject->Render(GRAPHIC_RENDERER::GetInstance(), options, Effect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
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
    Effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CORE_MATH_QUATERNION lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    lookat.RotateX(45.0f);
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 1000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    //AnimatedObject->GetAnimationController()->Update( 0.033f );
    
    //AnimatedObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    //options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    AnimatedObject->Render(GRAPHIC_RENDERER::GetInstance(), options, Effect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
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
    
    Effect->Initialize( text_shape->GetShaderBindParameter() );
    
    text_shape->Initialize( "Hello", *font, 1.0f, &Effect->GetProgram() );
    
    text_shape->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    //Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), lookat );
    Camera = new GRAPHIC_CAMERA_ORTHOGONAL( 10.0f, -10.0f, 10.0f, 10.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat);
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    RenderTarget.Apply();
    
    text_shape->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
    Effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    Effect->GetMaterial()->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( font->GetTexture() ) );
    
    options.SetPosition( CORE_MATH_VECTOR::Zero );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    text_shape->Render(GRAPHIC_RENDERER::GetInstance(), options, Effect );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
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
    
    CubeEffect->Initialize( CubeObject->GetShaderBindParameter() );
    CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
    
    CubeObject->InitializeShape();
    
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), lookat );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
    
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
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    
    GAMEPLAY_COMPONENT_HANDLE position_handle, render_handle;
    
    position_handle.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( position_handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    render_handle.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity->SetCompononent( render_handle, GAMEPLAY_COMPONENT_TYPE_Render );
    
    RESOURCE_PROXY effect( CubeEffect );
    RESOURCE_PROXY object( CubeObject );
    
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( effect );
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( object );
    
    scene->GetRenderableSystemTable()[0]->AddEntity( component_entity->GetHandle(), component_entity );
    
    RenderTarget.Apply();
    
    scene->Update( 0.033f );
    scene->Render();
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
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
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 100.0f, 0.0f), lookat );
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
    
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
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    
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
    
    abort(); //TODO : Fix memory placement for all objects (ex resource proxy must not be valid anymore
    scene->LoadFrom( CORE_FILESYSTEM_PATH::FindFilePath("scene-test-2", "scx", "") );
    
    RenderTarget.Apply();
    
    //scene->Update( 0.033f );
    scene->Render();
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderSceneAfterSerialization" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
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
    GRAPHIC_TEXTURE_BLOCK
        * TextureBlock = new GRAPHIC_TEXTURE_BLOCK,
        * TextureBlock2 = new GRAPHIC_TEXTURE_BLOCK,
        * TextureBlock3 = new GRAPHIC_TEXTURE_BLOCK;
    
    /*BlurEffect = (GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR ) GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SpeedBlur"), CORE_FILESYSTEM_PATH::FindFilePath( "FullScreenSpeedBlurShader" , "", "OPENGL2" ) );*/
    
    
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

    
    PrimaryRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    GaussianRenderTarget1.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    GaussianRenderTarget2.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    BloomRenderTarget.Initialize( Window->GetWidth() / 8, Window->GetHeight() / 8, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    FinalRenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    
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
    
    auto RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -100.0f, 100.0f, 1.0f, 1.0f, CORE_MATH_VECTOR::Zero, interface_lookat );
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    {
        CubeEffect->Initialize( CubeObject->GetShaderBindParameter() );
        CubeEffect->SetMaterial( new GRAPHIC_MATERIAL );
        
        CubeObject->InitializeShape();
        
        CORE_MATH_MATRIX rotation_mat;
        
        rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
        rotation_mat.XRotate(M_PI_2);
        
        CORE_MATH_QUATERNION lookat;
        
        lookat.FromMatrix( &rotation_mat[0] );
        lookat.Normalize();
        
        Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR( 0.0f, 0.0f, 10.0f, 0.0f), lookat );
        
        GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
        
        PrimaryRenderTarget.Apply();
        
        CubeObject->GetMeshTable()[0]->SetTransform( CORE_MATH_MATRIX() );
        
        CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), option, CubeEffect );
        
        GRAPHIC_TEXTURE * texture = PrimaryRenderTarget.GetTargetTexture();
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-0" , "png", "" ) );
        
        PrimaryRenderTarget.Discard();
    }
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        BloomEffect->SetMaterial( mat );
        
        BloomRenderTarget.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, BloomEffect );
        
        GRAPHIC_TEXTURE * texture = BloomRenderTarget.GetTargetTexture();
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-1" , "png", "" ) );
        
        BloomRenderTarget.Discard();
    }
    
    {
        TextureBlock->SetTexture( BloomRenderTarget.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        HorizontalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget1.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, HorizontalBlurEffect );
        
        GRAPHIC_TEXTURE * texture = GaussianRenderTarget1.GetTargetTexture();
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-2" , "png", "" ) );
        
        GaussianRenderTarget1.Discard();
    }
    
    {
        TextureBlock->SetTexture( GaussianRenderTarget1.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        VerticalBlurEffect->SetMaterial( mat );
        
        GaussianRenderTarget2.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, VerticalBlurEffect );
        
        GRAPHIC_TEXTURE * texture = GaussianRenderTarget2.GetTargetTexture();
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-3" , "png", "" ) );
        
        GaussianRenderTarget2.Discard();
    }
    
    {
        TextureBlock->SetTexture( PrimaryRenderTarget.GetTargetTexture() );
        TextureBlock2->SetTexture( GaussianRenderTarget2.GetTargetTexture() );
        
        auto mat = new GRAPHIC_MATERIAL;
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
        mat->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture1, TextureBlock2 );
        CombineBloomEffect->SetMaterial( mat );
         
        FinalRenderTarget.Apply();
        PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, CombineBloomEffect );
        
        GRAPHIC_TEXTURE * texture = FinalRenderTarget.GetTargetTexture();
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testLighBlurEffect-combined" , "png", "" ) );
        
        FinalRenderTarget.Discard();
    }
}

@end
