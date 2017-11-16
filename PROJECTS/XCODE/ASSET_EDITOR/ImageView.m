//
//  ImageView.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "ImageView.h"
#import "AtlasViewController.h"
@interface ImageView ()

@property (weak) IBOutlet NSImageCell *ImageCell;

@end

@implementation ImageView

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    self.ImageCell.image = [[NSImage alloc] initWithContentsOfFile:[self.DestinationFile stringByAppendingString:@".png"]];
}

@end
