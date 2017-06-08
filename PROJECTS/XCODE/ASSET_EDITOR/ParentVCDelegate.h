//
//  ParentVCDelegate.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//


@protocol ParentVCDelegate

-(void) CreateComponent:(NSView *) row;

-(void) SelectObject3d;
-(void) SelectEffect;
-(void) SelectScript;

@end
