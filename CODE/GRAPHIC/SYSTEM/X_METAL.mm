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
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_BIND.h"

#if X_METAL

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <ModelIO/ModelIO.h>
#import <ModelIO/MDLMeshBuffer.h>
#import "METAL_VIEW_DELEGATE.h"
#import "METAL_SHADER_TYPES.h"

static const NSUInteger kMaxBuffersInFlight = 3;
static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;

CORE_PARALLEL_LOCK_MUTEX GRAPHIC_SYSTEM::GraphicSystemLock;
const char * GRAPHIC_SYSTEM::ShaderDirectoryPath = "METAL";
CORE_HELPERS_COLOR GRAPHIC_SYSTEM::ClearColor = CORE_COLOR_Blue;

MTLCullMode METAL_GetPolygonFace( const GRAPHIC_POLYGON_FACE face ) {
    static MTLCullMode face_type[] { MTLCullModeFront, MTLCullModeBack, MTLCullModeNone, MTLCullModeNone };
    
    return face_type[ face ];
}

id <MTLDevice>
    _device;
id <MTLCommandQueue>
    _commandQueue;
id <MTLBuffer>
    _dynamicUniformBuffer;
id <MTLDepthStencilState>
    _depthState;
uint32_t
    _uniformBufferOffset;
uint8_t
    _uniformBufferIndex;
void*
    _uniformBufferAddress;
matrix_float4x4
    _projectionMatrix;
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

void * GRAPHIC_SYSTEM::CreateMtlVertexDescriptor( GRAPHIC_SHADER_BIND bind ) {
    
    MTLVertexDescriptor * mtlVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    
    int stride = 0;
    
    if ( bind & GRAPHIC_SHADER_BIND_Position ) {
        
        mtlVertexDescriptor.attributes[VertexAttributePosition].format = MTLVertexFormatFloat4;
        mtlVertexDescriptor.attributes[VertexAttributePosition].offset = 0;
        mtlVertexDescriptor.attributes[VertexAttributePosition].bufferIndex = BufferIndexMeshPositions;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stride = 16;
        mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 4;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Normal ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeNormal].format = MTLVertexFormatFloat4;
        mtlVertexDescriptor.attributes[VertexAttributeNormal].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeNormal].bufferIndex = BufferIndexMeshNormals;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshNormals].stride = 16;
        mtlVertexDescriptor.layouts[BufferIndexMeshNormals].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshNormals].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 4;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeTexcoords].format = MTLVertexFormatFloat2;
        mtlVertexDescriptor.attributes[VertexAttributeTexcoords].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeTexcoords].bufferIndex = BufferIndexMeshTexcoords;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshTexcoords].stride = 8;
        mtlVertexDescriptor.layouts[BufferIndexMeshTexcoords].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshTexcoords].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 2;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeSkinWeight].format = MTLVertexFormatFloat3;
        mtlVertexDescriptor.attributes[VertexAttributeSkinWeight].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeSkinWeight].bufferIndex = BufferIndexMeshSkinWeight;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshSkinWeight].stride = 12;
        mtlVertexDescriptor.layouts[BufferIndexMeshSkinWeight].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshSkinWeight].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeJointIndices].format = MTLVertexFormatFloat3;
        mtlVertexDescriptor.attributes[VertexAttributeJointIndices].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeJointIndices].bufferIndex = BufferIndexMeshSkinWeight;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshJointIndices].stride = 12;
        mtlVertexDescriptor.layouts[BufferIndexMeshJointIndices].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshJointIndices].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Tangents ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeTangents].format = MTLVertexFormatFloat3;
        mtlVertexDescriptor.attributes[VertexAttributeTangents].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeTangents].bufferIndex = BufferIndexMeshSkinWeight;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshTangents].stride = 12;
        mtlVertexDescriptor.layouts[BufferIndexMeshTangents].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshTangents].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeBitangents].format = MTLVertexFormatFloat3;
        mtlVertexDescriptor.attributes[VertexAttributeBitangents].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeBitangents].bufferIndex = BufferIndexMeshSkinWeight;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshBitangents].stride = 12;
        mtlVertexDescriptor.layouts[BufferIndexMeshBitangents].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshBitangents].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 3;
    }
    
    if ( bind & GRAPHIC_SHADER_BIND_CustomFloat ) {
        
        mtlVertexDescriptor.attributes[VertexAttributeCustomFloat].format = MTLVertexFormatFloat;
        mtlVertexDescriptor.attributes[VertexAttributeCustomFloat].offset = stride;
        mtlVertexDescriptor.attributes[VertexAttributeCustomFloat].bufferIndex = BufferIndexMeshSkinWeight;
        
        mtlVertexDescriptor.layouts[BufferIndexMeshCustomFloat].stride = 4;
        mtlVertexDescriptor.layouts[BufferIndexMeshCustomFloat].stepRate = 1;
        mtlVertexDescriptor.layouts[BufferIndexMeshCustomFloat].stepFunction = MTLVertexStepFunctionPerVertex;
        
        stride += 1;
    }
    
    return (__bridge void *) mtlVertexDescriptor;
}

