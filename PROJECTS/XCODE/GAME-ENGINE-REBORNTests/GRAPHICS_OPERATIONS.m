//
//  GRAPHICS_OPERATIONS.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Foundation/Foundation.h>

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

@end
