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

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

void GRAPHIC_SHADER_PROGRAM::LinkTogether( const GRAPHIC_SHADER_BIND shader_bind ) {
    
    //__bridge is used here because there is not retain increment to do in this function
    MTLRenderPipelineDescriptor * p = (__bridge MTLRenderPipelineDescriptor * ) _pipelineStateDescriptor;
    
    p.vertexDescriptor = (__bridge MTLVertexDescriptor *) GRAPHIC_SYSTEM::CreateMtlVertexDescriptor( shader_bind );
    
    //CFBridgingRetain is used because we assign a retain object to this instance
    _pipelineState = GRAPHIC_SYSTEM::CreateMetalPipelineState( (void *) CFBridgingRetain(p) );
}

void GRAPHIC_SHADER_PROGRAM::Initialize() {
    
    //Get the view
    
    //CFBridgingRetain is used because we assign a retain object to this instance
    _pipelineStateDescriptor = (void *) CFBridgingRetain( [[MTLRenderPipelineDescriptor alloc] init] );
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
    
    p.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    p.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    p.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
}

void GRAPHIC_SHADER_PROGRAM::LoadPartial( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type ) {
    

}

void GRAPHIC_SHADER_PROGRAM::Finalize() {
    
}

void GRAPHIC_SHADER_PROGRAM::Enable() {
    
    GRAPHIC_SYSTEM::EnableMtlPipelineState( _pipelineState );
}

void GRAPHIC_SHADER_PROGRAM::Disable() {
    
}

void GRAPHIC_SHADER_PROGRAM::BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    if ( shader_attribute.AttributeIndex != -1 ) {
        
        shader_attribute.AttributeName = identifier;
        
        setShaderAttribute( shader_attribute );
    }
}
