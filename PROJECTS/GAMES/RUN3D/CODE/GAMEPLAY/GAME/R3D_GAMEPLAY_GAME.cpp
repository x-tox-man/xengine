//
//  R3D_GAMEPLAY_GAME.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GAMEPLAY_GAME.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "PHYSICS_COLLISION_FILTER.h"
#include "R3D_RESOURCES.h"

R3D_GAMEPLAY_GAME::R3D_GAMEPLAY_GAME() :
    StateMachine(),
    Level(),
    Scene(),
    BulletSystem( new GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION() ) {
    
}

R3D_GAMEPLAY_GAME::~R3D_GAMEPLAY_GAME() {
    
}

void R3D_GAMEPLAY_GAME::Initialize() {
    
    BulletSystem->SetGravity( -2.81f );
    BulletSystem->Initialize();
    
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    Scene.InsertUpdatableSystem( BulletSystem );
    
    BulletSystem->SetCollisionFilter( new PHYSICS_COLLISION_FILTER() );
    
    Scene.InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    ((GAMEPLAY_COMPONENT_SYSTEM_RENDERER::PTR) Scene.GetRenderableSystemTable()[0])->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    Level.Initialize();
    
    CORE_FIXED_STATE_InitializeState( StateMachine, R3D_GAMEPLAY_GAME::GAME_STARTING, this );
}

void R3D_GAMEPLAY_GAME::Finalize() {
    
    Level.Finalize();
}

void R3D_GAMEPLAY_GAME::Render( GRAPHIC_RENDERER & renderer ) {
    
    Scene.Render( renderer );
}

void R3D_GAMEPLAY_GAME::Update( const float step ) {
    
    static float TimeMod = 0.0f;
    
    TimeMod += step;
    StateMachine.DispatchEvent( UPDATE_EVENT( step ) );
    
    auto proxy = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ) );
    GRAPHIC_SHADER_ATTRIBUTE & time_mod = proxy->GetResource< GRAPHIC_SHADER_EFFECT >()->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::TimeModulator );
    
    time_mod.AttributeValue.Value.FloatValue = sinf( TimeMod ) * 0.1f;
    
    Level.GetPlayerTable()[0]->GetShip()->Update( step );
}

//---------------------------------------------------------------------------------------//
//-------------------------- GAME STARTING ----------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::GAME_STARTING )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::GAME_STARTING, UPDATE_EVENT )
    static float t = 0.0f;

    if ( t > 1.0f ) {
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().GAME_STATE )
        
        t = 0.0f;
    }

    t += event.GetEventData();

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::GAME_STARTING )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//-------------------------- GAME STATE    ----------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::GAME_STATE, UPDATE_EVENT )

    GetContext().Scene.Update( event.GetEventData() );

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//-------------------------- PAUSE STATE    ---------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::PAUSE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::PAUSE_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::PAUSE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//-------------------------- END GAME STATE    ------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::END_GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::END_GAME_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::END_GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//

