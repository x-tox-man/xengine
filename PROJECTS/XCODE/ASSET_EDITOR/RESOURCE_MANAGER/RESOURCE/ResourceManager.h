//
//  ResourceManager.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ResourceSelectedDelegate.h"

@interface ResourceManager : NSViewController<NSTableViewDataSource, NSTableViewDelegate>

@property (weak) IBOutlet NSTableView *TableView;
@property NSMutableArray * FilteredTypes;
@property NSString * ResourceType;
@property NSObject<ResourceSelectedDelegate> * ResourceDelegate;

-(void) rowDoubleClicked;

@end
