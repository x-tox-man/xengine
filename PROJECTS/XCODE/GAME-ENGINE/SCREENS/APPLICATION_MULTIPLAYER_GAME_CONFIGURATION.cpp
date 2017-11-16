//
//  APPLICATION_GAME_CONFIGURATION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_SYSTEM.h"

#include "NETWORK_GAME_PLAYER_CELL.h"
#include "GLOBAL_RESOURCES.h"
#include "APPLICATION_SERVER_PRESENTER.h"
#include "APPLICATION_CLIENT_PRESENTER.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h"
#include "Application.h"

APPLICATION_MULTIPLAYER_GAME_CONFIGURATION::APPLICATION_MULTIPLAYER_GAME_CONFIGURATION() :
    GRAPHIC_UI_FRAME(),
    PlayersListAdapter( NULL ),
    PlayersList(),
    Presenter( NULL ) {
    
}

APPLICATION_MULTIPLAYER_GAME_CONFIGURATION::~APPLICATION_MULTIPLAYER_GAME_CONFIGURATION() {
    
    CORE_MEMORY_ObjectSafeDeallocation( PlayersListAdapter );
    CORE_MEMORY_ObjectSafeDeallocation( Presenter );
    
    std::vector< NETWORK_PLAYER * >::iterator it = PlayersList.begin();
    
    while ( it != PlayersList.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        
        it++;
    }
    
    PlayersList.clear();
}

void APPLICATION_MULTIPLAYER_GAME_CONFIGURATION::Initialize() {
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    auto button_render_state = new GRAPHIC_UI_RENDER_STYLE(GLOBAL_RESOURCES::GetInstance().UIPlanObject, &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) ) );
    
    auto start_button = new GRAPHIC_UI_ELEMENT();
    start_button->GetPlacement().SetAnchor(GRAPHIC_UI_Right);
    start_button->SetPosition( CORE_MATH_VECTOR(-25.0f, 0.0f) );
    start_button->GetPlacement().SetSize( CORE_MATH_VECTOR(64.0f, 64.0f ) );
    start_button->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, button_render_state);
    start_button->Initialize();
    
    AddObject(start_button);
    
    auto back_button = new GRAPHIC_UI_ELEMENT();
    
    back_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    back_button->SetPosition( CORE_MATH_VECTOR(-25.0f, 25.0f) );
    back_button->GetPlacement().SetSize( CORE_MATH_VECTOR(64.0f, 64.0f ) );
    back_button->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, button_render_state);
    back_button->Initialize();
    
    AddObject(back_button);
    
    auto detail_frame_1 = new GRAPHIC_UI_FRAME();
    detail_frame_1->GetPlacement().SetAnchor( GRAPHIC_UI_TopLeft );
    detail_frame_1->GetPlacement().SetSize( CORE_MATH_VECTOR(400.0f, 200.0f) );
    detail_frame_1->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
    detail_frame_1->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().FrameRenderStyle );
    {
        auto detail_text = new GRAPHIC_UI_ELEMENT();
        detail_text->GetPlacement().SetAnchor( GRAPHIC_UI_TopLeft );
        detail_text->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
        detail_text->Initialize();
        
        detail_frame_1->AddObject(detail_text);
    }
    
    AddObject(detail_frame_1);
    
    auto detail_frame_2 = new GRAPHIC_UI_FRAME();
    detail_frame_2->GetPlacement().SetAnchor(GRAPHIC_UI_TopRight);
    detail_frame_2->GetPlacement().SetSize( CORE_MATH_VECTOR(400.0f, 200.0f) );
    detail_frame_2->SetPosition( CORE_MATH_VECTOR(-25.0f, -25.0f) );
    detail_frame_2->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().FrameRenderStyle );
    {
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
    }
    
    AddObject(detail_frame_2);
    
    NETWORK_GAME_PLAYER_CELL * item_template = (NETWORK_GAME_PLAYER_CELL*) new NETWORK_GAME_PLAYER_CELL();
    item_template->Initialize();
    
    auto players_list = new GRAPHIC_UI_FRAME();
    players_list->GetPlacement().SetAnchor(GRAPHIC_UI_BottomLeft);
    players_list->GetPlacement().SetSize( CORE_MATH_VECTOR(600.0f, 300.0f) );
    players_list->SetPosition( CORE_MATH_VECTOR(25.0f, 25.0f) );
    players_list->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().PageFrameRenderStyle );
    
    PlayersListAdapter = new NETWORK_GAME_PLAYER_LIST_ADAPTER(players_list, item_template);
    PlayersListAdapter->SetCollection(&PlayersList);
    
    players_list->SetAdapter(PlayersListAdapter);
    players_list->Initialize();
    
    AddObject(players_list);
    
    OnPlacementPropertyChanged();
    
    if (((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->IsClient() ) {
        
        Presenter = new APPLICATION_CLIENT_PRESENTER( &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetClient() );
    }
    else {
        
        Presenter = new APPLICATION_SERVER_PRESENTER( &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetServer() );
    }
    
    Presenter->Initialize( this );
    Presenter->BindAction( start_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER::StartGameButtonClicked >, Presenter) );
    Presenter->BindAction( back_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER::OnBackButtonClicked >, Presenter) );
}

void APPLICATION_MULTIPLAYER_GAME_CONFIGURATION::Update( const float time_step ) {
    
    Presenter->Update( time_step );
}
