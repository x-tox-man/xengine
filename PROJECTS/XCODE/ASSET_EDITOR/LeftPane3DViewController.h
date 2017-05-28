//
//  LeftPane3DViewController.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Custom3dTableViewDelegate.h"

@interface LeftPane3DViewController : NSViewController<NSOutlineViewDelegate,NSOutlineViewDataSource>

@property Custom3dTableViewDelegate * custom3dTableViewDelegate;

@property (weak) IBOutlet NSOutlineView *OutlineView;
@property (weak) IBOutlet NSTableView *ComponentsTableView;

@end
