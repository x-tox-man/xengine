//
//  CORE_ABSTRACT_PROGRAM_BINDER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_CORE_ABSTRACT_PROGRAM_BINDER_h
#define GAME_ENGINE_REBORN_CORE_ABSTRACT_PROGRAM_BINDER_h

#include "CORE_ABSTRACT_PROGRAM_BINDER_MODE.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"

#include "CORE_HELPERS_UNIQUE.h"

#include <vector>

// -- SCRIPT BINDING METHODS :
template <typename __BINDER_CLASS__ > class BINDER;

template < typename __BINDER_CLASS__ >
class CORE_ABSTRACT_PROGRAM_BINDER_CLASS_BASE {
    
};

class CORE_ABSTRACT_PROGRAM_BINDER {
    
    XS_DEFINE_UNIQUE( CORE_ABSTRACT_PROGRAM_BINDER )

    ~CORE_ABSTRACT_PROGRAM_BINDER();
    
    public :
    
    typedef void (*BindClassMethodPointer)( CORE_ABSTRACT_RUNTIME_LUA & );

    template <typename __BINDER_CLASS__ >
    const char * RegisterClass( const char * class_name ) {
        
        StaticBindClassMethodPointerTable.resize( StaticBindClassMethodPointerTable.size() + 1 );
        
        StaticBindClassMethodPointerTable[ StaticBindClassMethodPointerTable.size() - 1 ] = BINDER< __BINDER_CLASS__ >::template BindClass< CORE_ABSTRACT_RUNTIME_LUA >;
        
        return class_name;
    }
    
    template <typename __BINDER_CLASS__ >
    void BindRuntime( CORE_ABSTRACT_RUNTIME_LUA & runtime ) {
        
        for ( int i = 0; i < StaticBindClassMethodPointerTable.size(); i++ ) {
            
            StaticBindClassMethodPointerTable[ i ]( runtime );
        }
    }
    
    private :
    
    std::vector< BindClassMethodPointer > StaticBindClassMethodPointerTable;
};

#define CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( __BINDER_CLASS__ ) \
    static const char * CLASS_NAME; \

#define CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( __BINDER_CLASS__ ) \
    template <typename __BINDER_CLASS__ > \
    class BINDER : public CORE_ABSTRACT_PROGRAM_BINDER_CLASS_BASE< __BINDER_CLASS__ > { \
        public: \
        template< typename _CORE_ABSTRACT_BASE_PROGRAM_RUNTIME_ > \
        static void BindClass( _CORE_ABSTRACT_BASE_PROGRAM_RUNTIME_ & runtime ) { \
            runtime.template initBindings< __BINDER_CLASS__>();


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD( __BINDER_CLASS__, __METHOD__ ) \
            runtime.template bind< __BINDER_CLASS__>( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( __BINDER_CLASS__, __METHOD__, __TYPE_1__ ) \
            runtime.template bind< __BINDER_CLASS__, __TYPE_1__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_2( __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__ ) \
            runtime.template bind< __BINDER_CLASS__, __TYPE_1__, __TYPE_2__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_3( __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ) \
            runtime.template bind< __BINDER_CLASS__, __TYPE_1__, __TYPE_2__, __TYPE_3__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__ ) \
            runtime.template staticBind< __RETURN_TYPE__, __BINDER_CLASS__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__ ) \
            runtime.template staticBind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_2( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__ ) \
            runtime.template staticBind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__, __TYPE_2__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_3( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ) \
            runtime.template staticBind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__, __TYPE_2__, __TYPE_3__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD( __BINDER_CLASS__, __METHOD__ ) \
            runtime.template staticBind< __BINDER_CLASS__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD_1( __BINDER_CLASS__, __METHOD__, __TYPE_1__ ) \
            runtime.template staticBind< __BINDER_CLASS__, __TYPE_1__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD_2( __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__ ) \
        runtime.template staticBind< __BINDER_CLASS__, __TYPE_1__, __TYPE_2__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD_3( __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ) \
        runtime.template staticBind< __BINDER_CLASS__, __TYPE_1__, __TYPE_2__, __TYPE_3__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__>( &__BINDER_CLASS__::__METHOD__, #__METHOD__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__>( &__BINDER_CLASS__::__METHOD__, #__METHOD__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_2( __RETURN_TYPE__,__METHOD__, __TYPE_1__, __TYPE_2__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__, __TYPE_2__ >( __RETURN_TYPE__, &__BINDER_CLASS__::__BINDER_CLASS__, __METHOD__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_3( __RETURN_TYPE__,__METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__, __TYPE_2__, __TYPE_3__ >( __RETURN_TYPE__, &__BINDER_CLASS__::__BINDER_CLASS__, __METHOD__ ); \

        /*#define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_CLASS_ATTRIBUTE( __TYPE__, __ATTRIBUTE__ ) \
            runtime.template bind( __TYPE__, __ATTRIBUTE__ ); \*/

#define CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( __BINDER_CLASS__ ) \
    \
    runtime.completeBindings(); \
        } \
    };\
    \
    const char * __BINDER_CLASS__::CLASS_NAME = CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().RegisterClass< __BINDER_CLASS__ >( #__BINDER_CLASS__ );

#define CORE_ABSTRACT_PROGRAM_BINDER_END_TEMPLATE_CLASS( __BINDER_CLASS__ ) \
    \
        runtime.completeBindings(); \
        } \
    };\
    \
    template<> \
    const char * __BINDER_CLASS__::CLASS_NAME = CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().RegisterClass< __BINDER_CLASS__ >( #__BINDER_CLASS__ );

#endif
