//
//  GAMEPLAY_GAME.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_GAME_hpp
#define GAMEPLAY_GAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_PLAYER.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_FIXED_STATE_EVENT.h"
#include "GAMEPLAY_GAME_BOARD.h"
#include "GAMEPLAY_SCENE.h"
#include "GAME_PLAYER_MODEL.h"
#include "GAMEPLAY_DICE_ROLL_RESULT.h"
#include "GAMEPLAY_GAME_CARD.h"
#include "GRAPHIC_BACKGROUND.h"

XS_CLASS_BEGIN( GAMEPLAY_GAME )

    GAMEPLAY_GAME();
    ~GAMEPLAY_GAME();

    void Initialize( std::vector<GAME_PLAYER_MODEL> & player_model_table );

    void Start();
    void Pause( bool enable );

    void Update(const float);
    void Render();

    void SelectNextPlayer();
    void PlayerDiceRoll();
    void PlayerBuyProperty();
    void PlayerEndTurn();

    void DisplayNextChanceCard(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void DisplayNextCommunityCaisseCard(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void ProposeBuyProperty( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player );

    void DisplayDiceRollResult( const GAMEPLAY_DICE_ROLL_RESULT & result );

    inline GAMEPLAY_GAME_BOARD & GetBoard() { return Board; }
    inline GAMEPLAY_SCENE & GetScene() { return Scene; }
    inline void SetUIGameHudPresenter( GAME_HUD_PRESENTER * presenter ) {UIGameHudPresenter = presenter;}
    inline GAME_HUD_PRESENTER * GetUIGameHudPresenter() { return UIGameHudPresenter; }
    inline std::vector<GAMEPLAY_PLAYER *> & GetPlayerTable() { return PlayerTable; }

    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, const float )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState(GAME_BASE_STATE, GAMEPLAY_GAME)
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STARTING )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STARTING )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, PLAYER_TURN_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_TURN_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, PLAYER_TRANSITION_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_TRANSITION_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, END_GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( END_GAME_STATE )

private:

    void InitializeCaisseCards();
    void InitializeChanceCards();

    GAMEPLAY_GAME_BOARD
        Board;
    std::vector<GAMEPLAY_PLAYER *>
        PlayerTable;
    int
        ActivePlayerIndex;
    float
        AnimationTimer;
    bool
        IsRunning;
    CORE_FIXED_STATE_MACHINE<GAME_BASE_STATE, GAMEPLAY_GAME>
        StateMachine;
    GAMEPLAY_SCENE
        Scene;
    GAME_HUD_PRESENTER
        * UIGameHudPresenter;
    std::vector< GAMEPLAY_GAME_CARD * >
        ChanceCardTable,
        CaisseCardTable;
    GRAPHIC_BACKGROUND
        * Background;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_hpp */
