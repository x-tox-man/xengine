//
//  GRAPHIC_RENDERER_TECHNIQUE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE.h"

GRAPHIC_RENDERER_TECHNIQUE::GRAPHIC_RENDERER_TECHNIQUE() :
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
    }
    else {
        GRAPHIC_SYSTEM::EnableDefaultFrameBuffer();
    }
    
    RendererCallback( renderer );
    
    if ( RenderTarget != NULL ) {
        
        RenderTarget->Discard();
    }
    else {
        GRAPHIC_SYSTEM::DisableDefaultFrameBuffer();
    }
        
}

void GRAPHIC_RENDERER_TECHNIQUE::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
}
