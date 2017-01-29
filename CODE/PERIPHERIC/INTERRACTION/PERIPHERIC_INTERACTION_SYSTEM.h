//
//  PERIPHERIC_INTERACTION_SYSTEM.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_SYSTEM__
#define __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "PERIPHERIC_INTERACTION_KEYBOARD.h"
#include "PERIPHERIC_INTERACTION_MOUSE.h"

XS_CLASS_BEGIN( PERIPHERIC_INTERACTION_SYSTEM )

    XS_DEFINE_UNIQUE( PERIPHERIC_INTERACTION_SYSTEM )

    ~PERIPHERIC_INTERACTION_SYSTEM();

    //For now there is only one mouse & one keyboard => hotseat is for 1980 gamers

    void Update();

    PERIPHERIC_INTERACTION_KEYBOARD & GetKeyboard() { return Keyboard; }
    PERIPHERIC_INTERACTION_MOUSE & GetMouse() { return Mouse; }

private :

    PERIPHERIC_INTERACTION_KEYBOARD
        Keyboard;
    PERIPHERIC_INTERACTION_MOUSE
        Mouse;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_SYSTEM__) */
