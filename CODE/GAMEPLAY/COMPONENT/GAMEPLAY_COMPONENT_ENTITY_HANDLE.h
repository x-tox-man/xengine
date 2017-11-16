//
//  GAMEPLAY_COMPONENT_ENTITY_HANDLE.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_ENTITY_HANDLE_hpp
#define GAMEPLAY_COMPONENT_ENTITY_HANDLE_hpp

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_ENTITY_HANDLE )

    XS_DEFINE_SERIALIZABLE

    GAMEPLAY_COMPONENT_ENTITY_HANDLE();
    GAMEPLAY_COMPONENT_ENTITY_HANDLE( int index, int offset );
    ~GAMEPLAY_COMPONENT_ENTITY_HANDLE();

    inline void SetIndex( int index ) { Index = index; }
    inline void SetOffset( int offset ) { Offset = offset; }
    inline int GetOffset() const { return Offset; }
    inline int GetIndex() const { return Index; }

    void operator = ( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & other ) {
        
        Index = other.Index;
        Offset = other.Offset;
    }

private:

    int
        Index,
        Offset;

XS_CLASS_END

bool operator < (const GAMEPLAY_COMPONENT_ENTITY_HANDLE & first, const GAMEPLAY_COMPONENT_ENTITY_HANDLE & second );

#endif /* GAMEPLAY_COMPONENT_ENTITY_HANDLE_hpp */
