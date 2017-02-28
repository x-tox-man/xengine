//
//  GAME_HUD_PRESENTER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAME_HUD_PRESENTER.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "INGAME_OPTIONS_PAGE.h"
#include "MULTIPOLY_APPLICATION.h"
#include "GAME_HUD_PAGE.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAME_HUD_PRESENTER::GAME_HUD_PRESENTER() :
    GRAPHIC_UI_PRESENTER(),
    NavigationIsRequested( false ) {
    
}

GAME_HUD_PRESENTER::~GAME_HUD_PRESENTER() {
    
}

void GAME_HUD_PRESENTER::Configure() {
    
    ((MULTIPOLY_APPLICATION*)&MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().SetUIGameHudPresenter( this );
    
    std::vector<GAMEPLAY_PLAYER *> players = ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGame().GetPlayerTable();
    
    for ( int i = 0; i < players.size(); i++ ) {
        
        CORE_HELPERS_CALLBACK_1<GAMEPLAY_PLAYER *> callback( &Wrapper1<GAME_HUD_PRESENTER, GAMEPLAY_PLAYER *, &GAME_HUD_PRESENTER::UpdateMoneyForPlayer>, this);
        
        players[i]->SetOnChangedCallback( callback );
    }
}

void GAME_HUD_PRESENTER::OnPauseClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed) {
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().DisplayModal< INGAME_OPTIONS_PAGE >( "ingame_options", CORE_MATH_VECTOR(200.0f, 200.0f) );
        
        ((MULTIPOLY_APPLICATION*)&MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().Pause( true );
        
        NavigationIsRequested = true;
    }
}

void GAME_HUD_PRESENTER::OnBuyPropertyButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed) {
        
        clicked_element->Disable();
        clicked_element->SetVisible( false );
        
        ((MULTIPOLY_APPLICATION*)&MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().PlayerBuyProperty();
    }
}

void GAME_HUD_PRESENTER::OnEndGameButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed) {
        
        clicked_element->Disable();
        clicked_element->SetVisible( false );
        
        (GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::BuyPropertyButtonId ) )->Disable();
        (GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::BuyPropertyButtonId ) )->SetVisible( false );
        
        ((MULTIPOLY_APPLICATION*)&MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().PlayerEndTurn();
    }
}

void GAME_HUD_PRESENTER::OnRollDiceButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_STATE_Pressed) {
        
        clicked_element->SetVisible( false );
        clicked_element->Disable();
        
        ((MULTIPOLY_APPLICATION*)&MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().PlayerDiceRoll();
    }
}

void GAME_HUD_PRESENTER::DisplayRollDiceButton() {
    
    auto item = GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::RollDiceButtonId );
    item->SetVisible( true );
    item->Enable();
}

void GAME_HUD_PRESENTER::DisplayRollDiceResult( const GAMEPLAY_DICE_ROLL_RESULT & result ) {
    
    static char dice_result[16];
    
    sprintf(dice_result, "%d", result.Total );
    
    GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::DiceRollResultId )->SetTextValue(dice_result);
}

void GAME_HUD_PRESENTER::UpdateMoneyForPlayer( GAMEPLAY_PLAYER * player  ) {
    
    CORE_HELPERS_IDENTIFIER * id_array[4];
    
    id_array[0] = &GAME_HUD_PAGE::Player1FrameId;
    id_array[1] = &GAME_HUD_PAGE::Player2FrameId;
    id_array[2] = &GAME_HUD_PAGE::Player3FrameId;
    id_array[3] = &GAME_HUD_PAGE::Player4FrameId;
    
    static char money_value_text[16];
    
    sprintf(money_value_text, "%d", player->GetMoney() );
    
    auto frame_element = GetView()->GetObjectForIdentifier( *id_array[ player->GetPlayerIndex() ] );
    frame_element->GetObjectForIdentifier( GAME_HUD_PAGE::MoneyId )->SetTextValue( money_value_text );
}

void GAME_HUD_PRESENTER::ProposeBuyProperty( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    (GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::BuyPropertyButtonId ) )->Enable();
    (GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::BuyPropertyButtonId ) )->SetVisible( true );
}

void GAME_HUD_PRESENTER::ShowEndButton() {
    
    (GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::EndTurnButtonId ) )->Enable();
    (GetView()->GetObjectForIdentifier( GAME_HUD_PAGE::EndTurnButtonId ) )->SetVisible( true );
}
