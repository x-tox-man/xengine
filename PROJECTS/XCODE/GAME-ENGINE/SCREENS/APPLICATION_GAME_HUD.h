//
//  APPLICATION_GAME_HUD.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_GAME_HUD_hpp
#define APPLICATION_GAME_HUD_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "APPLICATION_HUD_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_GAME_HUD, GRAPHIC_UI_FRAME )

    APPLICATION_GAME_HUD();
    virtual ~APPLICATION_GAME_HUD();

    virtual void Initialize() override;

    APPLICATION_HUD_PRESENTER
        * Presenter;

XS_CLASS_END


#endif /* APPLICATION_GAME_HUD_hpp */
