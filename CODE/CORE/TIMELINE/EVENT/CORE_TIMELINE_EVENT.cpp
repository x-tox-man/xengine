//
//  CORE_TIMELINE_EVENT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "CORE_TIMELINE_EVENT.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_TIMELINE_EVENT )
    XS_DEFINE_ClassMember( "Start", float, Start )
    XS_DEFINE_ClassMember( "End", float, End )
    XS_DEFINE_ClassMember( "Ended", bool, Ended )
    XS_DEFINE_ClassMember( "Cancelled", bool, Cancelled )
    XS_DEFINE_ClassMember( "Identifier", CORE_HELPERS_UNIQUE_IDENTIFIER, Identifier )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_TIMELINE_EVENT::CORE_TIMELINE_EVENT() :
    Id(0),
    Start( 0.0f ),
    End( 0.0f ),
    Ended( false ),
    Identifier(),
    Command( NULL ) {
    
}

CORE_TIMELINE_EVENT::~CORE_TIMELINE_EVENT() {
    
}

void CORE_TIMELINE_EVENT::Setup( float start, float end, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_TIMELINE_COMMAND * command ) {
    
    Start = start;
    End = end;
    Identifier = identifier;
    Command = command;
}

void CORE_TIMELINE_EVENT::Complete() {
    
    Command->Apply();
    Ended = true;
}
