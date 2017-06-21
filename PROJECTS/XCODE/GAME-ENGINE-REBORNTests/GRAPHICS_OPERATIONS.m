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
    //Window->EnableBackgroundContext( true );
    
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
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderSceneAfterSerializatrion" , "png", "" ) );
    
    RenderTarget.Discard();
    Window->EnableBackgroundContext( false );
}

@end
