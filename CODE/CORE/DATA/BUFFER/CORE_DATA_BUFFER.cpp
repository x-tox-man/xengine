//
//  CORE_DATA_BUFFER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "CORE_DATA_BUFFER.h"
#include "CORE_MEMORY_ALLOCATOR.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_DATA_BUFFER )
    XS_DEFINE_ClassMember( "Sections", int, Sections )
    XS_DEFINE_ClassMember( "Size", int, Size )
    XS_DEFINE_ClassMemberArray( "DataPointer", char, (char **) &DataPointer, Size )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_DATA_BUFFER::CORE_DATA_BUFFER() :
    DataPointer( NULL ),
    Sections ( 0 ),
    Size( 0 ) {
    
}

CORE_DATA_BUFFER::~CORE_DATA_BUFFER() {
    
    if ( DataPointer ) {
        
        CORE_MEMORY_ALLOCATOR_Free( DataPointer );
    }
    
    DataPointer = NULL;
}

void CORE_DATA_BUFFER::Initialize( unsigned int size, int section_count ) {
    
    this->DataPointer = CORE_MEMORY_ALLOCATOR_Allocate( size );
    this->Size = size;
    this->Sections = section_count;
}

void CORE_DATA_BUFFER::InitializeWithMemory( unsigned int size, int section_count, void * memory ) {
    
    // Only realloc memory if new array is bigger
    if ( this->DataPointer && this->Size < size ) {
        
        CORE_MEMORY_ALLOCATOR_Free( this->DataPointer );
        
        this->DataPointer = NULL;
    }
    
    if ( this->DataPointer == NULL ) {

        this->DataPointer = CORE_MEMORY_ALLOCATOR_Allocate( size );
    }
    
    CORE_MEMORY_CopyBytes( this->DataPointer, size, memory);
    this->Size = size;
    this->Sections = section_count;
}

void CORE_DATA_BUFFER::Finalize() {
    
    if ( DataPointer ) {
    
        CORE_MEMORY_ALLOCATOR_Free( this->DataPointer );
        DataPointer = NULL;
    }
    
    Size = 0;
    Sections = 0;
}

void CORE_DATA_BUFFER::setMarkerAtIndex( const CORE_HELPERS_IDENTIFIER * identifier, int section_index, int byte_offset, int item_size ) {
    
    CORE_RUNTIME_Abort();
    
    // *( ( int * ) DataPointer + section_index * 3 + 0 ) = identifier->GetValue(); // semantic for item in the buffer
    // *( ( int * ) DataPointer + section_index * 3 + 1 ) = byte_offset; // size of the data
    // *( ( int * ) DataPointer + section_index * 3 + 2 ) = item_size; // size of one data item
}

void * CORE_DATA_BUFFER::getpointerAtIndex( unsigned int byte_offset, int section ) {
    
    unsigned int * base_pointer = (unsigned int *) DataPointer;

    
    base_pointer += byte_offset / sizeof(unsigned int);
    
    //assert(base_pointer >= (uint8_t*)DataPointer + (sections - 1) * 3 * 4 );
    //assert (base_pointer <= (uint8_t*)DataPointer + (sections - 1) * 3 * 4 + size);
    
    return base_pointer;
}

int CORE_DATA_BUFFER::getSectionSize( int section_index )
{
    return *( ( unsigned int * ) DataPointer + section_index * 3 + 1 );
}

int CORE_DATA_BUFFER::getSectionSize( const CORE_HELPERS_IDENTIFIER * section )
{
    CORE_RUNTIME_Abort();
    
    /*for ( int i = 0; i < sections; i ++ )
    {
        if ( *((int*)DataPointer + i * 2 ) == section->GetValue() )
        {
            return *((char*)DataPointer + 4 * (i * 3 + 1 ) );
        }
    }*/
    

    return -1;
}

int CORE_DATA_BUFFER::getSectionItemOffset( int section_index )
{
    return *( ( int * ) DataPointer + section_index * 3 + 2 );
}

int CORE_DATA_BUFFER::getSectionItemOffset( const CORE_HELPERS_IDENTIFIER * section )
{
    CORE_RUNTIME_Abort();
    
    /*
    for ( int i = 0; i < sections; i ++ )
    {
        if ( *((int*)DataPointer + i * 2 ) == section->GetValue() )
        {
            return *((char*)DataPointer + 4 * ( i * 3 + 2 ) );
        }
    }
    */
    
    return -1;
}
