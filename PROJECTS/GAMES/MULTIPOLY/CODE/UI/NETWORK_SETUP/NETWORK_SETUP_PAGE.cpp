//
//  NETWORK_SETUP_PAGE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_SETUP_PAGE.h"
#include "NETWORK_SETUP_PLAYER_CELL.h"
#include "GLOBAL_RESOURCES.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "MULTIPOLY_APPLICATION.h"

NETWORK_SETUP_PAGE::NETWORK_SETUP_PAGE() :
    GRAPHIC_UI_FRAME(),
    PlayersListAdapter( NULL ),
    PlayersList(),
    Presenter() {
    
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
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
        auto ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"),
                                                                               CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
        
        auto button_render_state = new GRAPHIC_UI_RENDER_STYLE(GLOBAL_RESOURCES::CreateUIPlanShape( ui_textured_shader_effect ), GLOBAL_RESOURCES::CreateTextureBlockFromImagePath( "button_start" ) ) ;
        
        auto start_button = new GRAPHIC_UI_ELEMENT();
        start_button->GetPlacement().SetAnchor(GRAPHIC_UI_Right);
        start_button->SetPosition( CORE_MATH_VECTOR(-25.0f, 0.0f) );
        start_button->GetPlacement().SetSize( CORE_MATH_VECTOR(64.0f, 64.0f ) );
        start_button->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, button_render_state);
        start_button->Initialize();
        
        AddObject(start_button);
    
        printf( "game init DONE 0");
        
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
    
        NETWORK_SETUP_PLAYER_CELL * item_template = (NETWORK_SETUP_PLAYER_CELL*) new NETWORK_SETUP_PLAYER_CELL();
        item_template->Initialize();
        
        auto players_list = new GRAPHIC_UI_FRAME();
        players_list->GetPlacement().SetAnchor(GRAPHIC_UI_BottomLeft);
        players_list->GetPlacement().SetSize( CORE_MATH_VECTOR(600.0f, 300.0f) );
        players_list->SetPosition( CORE_MATH_VECTOR(25.0f, 25.0f) );
        players_list->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().PageFrameRenderStyle );
        
        PlayersListAdapter = new NETWORK_SETUP_PLAYER_LIST_ADAPTER(players_list, item_template);
        PlayersListAdapter->SetCollection(&PlayersList);
        
        players_list->SetAdapter(PlayersListAdapter);
        players_list->Initialize();
        
        AddObject(players_list);
    
    
        OnPlacementPropertyChanged();
    
        //TODO:
        /*if (((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->IsClient() ) {
            
            Presenter = new APPLICATION_CLIENT_PRESENTER( &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetClient() );
        }
        else {
            
            Presenter = new APPLICATION_SERVER_PRESENTER( &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetServer() );
        }*/
        
        Presenter.Initialize( this );
        Presenter.BindAction( start_button,
                              new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<NETWORK_SETUP_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &NETWORK_SETUP_PRESENTER::StartGameButtonClicked >, &Presenter) );
        Presenter.BindAction( back_button,
                              new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<NETWORK_SETUP_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &NETWORK_SETUP_PRESENTER::OnBackButtonClicked >, &Presenter) );
    
        Presenter.Configure();
    
        OnPlacementPropertyChanged();
        GRAPHIC_UI_FRAME::Initialize();
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    
    printf( "game init DONE 4");
}

void NETWORK_SETUP_PAGE::Update( const float time_step ) {
    
    Presenter.Update( time_step );
}

