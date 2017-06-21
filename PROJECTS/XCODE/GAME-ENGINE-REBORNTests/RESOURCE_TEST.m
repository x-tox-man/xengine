//
//  RESOURCE.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/05/17.
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
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"

@interface RESOURCE_TEST : XCTestCase

@end

@implementation RESOURCE_TEST {
    CORE_FILESYSTEM file_system;
    GRAPHIC_WINDOW_OSX_TEST * Window;
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
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    
    Window->EnableBackgroundContext( false );
    delete Window;
}

-(void)testLoadAtlas {
    
    GRAPHIC_TEXTURE_ATLAS atlas;
    
    atlas.Load( CORE_FILESYSTEM_PATH::FindFilePath("atlas_test", "iax", "TEXTURES" ), CORE_FILESYSTEM_PATH::FindFilePath("atlas_test", "png", "TEXTURES" ) );
    
    XCTAssert( atlas.GetTextureBlockTable().size() > 0 );
}

-(void)testLoadEffect {
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER:Color" ), CORE_FILESYSTEM_PATH::FindFilePath("ShaderColor", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    XCTAssert( shader != NULL );
}

-(void)testLoadImage {
    
    auto image = RESOURCE_IMAGE::LoadResourceForPath( "IMAGE:test", CORE_FILESYSTEM_PATH::FindFilePath("flowers", "png", "TEXTURES" ) );
    
    XCTAssert( image );
}

-(void) testLoadMesh {
    
    auto object = GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("cyl", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource );
    
    XCTAssert(object->GetMeshTable().size() > 0 );
}

-(void) testCreateCube {
    
    auto object = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    object->InitializeShape();

    XCTAssert(object->GetMeshTable().size() > 0 );
}

-(void) testLoadTexture {
    
    auto texture = GRAPHIC_TEXTURE::LoadResourceForPath( "TEXTURE:test", CORE_FILESYSTEM_PATH::FindFilePath("flowers", "png", "TEXTURES" ) );
    
    XCTAssert( texture );
}

-(void)testCreateResourceContainer {
    
    RESOURCE_CONTAINER * container = new RESOURCE_CONTAINER();
    RESOURCE_CONTAINER * container2 = new RESOURCE_CONTAINER();
    
    RESOURCE_PROXY * resource = new RESOURCE_PROXY( GRAPHIC_OBJECT::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "firstModel" ), CORE_FILESYSTEM_PATH::FindFilePath("cyl", "smx", "MODELS") ) );
    
    container->AddResource( resource, resource->GetIdentifier() );
    
    CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "rs1", "container", "" );
    
    container->Save( path );
    container2->Load( path );
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, RESOURCE_PROXY * >::iterator it = container->GetResourceMap().begin();
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, RESOURCE_PROXY * >::iterator it2 = container2->GetResourceMap().begin();
    
    bool success = true;
    
    while (it != container->GetResourceMap().end() ) {
        
        if ( it->first != it2->first ) {
            
            success = false;
            break;
        }
        
        it++;
        it2++;
    }
    
    XCTAssert( success );
}

-(void) testRegisterGeometryAsResource {
    
    auto object = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    object->InitializeShape();
    
    RESOURCE_CONTAINER * container = new RESOURCE_CONTAINER();
    
    container->AddResource(new RESOURCE_PROXY( object ), CORE_HELPERS_UNIQUE_IDENTIFIER("GRAPHIC_OBJECT_SHAPE_CUBE" ) );
}

@end
