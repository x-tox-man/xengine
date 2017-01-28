//
//  PERIPHERIC_INTERACTION_KEYBOARD.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_KEYBOARD__
#define __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_KEYBOARD__

#include "CORE_HELPERS_CLASS.h"
#include "KEYBOARD_KEY.h"

XS_CLASS_BEGIN( PERIPHERIC_INTERACTION_KEYBOARD )

PERIPHERIC_INTERACTION_KEYBOARD();

void Initialize();
void Update();

bool IsKeyPressed( const KEYBOARD_KEY key );
bool IsKeyReleased( const KEYBOARD_KEY key );

void SetKeyPressed( const KEYBOARD_KEY key );
void SetKeyReleased( const KEYBOARD_KEY key );

static KEYBOARD_KEY KeyFromCode( int code );

private :

int KeyTable[ KEYBOARD_KEY_Count ];

enum KEY_STATE{
    KEY_STATE_Up = 0x00000000,
    KEY_STATE_Pressed = 0x00000001,
    KEY_STATE_Released = 0x00000010
};

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_KEYBOARD__) */
