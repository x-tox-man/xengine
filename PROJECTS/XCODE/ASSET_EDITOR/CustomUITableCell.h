//
//  CustomUITableCell.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GRAPHIC_UI_ELEMENT.h"

@interface CustomUITableCell : NSTableCellView< NSTextFieldDelegate >
@property (weak) IBOutlet NSTextField *WidthText;
@property (weak) IBOutlet NSTextField *HeightText;
@property (weak) IBOutlet NSTextField *XText;
@property (weak) IBOutlet NSTextField *YText;
@property (strong) IBOutlet NSTableCellView *view;

@property GRAPHIC_UI_ELEMENT * Element;

-(void) update;


@end
