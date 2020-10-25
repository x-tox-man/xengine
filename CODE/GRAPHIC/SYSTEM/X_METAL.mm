//
//  METAL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/12/2018.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"

#if X_METAL

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <ModelIO/ModelIO.h>
#import <ModelIO/MDLMeshBuffer.h>
#import "METAL_VIEW_DELEGATE.h"
#import "METAL_SHADER_TYPES.h"

static const NSUInteger kMaxBuffersInFlight = 3;

CORE_PARALLEL_LOCK_MUTEX GRAPHIC_SYSTEM::GraphicSystemLock;
const char * GRAPHIC_SYSTEM::ShaderDirectoryPath = "METAL";
CORE_HELPERS_COLOR GRAPHIC_SYSTEM::ClearColor = CORE_COLOR_Blue;
bool GRAPHIC_SYSTEM::ItRenderOnScreen = true;

MTLCullMode METAL_GetPolygonFace( const GRAPHIC_POLYGON_FACE face ) {
    static MTLCullMode face_type[] { MTLCullModeFront, MTLCullModeBack, MTLCullModeNone, MTLCullModeNone };
    
    return face_type[ face ];
}

id <MTLDevice>
    _device;
id <MTLCommandQueue>
    _commandQueue;
id <MTLDepthStencilState>
    _depthState;
id<MTLLibrary>
    _defaultLibrary;
METAL_VIEW_DELEGATE *
    _metalDelegate;
MTKMeshBufferAllocator *
    _metalAllocator;
MTKTextureLoader *
    _textureLoader;
id <MTLRenderCommandEncoder>
    _renderEncoder;
dispatch_semaphore_t
    _inFlightSemaphore;
id <MTLCommandBuffer>
    _commandBuffer;
MTLRenderPassDescriptor
    * _renderPassDescriptor;
MTKView
    * _view;
std::map< GRAPHIC_RENDERER_STATE_DESCRIPTOR, void * >
    MetalDepthStateDescriptCache;

void * GRAPHIC_SYSTEM::MtlGetCachedStencilStateFromRenderer( GRAPHIC_RENDERER & renderer ) {
    
    void * state = MetalDepthStateDescriptCache[ renderer.GetDescriptor() ];
    
    int size = MetalDepthStateDescriptCache.size();
    
    //TODO: Buggy code
    if ( state == NULL ) {
        
        MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
        depthStateDesc.depthCompareFunction = renderer.GetDescriptor().ItDoesDepthTest ? MTLCompareFunctionLess : MTLCompareFunctionAlways;
        depthStateDesc.depthWriteEnabled = renderer.GetDescriptor().ItDoesDepthTest ? YES : NO;
        
        if ( renderer.GetDescriptor().ItDoesStencilTest ) {
            MTLStencilDescriptor *backfaceStencilDescriptor = [[MTLStencilDescriptor alloc]
             init];
            backfaceStencilDescriptor.stencilCompareFunction = MTLCompareFunctionAlways;
            backfaceStencilDescriptor.stencilFailureOperation = MTLStencilOperationKeep;
            backfaceStencilDescriptor.depthStencilPassOperation = MTLStencilOperationIncrementWrap;
            backfaceStencilDescriptor.writeMask = renderer.GetDescriptor().StencilMask;
            
            MTLStencilDescriptor *frontfaceStencilDescriptor = [[MTLStencilDescriptor alloc]
             init];
            frontfaceStencilDescriptor.stencilCompareFunction = MTLCompareFunctionAlways;
            frontfaceStencilDescriptor.stencilFailureOperation = MTLStencilOperationKeep;
            frontfaceStencilDescriptor.depthStencilPassOperation = MTLStencilOperationDecrementWrap;
            frontfaceStencilDescriptor.writeMask = renderer.GetDescriptor().StencilMask;
            
            //Need to check they are the same!
            depthStateDesc.backFaceStencil = backfaceStencilDescriptor;
            depthStateDesc.frontFaceStencil = frontfaceStencilDescriptor;
        }
        
        id <MTLDepthStencilState> tempState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];
        state = ( void *) CFBridgingRetain( tempState );
        
        MetalDepthStateDescriptCache[ renderer.GetDescriptor() ] = state;
        
        assert( MetalDepthStateDescriptCache[ renderer.GetDescriptor() ]  != NULL );
    }
    else if (state == NULL ) {
        state = (__bridge void * ) _depthState;
    }
    
    return state;
}

