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
    DepthTexture( NULL ),
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

        // Set the pixel dimensions of the texture
        textureDescriptor.width = TargetTextures[i]->GetTextureInfo().Width;
        textureDescriptor.height = TargetTextures[i]->GetTextureInfo().Height;
        textureDescriptor.textureType = MTLTextureType2D;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
        textureDescriptor.storageMode = MTLStorageModePrivate;
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
        
        //https://developer.apple.com/documentation/metal/textures/understanding_color-renderable_pixel_format_sizes
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( 0, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        
        void * tex = GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor );
        
        TargetTextures[i]->SetTextureHandle( tex );
        
        descriptor.colorAttachments[i].texture = (__bridge id <MTLTexture>) tex;
        descriptor.colorAttachments[i].loadAction = MTLLoadActionClear;
        descriptor.colorAttachments[i].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 0.0);
        descriptor.colorAttachments[i].storeAction = MTLStoreActionStore;
        
        //GFX_CHECK( glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, TargetTextures[i]->GetTextureHandle(), 0 ); )
    }
    
    if ( ItUsesDepth ) {
        
        GRAPHIC_SYSTEM::CreateDepthBuffer( this, width, height );
        
        MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

        // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
        // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;

        // Set the pixel dimensions of the texture
        textureDescriptor.width = width;
        textureDescriptor.height = height;
        textureDescriptor.textureType = MTLTextureType2D;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
        textureDescriptor.storageMode = MTLStorageModePrivate;
        textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float;
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( 0, GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        
        void * tex = GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor );
        
        descriptor.depthAttachment.texture = (__bridge id <MTLTexture>) tex;
        descriptor.depthAttachment.loadAction = MTLLoadActionClear;
        descriptor.depthAttachment.clearDepth = 1.0;
        descriptor.depthAttachment.storeAction = MTLStoreActionStore;
        
        DepthTexture = new GRAPHIC_TEXTURE;
        
        DepthTexture->GetTextureInfo().Width = width;
        DepthTexture->GetTextureInfo().Height = height;
        DepthTexture->GetTextureInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32;
        
        DepthTexture->SetTextureHandle( tex );
    }
    
    // For opengl only
    /*if ( generates_separate_depth_texture ) {
        
        
    }*/
    // /
    
    _renderEncoder = NULL;
    
    return true;
}

bool GRAPHIC_RENDER_TARGET::InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type )
{
    ItUsesDepth = true;
    Attachments = 0;
    Mode = GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All;
    
    //GRAPHIC_SYSTEM::CreateFrameBuffer( this, mode );
    
    MTLRenderPassDescriptor * descriptor = [[MTLRenderPassDescriptor alloc] init];
    _descriptor = (void *) CFBridgingRetain(descriptor);
    
    for ( int i = 0; i < Attachments; i++ ) {
        
        abort();
        TargetTextures[i] = new GRAPHIC_TEXTURE;
        
        TargetTextures[i]->GetTextureInfo().Width = width;
        TargetTextures[i]->GetTextureInfo().Height = height;
        TargetTextures[i]->GetTextureInfo().ImageType = type;
        
        MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

        // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
        // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)

        // Set the pixel dimensions of the texture
        textureDescriptor.width = TargetTextures[i]->GetTextureInfo().Width;
        textureDescriptor.height = TargetTextures[i]->GetTextureInfo().Height;
        textureDescriptor.textureType = MTLTextureType2D;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
        textureDescriptor.storageMode = MTLStorageModePrivate;
        textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float;
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( 0, GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        
        void * tex = GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor );
        
        TargetTextures[i]->SetTextureHandle( tex );
        
        descriptor.colorAttachments[i].texture = (__bridge id <MTLTexture>) tex;
        descriptor.colorAttachments[i].loadAction = MTLLoadActionClear;
        descriptor.colorAttachments[i].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 0.0);
        descriptor.colorAttachments[i].storeAction = MTLStoreActionStore;
        
        //GFX_CHECK( glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, TargetTextures[i]->GetTextureHandle(), 0 ); )
    }
    
    if ( ItUsesDepth ) {
        
        GRAPHIC_SYSTEM::CreateDepthBuffer( this, width, height );
        
        MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

        // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
        // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;

        // Set the pixel dimensions of the texture
        textureDescriptor.width = width;
        textureDescriptor.height = height;
        textureDescriptor.textureType = MTLTextureType2D;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
        textureDescriptor.storageMode = MTLStorageModePrivate;
        textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float;
        
        //FAIL
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( 0, GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        
        void * tex = GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor );
        
        descriptor.depthAttachment.texture = (__bridge id <MTLTexture>) tex;
        descriptor.depthAttachment.loadAction = MTLLoadActionClear;
        descriptor.depthAttachment.clearDepth = 1.0;
        descriptor.depthAttachment.storeAction = MTLStoreActionStore;
        
        DepthTexture = new GRAPHIC_TEXTURE;
        
        DepthTexture->GetTextureInfo().Width = width;
        DepthTexture->GetTextureInfo().Height = height;
        DepthTexture->GetTextureInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32;
        
        DepthTexture->SetTextureHandle( tex );
    }
    
    _renderEncoder = NULL;
    
    return true;
}

