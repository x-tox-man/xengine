//
//  GAMEPLAY_ACTION_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_ACTION_SYSTEM.h"

GAMEPLAY_ACTION_SYSTEM::GAMEPLAY_ACTION_SYSTEM() {
    
}

void GAMEPLAY_ACTION_SYSTEM::ProcessEvent( CORE_TIMELINE_EVENT * event ) {
    event->Complete();
}

void GAMEPLAY_ACTION_SYSTEM::OnTimelineEventAdded( CORE_TIMELINE_EVENT * event ) {
    
}
