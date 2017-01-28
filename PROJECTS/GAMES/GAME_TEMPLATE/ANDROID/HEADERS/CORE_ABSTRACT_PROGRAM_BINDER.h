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

// -- SCRIPT BINDING METHODS :

#define CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( __BINDER_CLASS__ ) \
    static const char * CLASS_NAME; \

#define CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( __BINDER_CLASS__ ) \
    template <typename __BINDER_CLASS__ > \
    class BINDER { \
        public: \
        template< typename _CORE_ABSTRACT_BASE_PROGRAM_RUNTIME_ > \
        static void BindClass( _CORE_ABSTRACT_BASE_PROGRAM_RUNTIME_ & runtime ) { \
            runtime.template initBindings< __BINDER_CLASS__>();


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD( __BINDER_CLASS__, __METHOD__ ) \
            runtime.template bind< __BINDER_CLASS__>( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( __BINDER_CLASS__, __METHOD__, __TYPE_1__ ) \
            runtime.template bind< __BINDER_CLASS__, __TYPE_1__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_2( __METHOD__, __TYPE_1__, __TYPE_2__ ) \
            runtime.template bind( void, __METHOD__, __TYPE_1__, __TYPE_2__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_3( __METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ) \
            runtime.template bind( void, __METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ );


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__ ) \
            runtime.template staticBind< __RETURN_TYPE__, __BINDER_CLASS__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD( __BINDER_CLASS__, __METHOD__ ) \
            runtime.template staticBind< __BINDER_CLASS__ >( &__BINDER_CLASS__::__METHOD__, #__METHOD__ );


        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__>( &__BINDER_CLASS__::__METHOD__, #__METHOD__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__>( __RETURN_TYPE__, __METHOD__, __TYPE_1__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_2( __RETURN_TYPE__,__METHOD__, __TYPE_1__, __TYPE_2__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__, __TYPE_2__ >( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_3( __RETURN_TYPE__,__METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ) \
            runtime.template bind< __RETURN_TYPE__, __BINDER_CLASS__, __TYPE_1__, __TYPE_2__, __TYPE_3__ >( __RETURN_TYPE__, __BINDER_CLASS__, __METHOD__, __TYPE_1__, __TYPE_2__, __TYPE_3__ ); \

        #define CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_CLASS_ATTRIBUTE( __TYPE__, __ATTRIBUTE__ ) \
            runtime.template bind( __TYPE__, __ATTRIBUTE__ ); \

#define CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( __BINDER_CLASS__ ) \
    \
    runtime.completeBindings(); \
        } \
    };\
    \
    const char * __BINDER_CLASS__::CLASS_NAME = #__BINDER_CLASS__; \

#endif
