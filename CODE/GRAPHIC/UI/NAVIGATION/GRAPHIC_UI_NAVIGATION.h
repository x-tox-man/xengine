//
//  APPLICATION_SCREENS_NAVIGATION.hpp
//  GAME-ENGINE
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
#include "CORE_PARALLEL.h"
#include "CORE_APPLICATION.h"

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
    
    inline std::map<std::string, NAVIGATION_ITEM * > GetNavigationChilds() { return NavigationChilds; }
    inline GRAPHIC_UI_FRAME * GetFrame() { return Window; }
    inline void SetFrame( GRAPHIC_UI_FRAME * frame ) { Window = frame; }
    
    void Release() {
        
        CORE_MEMORY_ObjectSafeDeallocation( Window );
    }
    
    inline NAVIGATION_ITEM * GetParentNavigationItem() { return ParentNavigationItem; }
    inline void SetParentNavigationItem(NAVIGATION_ITEM * item) { ParentNavigationItem = item; }
    inline std::string GetScreenName() { return ScreenName; }
    
    inline void SetOpenAnimation( const GRAPHIC_UI_ANIMATION & animation ) { OpenAnimation = animation; }
    inline const GRAPHIC_UI_ANIMATION & GetOpenAnimation() const { return OpenAnimation; }
    inline GRAPHIC_UI_ANIMATION & GetOpenAnimation() { return OpenAnimation; }
    
    private :
    
    GRAPHIC_UI_FRAME
        * Window;
    NAVIGATION_ITEM
        * ParentNavigationItem;
    std::map<std::string, NAVIGATION_ITEM * >
        NavigationChilds;
    std::string
        ScreenName;
    GRAPHIC_UI_ANIMATION
        OpenAnimation;
};

XS_CLASS_BEGIN( GRAPHIC_UI_NAVIGATION )

public :

    GRAPHIC_UI_NAVIGATION();
    ~GRAPHIC_UI_NAVIGATION();

    bool NavigateBackAsync();
    bool NavigateBackAsyncWithAnimation( const GRAPHIC_UI_ANIMATION & close_animation, const GRAPHIC_UI_ANIMATION & open_animation );
    void NavigationBackAsyncActionCompletedAnimation( GRAPHIC_UI_ANIMATION * animation );

    template<typename SCREEN_TYPE>
    void NavigateToAsync(const char * screen_name ) {
        
        CORE_PARALLEL_TASK_BEGIN(this, screen_name)
            auto item = GetNextItemForNavigation<SCREEN_TYPE>( screen_name );
        
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
                CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
                item->GetFrame()->Initialize();
                CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GetUILockMutex() )
                if ( CurrentNavigationItem != NULL ) {
                    
                    item->SetParentNavigationItem( CurrentNavigationItem );
                    UnregisterView(CurrentNavigationItem->GetScreenName().c_str());
                    CurrentNavigationItem->GetFrame()->OnViewDisappearing();
                    CurrentNavigationItem->GetFrame()->Finalize();
                    CurrentNavigationItem->GetNavigationChilds()[std::string(screen_name)] = item;
                }
                
                CurrentNavigationItem = item;
            
                RegisterView( CurrentNavigationItem->GetFrame(), screen_name);
                CurrentNavigationItem->GetFrame()->OnViewAppearing();
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
    }

    void NavigationAsyncActionCompletedAnimation( GRAPHIC_UI_ANIMATION * animation ) {
        
        // We are during Update loop
        CORE_PARALLEL_TASK_BEGIN(this)
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GetUILockMutex() )
                // TODO: check page is correctly loaded
                if ( CurrentNavigationItem != NULL ) {
                    
                    NewNavigationItem->SetParentNavigationItem( CurrentNavigationItem );
                    UnregisterView(CurrentNavigationItem->GetScreenName().c_str());
                    CurrentNavigationItem->GetFrame()->OnViewDisappearing();
                    CurrentNavigationItem->GetFrame()->Finalize();
                    CurrentNavigationItem->GetNavigationChilds()[ std::string( NewNavigationItem->GetScreenName() )] = NewNavigationItem;
                }
        
                CurrentNavigationItem = NewNavigationItem;
                RegisterView( CurrentNavigationItem->GetFrame(), NewNavigationItem->GetScreenName().c_str() );
                CurrentNavigationItem->GetOpenAnimation().SetElement( CurrentNavigationItem->GetFrame() );
                CurrentNavigationItem->GetOpenAnimation().Update( 0.0f );
                CurrentNavigationItem->GetFrame()->SetAnimation( CurrentNavigationItem->GetOpenAnimation() );
        
                NewNavigationItem = NULL;
        
                CurrentNavigationItem->GetFrame()->OnViewAppearing();
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
    }

    template<typename SCREEN_TYPE>
    void NavigateToAsyncWithAnimation( const char * screen_name, const GRAPHIC_UI_ANIMATION & close_animation, const GRAPHIC_UI_ANIMATION & open_animation ) {
        
        CORE_PARALLEL_TASK_BEGIN(this, screen_name, close_animation, open_animation )
            CORE_HELPERS_CALLBACK_1<GRAPHIC_UI_ANIMATION *>
            callback( &Wrapper1<GRAPHIC_UI_NAVIGATION, GRAPHIC_UI_ANIMATION *, &GRAPHIC_UI_NAVIGATION::NavigationAsyncActionCompletedAnimation>, this );
        
            NewNavigationItem = GetNextItemForNavigation<SCREEN_TYPE>( screen_name );
            NewNavigationItem->SetOpenAnimation( open_animation );
        
            CurrentNavigationItem->GetFrame()->SetAnimation( close_animation );
            CurrentNavigationItem->GetFrame()->GetAnimation().SetCallback( callback );
        
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
                CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
                NewNavigationItem->GetFrame()->Initialize();
                CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        CORE_PARALLEL_TASK_END()
    }

    template<typename SCREEN_TYPE>
    GRAPHIC_UI_FRAME & InitializeNavigation(const char * screen_name) {
        
        CurrentNavigationItem = CreateItemForNavigation<SCREEN_TYPE>( screen_name );
        
        RegisterView( CurrentNavigationItem->GetFrame(), screen_name );
        
        return *CurrentNavigationItem->GetFrame();
    }

    inline NAVIGATION_ITEM * GetCurrentNavigationItem() { return CurrentNavigationItem; }

private :

    void RegisterView( GRAPHIC_UI_FRAME * view, const char * screen_name );
    void UnregisterView( const char * screen_name );
    CORE_PARALLEL_LOCK_MUTEX & GetUILockMutex();

    NAVIGATION_ITEM * GetPreviousItem() {
        return CurrentNavigationItem->GetParentNavigationItem();
    }

    template<typename SCREEN_TYPE>
    NAVIGATION_ITEM * GetNextItemForNavigation( const char * screen_name ) {
        
        NAVIGATION_ITEM * item = NavigationItemsTable[std::string( screen_name ) ];
        
        if ( item == NULL ) {
            
            return CreateItemForNavigation< SCREEN_TYPE >( screen_name );
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

    NAVIGATION_ITEM
        * CurrentNavigationItem,
        * NewNavigationItem;
    std::map<std::string, NAVIGATION_ITEM * >
        NavigationItemsTable;

XS_CLASS_END

#endif /* APPLICATION_SCREENS_NAVIGATION_hpp */
