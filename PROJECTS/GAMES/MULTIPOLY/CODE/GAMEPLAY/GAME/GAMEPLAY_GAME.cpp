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
#include "GLOBAL_RESOURCES.h"
#include "GAMEPLAY_RULE_PROPERTY.h"
#include "GAMEPLAY_RULE_PAY_AMOUNT.h"
#include "GAMEPLAY_RULE_RECEIVE_AMOUNT.h"
#include "GAMEPLAY_RULE_PAY_HOTEL_HOUSES.h"
#include "GAMEPLAY_RULE_ADVANCE_TO.h"
#include "GAMEPLAY_RULE_PRISON.h"
#include "CORE_PARALLEL.h"
#include "CORE_PARALLEL_TASK.h"

CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_GAME::GAME_STARTING )
    GetContext().AnimationTimer = 0.0f;
    GetContext().IsRunning = true;
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_GAME::GAME_STARTING, UPDATE_EVENT )

    GetContext().AnimationTimer += event.GetEventData();

    std::vector< GAMEPLAY_GAME_CARD * >::iterator it = GetContext().ChanceCardTable.begin();
    std::vector< GAMEPLAY_GAME_CARD * >::iterator it2 = GetContext().CaisseCardTable.begin();
    int index = 0;

    while(it != GetContext().ChanceCardTable.end() ) {
        
        auto comp = ( ( GAMEPLAY_COMPONENT_POSITION *) (*it)->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
        auto comp2 = ( ( GAMEPLAY_COMPONENT_POSITION *) (*it2)->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
        CORE_MATH_VECTOR
            start(comp->GetPosition().X(), comp->GetPosition().Y(), -100.0f- (index * 3.2f), 1.0f ),
            end(comp->GetPosition().X(), comp->GetPosition().Y(), (index * 0.02f), 1.0f ),
            start2(comp2->GetPosition().X(), comp2->GetPosition().Y(), -100.0f - (index * 3.2f), 1.0f ),
            end2(comp2->GetPosition().X(), comp2->GetPosition().Y(), (index * 0.02f), 1.0f );
        
        float percentage = 0.0f;
        
        if ( GetContext().AnimationTimer >= 3.2f ) {
            
            percentage = 1.0f;
        }
        else {
            
            percentage = fmaxf(0.0f, fminf(1.0f, (GetContext().AnimationTimer - index * 0.1f)));
        }
        
        
        comp->SetPosition(start * (1.0f - percentage) + end * percentage);
        comp2->SetPosition(start2 * (1.0f - percentage) + end2 * percentage);
        
        it++;
        it2++;
        index++;
    }

    if ( GetContext().AnimationTimer >= 3.2f ) {
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PLAYER_TURN_STATE);
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_GAME::GAME_STARTING )
    GetContext().SelectNextPlayer();
CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_GAME::PLAYER_TURN_STATE )

    GetContext().SelectCell( NULL );
    GetContext().PlayerTable[GetContext().ActivePlayerIndex]->SetupTurn( GetContext().UIGameHudPresenter );

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

    auto player = GetContext().GetCurrentPlayer();

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
    ActivePlayerIndex( -1 ),
    NextHouseIndex( 0 ),
    AnimationTimer( 0.0f ),
    IsRunning( false ),
    StateMachine(),
    Scene(),
    UIGameHudPresenter( NULL ),
    ChanceCardTable(),
    CaisseCardTable(),
    Background( NULL ),
    HouseTable(),
    SelectedCell( NULL ) {
    
}

GAMEPLAY_GAME::~GAMEPLAY_GAME() {
    
}

