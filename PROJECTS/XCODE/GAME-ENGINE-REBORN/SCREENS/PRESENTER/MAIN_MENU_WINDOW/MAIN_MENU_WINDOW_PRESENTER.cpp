//
//  MAIN_MENU_WINDOW_PRESENTER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "MAIN_MENU_WINDOW_PRESENTER.h"
#include "Application.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h"
#include "APPLICATION_NETWORK_BROWSER.h"
#include "APPLICATION_MAIN_WINDOW.h"

MAIN_MENU_WINDOW_PRESENTER::MAIN_MENU_WINDOW_PRESENTER() :
    GRAPHIC_UI_PRESENTER() {
    
}

MAIN_MENU_WINDOW_PRESENTER::~MAIN_MENU_WINDOW_PRESENTER() {
    
}

void MAIN_MENU_WINDOW_PRESENTER::Configure() {
    
}

void MAIN_MENU_WINDOW_PRESENTER::StartLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartLobby ]->SetVisible( false );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartServer ]->SetVisible( true );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartClient ]->SetVisible( true );
    }
}

void MAIN_MENU_WINDOW_PRESENTER::StartServerButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Server = &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetServer();
        
        Server->Initialize(1.0f / 25.0f );
        IsClient = false;
        
        ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->SetItIsClient( false );
        ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->SetItIsServer( true );
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_MULTIPLAYER_GAME_CONFIGURATION>( "NetworkGameRoom" );
        
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartLobby ]->SetVisible( true );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartServer ]->SetVisible( false );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartClient ]->SetVisible( false );
    }
}

void MAIN_MENU_WINDOW_PRESENTER::StartClientButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_NETWORK_BROWSER>( "NetworkBrowser" );
        
        Client = &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetClient();
        Client->Initialize();
        
        IsClient = true;
        
        ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->SetItIsClient( IsClient );
        
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartLobby ]->SetVisible( true );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartServer ]->SetVisible( false );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartClient ]->SetVisible( false );
        
        /*NamedElementTable[ IdStartClient ]->SetVisible( false );
         NamedElementTable[ IdStartServer ]->SetVisible( false );
         NamedElementTable[ IdStopLobby ]->SetVisible( true );
         NamedElementTable[ IdSendCommand ]->SetVisible( true );*/
    }
}

void MAIN_MENU_WINDOW_PRESENTER::StopLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        if ( IsClient ) {
            Client->Disconnect();
            Client->Finalize();
        }
        
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStopLobby ]->SetVisible( false );
        GetView()->GetNamedElementTable()[ APPLICATION_MAIN_WINDOW::IdStartLobby ]->SetVisible( true );
    }
}

void MAIN_MENU_WINDOW_PRESENTER::SendCommandButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        abort();
        /*APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY * action = new APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY;
         
         action->NewPosition = CORE_MATH_VECTOR(10.0f, 1.0f, 1.0f, 1.0f);
         action->EntityToMove = NULL;
         
         CORE_TIMELINE_EVENT * event = new CORE_TIMELINE_EVENT();
         
         event->Setup( 10.0f, 0.0f, CORE_HELPERS_UNIQUE_IDENTIFIER( "TESTOUILLE"), action );
         
         CORE_DATA_STREAM
         stream;
         
         const char * string = "MOV_COMMAND_1";
         
         stream.Open();
         stream.InputBytes( string, ( int ) strlen( string ) );
         
         stream.Close();
         stream.ResetOffset();
         
         //XS_CLASS_SERIALIZER<CORE_MATH_VECTOR>::Serialize< std::true_type >( action->NewPosition, stream );
         
         if ( IsClient ) {
         Client->DispatchMessageToAllPlayers(stream);
         }
         else {
         Server->DispatchMessageToAllPlayers(stream);
         }*/
    }
}
