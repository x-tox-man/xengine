//
//  GAMEPLAY_COMPONENT_PROXY.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 18/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_HANDLE.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_HANDLE )
    XS_DEFINE_ClassMember( "Index", int, Index )
    XS_DEFINE_ClassMember( "Offset", int, Offset )
XS_END_INTERNAL_MEMORY_LAYOUT

GAMEPLAY_COMPONENT_HANDLE::GAMEPLAY_COMPONENT_HANDLE() :
    Component( NULL ),
    Index( -1 ),
    Offset( -1 ) {
    
}

GAMEPLAY_COMPONENT_HANDLE::GAMEPLAY_COMPONENT_HANDLE( int index, int offset, GAMEPLAY_COMPONENT * component ) :
    Component( component ),
    Index( index ),
    Offset( offset )
{
    
}

GAMEPLAY_COMPONENT_HANDLE::GAMEPLAY_COMPONENT_HANDLE( const GAMEPLAY_COMPONENT_HANDLE & other ) :
    Component( other.Component ),
    Index( other.Index ),
    Offset( other.Offset )
{
    
}

GAMEPLAY_COMPONENT_HANDLE::~GAMEPLAY_COMPONENT_HANDLE() {
    
}