void * GRAPHIC_SYSTEM::CreateMetalPipelineState( void * descriptor ) {
    
    NSError *error = NULL;
    
    id <MTLRenderPipelineState> pipeline_state = [_device newRenderPipelineStateWithDescriptor:(__bridge MTLRenderPipelineDescriptor *) descriptor error:&error];
    
    if (!pipeline_state)
    {
        NSLog(@"Failed to created pipeline state, error %@", error);
    }
    
    return (__bridge void *) pipeline_state;
}

void GRAPHIC_SYSTEM::EnableMtlPipelineState( void * pipeline_state ) {
    
    id<MTLRenderPipelineState> pps = (__bridge id<MTLRenderPipelineState>) pipeline_state;
    [_renderEncoder setRenderPipelineState:pps];
}

void * GRAPHIC_SYSTEM::CreateMetalFunction( const char * function_name ) {
    
    id <MTLFunction> fc = [_defaultLibrary newFunctionWithName:[[NSString alloc] initWithCString:function_name encoding:NSASCIIStringEncoding] ];
    
    return (__bridge void *) fc;
}

void GRAPHIC_SYSTEM::InitializeMetal( void * view ) {
    
    _view = (__bridge MTKView *) view;
    
    _view.device = MTLCreateSystemDefaultDevice();
    _metalDelegate = [[METAL_VIEW_DELEGATE alloc] initWithMetalKitView:_view];
    _defaultLibrary = [_device newDefaultLibrary];
    
    [_metalDelegate mtkView:_view drawableSizeWillChange:_view.bounds.size];
    
    _view.delegate = _metalDelegate;
    
    _view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    _view.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    _view.sampleCount = 1;
    
    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];
    
    NSUInteger uniformBufferSize = kAlignedUniformsSize * kMaxBuffersInFlight;
    
    _dynamicUniformBuffer = [_device newBufferWithLength:uniformBufferSize
                                                 options:MTLResourceStorageModeShared];
    
    _dynamicUniformBuffer.label = @"UniformBuffer";
    
    _commandQueue = [_device newCommandQueue];
    
    _metalAllocator = [[MTKMeshBufferAllocator alloc]
                                              initWithDevice: _device];
    
    _textureLoader = [[MTKTextureLoader alloc] initWithDevice:_device];
}

GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {
    
}

void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version ) {
    
}

void GRAPHIC_SYSTEM::Finalize() {
    
}

