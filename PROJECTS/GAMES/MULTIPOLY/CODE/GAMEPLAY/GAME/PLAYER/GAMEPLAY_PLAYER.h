//
//  GAMEPLAY_PLAYER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_PLAYER_hpp
#define GAMEPLAY_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_MATH_QUATERNION.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_HELPERS_COLOR.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_PLAYER, GAMEPLAY_COMPONENT_ENTITY)

    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, const float )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState(PLAYER_BASE_STATE, GAMEPLAY_PLAYER)
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, IDLE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( IDLE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, LAUNCH_DICE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( LAUNCH_DICE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, PLAYER_MOVE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_MOVE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, ACTION_CHOICE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( ACTION_CHOICE_STATE )


    GAMEPLAY_PLAYER(std::string & name);
    ~GAMEPLAY_PLAYER();

    void Initialize( CORE_HELPERS_COLOR & player_color, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_SCENE * scene, int money_amount );
    void Update(const float);

    void SetupTurn();
    void RollDice();
    int GetRollResult();

    bool IsDone() { return ItIsDone; }

private :

    GAMEPLAY_COMPONENT_ENTITY * CreateThisComponent(
        //const CORE_FILESYSTEM_PATH & path,
        GRAPHIC_OBJECT::PTR object,
        GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
        const CORE_MATH_VECTOR & position,
        const CORE_MATH_QUATERNION & orientation,
        const CORE_MATH_VECTOR & size,
        GAMEPLAY_SCENE * scene,
        CORE_HELPERS_COLOR & player_color );

    std::string
        Name;
    int
        Money,
        DiceRollResult,
        CellAdvance,
        CurrentCellIndex;
    float
        TurnTime,
        DiceRollTime,
        PlayerMoveAnimationTime;
    bool
        ItIsDone,
        HasLost,
        DiceIsRolling;
    CORE_FIXED_STATE_MACHINE<PLAYER_BASE_STATE, GAMEPLAY_PLAYER>
        StateMachine;


XS_CLASS_END

#endif /* GAMEPLAY_PLAYER_hpp */
