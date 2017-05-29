//
//  CORE_HELPERS_FACTORY.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_HELPERS_FACTORY__
#define __GAME_ENGINE_REBORN__CORE_HELPERS_FACTORY__

#include <map>
#include <stdlib.h>

template < typename __NAMED_CLASS__, typename __FACTORY_TYPE_ENUM__ >
class FACTORY {
public:
    
    static void __InternalRegisterFactoryClass( const __FACTORY_TYPE_ENUM__ classType,  const __NAMED_CLASS__ * creatable ) {

        if ( __InnerMap == NULL ) {
            
            __InnerMap = new std::map< __FACTORY_TYPE_ENUM__, const __NAMED_CLASS__ * >;
        }
        __InnerMap->insert( std::pair<__FACTORY_TYPE_ENUM__, const __NAMED_CLASS__ *>( classType, creatable ) );
    }
    
    static __NAMED_CLASS__ * __InternalCreateObject( const __FACTORY_TYPE_ENUM__ classType ) {
        
        return (*__InnerMap)[classType]->__InnerCreate();
    }
    
    static const __NAMED_CLASS__ * __InternalGetObject( const __FACTORY_TYPE_ENUM__ classType ) {
        
        return (*__InnerMap)[classType];
    }
    
    static void Finalize() {
        
        typename std::map< __FACTORY_TYPE_ENUM__, const __NAMED_CLASS__ * >::iterator it = (*__InnerMap).begin();
    }
    
    static std::map< __FACTORY_TYPE_ENUM__, const __NAMED_CLASS__ * > * __InnerMap;
};

template < typename __NAMED_CLASS__, typename __FACTORY_TYPE_ENUM__ >
std::map< __FACTORY_TYPE_ENUM__, const __NAMED_CLASS__ * > * FACTORY< __NAMED_CLASS__, __FACTORY_TYPE_ENUM__ >::__InnerMap = NULL;

template < typename __FACTORY_ELEMENT_CLASS__ >
class FACTORY_ELEMENT {
public:
    
    static __FACTORY_ELEMENT_CLASS__ * __InnerElement;
};

template < typename __FACTORY_ELEMENT_CLASS__ >
    __FACTORY_ELEMENT_CLASS__ * FACTORY_ELEMENT< __FACTORY_ELEMENT_CLASS__ >::__InnerElement = __FACTORY_ELEMENT_CLASS__::__InnerCreateElement();

#define CORE_HELPERS_FACTORY_Define( __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ ) \
    friend class FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >; \
    static void RegisterFactoryClass( const __FACTORY_TYPE_ENUM__ classType,  const __FACTORY_TYPE__ * creatable ) { \
        FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalRegisterFactoryClass(classType, creatable); \
    } \
\
    virtual int FactoryGetType() { return -1; } \
\
    static __FACTORY_TYPE__ * FactoryCreate( const __FACTORY_TYPE_ENUM__ factoryType) { \
        return FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalCreateObject( factoryType ); \
    }\
\
    static const __FACTORY_TYPE__ * FactoryGetTemplateElement( const __FACTORY_TYPE_ENUM__ factoryType) { \
        return FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalGetObject( factoryType ); \
    }\
\
    private : \
    virtual __FACTORY_TYPE__ * __InnerCreate() const { \
        CORE_RUNTIME_Abort();\
        return NULL; \
    };\
    public : \

#define CORE_HELPERS_FACTORY_Element( __CLASS_TYPE__, __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__, __FACTORY_TYPE_ENUMERATED__ ) \
    \
    friend class FACTORY_ELEMENT< __CLASS_TYPE__ >;\
    \
    virtual __FACTORY_TYPE__ * __InnerCreate() const override { \
        return new __CLASS_TYPE__();\
    }\
    \
    \
    static int GetFactoryType() { \
        return __FACTORY_TYPE_ENUMERATED__; \
    }\
    static __CLASS_TYPE__ * __InnerCreateElement() { \
        FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement = new __CLASS_TYPE__(); \
        __FACTORY_TYPE__::RegisterFactoryClass(__FACTORY_TYPE_ENUMERATED__, FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement); \
    \
        return FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement; \
    } \
    virtual int FactoryGetType() override { return (int) __FACTORY_TYPE_ENUMERATED__; }

#endif /* defined(__GAME_ENGINE_REBORN__CORE_HELPERS_FACTORY__) */
