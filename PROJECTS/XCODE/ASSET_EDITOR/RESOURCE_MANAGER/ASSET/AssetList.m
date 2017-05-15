//
//  AssetList.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "AssetList.h"
#import "DefaultAssetViewItem.h"

@interface AssetList ()

@end

@implementation AssetList

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    NSMutableArray * tl = [[NSMutableArray alloc] init];
    
    [tl addObject:@"png"];
    [tl addObject:@"mp3"];
    [tl addObject:@"smx"];
    [tl addObject:@"fsh"];
    [tl addObject:@"vsh"];
    [tl addObject:@"iax"];
    [tl addObject:@"fxb"];
    [tl addObject:@"abx"];
    [tl addObject:@"lua"];
    
    self.assetTypeList = [[NSArray alloc] initWithArray:tl];
    
    [self.CollectionView registerNib:[[NSNib alloc] initWithNibNamed:@"DefaultAssetViewItem" bundle:[NSBundle mainBundle]] forItemWithIdentifier:@"DefaultAssetViewItem"];
    
    [self.CollectionView reloadData];
    
    self.assetlist = [[NSMutableArray alloc] initWithCapacity:100];
    
    CustomDragView * v = self.view;
    
    v.dragProtocol = self;
    
    [self.view registerForDraggedTypes:[NSArray arrayWithObjects: NSFilenamesPboardType, nil]];
}

-(NSInteger)collectionView:(NSCollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    
    return [self.assetlist count];
}

-(NSInteger)numberOfSectionsInCollectionView:(NSCollectionView *)collectionView
{
    return 1;
}

-(NSCollectionViewItem *)collectionView:(NSCollectionView *)collectionView itemForRepresentedObjectAtIndexPath:(NSIndexPath *)indexPath {
    
    DefaultAssetViewItem * item = [collectionView makeItemWithIdentifier:@"DefaultAssetViewItem" forIndexPath:indexPath];
    
    NSRect r;
    
    r.origin = item.view.frame.origin;
    
    r.size.height = 64.0f;
    r.size.width = 64.0f;
    
    item.view.frame = r;
    
    [item.itemPath setStringValue:[self.assetlist objectAtIndex:[indexPath item]]];
    
    //[item.AssetTitle setStringValue:[self.assetlist objectAtIndex:[indexPath item]]];
    //[item.textField setStringValue:[self.assetlist objectAtIndex:[indexPath item]]];
    
    return item;
}

-(void)OnFileAdded:(NSString *)path {
    
    NSString * ext = [path pathExtension];
    
    // Contains all assets types
    if ( [self.assetTypeList containsObject:ext] ) {
        
        [self.assetlist addObject:path];
        
        [self.CollectionView reloadData];
    }
}


@end
