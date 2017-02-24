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

MAIN_MENU_PAGE::MAIN_MENU_PAGE() :
    GRAPHIC_UI_FRAME(),
    Presenter( new MAIN_MENU_PRESENTER() ) {
    
}

MAIN_MENU_PAGE::~MAIN_MENU_PAGE() {
    
}

void MAIN_MENU_PAGE::Initialize() {
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    auto start_single_game_button = new GRAPHIC_UI_TEXT;
    start_single_game_button->SetFont( font );
    start_single_game_button->SetColor(CORE_COLOR_Red);
    start_single_game_button->SetText( "Server" );
    start_single_game_button->SetSize( 12.0f );
    
    auto start_multiplayer_game_button = new GRAPHIC_UI_TEXT;
    start_multiplayer_game_button->SetFont( font );
    start_multiplayer_game_button->SetColor(CORE_COLOR_Red);
    start_multiplayer_game_button->SetText( "Client" );
    start_multiplayer_game_button->SetSize( 12.0f );
    
    start_single_game_button->GetPlacement().Initialize( &GetPlacement(),
                                           CORE_MATH_VECTOR( 0.0f, 160.0f, 0.0f, 1.0f ),
                                           CORE_MATH_VECTOR( 320.0f, 160.0f, 0.0f, 0.0f ),
                                           GRAPHIC_UI_Center );
    start_multiplayer_game_button->GetPlacement().Initialize( &GetPlacement(),
                                            CORE_MATH_VECTOR( 0.0f, -160.0f, 0.0f, 1.0f ),
                                            CORE_MATH_VECTOR( 320.0f, 160.0f, 0.0f, 0.0f ),
                                            GRAPHIC_UI_Center );
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    
    AddObject( start_single_game_button );
    AddObject( start_multiplayer_game_button );
    
    OnPlacementPropertyChanged();
    GRAPHIC_UI_FRAME::Initialize();
    
    Presenter->BindAction( start_single_game_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_PRESENTER::StartSingleGameButtonClicked >, Presenter) );
    Presenter->BindAction( start_multiplayer_game_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_PRESENTER::StartBrowsingMultiplayerButtonClicked >, Presenter) );
}