void * GRAPHIC_SYSTEM::CreateMtlVertexDescriptor( GRAPHIC_SHADER_BIND bind ) {
    
    MTLVertexDescriptor * mtlVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    
    int stride = 0;
    
    if ( bind & GRAPHIC_SHADER_BIND_Position ) {
        
        mtlVertexDescriptor.attributes[VertexAttributePosition].format = MTLVertexFormatFloat4;
        mtlVertexDescriptor.attributes[VertexAttributePosition].offset = 0;
        mtlVertexDescriptor.attributes[VertexAttributePosition].bufferIndex = 0;
        
        stride += 16;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Normal ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeNormal].format = MTLVertexFormatFloat4;
        mtlVertexDescriptor.attributes[VertexAttributeNormal].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeNormal].bufferIndex = 0;
        
        stride += 16;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeTexcoords].format = MTLVertexFormatFloat2;
        mtlVertexDescriptor.attributes[VertexAttributeTexcoords].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeTexcoords].bufferIndex = 0;
        
        stride += 8;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeSkinWeight].format = MTLVertexFormatFloat4;
        mtlVertexDescriptor.attributes[VertexAttributeSkinWeight].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeSkinWeight].bufferIndex = 0;
        
        stride += 16;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeJointIndices].format = MTLVertexFormatFloat4;
        mtlVertexDescriptor.attributes[VertexAttributeJointIndices].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeJointIndices].bufferIndex = 0;
        
        stride += 16;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Tangents ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeTangent].format = MTLVertexFormatFloat3;
        mtlVertexDescriptor.attributes[VertexAttributeTangent].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeTangent].bufferIndex = 0;
        
        stride += 12;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeBitangent].format = MTLVertexFormatFloat3;
        mtlVertexDescriptor.attributes[VertexAttributeBitangent].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeBitangent].bufferIndex = 0;
        
        stride += 12;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_CustomFloat ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeCustomFloat].format = MTLVertexFormatFloat;
        mtlVertexDescriptor.attributes[VertexAttributeCustomFloat].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeCustomFloat].bufferIndex = 0;
        
        stride += 4;
    }
    
    mtlVertexDescriptor.layouts[0].stride = stride;
    mtlVertexDescriptor.layouts[0].stepRate = 1;
    mtlVertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    
    return ( void *) CFBridgingRetain(mtlVertexDescriptor);
}

void * GRAPHIC_SYSTEM::CreateMetalPipelineState( void * descriptor, GRAPHIC_SHADER_PROGRAM & program ) {
    
    NSError *error = NULL;
    MTLRenderPipelineReflection* reflectionObj;
    MTLPipelineOption option = MTLPipelineOptionBufferTypeInfo | MTLPipelineOptionArgumentInfo;
    
    id <MTLRenderPipelineState> pipeline_state = [_device newRenderPipelineStateWithDescriptor:( MTLRenderPipelineDescriptor *) CFBridgingRelease(descriptor) options:option reflection:&reflectionObj error:&error];
    
    if (!pipeline_state)
    {
        NSLog(@"Failed to created pipeline state, error %@", error);
        
        return NULL;
    }
    
    for (MTLArgument *arg in reflectionObj.vertexArguments)
    {
        //NSLog(@"Found arg: %@\n", arg.name);
        
        if ( arg.bufferStructType.members.count > 0) {
            
            for( MTLStructMember * uniform in arg.bufferStructType.members )
            {
                //NSLog(@"uniform: %@ type:%lu, location: %lu", uniform.name, (unsigned long)uniform.dataType, (unsigned long)uniform.offset);
                
                CORE_HELPERS_IDENTIFIER
                    identifier( [uniform.name cStringUsingEncoding:NSASCIIStringEncoding] );
                GRAPHIC_SHADER_ATTRIBUTE & attribute = program.GetShaderAttributeTable()[ identifier ];

                attribute.AttributeIndex = uniform.offset;
                attribute.AttributeName = identifier;
            }
        }
        else if( arg.bufferPointerType ) {
            
            if ( strcmp( [arg.name cStringUsingEncoding:NSASCIIStringEncoding], "vertexBuffer.0" ) == 0 )
                continue;
            
            NSLog(@"uniform: %@ type:%lu, location: %lu", arg.name, (unsigned long)arg.bufferDataSize, (unsigned long)arg.index);
            
            CORE_HELPERS_IDENTIFIER
                identifier( [arg.name cStringUsingEncoding:NSASCIIStringEncoding] );
            GRAPHIC_SHADER_ATTRIBUTE & attribute = program.GetShaderAttributeTable()[ identifier ];

            //attribute.GPUBuffer = CreateMetalDynamicUniformBuffer( (unsigned long)128*16 * sizeof(float) * 3);
            attribute.AttributeIndex = 0;
            attribute.AttributeOffset = arg.index;
            attribute.AttributeName = identifier;
            
        }
    }
    
    for (MTLArgument *arg in reflectionObj.fragmentArguments)
    {
        //NSLog(@"Found arg: %@\n", arg.name);
        
        if ( arg.type == MTLArgumentTypeTexture ) {
            
            CORE_HELPERS_IDENTIFIER
                identifier( [arg.name cStringUsingEncoding:NSASCIIStringEncoding] );
            GRAPHIC_SHADER_ATTRIBUTE & attribute = program.GetShaderAttributeTable()[ identifier ];

            attribute.AttributeIndex = arg.index;
            attribute.AttributeName = identifier;
        }
    }
    
    return (void *) CFBridgingRetain(pipeline_state);
}

