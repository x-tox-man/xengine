//
//  NETWORK_SETUP_PAGE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_SETUP_PAGE.h"
#include "NETWORK_SETUP_PLAYER_CELL.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "RUN3D_APPLICATION.h"
#include "GRAPHIC_UI_HELPER.h"

NETWORK_SETUP_PAGE::NETWORK_SETUP_PAGE() :
    R3D_UI_FRAME(),
    PlayersListAdapter( NULL ),
    PlayersList() {
    
    SetPresenter( new NETWORK_SETUP_PRESENTER( this ) );
}

NETWORK_SETUP_PAGE::~NETWORK_SETUP_PAGE() {
    
    CORE_MEMORY_ObjectSafeDeallocation( PlayersListAdapter );
    
    std::vector< NETWORK_PLAYER * >::iterator it = PlayersList.begin();
    
    while ( it != PlayersList.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        
        it++;
    }
    
    PlayersList.clear();
}

void NETWORK_SETUP_PAGE::Initialize() {
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
        R3D_UI_FRAME::Initialize();
    
        auto start_button = GRAPHIC_UI_HELPER::CreateElement( "start_button" );
        GRAPHIC_UI_HELPER::CreateElementStyleWithContentTexture( start_button, CORE_COLOR_White, "button_start" );
        start_button->GetPlacement().SetAnchor(GRAPHIC_UI_Right);
        start_button->SetPosition( CORE_MATH_VECTOR(-25.0f, 0.0f) );
        start_button->GetPlacement().SetSize( CORE_MATH_VECTOR(64.0f, 64.0f ) );
    
        auto back_button = GRAPHIC_UI_HELPER::CreateElement( "BackButton" );
        back_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 64.0f ) );
        GRAPHIC_UI_HELPER::CreateElementStyleWithContentTexture( back_button, CORE_COLOR_White, CORE_HELPERS_IDENTIFIER( "frameBorder3" ) );
    
        AddObject( start_button );
        AddObject( back_button );

        auto detail_frame_1 = GRAPHIC_UI_HELPER::CreateElement( "detail_frame_1" );
        GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor( detail_frame_1, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frameBorder3" );
        detail_frame_1->GetPlacement().SetAnchor( GRAPHIC_UI_TopLeft );
        detail_frame_1->GetPlacement().SetSize( CORE_MATH_VECTOR(400.0f, 200.0f) );
        detail_frame_1->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
        /*{
            auto detail_text = new GRAPHIC_UI_ELEMENT();
            detail_text->GetPlacement().SetAnchor( GRAPHIC_UI_TopLeft );
            detail_text->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
            detail_text->Initialize();
            
            detail_frame_1->AddObject(detail_text);
        }
        
        AddObject(detail_frame_1);*/
        
        auto detail_frame_2 = GRAPHIC_UI_HELPER::CreateElement( "detail_frame_2" );
        GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor( detail_frame_2, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frameBorder3" );
        detail_frame_2->GetPlacement().SetAnchor(GRAPHIC_UI_TopRight);
        detail_frame_2->GetPlacement().SetSize( CORE_MATH_VECTOR(400.0f, 200.0f) );
        detail_frame_2->SetPosition( CORE_MATH_VECTOR(-25.0f, -25.0f) );
        /*{
            auto detail_text2 = new GRAPHIC_UI_ELEMENT();
            detail_text2->GetPlacement().SetAnchor(GRAPHIC_UI_TopLeft);
            detail_text2->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
            detail_text2->Initialize();
            
            detail_frame_2->AddObject(detail_text2);
            
            auto change_type_button = new GRAPHIC_UI_ELEMENT();
            change_type_button->GetPlacement().SetAnchor(GRAPHIC_UI_TopLeft);
            change_type_button->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
            change_type_button->Initialize();
            
            detail_frame_2->AddObject(change_type_button);
        }*/
        
        AddObject(detail_frame_2);
    
        NETWORK_SETUP_PLAYER_CELL * item_template = (NETWORK_SETUP_PLAYER_CELL*) new NETWORK_SETUP_PLAYER_CELL();
        item_template->Initialize();
    
        auto players_list = GRAPHIC_UI_HELPER::CreateFrame( "players_list" );
        GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor( players_list, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frameBorder3" );
        players_list->GetPlacement().SetAnchor(GRAPHIC_UI_BottomLeft);
        players_list->GetPlacement().SetSize( CORE_MATH_VECTOR(600.0f, 300.0f) );
        players_list->SetPosition( CORE_MATH_VECTOR(25.0f, 25.0f) );
        
        PlayersListAdapter = new NETWORK_SETUP_PLAYER_LIST_ADAPTER( players_list, item_template );
        PlayersListAdapter->SetCollection( &PlayersList );
        
        players_list->SetAdapter(PlayersListAdapter);
        players_list->Initialize();
        
        AddObject(players_list);
    
        //TODO:
        /*if (((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->IsClient() ) {
            
            Presenter = new APPLICATION_CLIENT_PRESENTER( &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetClient() );
        }
        else {
            
            Presenter = new APPLICATION_SERVER_PRESENTER( &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetServer() );
        }*/
    
        Presenter->BindAction<NETWORK_SETUP_PRESENTER, &NETWORK_SETUP_PRESENTER::StartGameButtonClicked>( start_button, (NETWORK_SETUP_PRESENTER*) Presenter);
        Presenter->BindAction<NETWORK_SETUP_PRESENTER, &NETWORK_SETUP_PRESENTER::OnBackButtonClicked>( back_button, (NETWORK_SETUP_PRESENTER*) Presenter);
    
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void NETWORK_SETUP_PAGE::Update( const float time_step ) {
    
}

