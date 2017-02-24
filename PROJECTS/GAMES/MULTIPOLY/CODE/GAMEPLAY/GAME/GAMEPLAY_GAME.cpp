//
//  GAMEPLAY_GAME.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "APPLICATION_CONFIGURATION.h"

CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_GAME::GAME_STARTING )
    GetContext().AnimationTimer = 0.0f;
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_GAME::GAME_STARTING, UPDATE_EVENT )

    GetContext().AnimationTimer += event.GetEventData();

    if ( GetContext().AnimationTimer >= 2.0f ) {
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PLAYER_TURN_STATE);
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_GAME::GAME_STARTING )

    GetContext().SelectNextPlayer();
CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_GAME::PLAYER_TURN_STATE )

    GetContext().PlayerTable[GetContext().ActivePlayerIndex]->SetupTurn();

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_GAME::PLAYER_TURN_STATE, UPDATE_EVENT )

    GAMEPLAY_PLAYER * player = GetContext().PlayerTable[GetContext().ActivePlayerIndex];
    player->Update( event.GetEventData() );

    if ( player->IsDone() ) {
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PLAYER_TRANSITION_STATE);
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_GAME::PLAYER_TURN_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_GAME::PLAYER_TRANSITION_STATE )
    GetContext().AnimationTimer = 0.0f;
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_GAME::PLAYER_TRANSITION_STATE, UPDATE_EVENT )

    GetContext().AnimationTimer += event.GetEventData();

    if ( GetContext().AnimationTimer >= 2.0f){
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PLAYER_TURN_STATE);
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_GAME::PLAYER_TRANSITION_STATE )
    GetContext().SelectNextPlayer();
CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_GAME::END_GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_GAME::END_GAME_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_GAME::END_GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()



GAMEPLAY_GAME::GAMEPLAY_GAME() :
    Board(),
    PlayerTable(),
    ActivePlayerIndex( 0 ),
    AnimationTimer( 0.0f ),
    StateMachine(),
    Scene() {
    
}

GAMEPLAY_GAME::~GAMEPLAY_GAME() {
    
}

void GAMEPLAY_GAME::Initialize( std::vector<GAME_PLAYER_MODEL> & player_model_table ) {
    
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    
    Scene.InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    Board.Initialize( &Scene );
    
    CORE_FIXED_STATE_InitializeState( StateMachine, GAMEPLAY_GAME::GAME_STARTING, this );
    
    PlayerTable.resize( player_model_table.size() );
    
    std::vector<GAMEPLAY_PLAYER *>::iterator it = PlayerTable.begin();
    std::vector<GAME_PLAYER_MODEL>::iterator names_it = player_model_table.begin();
    
    while (it != PlayerTable.end() ) {
        *it = new GAMEPLAY_PLAYER((*names_it).Name);
        (*it)->Initialize( (*names_it).Color, (GAMEPLAY_COMPONENT_POSITION*) Board.GetCell(0)->GetComponent(GAMEPLAY_COMPONENT_TYPE_Position), &Scene, APPLICATION_PLAYER_BASE_MONEY );
        
        it++;
        names_it++;
    }
}

void GAMEPLAY_GAME::Update(const float step) {
    
    std::vector<GAMEPLAY_PLAYER *>::iterator it = PlayerTable.begin();
    
    while (it != PlayerTable.end() ) {
        
        (*it)->Update( step );
        it++;
    }
    
    StateMachine.DispatchEvent( UPDATE_EVENT( step ) );
    
    Scene.Update( step );
}

void GAMEPLAY_GAME::Render() {
    
    Scene.Render();
}

void GAMEPLAY_GAME::SelectNextPlayer() {
    
    assert( PlayerTable.size() > 0 );
    
    ActivePlayerIndex++;
    
    if( ActivePlayerIndex >= PlayerTable.size() ) {
        ActivePlayerIndex = 0;
    }
}
