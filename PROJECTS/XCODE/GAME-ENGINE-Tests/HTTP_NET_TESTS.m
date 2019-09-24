//
//  HTTP_NET_TESTS.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 04/03/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "SERVICE_HTTP_CLIENT.h"
#include "CORE_FILESYSTEM.h"

@interface HTTP_NET_TESTS : XCTestCase

@end

@implementation HTTP_NET_TESTS {
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

-(void)testAction {
    
    SERVICE_HTTP_REQUEST
        request( "", "", SERVICE_HTTP_REQUEST_TYPE_Get );
    
    SERVICE_HTTP_CLIENT::GetInstance().SetBaseUrl( "http://localhost:5000/api/values" );
    SERVICE_HTTP_CLIENT::GetInstance().PerformRequestAsync( request );
}

-(void)testLocalhostRequest {
    
    SERVICE_HTTP_REQUEST
        request( "", "{\"id\":11,\"nick\":\"fkdjg\",\"realName\":\"slfjghq\",\"emailAddress\":\"sljfdkg@mzkldhjf.be\"}", SERVICE_HTTP_REQUEST_TYPE_Post );
    
    SERVICE_HTTP_CLIENT::GetInstance().SetHeader("Content-Type: application/json");
    SERVICE_HTTP_CLIENT::GetInstance().SetBaseUrl( "http://localhost:5000/api/values" );
    SERVICE_HTTP_CLIENT::GetInstance().PerformRequestAsync( request );
}

@end
