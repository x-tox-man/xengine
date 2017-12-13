//
//  APPLICATION_SCREENS_NAVIGATION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_NAVIGATION.h"
#include "GRAPHIC_UI_ANIMATION.h"
#include "GRAPHIC_UI_SYSTEM.h"

GRAPHIC_UI_NAVIGATION::GRAPHIC_UI_NAVIGATION() {
    
}

GRAPHIC_UI_NAVIGATION::~GRAPHIC_UI_NAVIGATION() {
    
    std::map<std::string, NAVIGATION_ITEM * >::iterator it = NavigationItemsTable.begin();
    
    while (it != NavigationItemsTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( it->second );
        
        it++;
    }
    
    NavigationItemsTable.clear();
}

bool GRAPHIC_UI_NAVIGATION::NavigateBackAsync() {
    
    auto item = GetPreviousItem();
    
    if ( item == NULL ) {
        return false;
    }
    else {
        
        CORE_PARALLEL_TASK_BEGIN(this, item)
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex())
            if ( this->CurrentNavigationItem != NULL ) {
                
                GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(this->CurrentNavigationItem->GetScreenName().c_str());
                this->CurrentNavigationItem->GetFrame()->OnViewDisappearing();
            }
        
            this->CurrentNavigationItem = item;
            this->CurrentNavigationItem->GetFrame()->OnViewAppearing();
        
            GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(this->CurrentNavigationItem->GetFrame(), CurrentNavigationItem->GetScreenName().c_str());
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
        
        return true;
    }
    
    return true;
}

void GRAPHIC_UI_NAVIGATION::RegisterView( GRAPHIC_UI_FRAME * view, const char * screen_name ) {
    
    GRAPHIC_UI_SYSTEM::GetInstance().RegisterView( view, screen_name);
}

void GRAPHIC_UI_NAVIGATION::UnregisterView( const char * screen_name ) {
    
    GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen( screen_name );
}

CORE_PARALLEL_LOCK_MUTEX & GRAPHIC_UI_NAVIGATION::GetUILockMutex() {
    
    return GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex();
}
