//
//  NETWORK_BROWSER_PAGE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_BROWSER_PAGE.h"
#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "NETWORK_BROWSER_LOBBY_CELL.h"
#include "NETWORK_SETUP_PAGE.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "RUN3D_APPLICATION.h"

NETWORK_BROWSER_PAGE::NETWORK_BROWSER_PAGE() :
    R3D_UI_FRAME() {
    
    SetPresenter( new NETWORK_BROWSER_PRESENTER( this ) );
    R3D_APP_PTR->GetNetworkManager().Initialize();
}

NETWORK_BROWSER_PAGE::~NETWORK_BROWSER_PAGE() {
    
}

void NETWORK_BROWSER_PAGE::Initialize() {
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
        NETWORK_BROWSER_LOBBY_CELL * item_template = new NETWORK_BROWSER_LOBBY_CELL();
        item_template->Initialize();
    
        GRAPHIC_UI_FRAME * list_frame = new GRAPHIC_UI_FRAME;
    
        CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO *> callback( &Wrapper1< NETWORK_BROWSER_PRESENTER , NETWORK_REMOTE_SERVER_INFO *, &NETWORK_BROWSER_PRESENTER::ConnectToServer >, &Presenter );
    
        ListAdapter = new NETWORK_BROWSER_LIST_ADAPTER( list_frame, item_template );
        ListAdapter->SetServerSelectedCallback( callback );
    
        list_frame->GetPlacement().SetSize( CORE_MATH_VECTOR( 500.0f, 500.0f ) );
        list_frame->SetAdapter( ListAdapter );
    
        auto start_lobby_button = new UI_BASE_BUTTON;
    
        start_lobby_button->GetPlacement().SetAnchor( GRAPHIC_UI_Bottom );
        start_lobby_button->SetPosition( CORE_MATH_VECTOR(0.0f, 0.0f) );
        start_lobby_button->GetPlacement().SetSize( CORE_MATH_VECTOR(128.0f, 128.0f ) );
    
        ( ( NETWORK_BROWSER_PRESENTER::PTR ) Presenter)->SetListAdapter( ListAdapter );
    
        Presenter->BindAction<NETWORK_BROWSER_PRESENTER, &NETWORK_BROWSER_PRESENTER::OnStartLobbyButtonPressed>(start_lobby_button, (NETWORK_BROWSER_PRESENTER*) Presenter);
    
        AddObject( start_lobby_button );
        //SetObjectForIdentifier( IdServerList, list_frame );
    
    
        R3D_UI_FRAME::Initialize();
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void NETWORK_BROWSER_PAGE::Finalize() {
    
    GRAPHIC_UI_FRAME::Finalize();
}

CORE_HELPERS_IDENTIFIER
    NETWORK_BROWSER_PAGE::IdServerList( "NB:ServerList" );
