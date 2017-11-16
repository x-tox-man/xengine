//
//  CORE_TIMELINE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_TIMELINE.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_TIMELINE )
    XS_DEFINE_ClassMember( "TimeOffset", float, TimeOffset )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_TIMELINE::CORE_TIMELINE() :
    TimeOffset( 0.0f ),
    EventTable(),
    CurrentItem(),
    OnEventAddedCallback(),
    OnEventCancelledCallback() {

    CurrentItem = EventTable.begin();
}

CORE_TIMELINE::~CORE_TIMELINE() {

}

void CORE_TIMELINE::Update( float time_step ) {
    
    TimeOffset += time_step;
    
    // GetEvents to trigger
    
    std::list< CORE_TIMELINE_EVENT * >::iterator update_iterator = CurrentItem;
    
    while ( update_iterator != EventTable.end() ) {
        
        if ( !(*update_iterator)->HasEnded() && (*update_iterator)->GetEnd() <= TimeOffset ) {
            
            (*update_iterator)->Complete();
        }
        
        update_iterator++;
    }
}

void CORE_TIMELINE::Reset() {
    
    TimeOffset = 0.0f;
    
    EventTable.clear();
    
    CurrentItem = EventTable.begin();
}

void CORE_TIMELINE::InsertNewEvent( CORE_TIMELINE_EVENT * event ) {
    
    if ( EventTable.size() == 0 ) {
        
        EventTable.push_back( event );
        
        CurrentItem = EventTable.begin();
    }
    
    if ( (*CurrentItem)->GetStart() > event->GetStart() ) {
        
        InsertPreviousEvent( event, CurrentItem );
    }
    else if ((*CurrentItem)->GetStart() < event->GetStart() ) {
        
        InsertNextEvent( event, CurrentItem );
    }
    else {
        
        EventTable.insert( CurrentItem, event );
        
        CurrentItem--;
    }
}

void CORE_TIMELINE::CancelEvent( CORE_TIMELINE_EVENT * item ) {
    
    EventTable.remove( item );
}

void CORE_TIMELINE::InsertNextEvent( CORE_TIMELINE_EVENT * event, std::list< CORE_TIMELINE_EVENT * >::iterator existing_event ){
    
    existing_event++;
    
    if ( (*CurrentItem)->GetStart() > event->GetStart() ) {
        
        return InsertNextEvent( event, CurrentItem );
    }
    else {
        
        if ( existing_event == EventTable.end() ) {
            
            EventTable.push_back( event );
            
            EventTable.end();
        }
        else {
            
            existing_event++;
            EventTable.insert( existing_event, event );
        }
    }
}

void CORE_TIMELINE::InsertPreviousEvent( CORE_TIMELINE_EVENT * event, std::list< CORE_TIMELINE_EVENT * >::iterator existing_event ) {
    
    existing_event--;
    
    if ( (*CurrentItem)->GetStart() < event->GetStart() ) {
        
        InsertPreviousEvent( event, CurrentItem );
    }
    else {
        
        EventTable.insert( existing_event, event );
        
        CurrentItem = existing_event--;
    }
}
