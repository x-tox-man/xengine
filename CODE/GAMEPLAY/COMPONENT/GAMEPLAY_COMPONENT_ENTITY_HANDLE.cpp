//
//  GAMEPLAY_COMPONENT_ENTITY_HANDLE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY_HANDLE )
    XS_DEFINE_ClassMember( "Offset", unsigned int, Offset )
XS_END_INTERNAL_MEMORY_LAYOUT

GAMEPLAY_COMPONENT_ENTITY_HANDLE::GAMEPLAY_COMPONENT_ENTITY_HANDLE() :
    Offset( UINT_MAX ),
    Size( 0 ) {
    
}

GAMEPLAY_COMPONENT_ENTITY_HANDLE::GAMEPLAY_COMPONENT_ENTITY_HANDLE( unsigned int offset, unsigned int size ) :
    Offset( offset ),
    Size( size ) {
    
}

GAMEPLAY_COMPONENT_ENTITY_HANDLE::GAMEPLAY_COMPONENT_ENTITY_HANDLE( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & other ) :
    Offset( other.Offset ),
    Size( other.Size ) {
    
}

GAMEPLAY_COMPONENT_ENTITY_HANDLE::~GAMEPLAY_COMPONENT_ENTITY_HANDLE() {
    
}

