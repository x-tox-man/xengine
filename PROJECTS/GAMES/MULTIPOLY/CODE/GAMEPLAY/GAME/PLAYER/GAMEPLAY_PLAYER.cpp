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

CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::IDLE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::IDLE_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::IDLE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::LAUNCH_DICE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::LAUNCH_DICE_STATE, UPDATE_EVENT )

    GetContext().DiceRollTime -= event.GetEventData();

    if ( GetContext().DiceRollTime <= 0.0f ) {
        
        GetContext().DiceIsRolling = false;
        GetContext().DiceRollResult = GetContext().GetRollResult();
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
    }

    if ( GetContext().CellAdvance == GetContext().DiceRollResult ) {
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().ACTION_CHOICE_STATE);
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




CORE_FIXED_STATE_DefineStateEnterEvent( GAMEPLAY_PLAYER::ACTION_CHOICE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( GAMEPLAY_PLAYER::ACTION_CHOICE_STATE, UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().IDLE_STATE);
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( GAMEPLAY_PLAYER::ACTION_CHOICE_STATE )
    GetContext().ItIsDone = true;
CORE_FIXED_STATE_EndOfStateEvent()



GAMEPLAY_PLAYER::GAMEPLAY_PLAYER(std::string & name) :
    GAMEPLAY_COMPONENT_ENTITY(),
    Name( name ),
    Money( -1 ),
    DiceRollResult( -1 ),
    CellAdvance( 0 ),
    CurrentCellIndex( 0 ),
    ItIsDone( true ),
    HasLost( false ),
    DiceIsRolling( false ),
    TurnTime( 0.0f ),
    DiceRollTime( 0.0f ),
    PlayerMoveAnimationTime( 0.0f ){
    
}

GAMEPLAY_PLAYER::~GAMEPLAY_PLAYER() {
    
}

void GAMEPLAY_PLAYER::Initialize( CORE_HELPERS_COLOR & player_color, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_SCENE * scene, int money_amount ) {

    Money = money_amount;
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
    
    if ( !HasLost && !ItIsDone ) {
        
        TurnTime += step;
        
        StateMachine.DispatchEvent(UPDATE_EVENT(step) );
    }
}

void GAMEPLAY_PLAYER::SetupTurn() {
    
    if (!HasLost ) {
        
        ItIsDone = false;
        TurnTime = 0.0f;
        CellAdvance = 0;
        StateMachine.ChangeState(LAUNCH_DICE_STATESTATE);
    }
}

void GAMEPLAY_PLAYER::RollDice() {
    
}

int GAMEPLAY_PLAYER::GetRollResult() {
    
    return (rand() % 6)+1;
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
    pos->GetOrientation().X(1.0f);
    pos->GetOrientation().Y(0.0f);
    pos->GetOrientation().Z(0.0f);
    
    return this;
}
