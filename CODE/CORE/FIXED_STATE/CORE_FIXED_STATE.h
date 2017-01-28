//
//  CORE_FIXED_STATE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_FIXED_STATE_h
#define CORE_FIXED_STATE_h

#include "CORE_FIXED_STATE_EVENT.h"

template <typename __STATE_MACHINE__ >
class CORE_FIXED_STATE {
    
public:
    
    virtual void EnterState() = 0;
    virtual void LeaveState() = 0;
};

#define CORE_FIXED_STATE_DefineStateEnterEvent( __STATE_TYPE__ ) \
    void __STATE_TYPE__::EnterState() {

#define CORE_FIXED_STATE_DefineStateLeaveEvent( __STATE_TYPE__ ) \
    void __STATE_TYPE__::LeaveState() {

#define CORE_FIXED_STATE_DefineStateEvent( __STATE_TYPE__, __EVENT_TYPE__ ) \
    void __STATE_TYPE__::HandleEvent( const __EVENT_TYPE__ & event ) {

#define CORE_FIXED_STATE_EndOfStateEvent() }


#endif /* CORE_FIXED_STATE_h */