void * GRAPHIC_SYSTEM::CreateMetalDynamicUniformBuffer( unsigned long size ) {
    
    id <MTLBuffer> buffer = [_device newBufferWithLength:size
                                                 options:MTLResourceStorageModeShared];

    buffer.label = @"UniformBuffer";
    return (void * ) CFBridgingRetain( buffer );
}

void GRAPHIC_SYSTEM::EnableMtlPipelineState( void * pipeline_state ) {
    
    id<MTLRenderPipelineState> pps = (__bridge id<MTLRenderPipelineState>) pipeline_state;
    [_renderEncoder setRenderPipelineState:pps];
}

void GRAPHIC_SYSTEM::EnableMtlUniforms( void * buffer, uint32_t offset, uint32_t size ) {
    
    //id<MTLBuffer> uniform_buffer = (__bridge id<MTLBuffer>) buffer;
    
    void* ptr =(((uint8_t*)  buffer) + offset);
    
#if DEBUG
    assert( size > 0 && size <= 4096);
#endif
    [_renderEncoder setVertexBytes:buffer length:size atIndex:1];
    [_renderEncoder setFragmentBytes:buffer length:size atIndex:1];
    
    /*[_renderEncoder setVertexBuffer:uniform_buffer
                            offset:offset
                           atIndex:1];*/
    
    

    /*[_renderEncoder setFragmentBuffer:uniform_buffer
                              offset:offset
                             atIndex:1];*/
}

void * GRAPHIC_SYSTEM::GetMtlBufferPointer( void * buffer ) {
    
    return ( (__bridge id<MTLBuffer>) buffer).contents;
}

void GRAPHIC_SYSTEM::MtlReleasePipelineState( void * state ) {
    
    CFBridgingRelease( state );
}

void * GRAPHIC_SYSTEM::CreateMtlTextureFromDescriptor( void * descriptor ) {
    
    // Create the texture from the device by using the descriptor
    id<MTLTexture> mtl_texture = [_device newTextureWithDescriptor:(__bridge MTLTextureDescriptor *) descriptor];
    
    return (void*) CFBridgingRetain( mtl_texture );
}

void * GRAPHIC_SYSTEM::CreateMetalFunction( const char * function_name ) {
    
    id <MTLFunction> fc = [_defaultLibrary newFunctionWithName:[[NSString alloc] initWithCString:function_name encoding:NSASCIIStringEncoding] ];
    
    return (void *) CFBridgingRetain(fc);
}

MTLPixelFormat GetMtlDepthStencilPixelFormatFromDescriptor( GRAPHIC_TEXTURE_IMAGE_TYPE depth, GRAPHIC_TEXTURE_IMAGE_TYPE stencil ) {
    
    if ( depth == GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 && stencil == GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8 ) {
        return MTLPixelFormatDepth32Float_Stencil8;
    }
    else {
        abort();
        //TODO:
        return MTLPixelFormatDepth32Float_Stencil8;
    }
}

