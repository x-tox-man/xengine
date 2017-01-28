//
//  APPLICATION_SCREENS_NAVIGATION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_SCREENS_NAVIGATION.h"

APPLICATION_SCREENS_NAVIGATION::APPLICATION_SCREENS_NAVIGATION() {
    
}

APPLICATION_SCREENS_NAVIGATION::~APPLICATION_SCREENS_NAVIGATION() {
    
}

bool APPLICATION_SCREENS_NAVIGATION::NavigateBackAsync() {
    
    auto item = GetPreviousItem();
    
    if ( item == NULL )
        return false;
    
    CORE_PARALLEL_TASK_BEGIN(this, item)
    
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex())
            if ( CurrentNavigationItem != NULL ) {
                
                GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(CurrentNavigationItem->GetScreenName().c_str());
            }
    
        CurrentNavigationItem = item;

        GRAPHIC_UI_SYSTEM::GetInstance().RegisterScreen(CurrentNavigationItem->GetFrame(), CurrentNavigationItem->GetScreenName().c_str());
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    
    CORE_PARALLEL_TASK_END()
    
    return true;
}
