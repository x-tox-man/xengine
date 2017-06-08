//
//  LeftPane3DViewController.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Custom3dTableViewDelegate.h"
#import "ParentVCDelegate.h"
#import "ModalBackDelegate.h"
#import "ResourceSelectedDelegate.h"

@interface LeftPane3DViewController : NSViewController<NSOutlineViewDelegate,NSOutlineViewDataSource, ParentVCDelegate, ModalBackDelegate, ResourceSelectedDelegate>

@property Custom3dTableViewDelegate * custom3dTableViewDelegate;

@property (weak) IBOutlet NSOutlineView *OutlineView;
@property (weak) IBOutlet NSTableView *ComponentsTableView;

-(void) CreateComponent:(NSView *) row;
-(void) SelectObject3d;
-(void) SelectEffect;

@end
