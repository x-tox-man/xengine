//
//  GAME_HUD_PRESENTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAME_HUD_PRESENTER_hpp
#define GAME_HUD_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"
#include "GAMEPLAY_DICE_ROLL_RESULT.h"

class GAMEPLAY_PLAYER;
class GAMEPLAY_GAME_BOARD_CELL;

XS_CLASS_BEGIN_WITH_ANCESTOR(GAME_HUD_PRESENTER, GRAPHIC_UI_PRESENTER)

    GAME_HUD_PRESENTER();
    virtual ~GAME_HUD_PRESENTER();

    virtual void Configure() override;

    void OnPauseClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void OnRollDiceButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void OnBuyPropertyButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void OnEndGameButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );


    void DisplayRollDiceButton();
    void DisplayRollDiceResult( const GAMEPLAY_DICE_ROLL_RESULT & result );
    void UpdateMoneyForPlayer( GAMEPLAY_PLAYER * player );
    void ProposeBuyProperty( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player );

    void ShowEndButton();

private:

    bool
        NavigationIsRequested;

XS_CLASS_END

#endif /* GAME_HUD_PRESENTER_hpp */
