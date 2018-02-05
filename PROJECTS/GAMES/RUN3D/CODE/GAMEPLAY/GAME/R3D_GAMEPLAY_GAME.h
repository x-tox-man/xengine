//
//  R3D_GAMEPLAY_GAME.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GAMEPLAY_GAME_hpp
#define R3D_GAMEPLAY_GAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_LEVEL.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_FIXED_STATE_EVENT.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "PHYSICS_COLLISION_NEAR_FILTER.h"
#include "GAME_PLAYER_MODEL.h"
#include "R3D_GAMEPLAY_GAME_DELEGATE.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "R3D_LEVEL_MANAGER.h"

XS_CLASS_BEGIN( R3D_GAMEPLAY_GAME )

    R3D_GAMEPLAY_GAME();
    ~R3D_GAMEPLAY_GAME();

    void Render( GRAPHIC_RENDERER & renderer );
    void Update( const float step );

    void OnPlayerCompleted( GAMEPLAY_COMPONENT_ENTITY * entity );

    void InternalUpdateGame( const float step) {
        
        float thrust = 0.0f;
        float orientation = 0.0f;
        
        if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_ARROW_UP ) ) {
            
            thrust = 1.0f;
        }
        else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_ARROW_DOWN ) ) {
            
            thrust = -1.0f;
        }
        
        if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_ARROW_LEFT ) ) {
            
            orientation = 1.0f;
        }
        else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_ARROW_RIGHT ) ) {
            
            orientation = -1.0f;
        }
        
#if PLATFORM_IOS || PLATFORM_ANDROID
        
        Delegate->SetThrust( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetTouch().GetY() );
        //Delegate->SetOrientation( orientation );
#else
        Delegate->SetThrust( thrust );
        Delegate->SetOrientation( orientation );
#endif
        
        Delegate->InternalUpdateGame( step );
    }

    void SetPlayers( const std::vector< GAME_PLAYER_MODEL > & players );

    void Initialize();
    void Finalize();
    void Restart();
    void SelectLevel( R3D_GAME_LEVEL_INFO::PTR info );

    inline int GetTick() const { return Tick; }
    inline R3D_LEVEL::PTR GetLevel() { return LevelManager.GetCurrentLevel(); }
    inline GAMEPLAY_SCENE & GetScene() { return Scene; }
    inline GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * GetBulletSystem() { return BulletSystem; }
    inline R3D_GAMEPLAY_GAME_DELEGATE * GetDelegate() { return Delegate; }
    inline void SetDelegate( R3D_GAMEPLAY_GAME_DELEGATE * delegate ) { Delegate = delegate; }
    inline void SetThisPlayerIndex( const CORE_HELPERS_UNIQUE_IDENTIFIER & index ) { ThisPlayerIndex = index; }
    inline R3D_LEVEL_MANAGER & GetLevelManager() { return LevelManager; }
    inline CORE_HELPERS_UNIQUE_IDENTIFIER & GetThisPlayerIndex() { return ThisPlayerIndex; }

    inline float GetGameDuration() const { return Tick * 0.033f; }

    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, const float )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( PAUSE_EVENT )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState(GAME_BASE_STATE, R3D_GAMEPLAY_GAME )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, IDLE_STATE )

    CORE_FIXED_STATE_MACHINE_EndDefineState( IDLE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STARTING )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STARTING )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( PAUSE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, PAUSE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PAUSE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, END_GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( END_GAME_STATE )

protected:

    CORE_FIXED_STATE_MACHINE<GAME_BASE_STATE, R3D_GAMEPLAY_GAME>
        StateMachine;
    R3D_LEVEL_MANAGER
        LevelManager;
    GAMEPLAY_SCENE
        Scene;
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION
        * BulletSystem;
    int
        Tick;
    CORE_HELPERS_UNIQUE_IDENTIFIER
        ThisPlayerIndex;
    float
        TimeMod;
    R3D_GAMEPLAY_GAME_DELEGATE::PTR
        Delegate;

XS_CLASS_END

#endif /* R3D_GAMEPLAY_GAME_hpp */
