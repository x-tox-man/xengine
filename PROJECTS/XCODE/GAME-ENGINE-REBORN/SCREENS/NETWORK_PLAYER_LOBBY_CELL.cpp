//
//  NETWORK_PLAYER_LOBBY_CELL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_PLAYER_LOBBY_CELL.h"

NETWORK_PLAYER_LOBBY_CELL::NETWORK_PLAYER_LOBBY_CELL() :
    ServerInfo( NULL ),
    OnClickedCallback() {
    
}

NETWORK_PLAYER_LOBBY_CELL::~NETWORK_PLAYER_LOBBY_CELL() {
    
}

void NETWORK_PLAYER_LOBBY_CELL::Initialize() {
    
    GetPlacement().SetSize(CORE_MATH_VECTOR(500.0f, 32.0f));
    
    GRAPHIC_UI_RENDER_STYLE * default_render_style = new GRAPHIC_UI_RENDER_STYLE;
    
    SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().CellRenderStyle);
    
    default_render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 1.0f, 1.0f ) );
    default_render_style->SetShape( GLOBAL_RESOURCES::GetInstance().UIPlanObject );
    default_render_style->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) ) );
    
    GRAPHIC_UI_ELEMENT * join_server_button = new GRAPHIC_UI_ELEMENT;
    
    auto callback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< NETWORK_PLAYER_LOBBY_CELL, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &NETWORK_PLAYER_LOBBY_CELL::ServerSelected>, this );
    
    join_server_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    join_server_button->SetActionCallback( *callback );
    join_server_button->GetPlacement().Initialize( &GetPlacement(),
                                                 CORE_MATH_VECTOR::Zero,
                                                 CORE_MATH_VECTOR( 32.0f, 32, 0.0f, 1.0f ),
                                                  GRAPHIC_UI_BottomLeft );
    
    AddObject(join_server_button);
}

void NETWORK_PLAYER_LOBBY_CELL::ServerSelected( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_STATE state) {
    
    if ( OnClickedCallback.IsConnected() && state == GRAPHIC_UI_ELEMENT_STATE::GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        OnClickedCallback(ServerInfo);
        OnClickedCallback.Disconnect();
    }
}

GRAPHIC_UI_ELEMENT * NETWORK_PLAYER_LOBBY_CELL::Copy() {
    
    return InnerCopy(new NETWORK_PLAYER_LOBBY_CELL());
}

void NETWORK_PLAYER_LOBBY_CELL::SetServerInfo(APPLICATION_NETWORK_REMOTE_SERVER_INFO * info) {
    
    ServerInfo = info;
}
