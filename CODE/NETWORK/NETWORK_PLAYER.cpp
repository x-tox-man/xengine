//
//  NETWORK_PLAYER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_PLAYER.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( NETWORK_PLAYER )
    XS_DEFINE_ClassMember( "IsActive", bool, IsActive )
    XS_DEFINE_ClassMember( "Name", std::string, Name )
    XS_DEFINE_ClassMember( "IsHost", bool, IsHost )
    XS_DEFINE_ClassMember( "IsReady", bool, IsReady )
    XS_DEFINE_ClassMember( "UniqueId", CORE_HELPERS_UNIQUE_IDENTIFIER, UniqueId )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( NETWORK_PLAYER * )

NETWORK_PLAYER::NETWORK_PLAYER() :
    Name(),
    OutGoingMessageQueue(),
    OutGoingMessageQueueIterator(0),
    CurrentNewtorkStream( NULL ),
    UniqueId( "Temporary" ),
    IsActive( false ),
    IsHost( false ),
    IsReady( false ) {
    
}

NETWORK_PLAYER::NETWORK_PLAYER( SERVICE_NETWORK_CONNECTION * connexion, CORE_HELPERS_UNIQUE_IDENTIFIER player_id, bool is_active, bool is_host, std::string & name ) :
    Name( name ),
    OutGoingMessageQueue(),
    OutGoingMessageQueueIterator(0),
    CurrentNewtorkStream( connexion ),
    UniqueId( player_id ),
    IsActive( is_active ),
    IsHost( is_host ) {
    
    for(int i = 0; i < OUTGOING_MESSAGE_QUEUE_SIZE; i++ ) {
        
        OutGoingMessageQueue[i] = NULL;
    }
}

NETWORK_PLAYER::NETWORK_PLAYER(int player_id, bool is_active) :
    Name(),
    OutGoingMessageQueue(),
    OutGoingMessageQueueIterator(0),
    CurrentNewtorkStream( NULL ),
    UniqueId( "Temporary" ),
    IsActive(is_active) {
    
    for(int i = 0; i < OUTGOING_MESSAGE_QUEUE_SIZE; i++ ) {
        
        OutGoingMessageQueue[i] = NULL;
    }
}

void NETWORK_PLAYER::Finalize() {
    
}

NETWORK_PLAYER::~NETWORK_PLAYER() {
    
    for(int i = 0; i < OUTGOING_MESSAGE_QUEUE_SIZE; i++ ) {
        
        if ( OutGoingMessageQueue[i] != NULL ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( OutGoingMessageQueue[i] );
        }
    }
}

CORE_DATA_STREAM & NETWORK_PLAYER::PrepareMessage() {
    
    OutGoingMessage.Reset();
    OutGoingMessage.Open();
    
    for(int i = 0; i < OUTGOING_MESSAGE_QUEUE_SIZE; i++ ) {
        
        if ( OutGoingMessageQueue[i] != NULL ) {
            
            SERVICE_NETWORK_COMMAND * command = OutGoingMessageQueue[i];
            
            command->Address[0] = 192;
            command->Address[1] = 168;
            command->Address[2] = 0;
            command->Address[3] = 12;
            command->Serialize( "command", OutGoingMessage );
            
            CORE_MEMORY_ObjectSafeDeallocation( OutGoingMessageQueue[i] );
        }
    }
    
    return OutGoingMessage;
}

void NETWORK_PLAYER::AppendMessage(SERVICE_NETWORK_COMMAND * message ) {
    
    OutGoingMessageQueue[OutGoingMessageQueueIterator++] = message;
    
    if ( OutGoingMessageQueueIterator == OUTGOING_MESSAGE_QUEUE_SIZE ) {
        
        OutGoingMessageQueueIterator = 0;
    }
}
