//
//  RESOURCE_PROXY.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_PROXY.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( RESOURCE_PROXY )
    XS_DEFINE_ClassMember( "Identifier", CORE_HELPERS_UNIQUE_IDENTIFIER , Identifier )
    XS_DEFINE_ClassMember( "Type", RESOURCE_TYPE , Type )
    XS_DEFINE_ClassMember( "ItShouldLoad", bool , ItShouldLoad )
XS_END_INTERNAL_MEMORY_LAYOUT

RESOURCE_PROXY::RESOURCE_PROXY()  :
    Identifier(),
    Type( RESOURCE_TYPE_None ),
    Resource( NULL ),
    ItShouldLoad( true ) {
    
}

RESOURCE_PROXY::RESOURCE_PROXY(BASE_RESOURCE * resource) :
    Identifier( resource->GetIdentifier() ),
    Resource( resource ),
    ItShouldLoad( true ),
    Type( (RESOURCE_TYPE) resource->FactoryGetType() ) {
    
}

RESOURCE_PROXY::RESOURCE_PROXY(const RESOURCE_PROXY & other) :
    Identifier( other.Identifier ),
    Resource( other.Resource ),
    ItShouldLoad( other.ItShouldLoad ),
    Type( other.Type ) {
    
}

RESOURCE_PROXY::~RESOURCE_PROXY() {
    
}
