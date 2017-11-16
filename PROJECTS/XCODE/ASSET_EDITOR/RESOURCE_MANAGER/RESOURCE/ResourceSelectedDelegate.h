//
//  ResourceSelectedDelegate.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "ResourceProxy.h"


@protocol ResourceSelectedDelegate

-(void) OnResourceSelected:(ResourceProxy *)Resource;

@end
