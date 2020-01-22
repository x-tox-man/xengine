//
//  Renderer.m
//  TestMetalMac
//
//  Created by Christophe Bernard on 08/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import <simd/simd.h>
#import <ModelIO/ModelIO.h>

#import "METAL_VIEW_DELEGATE.h"

// Include header shared between C code here, which executes Metal API commands, and .metal files
#import "METAL_SHADER_TYPES.h"
#import "GRAPHIC_SYSTEM.h"
#import "GRAPHIC_RENDERER.h"

@implementation METAL_VIEW_DELEGATE
{
    id <MTLDevice> _device;
}

-(nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)view;
{
    self = [super init];
    if(self)
    {
        _device = view.device;
        
        view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        view.colorPixelFormat = MTLPixelFormatBGRA8Unorm;
        view.sampleCount = 1;
    }

    return self;
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    /// Per frame updates here

    GRAPHIC_RENDERER::GetInstance().BeginFrame();
    GRAPHIC_RENDERER::GetInstance().Render();
    GRAPHIC_RENDERER::GetInstance().EndFrame();
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    /// Respond to drawable size or orientation changes here

    /*float aspect = size.width / (float)size.height;
    _projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);*/
}

#pragma mark Matrix Math Utilities

matrix_float4x4 matrix4x4_translation(float tx, float ty, float tz)
{
    return (matrix_float4x4) {{
        { 1,   0,  0,  0 },
        { 0,   1,  0,  0 },
        { 0,   0,  1,  0 },
        { tx, ty, tz,  1 }
    }};
}

static matrix_float4x4 matrix4x4_rotation(float radians, vector_float3 axis)
{
    axis = vector_normalize(axis);
    float ct = cosf(radians);
    float st = sinf(radians);
    float ci = 1 - ct;
    float x = axis.x, y = axis.y, z = axis.z;

    return (matrix_float4x4) {{
        { ct + x * x * ci,     y * x * ci + z * st, z * x * ci - y * st, 0},
        { x * y * ci - z * st,     ct + y * y * ci, z * y * ci + x * st, 0},
        { x * z * ci + y * st, y * z * ci - x * st,     ct + z * z * ci, 0},
        {                   0,                   0,                   0, 1}
    }};
}

matrix_float4x4 matrix_perspective_right_hand(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float ys = 1 / tanf(fovyRadians * 0.5);
    float xs = ys / aspect;
    float zs = farZ / (nearZ - farZ);

    return (matrix_float4x4) {{
        { xs,   0,          0,  0 },
        {  0,  ys,          0,  0 },
        {  0,   0,         zs, -1 },
        {  0,   0, nearZ * zs,  0 }
    }};
}

@end
