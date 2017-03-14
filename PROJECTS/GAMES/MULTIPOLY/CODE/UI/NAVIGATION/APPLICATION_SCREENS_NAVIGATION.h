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
        
        CORE_MEMORY_ObjectSafeDeallocation( Window );
    }
    
    std::map<std::string, NAVIGATION_ITEM * > & GetNavigationChilds() { return NavigationChilds; }
    
    GRAPHIC_UI_FRAME * GetFrame() {
        
        return Window;
    }
    
    void SetFrame( GRAPHIC_UI_FRAME * frame ) {
        
        Window = frame;
    }
    
    void Release() {
        
        CORE_MEMORY_ObjectSafeDeallocation( Window );
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
    bool NavigateBackAsyncWithAnimation();

    template <typename __SCREEN_TYPE__>
    void DisplayModal(const char * modal_name, const CORE_MATH_VECTOR & size ) {

        auto item = GetNextItemForNavigation<__SCREEN_TYPE__>( modal_name );
        item->GetFrame()->OnViewAppearing();
        
        if ( CurrentNavigationItem != NULL ) {
            
            item->SetParentNavigationItem( CurrentNavigationItem );
            GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(CurrentNavigationItem->GetScreenName().c_str());
            CurrentNavigationItem->GetFrame()->OnViewDisappearing();
            CurrentNavigationItem->GetNavigationChilds()[std::string(modal_name)] = item;
        }
        
        CurrentNavigationItem = item;
        
        GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(CurrentNavigationItem->GetFrame(), modal_name);
    }

    template<typename __SCREEN_TYPE__>
    void NavigateToAsync(const char * screen_name ) {
        
        CORE_PARALLEL_TASK_BEGIN(this, screen_name)
            auto item = GetNextItemForNavigation<__SCREEN_TYPE__>( screen_name );
        
            item->GetFrame()->OnViewAppearing();
        
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex())
                if ( CurrentNavigationItem != NULL ) {
                    
                    item->SetParentNavigationItem( CurrentNavigationItem );
                    GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(CurrentNavigationItem->GetScreenName().c_str());
                    CurrentNavigationItem->GetFrame()->OnViewDisappearing();
                    CurrentNavigationItem->GetNavigationChilds()[std::string(screen_name)] = item;
                }
                
                CurrentNavigationItem = item;
            
                GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(CurrentNavigationItem->GetFrame(), screen_name);
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
    }

    template<typename SCREEN_TYPE>
    GRAPHIC_UI_FRAME & InitializeNavigation(const char * screen_name) {
        
        CurrentNavigationItem = CreateItemForNavigation<SCREEN_TYPE>( screen_name );
        
        GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(CurrentNavigationItem->GetFrame(), screen_name);
        
        return *CurrentNavigationItem->GetFrame();
    }

private :

    NAVIGATION_ITEM * GetPreviousItem() {
        return CurrentNavigationItem->GetParentNavigationItem();
    }

    template<typename SCREEN_TYPE>
    NAVIGATION_ITEM * GetNextItemForNavigation( const char * screen_name ) {
        
        NAVIGATION_ITEM * item = CurrentNavigationItem->GetNavigationChilds()[std::string(screen_name)];
        
        if ( item == NULL ) {
            
            auto item = CreateItemForNavigation<SCREEN_TYPE>( screen_name );
            
            item->GetFrame()->GetPlacement().Initialize(
                                                        NULL,
                                                        CORE_MATH_VECTOR::Zero,
                                                        CORE_MATH_VECTOR( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().X(),
                                                                         GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().Y() ),
                                                        GRAPHIC_UI_Center );
            
            item->GetFrame()->Initialize();
            
            return item;
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
