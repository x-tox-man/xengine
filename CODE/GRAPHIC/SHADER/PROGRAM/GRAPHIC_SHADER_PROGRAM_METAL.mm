//
//  GRAPHIC_SHADER_PROGRAM_METAL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/08/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_BIND.h"

#import "METAL_SHADER_TYPES.h"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "GRAPHIC_RENDERER.h"

/*GRAPHIC_TEXTURE_IMAGE_TYPE_RGB = 0,
GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA,
GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY,
GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY_A,
GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16,
GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH24,
GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32,*/

GRAPHIC_TEXTURE_IMAGE_TYPE GetImageTypeFromMTLPixelFormat( MTLPixelFormat format ) {
    
    switch ( format ) {
        case MTLPixelFormatBGRA8Unorm:
            return GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;

        case MTLPixelFormatBGRA8Unorm_sRGB:
            abort();
            return GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA_SRGB;
            
        case MTLPixelFormatDepth32Float:
            return GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32;
            
        case MTLPixelFormatStencil8:
            return GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8;
            
        case MTLPixelFormatDepth24Unorm_Stencil8:
            return GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH24;
            
        case MTLPixelFormatDepth32Float_Stencil8 :
            return GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32;
            
        case MTLPixelFormatInvalid:
            return GRAPHIC_TEXTURE_IMAGE_TYPE_None;
            
        default:
            abort();
            break;
    }
}


void GRAPHIC_SHADER_PROGRAM::LinkTogether( const GRAPHIC_SHADER_BIND shader_bind ) {
    
    //__bridge is used here because there is not retain increment to do in this function
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    p.vertexDescriptor = (__bridge MTLVertexDescriptor *) GRAPHIC_SYSTEM::CreateMtlVertexDescriptor( shader_bind );
    
    //CFBridgingRetain is used because we assign a retain object to this instance
    
    GRAPHIC_RENDERER_STATE_DESCRIPTOR desc = GRAPHIC_RENDERER::GetInstance().GetDescriptor();
    // must be the same for all colorAttachments
    desc.ColorAttachmentPixelFormat[ 0 ] = GetImageTypeFromMTLPixelFormat( p.colorAttachments[0].pixelFormat );
    desc.DepthAttachmentPixelFormat = GetImageTypeFromMTLPixelFormat( p.depthAttachmentPixelFormat );
    desc.StencilAttachmentPixelFormat = GetImageTypeFromMTLPixelFormat( p.stencilAttachmentPixelFormat );
    
    MetalPipelineStateCache[ desc ] = (void * ) GRAPHIC_SYSTEM::CreateMetalPipelineState( (void *) CFBridgingRetain(p), *this );
}

void GRAPHIC_SHADER_PROGRAM::Initialize() {
    
    //Get the view
    
    //CFBridgingRetain is used because we assign a retain object to this instance
    _pipelineStateDescriptor = (void *) CFBridgingRetain( [[MTLRenderPipelineDescriptor alloc] init] );
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    p.label = @"MyPipeline";
    
    p.sampleCount = 1;
    
    if ( GRAPHIC_SYSTEM::RendersOnScreen() ) {
        
        MTKView * view = (__bridge MTKView *) GRAPHIC_SYSTEM::GetMtlView();
        p.colorAttachments[0].pixelFormat = view.colorPixelFormat;
        p.depthAttachmentPixelFormat = view.depthStencilPixelFormat;
        p.stencilAttachmentPixelFormat = view.depthStencilPixelFormat;
    }
    else {
        
        p.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
        p.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float;
        p.stencilAttachmentPixelFormat = MTLPixelFormatInvalid;
    }
}

void GRAPHIC_SHADER_PROGRAM::LoadProgram( const CORE_FILESYSTEM_PATH & path, int shader_load_options ) {
    
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    p.label = @"MyPipeline";
    
    p.sampleCount = 1;
    
    //1 pipeline descript per object ?
    //1 pipeline descript per object type? >> batch rendering would be ok
    // pipeline = effect?
    // => With deferred rendering this would make sense
    // Graphic object
    //  Effect
    //      Material
    //          Textures
    //      Shaders
    //          functions
    //          Uniforms
    //  Mesh(es)
    //      VertexDescriptor
    
    if ( shader_load_options & GRAPHIC_SHADER_LOAD_OPTION_Vertex) {
        
        p.vertexFunction = (id <MTLFunction>) CFBridgingRelease(GRAPHIC_SYSTEM::CreateMetalFunction( "vertexShader" ));
    }
    
    if ( shader_load_options & GRAPHIC_SHADER_LOAD_OPTION_Fragment) {
        
        p.fragmentFunction = (id <MTLFunction>) CFBridgingRelease(GRAPHIC_SYSTEM::CreateMetalFunction( "fragmentShader" ));
    }
}

