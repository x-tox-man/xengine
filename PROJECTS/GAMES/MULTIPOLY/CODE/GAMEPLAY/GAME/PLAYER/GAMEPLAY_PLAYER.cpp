//
//  GAMEPLAY_PLAYER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GLOBAL_RESOURCES.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_GAME_BOARD.h"
#include "MULTIPOLY_APPLICATION.h"
#include "CORE_MATH.h"
#include "GAMEPLAY_GAME_CARD.h"
#include "GAMEPLAY_RULE_PRISON.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "GAMEPLAY_ACTION_ROLL_DICE.h"
#include "GAMEPLAY_ACTION_BUY_HOUSE.h"
#include "GAMEPLAY_ACTION_BUY_PROPERTY.h"
#include "GAMEPLAY_ACTION_END_TURN.h"

CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::IDLE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::IDLE_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::IDLE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE, UPDATE_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE, MULTIPLAYER_ROLL_DICE )
        GetContext().SetRollDiceResult(event.GetEventData());
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PLAYER_MOVE_STATE);
    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE, MULTIPLAYER_BUY_HOUSE )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE, MULTIPLAYER_BUY_PROPERTY )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE, MULTIPLAYER_END_TURN )
        GetContext().SetTurnIsOver();
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().IDLE_STATE);

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE, MULTIPLAYER_APPLY_RULE )

    CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::MULTIPLAYER_STATE )

CORE_FIXED_STATE_EndOfStateEvent()





CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::LAUNCH_DICE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::LAUNCH_DICE_STATE, UPDATE_EVENT )

    GetContext().DiceRollTime -= event.GetEventData();

    if ( GetContext().DiceRollTime <= 0.0f ) {
        
        GetContext().DiceIsRolling = false;
        GetContext().DiceRollResult = GetContext().ComputeRollResult();
        
        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto cell = board->GetCell(GetContext().CurrentCellIndex);
        
        cell->GetRule()->OnLeftCell( cell, &GetContext() );
        
        ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGame().DisplayDiceRollResult( GetContext().DiceRollResult );
        
        GAMEPLAY_ACTION_ROLL_DICE
            action(GetContext().DiceRollResult);
        
        auto command = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand< GAMEPLAY_ACTION_ROLL_DICE >( action );
        ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetNetworkManager().SendCommand( command );
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PLAYER_MOVE_STATE);
    }

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::LAUNCH_DICE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::PLAYER_MOVE_STATE )
    GetContext().PlayerMoveAnimationTime = 0.0f;
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::PLAYER_MOVE_STATE, UPDATE_EVENT )

    GetContext().PlayerMoveAnimationTime += event.GetEventData();

    if ( GetContext().PlayerMoveAnimationTime > 0.75f) {
        
        GetContext().PlayerMoveAnimationTime = 0.0f;
        GetContext().CellAdvance++;
        GetContext().CurrentCellIndex = (GetContext().CurrentCellIndex+1) % 40;
        
        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto cell = board->GetCell(GetContext().CurrentCellIndex);
        
        cell->GetRule()->OnPassOntoCell( cell, &GetContext() );
    }

    if ( GetContext().CellAdvance == GetContext().DiceRollResult.Total ) {
        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto cell = board->GetCell(GetContext().CurrentCellIndex);
        
        cell->GetRule()->OnStoppedCell( cell, &GetContext() );
        
        if( &GetContext().StateMachine.GetState() != &GetContext().PLAYER_SPECIAL_MOVE_STATESTATE &&
            &GetContext().StateMachine.GetState() != &GetContext().PLAYER_DISPLAY_CARD_STATESTATE ) {
            
            CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().ACTION_CHOICE_STATE );
        }
    }
    else {

        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto pos = (GAMEPLAY_COMPONENT_POSITION *) GetContext().GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        auto cell_pos = (GAMEPLAY_COMPONENT_POSITION *)  board->GetCell(GetContext().CurrentCellIndex)->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        auto next_cell_pos = (GAMEPLAY_COMPONENT_POSITION *)  board->GetCell( (GetContext().CurrentCellIndex + 1) % 40 )->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        float
            percentage = GetContext().PlayerMoveAnimationTime / 0.75f;
        
        CORE_MATH_VECTOR lerp_pos = CORE_MATH_GetLerpInterpolation<CORE_MATH_VECTOR>(cell_pos->GetPosition(), next_cell_pos->GetPosition(), percentage );
        
        lerp_pos.Z(cell_pos->GetPosition().Z() - 2.0f * sinf( percentage*M_PI ));
        
        pos->SetPosition( lerp_pos );
    }

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::PLAYER_MOVE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::PLAYER_FORCED_ADVANCE_MOVE_STATE )
    GetContext().PlayerMoveAnimationTime = 0.0f;
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::PLAYER_FORCED_ADVANCE_MOVE_STATE, UPDATE_EVENT )

    GetContext().PlayerMoveAnimationTime += event.GetEventData();

    if ( GetContext().PlayerMoveAnimationTime > 0.75f) {
        
        GetContext().PlayerMoveAnimationTime = 0.0f;
        GetContext().CellAdvance++;
        GetContext().CellAdvance = (GetContext().CellAdvance++) % 40;
        GetContext().CurrentCellIndex = (GetContext().CurrentCellIndex+1) % 40;
        
        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto cell = board->GetCell(GetContext().CurrentCellIndex);
        
        cell->GetRule()->OnPassOntoCell( cell, &GetContext() );
    }

    if ( GetContext().CellAdvance == GetContext().SpecialDestination ) {
        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto cell = board->GetCell(GetContext().CurrentCellIndex);
        
        cell->GetRule()->OnStoppedCell( cell, &GetContext() );
        
        if( &GetContext().StateMachine.GetState() != &GetContext().PLAYER_SPECIAL_MOVE_STATESTATE &&
           &GetContext().StateMachine.GetState() != &GetContext().PLAYER_DISPLAY_CARD_STATESTATE ) {
            
            CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().ACTION_CHOICE_STATE );
        }
    }
    else {
        
        auto board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto pos = (GAMEPLAY_COMPONENT_POSITION *) GetContext().GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        auto cell_pos = (GAMEPLAY_COMPONENT_POSITION *)  board->GetCell(GetContext().CurrentCellIndex)->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        auto next_cell_pos = (GAMEPLAY_COMPONENT_POSITION *)  board->GetCell( (GetContext().CurrentCellIndex + 1) % 40 )->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        float
        percentage = GetContext().PlayerMoveAnimationTime / 0.75f;
        
        CORE_MATH_VECTOR lerp_pos = CORE_MATH_GetLerpInterpolation<CORE_MATH_VECTOR>(cell_pos->GetPosition(), next_cell_pos->GetPosition(), percentage );
        
        lerp_pos.Z(cell_pos->GetPosition().Z() - 2.0f * sinf( percentage*M_PI ));
        
        pos->SetPosition( lerp_pos );
    }

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::PLAYER_FORCED_ADVANCE_MOVE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::PLAYER_SPECIAL_MOVE_STATE )
    GetContext().PlayerMoveAnimationTime = 0.0f;
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::PLAYER_SPECIAL_MOVE_STATE, UPDATE_EVENT )

    GetContext().PlayerMoveAnimationTime += event.GetEventData();

    if ( GetContext().PlayerMoveAnimationTime > 1.75f) {
        
        GetContext().PlayerMoveAnimationTime = 0.0f;
        
        GetContext().CurrentCellIndex = GetContext().SpecialDestination;
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().ACTION_CHOICE_STATE);
    }
    else {
        
        auto
            board = &((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGameBoard();
        auto
            pos = (GAMEPLAY_COMPONENT_POSITION *) GetContext().GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        auto cell_pos = (GAMEPLAY_COMPONENT_POSITION *)  board->GetCell(GetContext().CurrentCellIndex)->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        auto next_cell_pos = (GAMEPLAY_COMPONENT_POSITION *)  board->GetCell( GetContext().SpecialDestination )->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        float
            percentage = GetContext().PlayerMoveAnimationTime / 1.75f;
        
        CORE_MATH_VECTOR lerp_pos = CORE_MATH_GetLerpInterpolation<CORE_MATH_VECTOR>(cell_pos->GetPosition(), next_cell_pos->GetPosition(), percentage );
        
        lerp_pos.Z(cell_pos->GetPosition().Z() - 2.0f * sinf( percentage * M_PI ));
        
        pos->SetPosition( lerp_pos );
    }

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::PLAYER_SPECIAL_MOVE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::ACTION_CHOICE_STATE )

    if ( GetContext().ItIsMultiplayer ) {
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().MULTIPLAYER_STATE);
    }
    else if ( GetContext().IsHuman() && !GetContext().GetRollResult().IsDouble ) {
        
        ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGame().GetUIGameHudPresenter()->ShowEndButton();
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::ACTION_CHOICE_STATE, UPDATE_EVENT )

    if ( GetContext().IsDone() ) {
        GAMEPLAY_ACTION_END_TURN
            action;
        
        auto command = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand< GAMEPLAY_ACTION_END_TURN >( action );
        ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetNetworkManager().SendCommand( command );
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().IDLE_STATE);
    }

    if ( !GetContext().ItIsMultiplayer && GetContext().GetRollResult().IsDouble && GetContext().GetRollResult().DoublesInRowCount < 3 ) {
        
        GetContext().PrepareForRollingDice( ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGame().GetUIGameHudPresenter() );
    }
    else if ( GetContext().GetRollResult().IsDouble && GetContext().GetRollResult().DoublesInRowCount == 3 ) {
        
        GAMEPLAY_RULE_PRISON prison_rule( true );
        
        prison_rule.Apply( NULL, &GetContext() );
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().IDLE_STATE);
        GetContext().ItIsDone = true;
    }
    else {
        
        if ( !GetContext().IsHuman()) {
            
            GetContext().PerformIAActions();
            GetContext().ItIsDone = true;
        }
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::ACTION_CHOICE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::PLAYER_DISPLAY_CARD_STATE )
    GetContext().PlayerMoveAnimationTime += 0.0f;

    GetContext().ActiveCard->SetupAnimation();
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::PLAYER_DISPLAY_CARD_STATE, UPDATE_EVENT )

    if ( GetContext().ActiveCard->Update( event.GetEventData(), &GetContext() ) ) {
        
        //if correctly applied then we can change the current state, otherwise we let the Rule perform the correct transition
        if ( GetContext().ActiveCard->ApplyRule( &GetContext() ) ) {
            
            CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().ACTION_CHOICE_STATE);
        }
    }

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::PLAYER_DISPLAY_CARD_STATE )
    GetContext().ActiveCard->ResetPosition();
