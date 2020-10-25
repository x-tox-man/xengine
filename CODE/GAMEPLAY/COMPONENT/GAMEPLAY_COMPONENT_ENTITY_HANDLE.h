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

/**-----------------------------------------------------
 ** Class Name  : GAMEPLAY_COMPONENT_ENTITY_HANDLE
 ** Description :
 **     Handle is really only an offset on base pointer.
 **/
XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_ENTITY_HANDLE )

    XS_DEFINE_SERIALIZABLE

    GAMEPLAY_COMPONENT_ENTITY_HANDLE();
    GAMEPLAY_COMPONENT_ENTITY_HANDLE( unsigned int offset, unsigned int size );
    ~GAMEPLAY_COMPONENT_ENTITY_HANDLE();

    bool operator == ( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & other ) const {
        return other.Offset == Offset;
    }

    inline void SetOffset( int offset ) { Offset = offset; }
    inline int GetOffset() const { return Offset; }
    inline bool IsValid() const { return Offset != UINT_MAX; }

    inline void SetSize( int size ) { Size = size; }
    inline int GetSize() const { return Size; }

    inline void operator = ( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & other ) {
        
        Offset = other.Offset;
        Size = other.Size;
    }

private:

    unsigned int
        Offset,
        Size;

XS_CLASS_END

inline bool operator < (const GAMEPLAY_COMPONENT_ENTITY_HANDLE & first, const GAMEPLAY_COMPONENT_ENTITY_HANDLE & second ) {
    
    return first.GetOffset() < second.GetOffset();
}


#endif /* GAMEPLAY_COMPONENT_ENTITY_HANDLE_hpp */
