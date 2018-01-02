//
//  PERIPHERIC_INTERACTION_KEYBOARD.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_KEYBOARD__
#define __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_KEYBOARD__

#include "CORE_HELPERS_CLASS.h"
#include "KEYBOARD_KEY.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN( PERIPHERIC_INTERACTION_KEYBOARD )

    PERIPHERIC_INTERACTION_KEYBOARD();
    ~PERIPHERIC_INTERACTION_KEYBOARD();

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( PERIPHERIC_INTERACTION_KEYBOARD );

    void Initialize();
    void Update();

    bool IsKeyPressed( int key );
    bool IsKeyReleased( int key );

    void SetKeyPressed( int key );
    void SetKeyReleased( int key );

    static KEYBOARD_KEY KeyFromCode( int code );

private :

    int KeyTable[ KEYBOARD_KEY_Count ];

    enum KEY_STATE{
        KEY_STATE_Up = 0x0001,
        KEY_STATE_Pressed = 0x0010,
        KEY_STATE_Released = 0x0100
    };

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_KEYBOARD__) */
