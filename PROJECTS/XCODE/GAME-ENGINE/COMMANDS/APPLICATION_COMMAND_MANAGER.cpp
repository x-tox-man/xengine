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

void APPLICATION_COMMAND_MANAGER::OnTimelineEventAdded( CORE_TIMELINE_EVENT * event ) {
    
    CORE_DATA_STREAM
        stream;
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< CORE_TIMELINE_EVENT, CORE_DATA_STREAM  >::Serialize< std::true_type >( "event", *event, stream );
    
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
