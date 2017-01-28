//
//  GRAPHIC_UI_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 20/12/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "GRAPHIC_UI_ELEMENT_SCRIPTED.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GRAPHIC_UI_SYSTEM )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( GRAPHIC_UI_FRAME *, GRAPHIC_UI_SYSTEM, GetCurrentScreen )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD( GRAPHIC_UI_SYSTEM &, GRAPHIC_UI_SYSTEM, GetInstance )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GRAPHIC_UI_SYSTEM )

GRAPHIC_UI_SYSTEM::GRAPHIC_UI_SYSTEM() :
    VisibleScreenTable(),
    CurrentScreen( NULL ),
    UISystemLock(),
    ScreenSize() {
    
}

GRAPHIC_UI_SYSTEM::~GRAPHIC_UI_SYSTEM() {

}

void GRAPHIC_UI_SYSTEM::Update( float time_step ) {
    
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_FRAME * >::iterator it;
    
    ScreenMouseCoordinates = PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetCenteredCoordinates();
    
    ScreenMouseCoordinates[ 0 ] *= ScreenSize[ 0 ];
    ScreenMouseCoordinates[ 1 ] *= ScreenSize[ 1 ];
    
    CORE_PARALLEL_LOCK Lock( UISystemLock );
    it = VisibleScreenTable.begin();
    
    const CORE_MATH_VECTOR & coordinates = GRAPHIC_UI_SYSTEM::GetInstance().GetScreenMouseCoordinates();
    
    while ( it != VisibleScreenTable.end()) {
        
        if ( it->second->IsEnabled() ) {
            
            it->second->Hover( coordinates );
            
            if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonClicked() ){
                
                it->second->Click( coordinates );
            }
            it->second->Update( time_step );
        }
        
        it++;
    }
}

void GRAPHIC_UI_SYSTEM::Render(GRAPHIC_RENDERER & renderer) {
    
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_FRAME * >::iterator it;
    
    CORE_PARALLEL_LOCK Lock( UISystemLock );
    it = VisibleScreenTable.begin();
    
    while ( it != VisibleScreenTable.end()) {
        
        if ( it->second->IsVisible() ) {
            
            it->second->Render( renderer );
        }
        
        it++;
    }
}

void GRAPHIC_UI_SYSTEM::RegisterScreen( GRAPHIC_UI_FRAME * screen, const char * screen_name ) {
    
    VisibleScreenTable[ CORE_HELPERS_IDENTIFIER( screen_name ) ] = screen;
    
    if ( CurrentScreen == NULL ) {
        
        CurrentScreen = screen;
    }
}

void GRAPHIC_UI_SYSTEM::RegisterScritpedScreen( const CORE_FILESYSTEM_PATH & script_path, const char * screen_name ) {
    
    GRAPHIC_UI_FRAME * frame = new GRAPHIC_UI_FRAME;
    
    GRAPHIC_UI_ELEMENT_SCRIPTED * script_element = new GRAPHIC_UI_ELEMENT_SCRIPTED;
    
    frame->SetIdentifier(CORE_HELPERS_IDENTIFIER( screen_name ));
    
    script_element->InitializeFrame( script_path, frame );
    
    VisibleScreenTable[ frame->GetIdentifier() ] = frame;
}

void GRAPHIC_UI_SYSTEM::UnregisterScreen(const char * screen_name) {
    
    VisibleScreenTable.erase(screen_name);
}
