//
//  APPLICATION_COMMAND_MANAGER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_COMMAND_MANAGER.h"

APPLICATION_COMMAND_MANAGER::APPLICATION_COMMAND_MANAGER() : Timeline() {
    
}

APPLICATION_COMMAND_MANAGER::~APPLICATION_COMMAND_MANAGER() {
    
}

void APPLICATION_COMMAND_MANAGER::CommandMoveCube( const CORE_MATH_VECTOR & new_position, GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    /*entity->SetPosition( new_position );
     
     APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY * action = new APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY;
     
     action->NewPosition = new_position;
     action->EntityToMove = entity;
     
     CORE_TIMELINE_EVENT * event = new CORE_TIMELINE_EVENT();
     
     event->Setup( ApplicationTimeline.GetTimeOffset(), 0.0f, CORE_HELPERS_UNIQUE_IDENTIFIER(), action );
     
     ApplicationTimeline.InsertNewEvent( event );
     
     if ( Lobby.ItIsClient || Lobby.ItIsServer ) {
     
     CORE_DATA_STREAM
     stream;
     
     const char * string = "MOV_COMMAND_1";
     
     stream.Open();
     stream.InputBytes( string, ( int ) strlen( string ) );
     stream<< ( int ) entity->GetIndex();
     
     XS_CLASS_SERIALIZER<CORE_MATH_VECTOR>::Serialize< std::true_type >( new_position, stream );
     
     stream.Close();
     stream.ResetOffset();
     
     Lobby.SendTcpCommand( stream );
     }*/
}

void APPLICATION_COMMAND_MANAGER::OnTimelineEventAdded( CORE_TIMELINE_EVENT * event ) {
    
    CORE_DATA_STREAM
        stream;
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< CORE_TIMELINE_EVENT, CORE_DATA_STREAM  >::Serialize< std::true_type >( *event, stream );
    
    stream.Close();
    stream.ResetOffset();
}

void APPLICATION_COMMAND_MANAGER::ProcessEvent( CORE_TIMELINE_EVENT * event ) {
    
    if ( event->IsCancelled() ) {
        
    }
    else {
        
        event->Complete();
    }
    
    Timeline.InsertNewEvent( event );
}
