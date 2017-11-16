//
//  CustomDragView.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol CustomDragViewDragProtocol

-(void)OnFileAdded:(NSString *) path;

@end

@interface CustomDragView : NSView

@property NSObject<CustomDragViewDragProtocol> * dragProtocol;

@end

