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

static const NSUInteger kMaxBuffersInFlight = 3;

static const size_t kAlignedUniformsSize = (sizeof(ObjectUniforms) & ~0xFF) + 0x100;

void GRAPHIC_SHADER_PROGRAM::LinkTogether( const GRAPHIC_SHADER_BIND shader_bind ) {
    
    //__bridge is used here because there is not retain increment to do in this function
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    p.vertexDescriptor = (__bridge MTLVertexDescriptor *) GRAPHIC_SYSTEM::CreateMtlVertexDescriptor( shader_bind );
    
    //CFBridgingRetain is used because we assign a retain object to this instance
    _pipelineState = GRAPHIC_SYSTEM::CreateMetalPipelineState( (void *) CFBridgingRetain(p), *this );
    
    _dynamicUniformBuffer = GRAPHIC_SYSTEM::CreateMetalDynamicUniformBuffer( sizeof(ObjectUniforms) );
}

void GRAPHIC_SHADER_PROGRAM::Initialize() {
    
    //Get the view
    
    //CFBridgingRetain is used because we assign a retain object to this instance
    _pipelineStateDescriptor = (void *) CFBridgingRetain( [[MTLRenderPipelineDescriptor alloc] init] );
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    p.label = @"MyPipeline";
    
    p.sampleCount = 1;
    
    p.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    p.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8; //MTLPixelFormatInvalid
    p.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8; //MTLPixelFormatInvalid
    
    _uniformBufferOffset = 0;
    _uniformBufferIndex = 0;
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

void GRAPHIC_SHADER_PROGRAM::Enable( GRAPHIC_RENDERER & renderer ) {
    
    /*std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_SHADER_ATTRIBUTE>::iterator it = ShaderAttributeTable.begin();
    
    id <MTLBuffer> buffer = (__bridge id <MTLBuffer>) _dynamicUniformBuffer;

    while (it != ShaderAttributeTable.end() ) {
        
        uint8_t * address = ((uint8_t*)buffer.contents + it->second.AttributeIndex);
        memcpy( (void*) address, (void*) &it->second.AttributeValue.Value.FloatMatrix4x4[0], 16 * sizeof(float) );
        it++;
    }*/

    GRAPHIC_SYSTEM::EnableMtlPipelineState( _pipelineState );
    
    GRAPHIC_SYSTEM::EnableMtlUniforms( renderer.MetalUniformBuffer, renderer.UniformOffset, _uniformBufferIndex );
}

void GRAPHIC_SHADER_PROGRAM::Disable() {
    
}

void GRAPHIC_SHADER_PROGRAM::BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    if ( shader_attribute.AttributeIndex != -1 ) {
        
        shader_attribute.AttributeName = identifier;
        
        setShaderAttribute( shader_attribute );
    }
}
