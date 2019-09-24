//
//  Renderer.h
//  TestMetalMac
//
//  Created by Christophe Bernard on 08/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import <MetalKit/MetalKit.h>

// Our platform independent renderer class.   Implements the MTKViewDelegate protocol which
//   allows it to accept per-frame update and drawable resize callbacks.
@interface METAL_VIEW_DELEGATE : NSObject <MTKViewDelegate>

-(nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)view;

@end

