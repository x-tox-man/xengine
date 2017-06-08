//
//  TIMELINE_TEST.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/06/17.
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

-(void)testAction {
    
}

-(void)serializeTimeLine {
    
}

-(void)serializeTimeLine {
    
}

@end
