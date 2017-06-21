//
//  GAMEPLAY_COMPONENT_ACTION.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_ACTION_hpp
#define GAMEPLAY_COMPONENT_ACTION_hpp

#include "GAMEPLAY_COMPONENT.h"
#include "CORE_HELPERS_CALLBACK.h"

class GAMEPLAY_COMPONENT_ENTITY;

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_ACTION, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_ACTION();
    virtual ~GAMEPLAY_COMPONENT_ACTION();

    void * operator new(size_t size);
    void operator delete( void* ptr );
    void operator() (GAMEPLAY_COMPONENT_ENTITY * entity) ;

    void SetActionCallback( const CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * > & callback ) {ActionCallback = callback; }

    CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_ACTION, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Action)

    struct INTERNAL_ARRAY{
        int LastIndex;
        GAMEPLAY_COMPONENT_ACTION * MemoryArray;
    };

    static void Clear();

    static void SaveToStream( CORE_DATA_STREAM & stream );
    static void LoadFromStream( CORE_DATA_STREAM & stream );

    virtual GAMEPLAY_COMPONENT * GetComponentAt( int index, int offset ) {
        
        return (GAMEPLAY_COMPONENT *) &(*InternalVector)[index].MemoryArray[offset];
    }

    static int
        LastIndex,
        LastOffset;

private :

    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >
        ActionCallback;
    static std::vector< INTERNAL_ARRAY > *
        InternalVector;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_ACTION_hpp */