void GAMEPLAY_GAME::Initialize() {
    
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    
    auto picking_system = new GAMEPLAY_COMPONENT_SYSTEM_PICKING;
    Scene.InsertUpdatableSystem( picking_system );
    
    auto * callback = new CORE_HELPERS_CALLBACK_1<GAMEPLAY_COMPONENT_ENTITY *>( &Wrapper1<GAMEPLAY_GAME, GAMEPLAY_COMPONENT_ENTITY *, &GAMEPLAY_GAME::OnObjectPicked >, this );
    
    picking_system->SetOnPickedCallback( callback );
    
    Scene.InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )

    Board.Initialize( &Scene );
    
    Background = new GRAPHIC_BACKGROUND;
    Background->Initialize( &Scene );
    
    InitializeHouses();
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void GAMEPLAY_GAME::Finalize() {
    
    StateMachine.FinalizeState();
    
    std::vector<GAMEPLAY_PLAYER *>::iterator it_p = PlayerTable.begin();
    
    while (it_p != PlayerTable.end()) {
        delete *it_p;
        it_p++;
    }
    
    PlayerTable.resize(0);
    UIGameHudPresenter = NULL;
    
    std::vector< GAMEPLAY_GAME_CARD * >::iterator
        it_chance = ChanceCardTable.begin(),
        it_caisse = CaisseCardTable.begin();
    
    while (it_chance != ChanceCardTable.end()) {
        
        delete *it_chance;
        it_chance++;
    }
    
    ChanceCardTable.resize( 0 );
    
    while (it_caisse != CaisseCardTable.end()) {
        
        delete *it_caisse;
        it_caisse++;
    }
    
    CaisseCardTable.resize( 0 );
    
    CORE_MEMORY_ObjectSafeDeallocation(Background);
    
}

void GAMEPLAY_GAME::Start() {
 
    InitializeCaisseCards();
    InitializeChanceCards();
    
    CORE_FIXED_STATE_InitializeState( StateMachine, GAMEPLAY_GAME::GAME_STARTING, this );
}

void GAMEPLAY_GAME::Pause( bool enable ) {
    
    IsRunning = !enable;
}

