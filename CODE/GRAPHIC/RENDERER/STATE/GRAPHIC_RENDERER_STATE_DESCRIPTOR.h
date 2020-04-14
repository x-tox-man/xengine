//
//  GRAPHIC_RENDERER_STATE_DESCRIPTOR.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 10/02/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_STATE_DESCRIPTOR_hpp
#define GRAPHIC_RENDERER_STATE_DESCRIPTOR_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SYSTEM_COMPARE_OPERATION.h"
#include "GRAPHIC_SYSTEM_BLEND_OPERATION.h"
#include "GRAPHIC_SYSTEM_BLEND_EQUATION.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "GRAPHIC_POLYGON_FACE.h"
#include "GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION.h"

#define GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS   8

struct GRAPHIC_RENDERER_STATE_DESCRIPTOR_STENCIL_DESCRIPTOR {
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION
        StencilPassAction,
        StencilFailAction,
        StencilAndDepthFailAction;
};

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_RENDERER_STATE_DESCRIPTOR )

    GRAPHIC_RENDERER_STATE_DESCRIPTOR();

    void operator = ( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & other ) {
        
        ItDoesBlending = other.ItDoesBlending;
        ItDoesStencilTest = other.ItDoesStencilTest;
        ItDoesDepthTest = other.ItDoesDepthTest;
        BlendFunction = other.BlendFunction;
        SampleCount = other.SampleCount;

        
        BlendingSourceOperation = other.BlendingSourceOperation;
        BlendingDestinationOperation = other.BlendingDestinationOperation;
        DepthAttachmentPixelFormat = other.DepthAttachmentPixelFormat;
        StencilAttachmentPixelFormat = other.StencilAttachmentPixelFormat;
        
        for (int i = 0; i < GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS; i++ ) {
            
            ColorAttachmentPixelFormat[i] = other.ColorAttachmentPixelFormat[i];
        }
    }

    friend bool operator == ( GRAPHIC_RENDERER_STATE_DESCRIPTOR & a, GRAPHIC_RENDERER_STATE_DESCRIPTOR & b );
    friend bool operator == ( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & a, const GRAPHIC_RENDERER_STATE_DESCRIPTOR & b );
    friend bool operator < ( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & a, const GRAPHIC_RENDERER_STATE_DESCRIPTOR & b );

    inline void SetColorAttachmentPixelFormat( int i, GRAPHIC_TEXTURE_IMAGE_TYPE type ) { ColorAttachmentPixelFormat[ i ] = type; }
    inline void SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE type ) { DepthAttachmentPixelFormat = type; }
    inline void SetStencilAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE type ) { StencilAttachmentPixelFormat = type; }

    void DisableColor() {
        
        for (int i = 0; i < GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS; i++ ) {
            
            ColorAttachmentPixelFormat[i] = GRAPHIC_TEXTURE_IMAGE_TYPE_None;
        }
    }

    GRAPHIC_SYSTEM_BLEND_EQUATION
        BlendFunction;
    GRAPHIC_SYSTEM_BLEND_OPERATION
        BlendingSourceOperation,
        BlendingDestinationOperation;
    GRAPHIC_TEXTURE_IMAGE_TYPE
        ColorAttachmentPixelFormat[ GRAPHIC_RENDERER_STATE_DESCRIPTOR_MAX_TARGETS ],
        DepthAttachmentPixelFormat,
        StencilAttachmentPixelFormat;
    GRAPHIC_SYSTEM_COMPARE_OPERATION
        StencilOperation;
    bool
        ItDoesBlending,
        ItDoesStencilTest,
        ItDoesDepthTest;
    int
        StencilRef;
    unsigned int
        SampleCount,
        StencilMask;

    GRAPHIC_RENDERER_STATE_DESCRIPTOR_STENCIL_DESCRIPTOR
        StencilFaceTable[ GRAPHIC_POLYGON_FACE_FrontAndBack ];
XS_CLASS_END

inline bool operator == ( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & a, const GRAPHIC_RENDERER_STATE_DESCRIPTOR & b ) {
    
    abort(); //TODO:
    return a.ItDoesBlending == b.ItDoesBlending &&
        a.BlendingSourceOperation == b.BlendingSourceOperation &&
        a.BlendingDestinationOperation == b.BlendingDestinationOperation &&
        a.BlendFunction == b.BlendFunction;
}

inline bool operator < ( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & a, const GRAPHIC_RENDERER_STATE_DESCRIPTOR & b ) {
    
    bool t = ( (int) a.ItDoesDepthTest < (int) b.ItDoesDepthTest ) ||
    a.StencilRef < b.StencilRef ||
    a.StencilMask < b.StencilMask ||
    ( (int) a.StencilOperation < (int) b.StencilOperation ) ||
    ( (int) a.ItDoesStencilTest < (int) b.ItDoesStencilTest ) ||
    ( (int) a.ItDoesBlending < (int) b.ItDoesBlending ) ||
    a.BlendingSourceOperation < b.BlendingSourceOperation ||
    a.BlendingDestinationOperation < b.BlendingDestinationOperation ||
    a.BlendFunction < b.BlendFunction ||
    a.ColorAttachmentPixelFormat[0] < b.ColorAttachmentPixelFormat[0] ||
    a.ColorAttachmentPixelFormat[1] < b.ColorAttachmentPixelFormat[1] ||
    a.ColorAttachmentPixelFormat[2] < b.ColorAttachmentPixelFormat[2] ||
    a.ColorAttachmentPixelFormat[3] < b.ColorAttachmentPixelFormat[3] ||
    a.ColorAttachmentPixelFormat[4] < b.ColorAttachmentPixelFormat[4] ||
    a.ColorAttachmentPixelFormat[5] < b.ColorAttachmentPixelFormat[5] ||
    a.ColorAttachmentPixelFormat[6] < b.ColorAttachmentPixelFormat[6] ||
    a.ColorAttachmentPixelFormat[7] < b.ColorAttachmentPixelFormat[7] ||
    a.DepthAttachmentPixelFormat < b.DepthAttachmentPixelFormat ||
    a.StencilAttachmentPixelFormat < b.StencilAttachmentPixelFormat;
    
    return t;
}

#endif /* GRAPHIC_RENDERER_STATE_DESCRIPTOR_hpp */
