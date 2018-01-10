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

GRAPHIC_UI_NAVIGATION::GRAPHIC_UI_NAVIGATION() :
    CurrentNavigationItem( NULL ),
    NewNavigationItem( NULL ),
    NavigationItemsTable() {
    
}

GRAPHIC_UI_NAVIGATION::~GRAPHIC_UI_NAVIGATION() {
    
    std::map<std::string, NAVIGATION_ITEM * >::iterator it = NavigationItemsTable.begin();
    
    while (it != NavigationItemsTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( it->second );
        
        it++;
    }
    
    NavigationItemsTable.clear();
}

bool GRAPHIC_UI_NAVIGATION::NavigateBackAsyncWithAnimation( const GRAPHIC_UI_ANIMATION & close_animation, const GRAPHIC_UI_ANIMATION & open_animation ) {
    
    NewNavigationItem = GetPreviousItem();
    
    if ( NewNavigationItem == NULL ) {
        
        return false;
    }
    else {
        
        CORE_HELPERS_CALLBACK_1<GRAPHIC_UI_ANIMATION *>
            callback( &Wrapper1<GRAPHIC_UI_NAVIGATION, GRAPHIC_UI_ANIMATION *, &GRAPHIC_UI_NAVIGATION::NavigationAsyncActionCompletedAnimation>, this );
        
        CurrentNavigationItem->GetFrame()->SetAnimation( close_animation );
        CurrentNavigationItem->GetFrame()->GetAnimation().SetCallback( callback );
        NewNavigationItem->SetOpenAnimation( open_animation );
        
        CORE_PARALLEL_TASK_BEGIN( this )
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
                CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
                this->NewNavigationItem->GetFrame()->Initialize();
                CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
    }
    
    return true;
}
    
void GRAPHIC_UI_NAVIGATION::NavigationBackAsyncActionCompletedAnimation( GRAPHIC_UI_ANIMATION * animation ) {
    
    CORE_PARALLEL_TASK_BEGIN( this )
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex())
    
            //TODO : check page is correctly loaded
            if ( this->CurrentNavigationItem != NULL ) {
                
                GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(this->CurrentNavigationItem->GetScreenName().c_str());
                this->CurrentNavigationItem->GetFrame()->OnViewDisappearing();
                this->CurrentNavigationItem->GetFrame()->Finalize();
            }
    
            this->CurrentNavigationItem = NewNavigationItem;
    
            this->CurrentNavigationItem->GetFrame()->OnViewAppearing();
    
            GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(this->CurrentNavigationItem->GetFrame(), CurrentNavigationItem->GetScreenName().c_str());
    
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    CORE_PARALLEL_TASK_END()
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
                    this->CurrentNavigationItem->GetFrame()->Finalize();
                }
        
                this->CurrentNavigationItem = item;
        
                CORE_PARALLEL_TASK_BEGIN(this)
                    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
                        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
                        this->CurrentNavigationItem->GetFrame()->Initialize();
                        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
        
                        this->CurrentNavigationItem->GetFrame()->OnViewAppearing();

                        GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(this->CurrentNavigationItem->GetFrame(), CurrentNavigationItem->GetScreenName().c_str());
                    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
                CORE_PARALLEL_TASK_END()
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
