//
//  RESOURCE_PROXY.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_PROXY.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( RESOURCE_PROXY )
    XS_DEFINE_ClassMember( CORE_HELPERS_IDENTIFIER , Identifier )
    XS_DEFINE_ClassMember( RESOURCE_TYPE , Type )
    XS_DEFINE_ClassMember(bool , ItShouldLoad )
XS_END_INTERNAL_MEMORY_LAYOUT

RESOURCE_PROXY::RESOURCE_PROXY()  :
    Identifier(),
    Resource( NULL ),
    ItShouldLoad( true ) {
    
}

RESOURCE_PROXY::RESOURCE_PROXY(BASE_RESOURCE * Resource) :
    Identifier(),
    Resource( Resource ),
    ItShouldLoad( true ) {
    
}

RESOURCE_PROXY::~RESOURCE_PROXY() {
    
}
