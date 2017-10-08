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

XS_CLASS_BEGIN( R3D_GAMEPLAY_GAME )

    R3D_GAMEPLAY_GAME();
    ~R3D_GAMEPLAY_GAME();

    void Render( GRAPHIC_RENDERER & renderer );
    void Update( const float step );

    void Initialize();
    void Finalize();

    inline GAMEPLAY_SCENE & GetScene() { return Scene; }
    inline GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * GetBulletSystem() { return BulletSystem; }

    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, const float )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState(GAME_BASE_STATE, R3D_GAMEPLAY_GAME )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STARTING )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STARTING )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, PAUSE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PAUSE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, END_GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( END_GAME_STATE )

private:

    CORE_FIXED_STATE_MACHINE<GAME_BASE_STATE, R3D_GAMEPLAY_GAME>
        StateMachine;
    R3D_LEVEL
        Level;
    GAMEPLAY_SCENE
        Scene;
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION
        * BulletSystem;

XS_CLASS_END

#endif /* R3D_GAMEPLAY_GAME_hpp */
