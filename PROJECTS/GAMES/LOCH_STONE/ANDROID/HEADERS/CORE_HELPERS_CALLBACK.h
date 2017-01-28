//
//  X_CALLBACK.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/06/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__X_CALLBACK__
#define __GAME_ENGINE_REBORN__X_CALLBACK__

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN_WITH_COPY( CORE_HELPER_CALLBACK )

    typedef void (*CALLBACK_FUNCTION)(void *);

    CORE_HELPER_CALLBACK() :
        CallbackFunction(),
        ObjectPointer() {
        
    }

    CORE_HELPER_CALLBACK(  CALLBACK_FUNCTION callback, void * object_pointer) :
        CallbackFunction( callback ),
        ObjectPointer( object_pointer )
    {
        
    }

    void operator() () {
        (*CallbackFunction)(ObjectPointer);
    }

private:
    CALLBACK_FUNCTION
        CallbackFunction;
    void
        *ObjectPointer;

XS_CLASS_END

template< typename __TYPE_1__ >
XS_CLASS_BEGIN_WITH_COPY( CORE_HELPER_CALLBACK_1 )
    
public:
    typedef void ( *CALLBACK_FUNCTION )( void* , __TYPE_1__ );
    
    CORE_HELPER_CALLBACK_1() : CallbackFunction(), ObjectPointer() {}
    
    CORE_HELPER_CALLBACK_1( CALLBACK_FUNCTION callback, void* object_pointer ) : CallbackFunction( callback ), ObjectPointer( object_pointer ) {}
    
    void operator()( __TYPE_1__ first )
    {
        return ( *CallbackFunction )( ObjectPointer, first );
    }
    
private:
    CALLBACK_FUNCTION
        CallbackFunction;
    void
        *ObjectPointer;

XS_CLASS_END

template< typename __TYPE_1__, typename __TYPE_2__ >
XS_CLASS_BEGIN_WITH_COPY( CORE_HELPER_CALLBACK_2 )
    
public:
    typedef void ( *CALLBACK_FUNCTION )( void*, __TYPE_1__, __TYPE_2__ );
    
    CORE_HELPER_CALLBACK_2() :
        CallbackFunction(),
        ObjectPointer() {
    
    }
    
    CORE_HELPER_CALLBACK_2( CALLBACK_FUNCTION callback, void * object_pointer ) :
        CallbackFunction( callback ),
        ObjectPointer( object_pointer ) {
    
    }
    
    void operator()( __TYPE_1__ first, __TYPE_2__ second ) {
        
        return ( *CallbackFunction )( ObjectPointer, first, second );
    }
    
private:
    
    CALLBACK_FUNCTION
        CallbackFunction;
    void
        *ObjectPointer;

XS_CLASS_END

template<class T, void (T::*Func)()>
void Wrapper(void* o) {
    
    return (static_cast<T*>(o)->*Func)();
}

template< class T, typename P1, void ( T::*Func )( P1 ) >
void Wrapper1( void* o, P1 a1 ) {
    
    return ( static_cast< T* >( o )->*Func )( a1 );
}

template< class T, typename P1, typename P2, void (T::*Func)(P1, P2) >
void Wrapper2( void* o, P1 a1, P2 a2 ) {
    
    return ( static_cast< T* >( o )->*Func )( a1, a2 );
}

#endif /* defined(__GAME_ENGINE_REBORN__X_CALLBACK__) */
