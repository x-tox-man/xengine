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

XS_CLASS_BEGIN( GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDERER_TECHNIQUE();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    CORE_HELPERS_CALLBACK_1< GRAPHIC_RENDERER & >
        RendererCallback,
        RendererCallback1;

XS_CLASS_END

#endif /* GRAPHIC_RENDERER_TECHNIQUE_hpp */
