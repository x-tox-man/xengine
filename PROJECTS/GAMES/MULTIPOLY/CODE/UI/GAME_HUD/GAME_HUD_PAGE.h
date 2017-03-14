//
//  GAME_HUD_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAME_HUD_PAGE_hpp
#define GAME_HUD_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "GAME_HUD_PRESENTER.h"
#include "GAMEPLAY_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAME_HUD_PAGE, GRAPHIC_UI_FRAME )

    GAME_HUD_PAGE();
    GAME_HUD_PAGE( GAME_HUD_PRESENTER * presenter);
    virtual ~GAME_HUD_PAGE();

    virtual void Initialize() override;

private :

    void CreatePlayerInfoFrames( GAMEPLAY_PLAYER * player, CORE_HELPERS_IDENTIFIER &, int offset );
    virtual GAME_HUD_PRESENTER * CreatePresenter() { return new GAME_HUD_PRESENTER; }

    GAME_HUD_PRESENTER *
        Presenter;

public:

    static CORE_HELPERS_IDENTIFIER
        Player1FrameId,
        Player2FrameId,
        Player3FrameId,
        Player4FrameId,
        RollDiceButtonId,
        DiceRollResultId,
        MoneyId,
        BuyPropertyButtonId,
        EndTurnButtonId,
        BuyHouseButtonId;

XS_CLASS_END

#endif /* GAME_HUD_PAGE_hpp */