void GRAPHIC_SHADER_PROGRAM::LoadPartial( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type ) {
    

    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    CORE_FILESYSTEM_PATH dest_path;
    dest_path = path.RemoveExtension();
    
    char shader_name[256];
    
    CORE_DATA_COPY_STRING( shader_name, dest_path.GetFileName() )
    
    if ( shader_type & GRAPHIC_SHADER_Vertex) {
        
        strcat(shader_name, "_vs" );
        p.vertexFunction = (__bridge id <MTLFunction>) GRAPHIC_SYSTEM::CreateMetalFunction( shader_name );
    }
    
    if ( shader_type & GRAPHIC_SHADER_Pixel) {
        
        strcat(shader_name, "_fs" );
        p.fragmentFunction = (__bridge id <MTLFunction>) GRAPHIC_SYSTEM::CreateMetalFunction( shader_name );
    }
}

void GRAPHIC_SHADER_PROGRAM::Finalize() {
    
}

MTLBlendOperation GetMTLBlendOperationFromDescriptor( const GRAPHIC_SYSTEM_BLEND_EQUATION & equation ) {
 
    static MTLBlendOperation _LOCAL_BLEND_OPS[ GRAPHIC_SYSTEM_BLEND_EQUATION_Count ] = {MTLBlendOperationAdd, MTLBlendOperationSubtract, MTLBlendOperationReverseSubtract, MTLBlendOperationMin, MTLBlendOperationMax };
    
    return _LOCAL_BLEND_OPS[ equation ];
}

MTLBlendFactor GetMTLBlendFactorFromDescriptor( const GRAPHIC_SYSTEM_BLEND_OPERATION & factor ) {
 
    /*MTLBlendFactorZero = 0,
    MTLBlendFactorOne = 1,
    MTLBlendFactorSourceColor = 2,
    MTLBlendFactorOneMinusSourceColor = 3,
    MTLBlendFactorSourceAlpha = 4,
    MTLBlendFactorOneMinusSourceAlpha = 5,
    MTLBlendFactorDestinationColor = 6,
    MTLBlendFactorOneMinusDestinationColor = 7,
    MTLBlendFactorDestinationAlpha = 8,
    MTLBlendFactorOneMinusDestinationAlpha = 9,
    MTLBlendFactorSourceAlphaSaturated = 10,
    MTLBlendFactorBlendColor = 11,
    MTLBlendFactorOneMinusBlendColor = 12,
    MTLBlendFactorBlendAlpha = 13,
    MTLBlendFactorOneMinusBlendAlpha = 14,
    MTLBlendFactorSource1Color              API_AVAILABLE(macos(10.12), ios(10.11)) = 15,
    MTLBlendFactorOneMinusSource1Color      API_AVAILABLE(macos(10.12), ios(10.11)) = 16,
    MTLBlendFactorSource1Alpha              API_AVAILABLE(macos(10.12), ios(10.11)) = 17,
    MTLBlendFactorOneMinusSource1Alpha      API_AVAILABLE(macos(10.12), ios(10.11)) = 18,
    
    GRAPHIC_SYSTEM_BLEND_OPERATION_Zero = 0,
    GRAPHIC_SYSTEM_BLEND_OPERATION_One,
    GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha,
    GRAPHIC_SYSTEM_BLEND_OPERATION_DestinationAlpha,
    GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha,
    GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusDestinationAlpha,*/
    
    static MTLBlendFactor _LOCAL_BLEND_FACTOR[ GRAPHIC_SYSTEM_BLEND_OPERATION_Count ] = {MTLBlendFactorZero, MTLBlendFactorOne, MTLBlendFactorSourceAlpha, MTLBlendFactorDestinationAlpha, MTLBlendFactorOneMinusSourceAlpha, MTLBlendFactorOneMinusDestinationAlpha };
    
    return _LOCAL_BLEND_FACTOR[ factor ];
}