void GAMEPLAY_GAME::Update(const float step) {
    
    if( PlayerTable.size() == 0 || !IsRunning )
        return;
    
    std::vector<GAMEPLAY_PLAYER *>::iterator it = PlayerTable.begin();
    
    while (it != PlayerTable.end() ) {
        
        (*it)->Update( step );
        it++;
    }
    
    std::vector< GAMEPLAY_GAME_HOUSE * >::iterator it_house = HouseTable.begin();
    
    while (it_house != HouseTable.end() ) {
        
        (*it_house)->Update(step );
        it_house++;
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

void GAMEPLAY_GAME::PlayerDiceRoll() {
    
    if ( PlayerTable[ActivePlayerIndex]->IsHuman() ) {
        
        PlayerTable[ActivePlayerIndex]->RollDice();
    }
    else {
        abort(); //cannot be here
    }
}

void GAMEPLAY_GAME::PlayerBuyProperty() {
    
    auto rule = ( GAMEPLAY_RULE_PROPERTY *) Board.GetCell( PlayerTable[ActivePlayerIndex]->GetCurrentCellIndex() )->GetRule();
    rule->Buy( Board.GetCell( PlayerTable[ActivePlayerIndex]->GetCurrentCellIndex() ), PlayerTable[ActivePlayerIndex] );
}

void GAMEPLAY_GAME::PlayerEndTurn() {
    
    PlayerTable[ActivePlayerIndex]->SetTurnIsOver();
}

void GAMEPLAY_GAME::PlayerBuyHouse() {
    
    if( SelectedCell ) {
        
        auto property = ( GAMEPLAY_RULE_PROPERTY *) SelectedCell->GetRule();
        property->BuyHouse(&Scene, SelectedCell, PlayerTable[ActivePlayerIndex], GetNextHouse() );
    }
    else {
        
        auto property = ( GAMEPLAY_RULE_PROPERTY *) Board.GetCell( PlayerTable[ActivePlayerIndex]->GetCurrentCellIndex() )->GetRule();
        property->BuyHouse(&Scene, Board.GetCell( PlayerTable[ActivePlayerIndex]->GetCurrentCellIndex()), PlayerTable[ActivePlayerIndex], GetNextHouse() );
    }
}

void GAMEPLAY_GAME::OnObjectPicked( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    ((GAMEPLAY_COMPONENT_RENDER*)entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render))->SetColor( CORE_COLOR_Cyan );
}

void GAMEPLAY_GAME::DisplayNextChanceCard(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player) {
    
    player->ShowActiveGameplayCard(ChanceCardTable[0]);
    
    auto temp = ChanceCardTable[0];
    
    for (int i = 0; i < 15; i++) {
        
        ChanceCardTable[i] = ChanceCardTable[i+1];
    }
    
    ChanceCardTable[15] = temp;
}

void GAMEPLAY_GAME::DisplayNextCommunityCaisseCard(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player) {
    
    player->ShowActiveGameplayCard(CaisseCardTable[0]);
    
    auto temp = CaisseCardTable[0];
    
    for (int i = 0; i < 15; i++) {
        CaisseCardTable[i] = CaisseCardTable[i+1];
    }
    
    CaisseCardTable[15] = temp;
}

void GAMEPLAY_GAME::ProposeBuyProperty( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    UIGameHudPresenter->ProposeBuyProperty( cell, player );
}

void GAMEPLAY_GAME::ProposeBuyHouse( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    UIGameHudPresenter->ProposeBuyHouse( cell, player );
}

void GAMEPLAY_GAME::SelectCell( GAMEPLAY_GAME_BOARD_CELL * cell ) {
    
    if ( SelectedCell ) {
        
        SelectedCell->SetSelected( false );
    }
    
    SelectedCell = cell;
    
    if ( SelectedCell ) {
        
        SelectedCell->SetSelected( true );
    }
}

void GAMEPLAY_GAME::SetPlayers( std::vector< GAME_PLAYER_MODEL > & players ) {
    
    PlayerTable.resize( players.size() );
    
    std::vector<GAMEPLAY_PLAYER *>::iterator it = PlayerTable.begin();
    std::vector<GAME_PLAYER_MODEL>::iterator names_it = players.begin();
    
    int index = 0;
    while (it != PlayerTable.end() ) {
        *it = new GAMEPLAY_PLAYER((*names_it).Name);
        (*it)->Initialize( (*names_it).Color, (GAMEPLAY_COMPONENT_POSITION*) Board.GetCell(0)->GetComponent(GAMEPLAY_COMPONENT_TYPE_Position), &Scene, (*names_it).IsHuman, (*names_it).IsMultiplayer,APPLICATION_PLAYER_BASE_MONEY, index++ );
        
        it++;
        names_it++;
    }
}

void GAMEPLAY_GAME::DisplayDiceRollResult( const GAMEPLAY_DICE_ROLL_RESULT & result ) {
    
    UIGameHudPresenter->DisplayRollDiceResult( result );
}

void GAMEPLAY_GAME::InitializeCaisseCards() {
    
    CORE_MATH_VECTOR
        start_position(7.5f, 7.5f, -100.0f, 1.0f),
        size( 0.75f, 1.5f);
    CORE_MATH_QUATERNION
        start_orientation(0.0f, 0.0f, M_PI_4, 0.0f );
    auto texture = GLOBAL_RESOURCES::CreateTextureBlockFromImagePath( "monopoly-chance-card" );
    
    std::vector<int> index_table;
    std::array<int, 16> random_table;
    
    index_table.resize(16);
    
    for( int j = 0; j < 16; j++ ) {
        
        index_table[j] = j;
    }
    
    for( int j = 0; j < 16; j++ ) {
        
        int rnd = rand() % index_table.size();
        
        random_table[ j ] = index_table[rnd];
        index_table.erase(index_table.begin() + rnd);
    }
    
    std::array<GAMEPLAY_RULE *, 16> RulesTable;
    
    RulesTable[random_table[0]] = new GAMEPLAY_RULE_PAY_AMOUNT( 100 );
    RulesTable[random_table[1]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 50 );
    RulesTable[random_table[2]] = new GAMEPLAY_RULE_PAY_HOTEL_HOUSES( 40, 115 );
    RulesTable[random_table[3]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 200 );
    RulesTable[random_table[4]] = new GAMEPLAY_RULE_PAY_AMOUNT( 150 );
    RulesTable[random_table[5]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_LAST_CELL );
    RulesTable[random_table[6]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 50 );
    RulesTable[random_table[7]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_1 );
    RulesTable[random_table[8]] = new GAMEPLAY_RULE_PAY_HOTEL_HOUSES( 25, 100 );
    
    RulesTable[random_table[9]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_2 );
    RulesTable[random_table[10]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_3 );
    
    RulesTable[random_table[11]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 150 );
    RulesTable[random_table[12]] = new GAMEPLAY_RULE_PRISON( true );
    RulesTable[random_table[13]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_1 );
    RulesTable[random_table[14]] = new GAMEPLAY_RULE_PAY_AMOUNT( 200 );
    RulesTable[random_table[15]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 100 );
    
    ChanceCardTable.resize(16);
    
    for (int i = 0; i < 16; i++) {
        
        ChanceCardTable[i] = new GAMEPLAY_GAME_CARD();
        ChanceCardTable[i]->Initialize(start_position, size, start_orientation, &Scene, texture );
        ChanceCardTable[i]->SetRule( RulesTable[i] );
        
        start_position.Z( start_position.Z() - 2.0f );
    }
}

void GAMEPLAY_GAME::InitializeChanceCards() {
    
    CORE_MATH_VECTOR
        start_position(2.5f, 2.5f, -100.0f, 1.0f),
        size( 0.75f, 1.5f);
    CORE_MATH_QUATERNION
        start_orientation(0.0f, 0.0f, -M_PI_4, 0.0f );
    
    auto texture = GLOBAL_RESOURCES::CreateTextureBlockFromImagePath( "monopoly-chance-card" );
    
    std::vector<int> index_table;
    std::array<int, 16> random_table;
    
    index_table.resize(16);
    
    for( int j = 0; j < 16; j++ ) {
        index_table[j] = j;
    }
    
    for( int j = 0; j < 16; j++ ) {
        int rnd = rand() % index_table.size();
        
        random_table[ j ] = index_table[rnd];
        index_table.erase(index_table.begin() + rnd);
    }
    
    std::array<GAMEPLAY_RULE *, 16> RulesTable;
    
    RulesTable[random_table[0]] = new GAMEPLAY_RULE_PAY_AMOUNT( 100 );
    RulesTable[random_table[1]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 50 );
    RulesTable[random_table[2]] = new GAMEPLAY_RULE_PAY_HOTEL_HOUSES( 40, 115 );
    RulesTable[random_table[3]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 200 );
    RulesTable[random_table[4]] = new GAMEPLAY_RULE_PAY_AMOUNT( 150 );
    RulesTable[random_table[5]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_LAST_CELL );
    RulesTable[random_table[6]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 50 );
    RulesTable[random_table[7]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_1 );
    RulesTable[random_table[8]] = new GAMEPLAY_RULE_PAY_HOTEL_HOUSES( 25, 100 );
    
    RulesTable[random_table[9]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_2 );
    RulesTable[random_table[10]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_3 );
    
    RulesTable[random_table[11]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 150 );
    RulesTable[random_table[12]] = new GAMEPLAY_RULE_PRISON( true );
    RulesTable[random_table[13]] = new GAMEPLAY_RULE_ADVANCE_TO( APPLICATION_SPECIAL_ADVANCE_1 );
    RulesTable[random_table[14]] = new GAMEPLAY_RULE_PAY_AMOUNT( 20 );
    RulesTable[random_table[15]] = new GAMEPLAY_RULE_RECEIVE_AMOUNT( 100 );
    
    CaisseCardTable.resize(16);
    
    for (int i = 0; i < 16; i++) {
        
        CaisseCardTable[i] = new GAMEPLAY_GAME_CARD();
        CaisseCardTable[i]->Initialize(start_position, size, start_orientation, &Scene, texture );
        CaisseCardTable[i]->SetRule( RulesTable[i] );
        
        start_position.Z( start_position.Z() - 2.0f );
    }
}

void GAMEPLAY_GAME::InitializeHouses() {
    
    HouseTable.resize( 23* 5 );
    CORE_MATH_VECTOR
    house_position( 1.5f, 3.5f, 0.0f, 1.0f );
    int index = 0;
    
    std::vector< GAMEPLAY_GAME_HOUSE * >::iterator it = HouseTable.begin();
    
    while (it != HouseTable.end() ) {
        
        house_position.X(house_position.X()+0.2f);
        
        (*it) = new GAMEPLAY_GAME_HOUSE;
        (*it)->Initialize(house_position, CORE_MATH_VECTOR::One, CORE_MATH_QUATERNION(), &Scene, CORE_COLOR_White );
        //(*it)->SetupAnimation(CORE_MATH_VECTOR(house_position.X(), house_position.Y() ), CORE_MATH_QUATERNION() );
        
        if ( index % 7 == 0) {
            
            house_position.X( 1.5f );
            house_position.Y( house_position.Y() + 0.2f );
        }
        
        it++;
        index++;
    }
}
