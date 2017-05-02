//
//  MainSplitViewController.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MainSplitViewController : NSSplitViewController<NSSplitViewDelegate>
@property (weak) IBOutlet NSSplitView *SplitView;

@end