MTLPixelFormat GetMTLDepthStencilPixelFormatFromDescriptor( GRAPHIC_TEXTURE_IMAGE_TYPE depth, GRAPHIC_TEXTURE_IMAGE_TYPE stencil ) {
    if ( depth == GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 && stencil == GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8 ) {
        return MTLPixelFormatDepth32Float_Stencil8;
    }
    else if ( depth == GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 && stencil == GRAPHIC_TEXTURE_IMAGE_TYPE_None ) {
        
        return MTLPixelFormatDepth32Float;
    }
    else if ( depth == GRAPHIC_TEXTURE_IMAGE_TYPE_None && stencil == GRAPHIC_TEXTURE_IMAGE_TYPE_None ) {
        
        return MTLPixelFormatInvalid;
    }
    else {
        
        abort();
        return MTLPixelFormatInvalid;
    }
}

void * GRAPHIC_SHADER_PROGRAM::GetMtlCachedPipelineState( const GRAPHIC_RENDERER & renderer ) {

    //Algo :
    /*
     1) Comparer l'état courrant avec le descripter du renderer actif.
     2) Si le descripteur n'existe pas, créer le state.
     3)
     */
    GRAPHIC_RENDERER_STATE_DESCRIPTOR desc = GRAPHIC_RENDERER::GetInstance().GetDescriptor();
    
    void * pipeline = MetalPipelineStateCache[ desc ];
    
    if ( pipeline == NULL ) {
        
        MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
        
        for( int i = 0; i < GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS; i++ ) {
            
            MTLPixelFormat pixel_format = (MTLPixelFormat) GetMTLPixelFormatFromDescriptor( desc.ColorAttachmentPixelFormat[ i ] );
            
            p.colorAttachments[i].pixelFormat = pixel_format;
            
            p.colorAttachments[i].blendingEnabled = pixel_format != MTLPixelFormatInvalid;

            p.colorAttachments[i].rgbBlendOperation = GetMTLBlendOperationFromDescriptor( desc.BlendFunction );
            p.colorAttachments[i].alphaBlendOperation = GetMTLBlendOperationFromDescriptor( desc.BlendFunction );
            
            p.colorAttachments[i].sourceRGBBlendFactor = GetMTLBlendFactorFromDescriptor( desc.BlendingSourceOperation );
            p.colorAttachments[i].sourceAlphaBlendFactor = GetMTLBlendFactorFromDescriptor( desc.BlendingSourceOperation );
            
            p.colorAttachments[i].destinationRGBBlendFactor = GetMTLBlendFactorFromDescriptor( desc.BlendingDestinationOperation );
            p.colorAttachments[i].destinationAlphaBlendFactor = GetMTLBlendFactorFromDescriptor( desc.BlendingDestinationOperation );
        }
        
        p.depthAttachmentPixelFormat = (MTLPixelFormat) GetMTLDepthStencilPixelFormatFromDescriptor( desc.DepthAttachmentPixelFormat, desc.StencilAttachmentPixelFormat );
        
        if ( desc.StencilAttachmentPixelFormat != GRAPHIC_TEXTURE_IMAGE_TYPE_None && desc.DepthAttachmentPixelFormat != GRAPHIC_TEXTURE_IMAGE_TYPE_None ) {
            
            p.stencilAttachmentPixelFormat = p.depthAttachmentPixelFormat;
        }
        else if ( desc.StencilAttachmentPixelFormat != GRAPHIC_TEXTURE_IMAGE_TYPE_None && desc.DepthAttachmentPixelFormat == GRAPHIC_TEXTURE_IMAGE_TYPE_None ) {
         
            abort();
            p.stencilAttachmentPixelFormat = p.depthAttachmentPixelFormat;
        }
        else {
            p.stencilAttachmentPixelFormat = MTLPixelFormatInvalid;
        }
         
        void * pp = (void * ) GRAPHIC_SYSTEM::CreateMetalPipelineState( (void *) CFBridgingRetain(p), *this );
        assert( pp != NULL );
        MetalPipelineStateCache[ desc ] = pp;
        
        pipeline = MetalPipelineStateCache[ desc ];
        assert( pipeline != nil );
    }
    
    return pipeline;
}


void GRAPHIC_SHADER_PROGRAM::Enable( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_SYSTEM::EnableMtlPipelineState( GetMtlCachedPipelineState( renderer ) );
    
    GRAPHIC_SYSTEM::EnableMtlUniforms( renderer.MetalUniformBuffer, renderer.UniformOffset, -1 );
}

void GRAPHIC_SHADER_PROGRAM::Disable() {
    
}

void GRAPHIC_SHADER_PROGRAM::BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    if ( shader_attribute.AttributeIndex != -1 ) {
        
        shader_attribute.AttributeName = identifier;
        
        setShaderAttribute( shader_attribute );
    }
}
