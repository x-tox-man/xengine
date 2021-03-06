//
//  GRAPHIC_RENDERER_TECHNIQUE.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_TECHNIQUE_hpp
#define GRAPHIC_RENDERER_TECHNIQUE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_RENDER_TARGET.h"

XS_CLASS_BEGIN( GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDERER_TECHNIQUE();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    inline void SetTransparentMask( int mask ) { TransparentMask = mask; }
    inline int GetTransparentMask() const { return TransparentMask; }

    int
        TransparentMask;
    CORE_HELPERS_CALLBACK_2< GRAPHIC_RENDERER &, int >
        RendererCallback,
        RendererCallback1;
    GRAPHIC_RENDER_TARGET::PTR
        RenderTarget,
        FinalRenderTarget;
XS_CLASS_END

#endif /* GRAPHIC_RENDERER_TECHNIQUE_hpp */