CORE_FIXED_STATE_EndOfStateEvent()



GAMEPLAY_PLAYER::GAMEPLAY_PLAYER(std::string & name) :
    GAMEPLAY_COMPONENT_ENTITY(),
    Name( name ),
    Money( -1 ),
    DiceRollResult(),
    CellAdvance( 0 ),
    CurrentCellIndex( 0 ),
    SpecialDestination( 0 ),
    PlayerIndex( 0 ),
    ItIsHuman( false ),
    ItIsMultiplayer( false ),
    ItIsDone( true ),
    HasLost( false ),
    DiceIsRolling( false ),
    TurnTime( 0.0f ),
    DiceRollTime( 0.0f ),
    PlayerMoveAnimationTime( 0.0f ),
    RollResult(),
    ActiveCard( NULL ),
    Color() {
    
}

GAMEPLAY_PLAYER::~GAMEPLAY_PLAYER() {
    
}

void GAMEPLAY_PLAYER::Initialize( CORE_HELPERS_COLOR & player_color, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_SCENE * scene, bool is_human, bool is_multiplayer, int money_amount, int index ) {

    Money = money_amount;
    ItIsHuman = is_human;
    ItIsMultiplayer = is_multiplayer;
    PlayerIndex = index;
    Color = player_color;
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(
        CORE_HELPERS_UNIQUE_IDENTIFIER("PlayerShader"),
        CORE_FILESYSTEM_PATH::FindFilePath("BasicGeometryShaderPoNoUVTaBi", "vsh", "OPENGL2"));
    
    shader->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    
    GRAPHIC_OBJECT::PTR shape = GRAPHIC_OBJECT::LoadResourceForPath("mesh2", CORE_FILESYSTEM_PATH::FindFilePath("mesh2", "smx", "MODELS" ) );
    
    CreateThisComponent(
        shape,
        &shader->GetProgram(),
        component->GetPosition(),
        component->GetOrientation(),
        CORE_MATH_VECTOR(1.0f, 1.0f, 0.0f, 1.0f ),
        scene,
        player_color);
    
    CORE_FIXED_STATE_InitializeState( StateMachine, GAMEPLAY_PLAYER::IDLE_STATE, this );
}

