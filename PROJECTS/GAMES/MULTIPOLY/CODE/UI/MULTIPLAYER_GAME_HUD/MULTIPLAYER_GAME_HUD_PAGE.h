//
//  MULTIPLAYER_GAME_HUD_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MULTIPLAYER_GAME_HUD_PAGE_hpp
#define MULTIPLAYER_GAME_HUD_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "MAIN_MENU_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( MULTIPLAYER_GAME_HUD_PAGE, GRAPHIC_UI_FRAME )

    MULTIPLAYER_GAME_HUD_PAGE();
    virtual ~MULTIPLAYER_GAME_HUD_PAGE();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* MULTIPLAYER_GAME_HUD_PAGE_hpp */
