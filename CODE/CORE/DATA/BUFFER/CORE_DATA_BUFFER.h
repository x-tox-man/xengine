//
//  CORE_DATA_BUFFER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_DATA_BUFFER__
#define __GAME_ENGINE_REBORN__CORE_DATA_BUFFER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN( CORE_DATA_BUFFER )

XS_DEFINE_SERIALIZABLE

public:
    CORE_DATA_BUFFER();
    ~CORE_DATA_BUFFER();

    void Initialize( size_t size, int section_count = 0 );
    void InitializeWithMemory( size_t size, int section_count, void * memory );
    void Finalize();

    void setMarkerAtIndex( const CORE_HELPERS_IDENTIFIER * identifier, int section_index, int offset = 0, size_t item_size = 0 );

    void * getpointerAtIndex( size_t byte_offset, int section );
//    void * getpointerAtIndex( unsigned int byte_offset, const CORE_HELPERS_IDENTIFIER & section );

    int getSectionSize( int section_index );
    int getSectionSize( const CORE_HELPERS_IDENTIFIER * section = NULL );

    int getSectionItemOffset( int section_index );
    int getSectionItemOffset( const CORE_HELPERS_IDENTIFIER * section = NULL );

    Scalar_SGet( int, Sections );
    Scalar_SGet( size_t, Size );

    template<typename __SCALAR__>
    __SCALAR__ * getpointerAtIndex( __SCALAR__ offset )
    {
        __SCALAR__ * base_pointer = (__SCALAR__ *) DataPointer;
        
        base_pointer += offset;
        
        #if DEBUG
            if ( (__SCALAR__ *)base_pointer > (__SCALAR__ *)DataPointer + Size ) {
                CORE_RUNTIME_Abort();
            }
        #endif
        
        return base_pointer;
    }

private :

    void
        * DataPointer;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_BUFFER__) */
