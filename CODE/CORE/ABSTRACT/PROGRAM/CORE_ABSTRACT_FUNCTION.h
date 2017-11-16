//
//  CORE_ABSTRACT_PROGRAM_FUNCTION.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_ABSTRACT_FUNCTION_h
#define CORE_ABSTRACT_FUNCTION_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_ABSTRACT_FUNCTION_PARAMETER.h"
#include "CORE_MEMORY.h"

template < typename __ABSTRACT_PROGRAM_TYPE__ >
class CORE_ABSTRACT_FUNCTION {
    
public:
    
    CORE_ABSTRACT_FUNCTION() {
        
    }
    
    CORE_ABSTRACT_FUNCTION( const char * method_name ) :
        Program( NULL ),
        MethodName( NULL ) {
        
            MethodName = (char * ) CORE_MEMORY_ALLOCATOR_Allocate( ( int ) strlen( method_name ) );
            
            strcpy( MethodName, method_name );
            
            Program = CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram;
    }
    
    virtual    ~CORE_ABSTRACT_FUNCTION() {
        
        Program = NULL;
        
        CORE_MEMORY_ALLOCATOR_Free( MethodName );
    }
    
    void Initialize( const char * method_name ) {
        
        Program = CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram;
        
        MethodName = (char * ) CORE_MEMORY_ALLOCATOR_Allocate( ( int ) strlen( method_name ) );
        
        strcpy( MethodName, method_name );
    }
    
    
    template< typename __TYPE1__, typename __TYPE2__ >
    void CallLuaCallback( __TYPE1__ param1, __TYPE2__ param2 ) {
        
        ( (__ABSTRACT_PROGRAM_TYPE__ *) Program )->template AddParameter< __TYPE1__ >( param1, 0 );
        ( (__ABSTRACT_PROGRAM_TYPE__ *) Program )->template AddParameter< __TYPE2__ >( param2, 1 );
        
        Call( 2 );
    }
    
    void Call( int parameter_count ) {
        
        Program->ExecuteFunction( MethodName, parameter_count, 0, 0 );
    }
    
private :
    
    char * MethodName;
    CORE_ABSTRACT_PROGRAM_FACTORY * Program;
};

#endif /* CORE_ABSTRACT_FUNCTION_h */
