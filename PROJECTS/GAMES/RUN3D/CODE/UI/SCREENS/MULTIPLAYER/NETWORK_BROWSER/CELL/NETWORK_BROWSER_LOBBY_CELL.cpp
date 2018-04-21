//
//  NETWORK_PLAYER_LOBBY_CELL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_BROWSER_LOBBY_CELL.h"
#include "UI_BASE_BUTTON.h"
#include "GRAPHIC_UI_HELPER.h"

NETWORK_BROWSER_LOBBY_CELL::NETWORK_BROWSER_LOBBY_CELL() :
    GRAPHIC_UI_FRAME(),
    ServerInfo( NULL ),
    OnClickedCallback(),
    Callback( Wrapper2< NETWORK_BROWSER_LOBBY_CELL, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT , &NETWORK_BROWSER_LOBBY_CELL::ServerSelected>,  this ){
    
}

NETWORK_BROWSER_LOBBY_CELL::~NETWORK_BROWSER_LOBBY_CELL() {
    
}

void NETWORK_BROWSER_LOBBY_CELL::Initialize() {

    GetPlacement().SetSize( CORE_MATH_VECTOR( 500.0f, 196.0f ) );
    
    auto join_server_button = new UI_BASE_BUTTON;

    join_server_button->SetActionCallback( Callback );
    join_server_button->GetPlacement().Initialize( &GetPlacement(),
                                                  CORE_MATH_VECTOR::Zero,
                                                  CORE_MATH_VECTOR( 196.0f, 196, 0.0f, 1.0f ),
                                                  GRAPHIC_UI_Right );
    join_server_button->Initialize();

    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 1.0f, 0.0f, 0.5f, 0.5f ), "frameBorder3" );

    AddObject(join_server_button);

    GRAPHIC_UI_FRAME::Initialize();
}

void NETWORK_BROWSER_LOBBY_CELL::ServerSelected( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        OnClickedCallback( ServerInfo );
    }
}

GRAPHIC_UI_ELEMENT * NETWORK_BROWSER_LOBBY_CELL::Copy() {
    
    return InnerCopy(new NETWORK_BROWSER_LOBBY_CELL());
}

void NETWORK_BROWSER_LOBBY_CELL::SetServerInfo( NETWORK_REMOTE_SERVER_INFO * info) {
    
    ServerInfo = info;
}
