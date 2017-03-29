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
#include "GAMEPLAY_GAME_HOUSE.h"
#include "GRAPHICS_CAMERA_MANAGER.h"

XS_CLASS_BEGIN( GAMEPLAY_GAME )

    GAMEPLAY_GAME();
    ~GAMEPLAY_GAME();

    void Initialize();
    void Finalize();

    void Start(int seed = -1);
    void Pause( bool enable );

    void Update(const float);
    void Render();

    void SelectNextPlayer();
    void PlayerDiceRoll();
    void PlayerBuyProperty();
    void PlayerEndTurn();
    void PlayerBuyHouse();
    void OnObjectPicked( GAMEPLAY_COMPONENT_ENTITY * entity );

    void DisplayNextChanceCard(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void DisplayNextCommunityCaisseCard(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void ProposeBuyProperty( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player );
    void ProposeBuyHouse( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player );
    void SelectCell( GAMEPLAY_GAME_BOARD_CELL * cell );
    void SetPlayers( std::vector< GAME_PLAYER_MODEL > & players );
    void UpdatePlayer( GAMEPLAY_PLAYER * player_to_update );

    void DisplayDiceRollResult( const GAMEPLAY_DICE_ROLL_RESULT & result );

    inline GAMEPLAY_GAME_BOARD & GetBoard() { return Board; }
    inline GAMEPLAY_SCENE & GetScene() { return Scene; }
    inline void SetUIGameHudPresenter( GAME_HUD_PRESENTER * presenter ) {UIGameHudPresenter = presenter;}
    inline GAME_HUD_PRESENTER * GetUIGameHudPresenter() { return UIGameHudPresenter; }
    inline std::vector<GAMEPLAY_PLAYER *> & GetPlayerTable() { return PlayerTable; }
    inline GAMEPLAY_GAME_HOUSE * GetNextHouse() {return HouseTable[NextHouseIndex++]; }
    inline GAMEPLAY_PLAYER * GetCurrentPlayer() { return PlayerTable[ActivePlayerIndex]; }

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
    void InitializeHouses();

    GAMEPLAY_GAME_BOARD
        Board;
    std::vector<GAMEPLAY_PLAYER *>
        PlayerTable;
    int
        ActivePlayerIndex,
        NextHouseIndex;
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
    std::vector< GAMEPLAY_GAME_HOUSE * >
        HouseTable;
    GAMEPLAY_GAME_BOARD_CELL
        *SelectedCell;
    GRAPHICS_CAMERA_MANAGER
        GameCamera;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_hpp */
