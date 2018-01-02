//
//  NETWORK_SERVER_INFO.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_SERVER_INFO.h"
#include "CORE_DATA_TYPES.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( NETWORK_SERVER_INFO )
XS_DEFINE_ClassMemberArray( "Name", char, (char **) &Name, ((Name == NULL) ? 0 : (int)strlen( Name ) ) )
    XS_DEFINE_ClassMemberArray( "GameTitle", char, (char **) &GameTitle, ((GameTitle == NULL) ? 0 : (int)strlen( GameTitle ) ) )
    XS_DEFINE_ClassMemberArray( "Adress", char, (char **) &Adress, ((Adress == NULL) ? 0 : (int)strlen( Adress ) ) )
    XS_DEFINE_ClassMember( "PlayersCount", int, PlayersCount )
    XS_DEFINE_ClassMember( "MaxPlayers", int, MaxPlayers )
    XS_DEFINE_ClassMember( "AppVersion", int, AppVersion )
    XS_DEFINE_ClassMember( "SpecificGameInfo", CORE_DATA_BUFFER, SpecificGameInfo )
XS_END_INTERNAL_MEMORY_LAYOUT

NETWORK_SERVER_INFO::NETWORK_SERVER_INFO() :
    Name(NULL),
    GameTitle(NULL),
    Adress(NULL),
    PlayersCount(0),
    MaxPlayers(0),
    AppVersion(0) {
    
}

NETWORK_SERVER_INFO::NETWORK_SERVER_INFO(const char * name, const char * title, const char * adress, int players, int max) {
    
    CORE_DATA_COPY_STRING(Name, name);
    CORE_DATA_COPY_STRING(GameTitle, title);
    CORE_DATA_COPY_STRING(Adress, adress);
    PlayersCount = players;
    MaxPlayers = max;
}

NETWORK_SERVER_INFO::~NETWORK_SERVER_INFO() {
    
    CORE_MEMORY_ObjectSafeDeallocation( Name );
    CORE_MEMORY_ObjectSafeDeallocation(GameTitle);
    CORE_MEMORY_ObjectSafeDeallocation( Adress );
}