void GAMEPLAY_PLAYER::Update(const float step ) {
    
    if ( !HasLost ) {
        
        TurnTime += step;
        
        StateMachine.DispatchEvent(UPDATE_EVENT(step) );
    }
}

void GAMEPLAY_PLAYER::SetupTurn( GAME_HUD_PRESENTER * presenter ) {
    
    if (!HasLost ) {
        
        RollResult.DoublesInRowCount = 0;
        TurnTime = 0.0f;
        
        PrepareForRollingDice( presenter );
    }
    else {
        
        ItIsDone = true;
    }
}

void GAMEPLAY_PLAYER::PrepareForRollingDice( GAME_HUD_PRESENTER * presenter ) {
    
    ItIsDone = false;
    
    CellAdvance = 0;
    
    if ( ItIsHuman && !ItIsMultiplayer ) {
        
        presenter->DisplayRollDiceButton();
    }
    else if ( ItIsMultiplayer ) {
        
        StateMachine.ChangeState( MULTIPLAYER_STATESTATE );
    }
    else {
        
        RollDice();
    }
}

void GAMEPLAY_PLAYER::RollDice() {
    
    StateMachine.ChangeState( LAUNCH_DICE_STATESTATE );
}

GAMEPLAY_DICE_ROLL_RESULT GAMEPLAY_PLAYER::ComputeRollResult() {
    
    RollResult.FirstDice = (rand() % 6)+1;
    RollResult.SecondDice = (rand() % 6)+1;
    RollResult.Total = RollResult.FirstDice + RollResult.SecondDice;
    RollResult.IsDouble = RollResult.FirstDice == RollResult.SecondDice;
    
    if ( RollResult.IsDouble ) {
        
        RollResult.DoublesInRowCount++;
    }
    
    return RollResult;
}

GAMEPLAY_COMPONENT_ENTITY * GAMEPLAY_PLAYER::CreateThisComponent(
    GRAPHIC_OBJECT::PTR object,
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_QUATERNION & orientation,
    const CORE_MATH_VECTOR & size,
    GAMEPLAY_SCENE * scene,
    CORE_HELPERS_COLOR & player_color ) {
     
     for ( int i = 0; i < object->GetMeshTable().size(); i++ ) {
     
         object->GetMeshTable()[ i ]->CreateBuffers();
     }
     
     object->GetShaderTable().resize( 1 );
     object->GetShaderTable()[ 0 ] = program;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    
    SetCompononent( pos, GAMEPLAY_COMPONENT_TYPE_Position );
    SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject(  object );
    ( ( GAMEPLAY_COMPONENT_RENDER *) GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetColor( player_color );
    ( ( GAMEPLAY_COMPONENT_RENDER *) GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetScaleFactor( 0.25f );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( this );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    pos->SetPosition( position );
    pos->SetOrientation( orientation );
    
    pos->GetOrientation().X( 1.0f );
    pos->GetOrientation().Y( 0.0f );
    pos->GetOrientation().Z( 0.0f );
    
    return this;
}

int GAMEPLAY_PLAYER::AttemptPay( int amount ) {
    
    //TODO: propose alternative to pay
    
    if ( Money >= amount ) {
        
        RemoveMoney( amount );
        
        return amount;
    }
    else if( Money > 0 ) {
        
        int remaining = Money;
        
        RemoveMoney( Money );
        
        return remaining;
    }
    
    return 0;
}

void GAMEPLAY_PLAYER::JumpTo( int cell_index ) {
    
    SpecialDestination = cell_index;
    
    StateMachine.ChangeState( PLAYER_SPECIAL_MOVE_STATESTATE );
}

void GAMEPLAY_PLAYER::ForceAdvanceTo( int cell_index ) {
    
    SpecialDestination = cell_index;
    
    StateMachine.ChangeState( PLAYER_FORCED_ADVANCE_MOVE_STATESTATE );
}

void GAMEPLAY_PLAYER::PerformIAActions() {
    
}

void GAMEPLAY_PLAYER::ShowActiveGameplayCard( GAMEPLAY_GAME_CARD * card ) {
    
    ActiveCard = card;
    
    StateMachine.ChangeState( PLAYER_DISPLAY_CARD_STATESTATE );
}
