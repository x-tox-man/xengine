//
//  Create3dItem.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GAMEPLAY_COMPONENT_ENTITY.h"
#import "GAMEPLAY_COMPONENT_MANAGER.h"
#import "GRAPHIC_OBJECT.h"
#import "GRAPHIC_SHADER_EFFECT.h"
#import "ResourceProxy.h"
#import "ResourceSelectedDelegate.h"
#import "ModalBackDelegate.h"

@interface Create3dItem : NSViewController< ResourceSelectedDelegate >
@property (weak) IBOutlet NSTextField *Id;
@property (weak) IBOutlet NSTextField *X;
@property (weak) IBOutlet NSTextField *Y;
@property (weak) IBOutlet NSTextField *Z;
@property (weak) IBOutlet NSTextField *W;
@property (weak) IBOutlet NSTextField *MeshName;

@property (weak) IBOutlet NSTextField *EffectName;
@property GRAPHIC_OBJECT * Object3d;
@property GRAPHIC_SHADER_EFFECT * Effect;
@property NSObject<ModalBackDelegate> * BackDelegate;

-(void) OnResourceSelected:(ResourceProxy *)Resource;

@end
