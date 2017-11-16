//
//  ResourceProxy.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RESOURCE_CONTAINER.h"
#import "GRAPHIC_OBJECT.h"
#import "GRAPHIC_SHADER_EFFECT.h"

@interface ResourceProxy : NSObject

@property GRAPHIC_OBJECT * Object3d;
@property GRAPHIC_SHADER_EFFECT * Effect;

@end
