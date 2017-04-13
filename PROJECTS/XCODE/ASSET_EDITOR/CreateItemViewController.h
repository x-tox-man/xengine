//
//  CreateItemViewController.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import "ItemTableViewSource.h"
#import "ItemTableViewDelegate.h"

@interface CreateItemViewController : NSViewController

@property (weak) IBOutlet NSTableView * TableView;
@property (strong) ItemTableViewSource * Source;
@property (strong) ItemTableViewDelegate * Delegate;

@property (weak) IBOutlet NSPopUpButtonCell *PopupMenu;

@end
