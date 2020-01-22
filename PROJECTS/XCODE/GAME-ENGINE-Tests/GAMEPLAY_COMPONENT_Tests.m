//
//  GAMEPLAY_COMPONENT_Tests.m
//  GAME-ENGINE-Tests
//
//  Created by Christophe Bernard on 21/05/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "CORE_FILESYSTEM.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

@interface GAMEPLAY_COMPONENT_TESTS : XCTestCase

@end

@implementation GAMEPLAY_COMPONENT_TESTS {
    CORE_FILESYSTEM file_system;
}


- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    file_system.Initialize( "/Users/c.bernard/DEVELOP/PROJECTS/game-engine/RESOURCES/" );
    
    CORE_FILESYSTEM::SetDefaultFilesystem( file_system );
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testCreateEntity {
    
    //GAMEPLAY_COMPONENT_MANAGER::GetInstance().
}


@end
