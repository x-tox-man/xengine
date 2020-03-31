//
//  GRAPHIC_RENDERER_STATE_DESCRIPTOR.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 10/02/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"

GRAPHIC_RENDERER_STATE_DESCRIPTOR::GRAPHIC_RENDERER_STATE_DESCRIPTOR() :
    ItDoesBlending( false ),
    ItDoesDepthTest( true ),
    SampleCount( 1 ),
    BlendFunction( GRAPHIC_SYSTEM_BLEND_EQUATION_Add ),
    BlendingSourceOperation( GRAPHIC_SYSTEM_BLEND_OPERATION_One ),
    BlendingDestinationOperation( GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha ),
    ColorAttachmentPixelFormat(),
    DepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 ),
    StencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8 ) {
    
    for (int i = 0; i < GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS; i++ ) {
        
        ColorAttachmentPixelFormat[i] = GRAPHIC_TEXTURE_IMAGE_TYPE_None;
    }

    ColorAttachmentPixelFormat[0] = GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;
}

GRAPHIC_RENDERER_STATE_DESCRIPTOR::GRAPHIC_RENDERER_STATE_DESCRIPTOR( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & other ) :
    ItDoesBlending( other.ItDoesBlending ),
    ItDoesDepthTest( other.ItDoesDepthTest ),
    SampleCount( other.SampleCount ),
    BlendFunction( other.BlendFunction ),
    BlendingSourceOperation( other.BlendingSourceOperation ),
    BlendingDestinationOperation( other.BlendingDestinationOperation ),
    ColorAttachmentPixelFormat(),
    DepthAttachmentPixelFormat( other.DepthAttachmentPixelFormat ),
    StencilAttachmentPixelFormat( other.StencilAttachmentPixelFormat ) {
    
    for (int i = 0; i < GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS; i++ ) {
        
        ColorAttachmentPixelFormat[i] = other.ColorAttachmentPixelFormat[i];
    }
}
