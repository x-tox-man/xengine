//
//  LeftPane.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef LeftPane_h
#define LeftPane_h

#import <Cocoa/Cocoa.h>

@interface LeftPaneViewController : NSViewController<NSMenuDelegate, NSOutlineViewDelegate,NSOutlineViewDataSource>

- (IBAction)CreateItemButtonClicked:(id)sender;
- (IBAction)DeleteItemButtonClicked:(id)sender;
- (IBAction)PrintViewButtonClicked:(id)sender;
- (IBAction)OnResolutionChanged:(id)sender;
-(void) onObjectCollectionChanged;

@property (weak) IBOutlet NSMenu *Menu;
@property (weak) IBOutlet NSPopUpButtonCell *PopupButton;
@property (weak) IBOutlet NSOutlineView *OutlineView;

@end



#endif /* LeftPane_h */
