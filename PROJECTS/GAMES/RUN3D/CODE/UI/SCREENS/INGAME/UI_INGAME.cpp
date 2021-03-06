//
//  UI_INGAME.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_INGAME.h"
#include "UI_INGAME_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_ACTION_COMMAND_GAME_LOADED.h"

UI_INGAME::UI_INGAME() :
    R3D_UI_FRAME() {
    
    SetPresenter( new UI_INGAME_PRESENTER( this ) );
}

UI_INGAME::~UI_INGAME() {
    
}

void UI_INGAME::Initialize() {
    
    R3D_UI_FRAME::SetBorderLess();
    
    auto pause_button = new UI_BASE_BUTTON;
    pause_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    pause_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    pause_button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, .0f ) );
    pause_button->Initialize();
    
    Presenter->BindAction<UI_INGAME_PRESENTER, &UI_INGAME_PRESENTER::OnPauseButtonPressed >( pause_button, (UI_INGAME_PRESENTER*) Presenter);
    
    const wchar_t * speed = L"0";
    
    auto text = GRAPHIC_UI_HELPER::CreateTextElement( SpeedText, speed );
    text->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
    text->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, 32.0f ) );
    text->Initialize();
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    auto time = GRAPHIC_UI_HELPER::CreateTextElement( TimeText, speed );
    time->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
    time->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, .0f ) );
    time->Initialize();
    time->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
/*#if DEBUG
    auto fps = GRAPHIC_UI_HELPER::CreateTextElement( FPSText, speed );
    text->GetPlacement().SetAnchor( GRAPHIC_UI_TopLeft );
    text->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( -32.0f, -32.0f ) );
    text->Initialize();
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_Green );
    
    AddObject( fps );
#endif*/
    
    AddObject( text );
    AddObject( time );
    AddObject( pause_button );
    
    R3D_UI_FRAME::Initialize();
}

void UI_INGAME::Update( float time_step ) {
    
    R3D_UI_FRAME::Update( time_step );
    
#if DEBUG
    /*static CORE_DATA_UTF8_TEXT fps_text( L"%d");
    
    static int local_fps = 0;
    
    local_fps++;
    
    GetObjectForIdentifier( FPSText )->SetTextValue( fps_text.Format( local_fps ) );*/
#endif
    ((UI_INGAME_PRESENTER::PTR) GetPresenter())->Update( time_step );
}

void UI_INGAME::SetSpeed( float speed ) {
    
    static CORE_DATA_UTF8_TEXT text( L"%.1f km/h\0");
    GetObjectForIdentifier( SpeedText )->SetTextValue( text.Format( speed ) );
}

void UI_INGAME::SetEllapsedTime( float time ) {
    
    static CORE_DATA_UTF8_TEXT text( L"%2d:%2d:%2d");
    
    int sec = ((int) time) % 60 ;
    int min = (((int) time ) - sec) / 60;
    int msec = (time - min - sec) * 100;
    
    GetObjectForIdentifier( TimeText )->SetTextValue( text.Format( min, sec, msec ) );
}

void UI_INGAME::OnViewAppearing() {
    
    if ( R3D_APP_PTR->GetNetworkManager().GetClient() != NULL ) {
        
        GAMEPLAY_ACTION_COMMAND_GAME_LOADED
            command;
        
        command.Player = &R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer() ;
        
        R3D_APP_PTR->GetNetworkManager().GetClient()->DispatchMessageToServer( GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand( command, 0 ) );
    }
}

CORE_HELPERS_IDENTIFIER
    UI_INGAME::SpeedText( "SpeedText" ),
    UI_INGAME::TimeText( "TimeText" ),
    UI_INGAME::FPSText( "FPS" );
