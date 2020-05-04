//
//  GRAPHIC_RENDERER_TECHNIQUE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"

GRAPHIC_RENDERER_TECHNIQUE::GRAPHIC_RENDERER_TECHNIQUE() :
    TransparentMask(),
    RendererCallback(),
    RendererCallback1(),
    RenderTarget( NULL ),
    FinalRenderTarget( NULL ) {
    
}

GRAPHIC_RENDERER_TECHNIQUE::~GRAPHIC_RENDERER_TECHNIQUE() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE::Initialize( GRAPHIC_RENDERER & renderer ) {
    
}

void GRAPHIC_RENDERER_TECHNIQUE::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    if ( RenderTarget != NULL ) {
        
        RenderTarget->BindForWriting();
        RenderTarget->Apply( renderer );
    }
    else {
        renderer.GetDescriptor().DisableColor();
        renderer.GetDescriptor().SetColorAttachmentPixelFormat( 0, GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
        renderer.GetDescriptor().SetDepthAttachmentPixelFormat( GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
        renderer.GetDescriptor().SetStencilAttachmentPixelFormat(GRAPHIC_TEXTURE_IMAGE_TYPE_STENCIL8 );
        GRAPHIC_SYSTEM::EnableDefaultFrameBuffer();
    }
    
    RendererCallback( renderer, GetTransparentMask() );
    
    if ( RenderTarget != NULL ) {
        
        RenderTarget->Discard();
    }
    else {
        GRAPHIC_SYSTEM::DisableDefaultFrameBuffer();
    }
        
}

void GRAPHIC_RENDERER_TECHNIQUE::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
}