unsigned long GetMTLPixelFormatFromDescriptor( GRAPHIC_TEXTURE_IMAGE_TYPE color ) {
    
    switch ( color ) {
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA:
            return MTLPixelFormatBGRA8Unorm;
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32:
            return MTLPixelFormatDepth32Float;
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8:
            return MTLPixelFormatStencil8;
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_None:
            return MTLPixelFormatInvalid;
            
        default:
            abort();
            return MTLPixelFormatInvalid;
    }
}

void GRAPHIC_SYSTEM::InitializeMetal( void * view ) {
    
    _view = (__bridge MTKView *) view;
    
    _view.device = MTLCreateSystemDefaultDevice();
    _device = _view.device;
    _metalDelegate = [[METAL_VIEW_DELEGATE alloc] initWithMetalKitView:_view];
    _defaultLibrary = [_device newDefaultLibrary];
    
    [_metalDelegate mtkView:_view drawableSizeWillChange:_view.bounds.size];
    
    _view.delegate = _metalDelegate;
    
    _view.depthStencilPixelFormat = GetMtlDepthStencilPixelFormatFromDescriptor( GRAPHIC_RENDERER::GetInstance().GetDescriptor().DepthAttachmentPixelFormat, GRAPHIC_RENDERER::GetInstance().GetDescriptor().StencilAttachmentPixelFormat);
    _view.colorPixelFormat = (MTLPixelFormat) GetMTLPixelFormatFromDescriptor( GRAPHIC_RENDERER::GetInstance().GetDescriptor().ColorAttachmentPixelFormat[ 0 ] );
    _view.sampleCount = 1;
    
    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];
    
    _commandQueue = [_device newCommandQueue];
    
    _metalAllocator = [[MTKMeshBufferAllocator alloc]
                                              initWithDevice: _device];
    
    _textureLoader = [[MTKTextureLoader alloc] initWithDevice:_device];
    
    _inFlightSemaphore = dispatch_semaphore_create(kMaxBuffersInFlight);
}

void * GRAPHIC_SYSTEM::GetMtlView() {
    
    return (__bridge void *) _view;
}

GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {
    
}

void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version ) {
    
}

void GRAPHIC_SYSTEM::Finalize() {
    
}

void GRAPHIC_SYSTEM::EnableScissor(bool enable, void * __GRAPHIC_SYSTEM_CONTEXT) {
    
    if ( !enable ) {
        
        MTLScissorRect
            rect;
        
        rect.x = 0;
        rect.y = 0;
        
        rect.width = _view.bounds.size.width;
        rect.height = _view.bounds.size.height;
        
        [_renderEncoder setScissorRect:rect];
    }
}

void GRAPHIC_SYSTEM::SetScissorRectangle( float x, float y, float width, float height, void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    //#error "TODO IMPLEMENT"
    
    MTLScissorRect rect;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    
    [_renderEncoder setScissorRect:rect];
}

