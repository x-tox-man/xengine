//
//  ParentVCDelegate.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "CORE_HELPERS_CALLBACK.h"

@protocol ParentVCDelegate

-(void) CreateComponent:(NSView *) row;

-(void) SelectObject3d;
-(void) SelectEffect;
-(void) SelectScript;
-(void) SetCallback:(CORE_HELPERS_CALLBACK *) callback;

@end
