//
//  CORE_HELPERS_FACTORY.h
//  GAME-ENGINE
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
    
    static __NAMED_CLASS__ * __InternalCopyObject( const __FACTORY_TYPE_ENUM__ classType, const __NAMED_CLASS__ & object_to_copy ) {
        
        return (*__InnerMap)[classType]->__InnerCopy( object_to_copy );
    }
    
    static const __NAMED_CLASS__ * __InternalGetObject( const __FACTORY_TYPE_ENUM__ classType ) {
        
        return (*__InnerMap)[classType];
    }
    
    static const __FACTORY_TYPE_ENUM__ __InternalGetIndex( __NAMED_CLASS__ * element_class ) {
        
        typename std::map< __FACTORY_TYPE_ENUM__, const __NAMED_CLASS__ * >::iterator it = __InnerMap->begin();
        
        while (it != __InnerMap->end() ) {
            if ( it->second == element_class ) {
                return it->first;
            }
            it++;
        }
        return __FACTORY_TYPE_ENUM__();
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
    int FactoryGetType() { return __InnerFactoryType; } \
\
    static __FACTORY_TYPE__ * FactoryCreate( const __FACTORY_TYPE_ENUM__ factoryType) { \
        return FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalCreateObject( factoryType ); \
    }\
\
    static __FACTORY_TYPE__ * FactoryCopy( const __FACTORY_TYPE_ENUM__ factoryType, const __FACTORY_TYPE__ & object_to_copy ) { \
        return FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalCopyObject( factoryType, object_to_copy ); \
    }\
\
    static const __FACTORY_TYPE__ * FactoryGetTemplateElement( const __FACTORY_TYPE_ENUM__ factoryType) { \
        return FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalGetObject( factoryType ); \
    }\
\
    static const __FACTORY_TYPE_ENUM__ FactoryGetTemplateIndex( __FACTORY_TYPE__ * element) { \
        return FACTORY< __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__ >::__InternalGetIndex( element ); \
    }\
\
    void __SetInnerFactoryType( unsigned int type ) { __InnerFactoryType = type; }\
    private : \
    virtual __FACTORY_TYPE__ * __InnerCreate() const { \
        CORE_RUNTIME_Abort();\
        return NULL; \
    };\
\
    virtual __FACTORY_TYPE__ * __InnerCopy( const __FACTORY_TYPE__ & object ) const { \
        CORE_RUNTIME_Abort();\
        return NULL; \
    };\
\
    unsigned int __InnerFactoryType;\
    public : \

#define CORE_HELPERS_FACTORY_Element( __CLASS_TYPE__, __FACTORY_TYPE__, __FACTORY_TYPE_ENUM__, __FACTORY_TYPE_ENUMERATED__ ) \
    \
    friend class FACTORY_ELEMENT< __CLASS_TYPE__ >;\
    \
    virtual __FACTORY_TYPE__ * __InnerCreate() const override { \
        auto c = new __CLASS_TYPE__();\
        c->__SetInnerFactoryType( (int) __FACTORY_TYPE_ENUMERATED__ );\
        return c;\
    }\
\
    virtual __FACTORY_TYPE__ * __InnerCopy( const __FACTORY_TYPE__ & object ) const override { \
        auto c = new __CLASS_TYPE__( *((__CLASS_TYPE__*) &object) );\
        c->__SetInnerFactoryType( (int) __FACTORY_TYPE_ENUMERATED__ );\
        return c;\
    };\
\
    static __CLASS_TYPE__ * GetFactoryElement() { \
        return FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement; \
    }\
\
    static __CLASS_TYPE__ * __InnerCreateElement() { \
        FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement = new __CLASS_TYPE__(); \
        __FACTORY_TYPE__::RegisterFactoryClass(__FACTORY_TYPE_ENUMERATED__, FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement); \
\
        return FACTORY_ELEMENT<__CLASS_TYPE__>::__InnerElement; \
    }

#endif /* defined(__GAME_ENGINE_REBORN__CORE_HELPERS_FACTORY__) */
