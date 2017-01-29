//
//  GRAPHIC_WINDOW_ANDROID.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_WINDOW_ANDROID__
#define __GAME_ENGINE_REBORN__GRAPHIC_WINDOW_ANDROID__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_WINDOW.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_ANDROID, GRAPHIC_WINDOW )

    GRAPHIC_WINDOW_ANDROID();
    virtual ~GRAPHIC_WINDOW_ANDROID();

    virtual void Initialize() override;

private :

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_WINDOW_ANDROID__) */
