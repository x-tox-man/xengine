//
//  CORE_FIXED_STATE_MACHINE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_FIXED_STATE_MACHINE__
#define __GAME_ENGINE_REBORN__CORE_FIXED_STATE_MACHINE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_CALLBACK.h"

template <typename __CLASS_NAME__>
XS_CLASS_BEGIN( CORE_FIXED_STATE_MACHINE )

template <typename __STATE__, typename __CALLBACK_CODE__ >
void BasicState( void ) {
    
    __CALLBACK_CODE__();
}

XS_CLASS_END

#define CORE_FIXED_STATE_MACHINE_Declare( __CLASS_NAME__ ) \
    CORE_FIXED_STATE_MACHINE< __CLASS_NAME__ > __InnerMachine; \
    friend class CORE_FIXED_STATE_MACHINE< __CLASS_NAME__ >

#define CORE_FIXED_STATE_MACHINE_STATE_Begin( __CLASS_NAME__ ) \
    __CLASS_NAME__::__InnerMachine;

#define CORE_FIXED_STATE_MACHINE_STATE_End( __CLASS_NAME__ ) \
__CLASS_NAME__::__InnerMachine;

#endif /* defined(__GAME_ENGINE_REBORN__CORE_FIXED_STATE_MACHINE__) */
