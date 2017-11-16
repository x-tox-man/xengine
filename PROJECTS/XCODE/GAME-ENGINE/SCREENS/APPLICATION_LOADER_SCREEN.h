//
//  APPLICATION_LOADER_SCREEN.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_LOADER_SCREEN_hpp
#define APPLICATION_LOADER_SCREEN_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "NETWORK_PLAYER.h"
#include "NETWORK_CLIENT.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_GAME_PLAYER_LIST_ADAPTER.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_LOADER_SCREEN, GRAPHIC_UI_FRAME )

APPLICATION_LOADER_SCREEN();
virtual ~APPLICATION_LOADER_SCREEN();

virtual void Initialize() override;
virtual void Update( const float ) override;

private:

    float
        Percentage;
    GRAPHIC_UI_FRAME
        * ProgressBar;
    GRAPHIC_UI_RENDER_STYLE
        * DefaultRenderStyle;
XS_CLASS_END

#endif /* APPLICATION_LOADER_SCREEN_hpp */
