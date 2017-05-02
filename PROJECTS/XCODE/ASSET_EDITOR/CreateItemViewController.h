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
#import "GRAPHIC_UI_FRAME.h"

@interface CreateItemViewController : NSViewController<NSTableViewDataSource, NSTableViewDelegate>

@property (weak) IBOutlet NSTableView * TableView;
@property (strong) ItemTableViewSource * Source;
@property (strong) ItemTableViewDelegate * Delegate;
@property (weak) IBOutlet NSTextField *TextFieldValue;
@property (weak) IBOutlet NSTextField *ObjectIdentifierTextField;
@property GRAPHIC_UI_FRAME * Parent;

@property (weak) IBOutlet NSPopUpButtonCell *PopupMenu;
- (IBAction)CreateContainerAction:(id)sender;

@end