void GRAPHIC_SYSTEM::EnableStencilTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, int ref, unsigned int mask, void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}
void GRAPHIC_SYSTEM::DisableStencil( void * __GRAPHIC_SYSTEM_CONTEXT) {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::SetStencilOperation( const GRAPHIC_POLYGON_FACE face, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_fail, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_pass, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_and_depth_fail, void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination, void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    //NULL OP : this will be handled by the GRAPHIC_RENDERER
    
    /*assert( __GRAPHIC_SYSTEM_CONTEXT != NULL );
    
    //Create a representation of shader states
    //Fetch the MTLRenderPipelineDescriptor coorresponding from a cache, instead of recreating it everytime.
    
    //MTLPipelineDescriptorCache
    
    GRAPHIC_SHADER_PROGRAM * program = (GRAPHIC_SHADER_PROGRAM *) __GRAPHIC_SYSTEM_CONTEXT;
    
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) program->GetMtlPipelineDescriptor();
    
    p.colorAttachments[0].blendingEnabled = true;
    p.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    p.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    p.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOne;
    p.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    
    p.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    p.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    MtlReleasePipelineState( program->GetMtlPipelineState() );
    void * state = CreateMetalPipelineState( (void *) CFBridgingRetain(p), *program );
    program->SetMtlPipelineState( state );*/
}

void GRAPHIC_SYSTEM::DisableBlend( void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    /*assert( __GRAPHIC_SYSTEM_CONTEXT != NULL );
    
    GRAPHIC_SHADER_PROGRAM * program = (GRAPHIC_SHADER_PROGRAM *) __GRAPHIC_SYSTEM_CONTEXT;
    
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) program->GetMtlPipelineDescriptor();
    
    p.colorAttachments[0].blendingEnabled = false;
    
    MtlReleasePipelineState( program->GetMtlPipelineState() );
    void * state = CreateMetalPipelineState( (void *) CFBridgingRetain(p), *program );
    program->SetMtlPipelineState( state );*/
}

void GRAPHIC_SYSTEM::SetBlendFunction( const GRAPHIC_SYSTEM_BLEND_EQUATION equation, void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    abort();
    
    /*GRAPHIC_SHADER_PROGRAM * program = (GRAPHIC_SHADER_PROGRAM *) __GRAPHIC_SYSTEM_CONTEXT;
    
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) program->GetMtlPipelineDescriptor();
    
    p.colorAttachments[0].blendingEnabled = true;
    p.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    p.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    p.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOne;
    p.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    
    p.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    p.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    MtlReleasePipelineState( program->GetMtlPipelineState() );
    void * state = CreateMetalPipelineState( (void *) CFBridgingRetain(p), *program );
    program->SetMtlPipelineState( state );*/
}

void GRAPHIC_SYSTEM::EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin, float range_end, void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::EnableBackfaceCulling( const GRAPHIC_POLYGON_FACE face ) {
    
    [_renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
    [_renderEncoder setCullMode:METAL_GetPolygonFace( face )];
}

void GRAPHIC_SYSTEM::DisableFaceCulling() {
    
    [_renderEncoder setCullMode:MTLCullModeNone];
}

void GRAPHIC_SYSTEM::UpdateVertexBuffer( GRAPHIC_MESH * mesh, CORE_DATA_BUFFER & data ) {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode ) {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::DisableDepthTest( void * __GRAPHIC_SYSTEM_CONTEXT ) {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::ReleaseTexture( GRAPHIC_TEXTURE * texture ) {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture ) {
    
    //#error "TODO IMPLEMENT"
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

    // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
    // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)
    textureDescriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;

    // Set the pixel dimensions of the texture
    textureDescriptor.width = texture->GetTextureInfo().Width;
    textureDescriptor.height = texture->GetTextureInfo().Height;
    
    texture->SetTextureHandle( CreateMtlTextureFromDescriptor( (__bridge void *) textureDescriptor ) );
}

void GRAPHIC_SYSTEM::SetTextureOptions( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_FILTERING filtering, GRAPHIC_TEXTURE_WRAP wrap, const CORE_HELPERS_COLOR & color ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateFrameBuffer( GRAPHIC_RENDER_TARGET * target, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateDepthBuffer( GRAPHIC_RENDER_TARGET * target, int width, int height ) {
    
    //#error "TODO IMPLEMENT"
    // Handled at IOS/OSX view's pixel format.
}

void GRAPHIC_SYSTEM::CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, CORE_DATA_BUFFER & texture_data, bool generate_mipmap ) {
    
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];

    // Indicate that each pixel has a blue, green, red, and alpha channel, where each channel is
    // an 8-bit unsigned normalized value (i.e. 0 maps to 0.0 and 255 maps to 1.0)
    textureDescriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;

    // Set the pixel dimensions of the texture
    textureDescriptor.width = texture->GetTextureInfo().Width;
    textureDescriptor.height = texture->GetTextureInfo().Height;

    // Create the texture from the device by using the descriptor
    id<MTLTexture> mtl_texture = [_device newTextureWithDescriptor:textureDescriptor];
    
    MTLRegion region = {
        { 0, 0, 0 },                   // MTLOrigin
        {textureDescriptor.width, textureDescriptor.height, 1} // MTLSize
    };
    
    NSUInteger bytesPerRow = 4 * textureDescriptor.width;
    
    [mtl_texture replaceRegion:region
                   mipmapLevel:0
                     withBytes:texture_data.GetDataPointer()
                   bytesPerRow:bytesPerRow];
    
    texture->SetTextureHandle( (void *)  CFBridgingRetain(mtl_texture) );
}

void * GRAPHIC_SYSTEM::CreateMtlRenderEncoder( void * descriptor ) {
    
    _renderEncoder = [_commandBuffer renderCommandEncoderWithDescriptor: (__bridge MTLRenderPassDescriptor *) descriptor];
    
    return (__bridge void *) _renderEncoder;
}

void GRAPHIC_SYSTEM::CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data ) {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    //#error "TODO IMPLEMENT"
    
    [_renderEncoder setFragmentTexture:(__bridge id <MTLTexture>)texture->GetTextureHandle() atIndex:texture_index];
}

void GRAPHIC_SYSTEM::ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::DiscardTexture( GRAPHIC_TEXTURE * texture ) {
    
    //Not needed
}

void GRAPHIC_SYSTEM::ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    //[_renderEncoder setVertexBytes:( void* ) &light.InternalLight.Directional length:sizeof(GRAPHIC_SHADER_LIGHT_DIRECTIONAL) atIndex:BufferIndexDirectionalLightsConstants];
    
    [_renderEncoder setFragmentBytes:( void* ) &light.InternalLight.Directional length:( 2* sizeof(GRAPHIC_SHADER_LIGHT_DIRECTIONAL)) atIndex:BufferIndexDirectionalLightsConstants];
}

void GRAPHIC_SYSTEM::ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    [_renderEncoder setFragmentBytes:( void* ) &light.InternalLight.Ambient length:( 2* sizeof(GRAPHIC_SHADER_LIGHT_AMBIENT) ) atIndex:BufferIndexAmbientLightConstants];
}

void GRAPHIC_SYSTEM::ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    [_renderEncoder setVertexBytes:( void* ) &light.InternalLight.Point length:( 2* sizeof(GRAPHIC_SHADER_LIGHT_POINT)) atIndex:BufferIndexPointLightsConstants];
    
    [_renderEncoder setFragmentBytes:( void* ) &light.InternalLight.Point length:( 2* sizeof(GRAPHIC_SHADER_LIGHT_POINT) ) atIndex:BufferIndexPointLightsConstants];
}

