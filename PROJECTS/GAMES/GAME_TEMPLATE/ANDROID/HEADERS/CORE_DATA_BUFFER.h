//
//  CORE_DATA_BUFFER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_DATA_BUFFER__
#define __GAME_ENGINE_REBORN__CORE_DATA_BUFFER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"

#include "assert.h"
#include <stdlib.h>

XS_CLASS_BEGIN( CORE_DATA_BUFFER )

XS_DEFINE_SERIALIZABLE

public:
    CORE_DATA_BUFFER();

    void Initialize( unsigned int size, int section_count = 0 );
    void InitializeWithMemory( unsigned int size, int section_count, void * memory );
    void Finalize();

    void setMarkerAtIndex( const CORE_HELPERS_IDENTIFIER * identifier, int section_index, int offset = 0, int item_size = 0 );

    void * getpointerAtIndex( unsigned int byte_offset, int section );
//    void * getpointerAtIndex( unsigned int byte_offset, const CORE_HELPERS_IDENTIFIER & section );

    int getSectionSize( int section_index );
    int getSectionSize( const CORE_HELPERS_IDENTIFIER * section = NULL );

    int getSectionItemOffset( int section_index );
    int getSectionItemOffset( const CORE_HELPERS_IDENTIFIER * section = NULL );

    Scalar_SGet( int, sections );
    Scalar_SGet( int, size );

    template<typename __SCALAR__>
    __SCALAR__ * getpointerAtIndex( __SCALAR__ size )
    {
        __SCALAR__ * base_pointer = (__SCALAR__ *) DataPointer;
        
        base_pointer += size;
        
        return base_pointer;
    }

private :
    void * DataPointer;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_BUFFER__) */
