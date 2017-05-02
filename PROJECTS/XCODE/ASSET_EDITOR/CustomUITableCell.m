//
//  CustomUITableCell.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "CustomUITableCell.h"

@implementation CustomUITableCell


-(instancetype)initWithFrame:(NSRect)frameRect
{
    self = [super initWithFrame:frameRect];
    
    [[NSBundle mainBundle] loadNibNamed:@"CustomUITableCell" owner:self topLevelObjects:nil];
    
    self.view.frame = frameRect;
    self.WidthText.delegate = self;
    self.HeightText.delegate = self;
    
    self.XText.delegate = self;
    self.YText.delegate = self;
    
    [self addSubview:self.view];
    
    return self;
}
- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

-(void) update {
    
    self.XText.stringValue = [NSString stringWithFormat:@"%f", self.Element->GetPlacement().GetAbsolutePosition().X()];
    self.YText.stringValue = [NSString stringWithFormat:@"%f", self.Element->GetPlacement().GetAbsolutePosition().Y()];
    
    self.WidthText.stringValue = [NSString stringWithFormat:@"%f", self.Element->GetPlacement().GetSize().X()];
    self.HeightText.stringValue = [NSString stringWithFormat:@"%f", self.Element->GetPlacement().GetSize().Y()];
}

- (void)controlTextDidChange:(NSNotification *)notification
{
    CORE_MATH_VECTOR size = self.Element->GetPlacement().GetSize();
    CORE_MATH_VECTOR position = self.Element->GetPlacement().GetRelativePosition();
    
    if([notification object] == self.WidthText)
    {
        size.X( [self.WidthText integerValue] );
    }
    else if([notification object] == self.HeightText)
    {
        size.Y( [self.HeightText integerValue] );
    }
    else if([notification object] == self.XText)
    {
        position.X( [self.XText integerValue]);
    }
    else if([notification object] == self.YText)
    {
        position.Y( [self.YText integerValue]);
    }
    
    self.Element->GetPlacement().SetSize( size );
    self.Element->GetPlacement().SetRelativePosition( position );
}

@end
