//
//  CreateFontViewController.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 15/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CreateFontViewController : NSViewController

@property (weak) IBOutlet NSSearchField *FontName;
@property (weak) IBOutlet NSPopUpButton *Size;
@property (weak) IBOutlet NSPopUpButton *SelectedFont;
@property (weak) IBOutlet NSMenu *SelectedFontMenu;

@end
