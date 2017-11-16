//
//  AtlasViewController.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 9/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AtlasViewController : NSViewController<NSTableViewDelegate, NSTableViewDataSource>

@property NSArray<NSString *> * DirFiles;
@property NSString * DirectoryPath;
@property NSString * DesintationAtlasFile;
@property (weak) IBOutlet NSTableView *TableView;
@property (weak) IBOutlet NSImageCell *ImageCellView;

@end
