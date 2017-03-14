//
//  GAME_LOADER_SCREEN.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 6/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAME_LOADER_SCREEN_hpp
#define GAME_LOADER_SCREEN_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAME_LOADER_SCREEN, GRAPHIC_UI_FRAME )

    GAME_LOADER_SCREEN();
    virtual ~GAME_LOADER_SCREEN();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* GAME_LOADER_SCREEN_hpp */