void GRAPHIC_RENDER_TARGET::Finalize() {
    
    CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::Apply() {
    
    _renderEncoder = GRAPHIC_SYSTEM::CreateMtlRenderEncoder( (void *) _descriptor );
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder>) _renderEncoder;
    
    MTLRenderPassDescriptor * descriptor = (__bridge MTLRenderPassDescriptor*) _descriptor;
    
    for ( int i = 0; i < Attachments; i++ ) {
        
        MTLPixelFormat pxf = descriptor.colorAttachments[i].texture.pixelFormat;
        
        if ( descriptor.colorAttachments[i].texture != NULL && descriptor.colorAttachments[i].texture.pixelFormat == MTLPixelFormatBGRA8Unorm ) {
            GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( i, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
        }
        else {
            GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( i, GRAPHIC_TEXTURE_IMAGE_TYPE_None );
        }
    }
    
    for ( int i = Attachments; i < MAX_FRAME_BUFFERS; i++ ) {
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( i, GRAPHIC_TEXTURE_IMAGE_TYPE_None );
    }
    
    if( descriptor.depthAttachment.texture != NULL && descriptor.depthAttachment.texture.pixelFormat == MTLPixelFormatDepth32Float ) {
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    }
    else {
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
    }
    
    if( descriptor.stencilAttachment.texture != NULL && descriptor.stencilAttachment.texture.pixelFormat == MTLPixelFormatStencil8 ) {
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8 );
    }
    else {
        
        GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
    }
    
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
    
    abort();
    assert( Attachments > 0 );
    
    /*int attachment_index = Attachments;
    Attachments++;
        
    TargetTextures[attachment_index] = new GRAPHIC_TEXTURE;
    
    TargetTextures[attachment_index]->GetTextureInfo().Width = width;
    TargetTextures[attachment_index]->GetTextureInfo().Height = height;
    TargetTextures[attachment_index]->GetTextureInfo().ImageType = type;
    
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

    // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
    // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)

    // Set the pixel dimensions of the texture
    textureDescriptor.width = TargetTextures[attachment_index]->GetTextureInfo().Width;
    textureDescriptor.height = TargetTextures[attachment_index]->GetTextureInfo().Height;
    textureDescriptor.textureType = MTLTextureType2D;
    textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    textureDescriptor.storageMode = MTLStorageModePrivate;
    textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
    
    //https://developer.apple.com/documentation/metal/textures/understanding_color-renderable_pixel_format_sizes
    GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetColorAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
    GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
    GRAPHIC_RENDERER::GetInstance().GetDescriptor().SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_None );
    
    void * tex = GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor );
    
    TargetTextures[attachment_index]->SetTextureHandle( tex );
    
    descriptor.colorAttachments[attachment_index].texture = (__bridge id <MTLTexture>) tex;
    descriptor.colorAttachments[attachment_index].loadAction = MTLLoadActionClear;
    descriptor.colorAttachments[attachment_index].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 0.0);
    descriptor.colorAttachments[attachment_index].storeAction = MTLStoreActionStore;*/
}

void GRAPHIC_RENDER_TARGET::BindForWriting() {
    
    Apply();
}

void GRAPHIC_RENDER_TARGET::BindForReading() {
    
    //Apply();
}

void GRAPHIC_RENDER_TARGET::SetReadBuffer( int type )
{
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::SetWriteBuffer( int type )
{
    CORE_RUNTIME_Abort();
}

void GRAPHIC_RENDER_TARGET::CopyDepthFrom( GRAPHIC_RENDER_TARGET & other ) {
    
    CORE_RUNTIME_Abort();
}

#endif
