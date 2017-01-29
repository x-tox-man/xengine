//
//  APPLICATION_SCREENS_NAVIGATION.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_SCREENS_NAVIGATION_hpp
#define APPLICATION_SCREENS_NAVIGATION_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_PARALLEL.h"

class NAVIGATION_ITEM {
    
    public :
    
    NAVIGATION_ITEM( std::string & screen_name) :
        Window( NULL ),
        ParentNavigationItem( NULL ),
        NavigationChilds(),
        ScreenName(screen_name) {
        
    }
    
    ~NAVIGATION_ITEM() {
        
    }
    
    std::map<std::string, NAVIGATION_ITEM * > GetNavigationChilds() { return NavigationChilds; }
    
    GRAPHIC_UI_FRAME * GetFrame() {
        
        return Window;
    }
    
    void SetFrame( GRAPHIC_UI_FRAME * frame ) {
        
        Window = frame;
    }
    
    void Release() {
        
        delete Window;
        
        Window = NULL;
    }
    
    NAVIGATION_ITEM * GetParentNavigationItem() { return ParentNavigationItem; }
    void SetParentNavigationItem(NAVIGATION_ITEM * item) { ParentNavigationItem = item; }
    
    std::string GetScreenName() { return ScreenName; }
    
    private :
    
    GRAPHIC_UI_FRAME
        * Window;
    NAVIGATION_ITEM
        * ParentNavigationItem;
    std::map<std::string, NAVIGATION_ITEM * >
        NavigationChilds;
    std::string
        ScreenName;
};

XS_CLASS_BEGIN( APPLICATION_SCREENS_NAVIGATION )

XS_DEFINE_UNIQUE( APPLICATION_SCREENS_NAVIGATION )

public :

    ~APPLICATION_SCREENS_NAVIGATION();
    bool NavigateBackAsync();

    template<typename SCREEN_TYPE>
    void NavigateToAsync(const char * screen_name ) {
        
        CORE_PARALLEL_TASK_BEGIN(this, screen_name)
            auto item = GetNextItemForNavigation<SCREEN_TYPE>( screen_name );
            item->GetFrame()->Initialize();
        
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex())
                if ( CurrentNavigationItem != NULL ) {
                    
                    item->SetParentNavigationItem( CurrentNavigationItem );
                    GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(CurrentNavigationItem->GetScreenName().c_str());
                }
                
                CurrentNavigationItem = item;
            
                GRAPHIC_UI_SYSTEM::GetInstance().RegisterScreen(CurrentNavigationItem->GetFrame(), screen_name);
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
    }

    template<typename SCREEN_TYPE>
    GRAPHIC_UI_FRAME & InitializeNavigation(const char * screen_name) {
        
        CurrentNavigationItem = CreateItemForNavigation<SCREEN_TYPE>( screen_name );
        
        GRAPHIC_UI_SYSTEM::GetInstance().RegisterScreen(CurrentNavigationItem->GetFrame(), screen_name);
        
        return *CurrentNavigationItem->GetFrame();
    }

private :

    NAVIGATION_ITEM * GetPreviousItem() {
        return CurrentNavigationItem->GetParentNavigationItem();
    }

    template<typename SCREEN_TYPE>
    NAVIGATION_ITEM * GetNextItemForNavigation( const char * screen_name ) {
        
        NAVIGATION_ITEM * item = CurrentNavigationItem->GetNavigationChilds()[screen_name];
        
        if ( item == NULL ) {
            
            return CreateItemForNavigation<SCREEN_TYPE>( screen_name );
        }
        
        return item;
    }

    template<typename SCREEN_TYPE>
    NAVIGATION_ITEM * CreateItemForNavigation( const char * screen_name ) {
        
        std::string str(screen_name);
        NAVIGATION_ITEM * item = new NAVIGATION_ITEM(str);
        item->SetFrame(new SCREEN_TYPE() );
        
        NavigationItemsTable[str] = item;
        
        return item;
    }

NAVIGATION_ITEM *
    CurrentNavigationItem;
std::map<std::string, NAVIGATION_ITEM * >
    NavigationItemsTable;

XS_CLASS_END

#endif /* APPLICATION_SCREENS_NAVIGATION_hpp */
