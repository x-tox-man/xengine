//
//  Custom3dTableViewDelegate.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Cpp3dDataProxy.h"
#import "ParentVCDelegate.h"

@interface Custom3dTableViewDelegate : NSObject< NSTableViewDelegate, NSTableViewDataSource >

@property Cpp3dDataProxy * Entity;
@property NSObject<ParentVCDelegate> * ParentVCDelegate;

@property (weak) IBOutlet NSTextField *XposTextField;
@property (weak) IBOutlet NSTextField *YposTextField;
@property (weak) IBOutlet NSTextField *ZposTextField;
@property (weak) IBOutlet NSTextField *WposTextField;

@property (weak) IBOutlet NSTextField *XRotTextField;
@property (weak) IBOutlet NSTextField *YRotTextField;
@property (weak) IBOutlet NSTextField *ZRotTextField;
@property (weak) IBOutlet NSTextField *WRotTextField;

@end
