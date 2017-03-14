//
//  MAIN_MENU_PAGE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "MAIN_MENU_PAGE.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "GRAPHIC_UI_FRAME_ADAPTER.h"

MAIN_MENU_PAGE::MAIN_MENU_PAGE() :
    GRAPHIC_UI_FRAME(),
    Presenter( new MAIN_MENU_PRESENTER() ) {
    
    Presenter->Initialize( this );
}

MAIN_MENU_PAGE::~MAIN_MENU_PAGE() {
    
}

void MAIN_MENU_PAGE::Initialize() {
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    auto start_single_game_button = new GRAPHIC_UI_TEXT;
    start_single_game_button->SetFont( font );
    start_single_game_button->SetColor(CORE_COLOR_Red);
    start_single_game_button->SetText( "Solo" );
    start_single_game_button->SetSize( 1.0f );
    
    auto start_multiplayer_game_button = new GRAPHIC_UI_TEXT;
    start_multiplayer_game_button->SetFont( font );
    start_multiplayer_game_button->SetColor(CORE_COLOR_Red);
    start_multiplayer_game_button->SetText( "Multijoueur" );
    start_multiplayer_game_button->SetSize( 1.0f );
    
    auto option_button = new GRAPHIC_UI_TEXT;
    option_button->SetFont( font );
    option_button->SetColor(CORE_COLOR_Red);
    option_button->SetText( "Options" );
    option_button->SetSize( 1.0f );
    
    auto about = new GRAPHIC_UI_TEXT;
    about->SetFont( font );
    about->SetColor(CORE_COLOR_Red);
    about->SetText( "About" );
    about->SetSize( 1.0f );
    
    start_single_game_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 128.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    start_multiplayer_game_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 32.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    option_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, -32.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    about->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, -128.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    SetAdapter( new GRAPHIC_UI_FRAME_ADAPTER() );
    
    AddObject( start_single_game_button );
    AddObject( start_multiplayer_game_button );
    AddObject( option_button );
    AddObject( about );
    
    OnPlacementPropertyChanged();
    
    Presenter->BindAction( start_single_game_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_PRESENTER::StartSingleGameButtonClicked >, Presenter) );
    Presenter->BindAction( start_multiplayer_game_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_PRESENTER::StartBrowsingMultiplayerButtonClicked >, Presenter) );
    Presenter->Configure();
    
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
        GRAPHIC_UI_FRAME::Initialize();
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void MAIN_MENU_PAGE::OnViewAppearing() {
    
    Presenter->Configure();
}
