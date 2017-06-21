//
//  GAMEPLAY_TEST.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 13/06/17.
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

@interface GAMEPLAY_TEST : XCTestCase

@end

@implementation GAMEPLAY_TEST {
    CORE_FILESYSTEM file_system;
}


- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    file_system.Initialize( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/" );
    
    CORE_FILESYSTEM::SetDefaultFilesystem( file_system );
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testSerializeScene {
    
    GAMEPLAY_SCENE * scene = new GAMEPLAY_SCENE();
    
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    
    scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    
    GAMEPLAY_COMPONENT_HANDLE handle;
    
    handle.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    scene->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath("scene-test", "scx", "") );
    
    scene->Clear();
    scene->LoadFrom( CORE_FILESYSTEM_PATH::FindFilePath("scene-test", "scx", "") );
}

-(void)unserializeSceneAndCheckResult {
    
}

@end
