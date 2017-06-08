//
//  AssetList.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CustomDragView.h"
#import "GRAPHIC_SHADER_EFFECT_LOADER.h"

@interface AssetList : NSViewController<NSCollectionViewDelegate, NSCollectionViewDataSource, NSWindowDelegate, CustomDragViewDragProtocol>

@property (weak) IBOutlet NSCollectionView *CollectionView;
@property NSMutableArray * assetlist;
@property NSArray * assetTypeList;

@end
