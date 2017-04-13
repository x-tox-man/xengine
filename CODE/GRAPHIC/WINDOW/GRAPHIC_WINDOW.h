//
//  GRAPHIC_WINDOW.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_WINDOW__
#define __GAME_ENGINE_REBORN__GRAPHIC_WINDOW__

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN( GRAPHIC_WINDOW )

    GRAPHIC_WINDOW();
    virtual ~GRAPHIC_WINDOW();

    virtual void Resize( int width, int height ) {}

protected:

    Scalar_SGet( int, Height );
    Scalar_SGet( int, Width );

    Scalar_SGet( int, PositionX );
    Scalar_SGet( int, PositionY );

    virtual void Initialize() = 0;
    virtual void EnableBackgroundContext(bool enable) = 0;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_WINDOW__) */
