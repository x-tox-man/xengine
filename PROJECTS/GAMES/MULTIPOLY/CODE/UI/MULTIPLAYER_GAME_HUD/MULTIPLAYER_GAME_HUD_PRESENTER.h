//
//  MULTIPLAYER_GAME_HUD_PRESENTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MULTIPLAYER_GAME_HUD_PRESENTER_hpp
#define MULTIPLAYER_GAME_HUD_PRESENTER_hpp

#include "GAME_HUD_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( MULTIPLAYER_GAME_HUD_PRESENTER, GAME_HUD_PRESENTER)

    MULTIPLAYER_GAME_HUD_PRESENTER();
    virtual ~MULTIPLAYER_GAME_HUD_PRESENTER();

    virtual void Configure() override;

    void OnPauseClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );

private:

    bool
        NavigationIsRequested;

XS_CLASS_END

#endif /* MULTIPLAYER_GAME_HUD_PRESENTER_hpp */