void GRAPHIC_SYSTEM::EnableScissor(bool enable) {
    
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

void GRAPHIC_SYSTEM::SetScissorRectangle( float x, float y, float width, float height ) {
    
    //#error "TODO IMPLEMENT"
    
    MTLScissorRect rect;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    
    [_renderEncoder setScissorRect:rect];
}

void GRAPHIC_SYSTEM::EnableStencilTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, int ref, unsigned int mask ) {
    
    //#error "TODO IMPLEMENT"
}
void GRAPHIC_SYSTEM::DisableStencil() {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetStencilOperation( const GRAPHIC_POLYGON_FACE face, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_fail, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_pass, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_and_depth_fail ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DisableBlend() {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetBlendFunction( const GRAPHIC_SYSTEM_BLEND_EQUATION equation ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin, float range_end ) {
    
    //#error "TODO IMPLEMENT"
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
}

void GRAPHIC_SYSTEM::SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DisableDepthTest() {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ReleaseTexture( GRAPHIC_TEXTURE * texture ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetTextureOptions( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_FILTERING filtering, GRAPHIC_TEXTURE_WRAP wrap, const CORE_HELPERS_COLOR & color ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateFrameBuffer( GRAPHIC_RENDER_TARGET * target, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateDepthBuffer( GRAPHIC_RENDER_TARGET * target, int width, int height ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, CORE_DATA_BUFFER & texture_data, bool generate_mipmap ) {
    
    NSError *error = NULL;
    
    NSDictionary *textureLoaderOptions =
    @{
      MTKTextureLoaderOptionTextureUsage       : @(MTLTextureUsageShaderRead),
      MTKTextureLoaderOptionTextureStorageMode : @(MTLStorageModePrivate)
      };
    
    texture->SetTextureHandle( (__bridge void *)  [_textureLoader newTextureWithData:[NSData dataWithBytes:texture_data.GetDataPointer() length:texture_data.GetSize()] options:textureLoaderOptions error:&error] );
    
    if(texture->GetTextureHandle() == NULL || error)
    {
        NSLog(@"Error creating texture %@", error.localizedDescription);
    }
}

void GRAPHIC_SYSTEM::CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DiscardTexture( GRAPHIC_TEXTURE * texture ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVector( const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVectorTable( const float * vector, int size, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( const float * matrix, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateVertexBuffer(GRAPHIC_MESH &mesh) {
    
    id<MDLMeshBuffer> buffer = [_metalAllocator newBufferWithData:[NSData dataWithBytes:mesh.GetVertexCoreBuffer()->GetDataPointer() length:mesh.GetVertexCoreBuffer()->GetSize()] type:(MDLMeshBufferTypeVertex)];
    
    mesh.SetMTKVertexBuffer( (void *) CFBridgingRetain(buffer) );
}

void GRAPHIC_SYSTEM::CreateIndexBuffer(GRAPHIC_MESH &mesh) {
    
    id<MDLMeshBuffer> buffer = [_metalAllocator newBufferWithData:[NSData dataWithBytes:mesh.GetIndexCoreBuffer()->GetDataPointer() length:mesh.GetIndexCoreBuffer()->GetSize()] type:(MDLMeshBufferTypeIndex)];
    
    mesh.SetMTKIndexBuffer( (void *) CFBridgingRetain(buffer) );
}

void GRAPHIC_SYSTEM::ApplyBuffers(GRAPHIC_MESH & mesh) {
    
    //#error "TODO IMPLEMENT"
    
    [_renderEncoder setDepthStencilState:_depthState];
    
    [_renderEncoder setVertexBuffer:_dynamicUniformBuffer
                            offset:_uniformBufferOffset
                           atIndex:BufferIndexUniforms];
    
    [_renderEncoder setFragmentBuffer:_dynamicUniformBuffer
                              offset:_uniformBufferOffset
                             atIndex:BufferIndexUniforms];
    
    /*for (NSUInteger bufferIndex = 0; bufferIndex < _mesh.vertexBuffers.count; bufferIndex++)
    {
        MTKMeshBuffer *vertexBuffer = _mesh.vertexBuffers[bufferIndex];
        if((NSNull*)vertexBuffer != [NSNull null])
        {
            [_renderEncoder setVertexBuffer:vertexBuffer.buffer
                                    offset:vertexBuffer.offset
                                   atIndex:bufferIndex];
        }
    }
    
    [_renderEncoder setFragmentTexture:_colorMap
                              atIndex:TextureIndexColor];
    
    for(MTKSubmesh *submesh in _mesh.submeshes)
    {
        [_renderEncoder drawIndexedPrimitives:submesh.primitiveType
                                  indexCount:submesh.indexCount
                                   indexType:submesh.indexType
                                 indexBuffer:submesh.indexBuffer.buffer
                           indexBufferOffset:submesh.indexBuffer.offset];
    }*/
}

void GRAPHIC_SYSTEM::ReleaseBuffers(GRAPHIC_MESH &mesh) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::Clear() {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ClearFrambufferDepth( float default_depth ) {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ClearFrambufferColor() {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ClearFrambufferStencil() {
    
    //#error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::BeginRendering() {
    
    dispatch_semaphore_wait(_inFlightSemaphore, DISPATCH_TIME_FOREVER);
    
    _commandBuffer = [_commandQueue commandBuffer];
    _commandBuffer.label = @"MyCommand";
    
    __block dispatch_semaphore_t block_sema = _inFlightSemaphore;
    [_commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer)
     {
         dispatch_semaphore_signal(block_sema);
     }];
    
    _renderPassDescriptor = _view.currentRenderPassDescriptor;
    
    _renderEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:_renderPassDescriptor];
    _renderEncoder.label = @"MyRenderEncoder";
    
    [_renderEncoder pushDebugGroup:@"DrawBox"];
}

void GRAPHIC_SYSTEM::EndRendering() {
    
    [_renderEncoder popDebugGroup];
    
    [_renderEncoder endEncoding];
    
    [_commandBuffer presentDrawable:_view.currentDrawable];

    [_commandBuffer commit];
}

#endif