void GRAPHIC_SYSTEM::ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    [_renderEncoder setVertexBytes:( void* ) &light.InternalLight.Spot length:( 2* sizeof(GRAPHIC_SHADER_LIGHT_SPOT) ) atIndex:BufferIndexSpotLightsConstants];
    
    [_renderEncoder setFragmentBytes:( void* ) &light.InternalLight.Spot length:( 2* sizeof(GRAPHIC_SHADER_LIGHT_SPOT) ) atIndex:BufferIndexSpotLightsConstants];
}

void GRAPHIC_SYSTEM::ApplyMaterial( const GRAPHIC_MATERIAL & material ) {
    
    [_renderEncoder setFragmentBytes:( void* ) &material.InnerMaterial length:( 2* sizeof( GRAPHIC_MATERIAL_POCO ) ) atIndex:MaterialUniforms];
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVector( GRAPHIC_RENDERER & renderer, const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    //GRAPHIC_SYSTEM_ApplyFloatArray(index, size, array)(indexattribute.AttributeIndex, vector)
    GRAPHIC_SYSTEM_ApplyFloatArray( attribute.AttributeIndex, 4, vector )
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( GRAPHIC_RENDERER & renderer, const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    GRAPHIC_SYSTEM_ApplyFloat( attribute.AttributeIndex, value)
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVectorTable( GRAPHIC_RENDERER & renderer, const float * vector, int size, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    if ( attribute.AttributeOffset > 0 ) {
        
        [_renderEncoder setVertexBuffer:(__bridge id <MTLBuffer>) attribute.GPUBuffer.GetGPUBufferPointer()
                                 offset:(size * 0)//TODO: renderer.BufferPassIndex)
                                atIndex:attribute.AttributeOffset];
        
        [_renderEncoder setFragmentBuffer:(__bridge id <MTLBuffer>) attribute.GPUBuffer.GetGPUBufferPointer()
                                   offset:(size * 0)//TODO: renderer.BufferPassIndex)
                                  atIndex:attribute.AttributeOffset];
    }
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( GRAPHIC_RENDERER & renderer, const float * matrix, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    GRAPHIC_SYSTEM_ApplyMatrix( attribute.AttributeIndex, 64, 0, matrix );
}

void GRAPHIC_SYSTEM::CreateVertexBuffer(GRAPHIC_MESH &mesh) {
    
    id<MDLMeshBuffer> buffer = [_metalAllocator newBufferWithData:[NSData dataWithBytes:mesh.GetVertexCoreBuffer()->GetDataPointer() length:mesh.GetVertexCoreBuffer()->GetSize()] type:(MDLMeshBufferTypeVertex)];
    
    mesh.SetMTKVertexBuffer( (void *) CFBridgingRetain(buffer) );
}

void GRAPHIC_SYSTEM::CreateIndexBuffer(GRAPHIC_MESH &mesh) {
    
    id<MDLMeshBuffer> buffer = [_metalAllocator newBufferWithData:[NSData dataWithBytes:mesh.GetIndexCoreBuffer()->GetDataPointer() length:mesh.GetIndexCoreBuffer()->GetSize()] type:(MDLMeshBufferTypeIndex)];
    
    mesh.SetMTKIndexBuffer( (void *) CFBridgingRetain(buffer) );
}

void GRAPHIC_SYSTEM::ApplyBuffers( GRAPHIC_RENDERER & renderer, GRAPHIC_MESH & mesh ) {
    
    MTKMeshBuffer *vertexBuffer = (__bridge MTKMeshBuffer *) mesh.GetMTKVertexBuffer();
    MTKMeshBuffer *indexBuffer = (__bridge MTKMeshBuffer *) mesh.GetMTKIndexBuffer();
    
    id <MTLDepthStencilState> cachedStencilState = (__bridge id<MTLDepthStencilState>) MtlGetCachedStencilStateFromRenderer( renderer );
    [_renderEncoder setDepthStencilState:cachedStencilState];
    
    if((NSNull*)vertexBuffer != [NSNull null])
    {
        [_renderEncoder setVertexBuffer:vertexBuffer.buffer
                                offset:vertexBuffer.offset
                               atIndex:0];
    }
    
    {
        unsigned int count = (unsigned int) (mesh.GetIndexCoreBuffer()->GetSize() / sizeof( unsigned int ) );
        
        EnableMtlUniforms( renderer.GetOffsetPointer( 0 ), 0, 544 );//renderer.CurrentOffset );
        
        [_renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                  indexCount:count
                                   indexType:MTLIndexTypeUInt32
                                 indexBuffer:indexBuffer.buffer
                           indexBufferOffset:0];
        
        renderer.MtlApplyCurrentOffset();
    }
}

void GRAPHIC_SYSTEM::ReleaseBuffers(GRAPHIC_MESH &mesh) {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::Clear() {
    
    //#error "TODO IMPLEMENT"
    //CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::ClearFrambufferDepth( float default_depth ) {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::ClearFrambufferColor() {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::ClearFrambufferStencil() {
    
    //#error "TODO IMPLEMENT"
    CORE_RUNTIME_Abort();
}

void GRAPHIC_SYSTEM::BeginMtlFrame() {
    
    dispatch_semaphore_wait(_inFlightSemaphore, DISPATCH_TIME_FOREVER);
    
    _commandBuffer = [_commandQueue commandBuffer];
    _commandBuffer.label = @"MyCommand";
    
    __block dispatch_semaphore_t block_sema = _inFlightSemaphore;
    [_commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer)
     {
         dispatch_semaphore_signal(block_sema);
     }];
}

void GRAPHIC_SYSTEM::EndMtlFrame() {
    
    [_commandBuffer presentDrawable:_view.currentDrawable];
    [_commandBuffer commit];
}

void GRAPHIC_SYSTEM::BeginRendering() {
    
    if ( false /*immediate*/ ) {
        //pre-render
        EnableDefaultFrameBuffer();
    }
}

void GRAPHIC_SYSTEM::EndRendering() {
    
    if ( false /*immediate*/ ) {
        
        DisableDefaultFrameBuffer();
    }
}

void GRAPHIC_SYSTEM::EnableDefaultFrameBuffer() {
    
    _renderPassDescriptor = _view.currentRenderPassDescriptor;
    _renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);
    
    _renderEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:_renderPassDescriptor];
    _renderEncoder.label = @"MyRenderEncoder";
    
    [_renderEncoder pushDebugGroup:@"DrawScene"];
    
    [_renderEncoder setCullMode:MTLCullModeBack];
    [_renderEncoder setTriangleFillMode:MTLTriangleFillModeFill];
    [_renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
}

void GRAPHIC_SYSTEM::DisableDefaultFrameBuffer() {
    
    [_renderEncoder popDebugGroup];

    [_renderEncoder endEncoding];
}

#endif
