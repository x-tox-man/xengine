//
//  INGAM_OPTIONS_PAGE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "INGAME_OPTIONS_PAGE.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "GRAPHIC_FONT_MANAGER.h"

INGAME_OPTIONS_PAGE::INGAME_OPTIONS_PAGE() :
    POPUP(),
    Presenter() {
        
    Presenter.Initialize( this );
}

INGAME_OPTIONS_PAGE::~INGAME_OPTIONS_PAGE() {
    
}

void INGAME_OPTIONS_PAGE::Initialize() {
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    GetPlacement().SetSize( GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize() );
    
    auto options_button = new GRAPHIC_UI_TEXT;
    options_button->SetFont( font );
    options_button->SetColor(CORE_COLOR_Red);
    options_button->SetText( "Options" );
    options_button->SetSize( 1.0f );
    
    auto quit_button = new GRAPHIC_UI_TEXT;
    quit_button->SetFont( font );
    quit_button->SetColor(CORE_COLOR_Red);
    quit_button->SetText( "Multijoueur" );
    quit_button->SetSize( 1.0f );
    
    auto back_button = new GRAPHIC_UI_TEXT;
    back_button->SetFont( font );
    back_button->SetColor(CORE_COLOR_Red);
    back_button->SetText( "Retour" );
    back_button->SetSize( 1.0f );
    
    options_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 32.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    quit_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    back_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, -32.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    AddObject( options_button );
    AddObject( quit_button );
    AddObject( back_button );
    
    Presenter.BindAction( back_button,
                         new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<INGAME_OPTIONS_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &INGAME_OPTIONS_PRESENTER::OnBackButtonPressed >, &Presenter) );
    Presenter.Configure();
    
    OnPlacementPropertyChanged();
    
    POPUP::Initialize();
    
    GRAPHIC_UI_FRAME::Initialize();
    
}
