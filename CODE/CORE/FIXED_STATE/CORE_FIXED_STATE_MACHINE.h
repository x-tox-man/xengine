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
#include "CORE_FIXED_STATE_EVENT.h"
#include "CORE_FIXED_STATE.h"

template <typename __BASE_STATE__, typename __PARENT_CONTEXT__ >
class CORE_FIXED_STATE_MACHINE {
    
public:

    CORE_FIXED_STATE_MACHINE() : CurrentState( NULL ), Context( NULL ){
        
    }
    
    virtual ~CORE_FIXED_STATE_MACHINE() {
        
        if ( CurrentState ) {
            
            FinalizeState();
        }
    }

    void InitializeState( __BASE_STATE__ & state, __PARENT_CONTEXT__ * context ) {
        
        Context = context;
        CurrentState = &state;
        CurrentState->SetContext( Context );
        CurrentState->EnterState();
    }
    
    void FinalizeState() {
        
        CurrentState->LeaveState();
        CurrentState = NULL;
        Context = NULL;
        
    }

    template < typename __EVENT__ >
    void DispatchEvent( const __EVENT__ & event) {
        
        CurrentState->HandleEvent( event );
    }
    
    template < typename __EVENT__ >
    static void HandleEvent( const __EVENT__ & event ) {
        
        //DUMMY METHOD
    }

    void ChangeState( __BASE_STATE__ & state ) {
        
        CurrentState->LeaveState();
        CurrentState = &state;
        CurrentState->SetContext( Context );
        CurrentState->EnterState();
    }
    
    const __BASE_STATE__ & GetState() {
        
        return *CurrentState;
    }
    
    __PARENT_CONTEXT__ * GetContext() { return Context; }

private :

    __BASE_STATE__ * CurrentState;
    __PARENT_CONTEXT__ * Context;
};

#define CORE_FIXED_STATE_MACHINE_DeclareBaseState( __BASE_STATE_NAME__, __BASE_MACHINE_TYPE_CONTEXT__ ) \
class __BASE_STATE_NAME__ { \
    private: \
    __BASE_MACHINE_TYPE_CONTEXT__ * Context; \
    public : \
    __BASE_STATE_NAME__() {} \
    virtual ~__BASE_STATE_NAME__() {} \
    virtual void EnterState() {}; \
    virtual void LeaveState() {}; \
    __BASE_MACHINE_TYPE_CONTEXT__ & GetContext() {return *Context; } \
    void SetContext( __BASE_MACHINE_TYPE_CONTEXT__ * context) { Context = context; }


#define CORE_FIXED_STATE_MACHINE_End() \
};

// Must declare within state chart
#define CORE_FIXED_STATE_MACHINE_DefineEvent( __EVENT_NAME__, __TYPE__ ) \
    class __EVENT_NAME__ : public CORE_FIXED_STATE_EVENT< __TYPE__ > { \
        public : __EVENT_NAME__( __TYPE__ & param ) : CORE_FIXED_STATE_EVENT< __TYPE__ >(param ) {} \
    };

#define CORE_FIXED_STATE_MACHINE_DefineEventVoid( __EVENT_NAME__ ) \
    class __EVENT_NAME__ : CORE_FIXED_STATE_EVENT< void > {};

#define CORE_FIXED_STATE_MACHINE_EndDefineState( __STATE_NAME__ ) \
    }; \
    __STATE_NAME__ __STATE_NAME__##STATE;

#define CORE_FIXED_STATE_MACHINE_DefineState( __BASE_STATE__, __STATE_NAME__ ) \
    class __STATE_NAME__ : public __BASE_STATE__ { \
        public : \
        __STATE_NAME__() {} \
        virtual void EnterState(); \
        virtual void LeaveState(); \

#define CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( __EVENT_TYPE__ ) \
virtual void HandleEvent( const __EVENT_TYPE__ & event ) {};

#define CORE_FIXED_STATE_MACHINE_DefineHandleEvent( __EVENT_TYPE__ ) \
    virtual void HandleEvent( const __EVENT_TYPE__ & event );

// Can be called from anywhere 

#define CORE_FIXED_STATE_MACHINE_ChangeState( __FSM__, __STATE_NAME__ ) \
    __FSM__.ChangeState( __STATE_NAME__##STATE );

#define CORE_FIXED_STATE_InitializeState( __FSM__, __STATE_NAME__, __CONTEXT__ ) \
    __FSM__.InitializeState( __STATE_NAME__##STATE, __CONTEXT__ );

#endif /* defined(__GAME_ENGINE_REBORN__CORE_FIXED_STATE_MACHINE__) */
