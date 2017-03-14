//
//  NETWORK_BROWSER_PAGE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_BROWSER_PAGE.h"
#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "NETWORK_BROWSER_LOBBY_CELL.h"
#include "NETWORK_SETUP_PAGE.h"

NETWORK_BROWSER_PAGE::NETWORK_BROWSER_PAGE() :
    GRAPHIC_UI_FRAME(),
    Presenter() {
    
}

NETWORK_BROWSER_PAGE::~NETWORK_BROWSER_PAGE() {
    
}

void NETWORK_BROWSER_PAGE::Initialize() {
    
    NETWORK_BROWSER_LOBBY_CELL * item_template = new NETWORK_BROWSER_LOBBY_CELL();
    item_template->Initialize();
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    GRAPHIC_UI_FRAME * list_frame = new GRAPHIC_UI_FRAME;
    
    CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO *> callback( &Wrapper1< NETWORK_BROWSER_PRESENTER , NETWORK_REMOTE_SERVER_INFO *, &NETWORK_BROWSER_PRESENTER::ConnectToServer >, &Presenter );
    
    ListAdapter = new NETWORK_BROWSER_LIST_ADAPTER( list_frame, item_template );
    ListAdapter->SetServerSelectedCallback( callback );
    
    list_frame->GetPlacement().SetSize( CORE_MATH_VECTOR( 500.0f, 500.0f ) );
    list_frame->SetAdapter( ListAdapter );
    
    auto back_button = new GRAPHIC_UI_ELEMENT();
    
    back_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
    back_button->SetPosition( CORE_MATH_VECTOR(0.0f, 0.0f) );
    back_button->GetPlacement().SetSize( CORE_MATH_VECTOR(128.0f, 128.0f ) );
    back_button->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::CreateRenderStyleFromTextureName( "back_button" ) );
    back_button->Initialize();
    
    auto start_lobby_button = new GRAPHIC_UI_ELEMENT();
    
    start_lobby_button->GetPlacement().SetAnchor( GRAPHIC_UI_Bottom );
    start_lobby_button->SetPosition( CORE_MATH_VECTOR(0.0f, 0.0f) );
    start_lobby_button->GetPlacement().SetSize( CORE_MATH_VECTOR(128.0f, 128.0f ) );
    start_lobby_button->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::CreateRenderStyleFromTextureName( "server_icon" ) );
    start_lobby_button->Initialize();
    
    Presenter.Initialize( this );
    Presenter.SetListAdapter( ListAdapter );
    Presenter.BindAction( back_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<NETWORK_BROWSER_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &NETWORK_BROWSER_PRESENTER::OnBackButtonClicked >, &Presenter) );
    Presenter.BindAction( start_lobby_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<NETWORK_BROWSER_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &NETWORK_BROWSER_PRESENTER::OnStartLobbyButtonPressed >, &Presenter) );
    Presenter.Configure();
    
    list_frame->Initialize();
    
    AddObject( start_lobby_button );
    AddObject( back_button );
    SetObjectForIdentifier( IdServerList, list_frame );
    
    OnPlacementPropertyChanged();
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
        GRAPHIC_UI_FRAME::Initialize();
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void NETWORK_BROWSER_PAGE::Finalize() {
    
    GRAPHIC_UI_FRAME::Finalize();
}

void NETWORK_BROWSER_PAGE::NETWORK_BROWSER_PAGE::OnViewAppearing() {
    
    Presenter.Configure();
}

CORE_HELPERS_IDENTIFIER
    NETWORK_BROWSER_PAGE::IdServerList( "NB:ServerList" );
