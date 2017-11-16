//
//  GAMEPLAY_COMPONENT_ENTITY_HANDLE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 18/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_PROXY_hpp
#define GAMEPLAY_COMPONENT_PROXY_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_HANDLE )

    XS_DEFINE_SERIALIZABLE

    GAMEPLAY_COMPONENT_HANDLE();
    GAMEPLAY_COMPONENT_HANDLE( int index, int offset, GAMEPLAY_COMPONENT * component );
    ~GAMEPLAY_COMPONENT_HANDLE();

    inline void SetComponent( GAMEPLAY_COMPONENT * component ) { Component = component; }
    inline void SetIndex( int index ) { Index = index; }
    inline void SetOffset( int offset ) { Offset = offset; }
    inline int GetOffset() { return Offset; }
    inline int GetIndex() { return Index; }

    inline GAMEPLAY_COMPONENT * GetComponent() { return Component; }

    template <typename __COMPONENT_TYPE__ >
    __COMPONENT_TYPE__ * GetComponent() { return (__COMPONENT_TYPE__*) Component; }

    void operator = ( const GAMEPLAY_COMPONENT_HANDLE & other ) {
        
        Component = other.Component;
        Index = other.Index;
        Offset = other.Offset;
    }

    template <typename __COMPONENT_TYPE__>
    void Create( GAMEPLAY_COMPONENT_TYPE type) {
        
        auto position_component = ( __COMPONENT_TYPE__ * ) GAMEPLAY_COMPONENT::FactoryCreate( type );
        
        SetIndex( __COMPONENT_TYPE__::LastIndex );
        SetOffset( __COMPONENT_TYPE__::LastOffset );
        SetComponent( position_component );
    }

    GAMEPLAY_COMPONENT_HANDLE Clone() const {
        
        GAMEPLAY_COMPONENT_HANDLE
            c;
        
        c.SetComponent( GAMEPLAY_COMPONENT::FactoryCopy( (GAMEPLAY_COMPONENT_TYPE) Component->FactoryGetType(), *Component )  );
        
        return c;
    }

private:

    GAMEPLAY_COMPONENT
        * Component;
    int
        Index,
        Offset;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_PROXY_hpp */
