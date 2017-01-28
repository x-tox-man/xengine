//
//  X_CALLBACK.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/06/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__X_CALLBACK__
#define __GAME_ENGINE_REBORN__X_CALLBACK__

#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

class CORE_HELPERS_FUNCTION_CALLBACK {
    
public:
    
    typedef void (*XS_CALLBACK_FUNCTION)();
    
    CORE_HELPERS_FUNCTION_CALLBACK() :
        CallbackFunction() {
        
    }
    
    CORE_HELPERS_FUNCTION_CALLBACK( XS_CALLBACK_FUNCTION callback) :
        CallbackFunction( callback ) {
        
    }
    
    inline bool IsConnected() const { return true; }
    inline void Disconnect() {}
    
    void operator() () {
        
        (*CallbackFunction)();
    }

private:
    XS_CALLBACK_FUNCTION
        CallbackFunction;
};

class CORE_HELPERS_CALLBACK {

public :
    
    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( CORE_HELPERS_CALLBACK )

    typedef void (*XS_CALLBACK_FUNCTION)(void *);

    CORE_HELPERS_CALLBACK() :
        CallbackFunction(),
        ObjectPointer( NULL ) {
        
    }

    CORE_HELPERS_CALLBACK( XS_CALLBACK_FUNCTION callback, void * object_pointer) :
        CallbackFunction( callback ),
        ObjectPointer( object_pointer )
    {
        
    }
    
    void Connect(XS_CALLBACK_FUNCTION callback, void* object_pointer) {
        
        CallbackFunction = callback;
        ObjectPointer = object_pointer;
    }

    inline bool IsConnected() const { return ObjectPointer != NULL; }
    inline void Disconnect() { ObjectPointer = NULL; }
    
    void SetObject( void * object  ) { ObjectPointer = object;}
    void * GetObjectPointer() { return ObjectPointer; }

    void operator() () {
        
        (*CallbackFunction)(ObjectPointer);
    }

private:
	XS_CALLBACK_FUNCTION
        CallbackFunction;
    void
        *ObjectPointer;
};

template< typename __TYPE_1__ >
class CORE_HELPERS_CALLBACK_1 {
    
public:
    
    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( CORE_HELPERS_CALLBACK_1 )
    
    typedef void ( *XS_CALLBACK_FUNCTION)( void* , __TYPE_1__ );
    
    CORE_HELPERS_CALLBACK_1() : CallbackFunction(), ObjectPointer( NULL ) {}
    
    CORE_HELPERS_CALLBACK_1(XS_CALLBACK_FUNCTION callback, void* object_pointer ) : CallbackFunction( callback ), ObjectPointer( object_pointer ) {}

    void Connect(XS_CALLBACK_FUNCTION callback, void* object_pointer) {
        
        CallbackFunction = callback;
        ObjectPointer = object_pointer;
    }
    
    inline bool IsConnected() const { return ObjectPointer != NULL; }
    inline void Disconnect() { ObjectPointer = NULL; }
    
    void SetObject( void * object  ) { ObjectPointer = object;}
    void * GetObjectPointer() { return ObjectPointer; }
    
    void operator()( __TYPE_1__ first )
    {
        return ( *CallbackFunction )( ObjectPointer, first );
    }
    
private:
	XS_CALLBACK_FUNCTION
        CallbackFunction;
    void
        *ObjectPointer;

};

template< typename __TYPE_1__, typename __TYPE_2__ >
class  CORE_HELPERS_CALLBACK_2 {
    
public:
    
    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( CORE_HELPERS_CALLBACK_2 )
    
    typedef void ( *XS_CALLBACK_FUNCTION)( void*, __TYPE_1__, __TYPE_2__ );
    
    CORE_HELPERS_CALLBACK_2() :
        CallbackFunction(),
        ObjectPointer( NULL ) {
    
    }
    
    CORE_HELPERS_CALLBACK_2(XS_CALLBACK_FUNCTION callback, void * object_pointer ) :
        CallbackFunction( callback ),
        ObjectPointer( object_pointer ) {
    
    }
    
    void Connect(XS_CALLBACK_FUNCTION callback, void* object_pointer) {
        
        CallbackFunction = callback;
        ObjectPointer = object_pointer;
    }

    inline bool IsConnected() const { return ObjectPointer != NULL; }
    inline void Disconnect() { ObjectPointer = NULL; }
    
    void operator=( const CORE_HELPERS_CALLBACK_2< __TYPE_1__, __TYPE_2__> & other ) {
        
        CallbackFunction = other.CallbackFunction;
        ObjectPointer = other.ObjectPointer;
    }
    
    void SetObject( void * object  ) { ObjectPointer = object;}
    void * GetObjectPointer() { return ObjectPointer; }
    
    void operator()( __TYPE_1__ first, __TYPE_2__ second ) {
        if ( ObjectPointer == 0 ) {
            return;
        }
        
        ( *CallbackFunction )( ObjectPointer, first, second );
    }
    
private:
    
	XS_CALLBACK_FUNCTION
        CallbackFunction;
    void
        *ObjectPointer;

};

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

template<void (*Func)()>
void WrappedFunction() {
    
    return (*Func)();
}


#endif /* defined(__GAME_ENGINE_REBORN__X_CALLBACK__) */
