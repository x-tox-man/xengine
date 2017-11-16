//
//  CustomTab.h
//  ASSET_EDITOR
//
//  Created by Christophe Bernard on 11/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CustomTab : NSTabViewController < NSTabViewDelegate >
    - (void)tabView:(NSTabView *)tabView didSelectTabViewItem:(nullable NSTabViewItem *)tabViewItem;
@end
