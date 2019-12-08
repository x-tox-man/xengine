//
//  GRAPHIC_RENDER_TARGET_METAL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/08/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDER_TARGET.h"
#include "CORE_APPLICATION.h"
#include "GRAPHIC_SYSTEM.h"

#if X_METAL

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

GRAPHIC_RENDER_TARGET::GRAPHIC_RENDER_TARGET() :
    ItUsesDepth( false ),
    Attachments( 0 ) {
    
}

GRAPHIC_RENDER_TARGET::~GRAPHIC_RENDER_TARGET() {

    Finalize();
}

bool GRAPHIC_RENDER_TARGET::Initialize(int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool generates_separate_depth_texture, int attachments, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode ) {
    
    ItUsesDepth = uses_depth;
    Attachments = attachments;
    Mode = mode;
    
    //GRAPHIC_SYSTEM::CreateFrameBuffer( this, mode );
    
    if ( ItUsesDepth ) {
        
        GRAPHIC_SYSTEM::CreateDepthBuffer( this, width, height );
    }
    
    MTLRenderPassDescriptor * descriptor = [[MTLRenderPassDescriptor alloc] init];
    _descriptor = (void *) CFBridgingRetain(descriptor);
    
    for ( int i = 0; i < attachments; i++ ) {
        
        TargetTextures[i] = new GRAPHIC_TEXTURE;
        
        TargetTextures[i]->GetTextureInfo().Width = width;
        TargetTextures[i]->GetTextureInfo().Height = height;
        TargetTextures[i]->GetTextureInfo().ImageType = type;
        
        MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

        // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
        // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)
        textureDescriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;

        // Set the pixel dimensions of the texture
        textureDescriptor.width = TargetTextures[i]->GetTextureInfo().Width;
        textureDescriptor.height = TargetTextures[i]->GetTextureInfo().Height;
        textureDescriptor.textureType = MTLTextureType2D;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
        textureDescriptor.storageMode = MTLStorageModePrivate;
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
        
        void * tex = GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor );
        
        TargetTextures[i]->SetTextureHandle( tex );
        
        descriptor.colorAttachments[0].texture = (__bridge id <MTLTexture>) tex;
        descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        descriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.1, 0.0);
        descriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        
        //GFX_CHECK( glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, TargetTextures[i]->GetTextureHandle(), 0 ); )
    }
    
    if ( generates_separate_depth_texture ) {
        
        //GFX_CHECK( glFramebufferTexture( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, TargetTextures[0]->GetDepthTextureHandle(), 0/*mipmap level*/); )
    }
    
    _renderEncoder = NULL;
    
    return true;
}

bool GRAPHIC_RENDER_TARGET::InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type )
{
    //CORE_RUNTIME_Abort();
    
    return true;
}

void GRAPHIC_RENDER_TARGET::Finalize() {
    
    CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::Apply() {
    
    _renderEncoder = GRAPHIC_SYSTEM::CreateMtlRenderEncoder( (void *) _descriptor );
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder>) _renderEncoder;
    
    encoder.label = @"MyRenderEncoder";
    
    [encoder pushDebugGroup:@"GRAPHIC_RENDER_TARGET_RenderToTexture"];
    [encoder setCullMode:MTLCullModeBack];
    [encoder setTriangleFillMode:MTLTriangleFillModeFill];
    [encoder setFrontFacingWinding:MTLWindingCounterClockwise];
}

void GRAPHIC_RENDER_TARGET::Discard() {
    
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder>) _renderEncoder;
    
    [encoder popDebugGroup];
    [encoder endEncoding];
}

void GRAPHIC_RENDER_TARGET::EnableTextureBlending() {
    
    MTLRenderPassDescriptor * descriptor = (__bridge MTLRenderPassDescriptor*) _descriptor;
    
    descriptor.colorAttachments[0].loadAction = MTLLoadActionLoad;
}

void GRAPHIC_RENDER_TARGET::Clear() {
    
    MTLRenderPassDescriptor * descriptor = (__bridge MTLRenderPassDescriptor*) _descriptor;
    
    MTLLoadAction load_action = descriptor.colorAttachments[0].loadAction;
    
    descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    
    Apply();
    Discard();
    
    descriptor.colorAttachments[0].loadAction = load_action;
}

void GRAPHIC_RENDER_TARGET::AddAttachment( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::BindForWriting() {
    
    Apply();
}

void GRAPHIC_RENDER_TARGET::BindForReading() {
    
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::SetReadBuffer( int type )
{
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::SetWriteBuffer( int type )
{
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::CopyDepthFrom( GRAPHIC_RENDER_TARGET & other ) {
    
    CORE_RUNTIME_Abort();
}

#endif
