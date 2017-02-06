//
//  NETWORK_GAME_PLAYER_CELL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "NETWORK_GAME_PLAYER_CELL.h"
#include "GLOBAL_RESOURCES.h"

NETWORK_GAME_PLAYER_CELL::NETWORK_GAME_PLAYER_CELL() :
    GRAPHIC_UI_FRAME(),
    PlayerInfo( NULL ) {
    
}

NETWORK_GAME_PLAYER_CELL::~NETWORK_GAME_PLAYER_CELL() {
    
}

void NETWORK_GAME_PLAYER_CELL::Initialize() {
    
    GetPlacement().SetSize(CORE_MATH_VECTOR(500.0f, 32.0f));
    
    GRAPHIC_UI_RENDER_STYLE * default_render_style = new GRAPHIC_UI_RENDER_STYLE;
    
    SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().CellRenderStyle);
    
    default_render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 1.0f, 1.0f ) );
    default_render_style->SetShape( GLOBAL_RESOURCES::GetInstance().UIPlanObject );
    default_render_style->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) ) );
    
    GRAPHIC_UI_ELEMENT * join_server_button = new GRAPHIC_UI_ELEMENT;
    
    join_server_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    join_server_button->SetEnabled( false );
    join_server_button->GetPlacement().Initialize( &GetPlacement(),
                                                  CORE_MATH_VECTOR::Zero,
                                                  CORE_MATH_VECTOR( 32.0f, 32, 0.0f, 1.0f ),
                                                  GRAPHIC_UI_BottomLeft );
    
    AddObject(join_server_button);
}

void NETWORK_GAME_PLAYER_CELL::SetPlayerInfo(NETWORK_PLAYER * info) {
    
    if ( PlayerInfo ) {
        
        PlayerInfo->RemoveObserver(this);
    }
    
    PlayerInfo = info;
    PlayerInfo->AddObserver(this);
}

void NETWORK_GAME_PLAYER_CELL::NotifyPropertyChanged( CORE_DATA_MODEL * PlayerInfo ) {
    
    
}

GRAPHIC_UI_ELEMENT * NETWORK_GAME_PLAYER_CELL::Copy() {
    
    return GRAPHIC_UI_FRAME::InnerCopy( new NETWORK_GAME_PLAYER_CELL() );
}
