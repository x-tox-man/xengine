//
//  NETWORK_GAME_PLAYER_CELL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "NETWORK_SETUP_PLAYER_CELL.h"
#include "GRAPHIC_UI_HELPER.h"
#include "UI_BASE_BUTTON.h"
#include "RUN3D_APPLICATION.h"

NETWORK_SETUP_PLAYER_CELL::NETWORK_SETUP_PLAYER_CELL() :
    GRAPHIC_UI_FRAME(),
    PlayerInfo( NULL ),
    IsReady( false ) {
    
}

NETWORK_SETUP_PLAYER_CELL::~NETWORK_SETUP_PLAYER_CELL() {
    
}

void NETWORK_SETUP_PLAYER_CELL::Initialize() {
    
    IsReady = false;

    CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT>
        callback( Wrapper2< NETWORK_SETUP_PLAYER_CELL, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT , &NETWORK_SETUP_PLAYER_CELL::OnClick>,  this );
    
#if !PLATFORM_ANDROID
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( true );
#endif
    GetPlacement().SetSize( CORE_MATH_VECTOR( 500.0f, 32.0f ) );
    GRAPHIC_UI_FRAME::Initialize();
    
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.6f, 0.4f, 0.5f, 0.5f ), "frameBorder3" );
    
    auto button = new UI_BASE_BUTTON;
    button->GetPlacement().SetAnchor( GRAPHIC_UI_Right );
    button->SetEnabled( false );
    button->GetPlacement().SetSize( CORE_MATH_VECTOR( 32.0f, 32.0f ) );
    button->Initialize();
    button->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_Red );
    button->SetIdentifier( ButtonId );
    
    SetActionCallback( callback );
    
    SetObjectForIdentifier( ButtonId, button );
    
    #if !PLATFORM_ANDROID
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( false );
    #endif
}

void NETWORK_SETUP_PLAYER_CELL::OnClick( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( PlayerInfo == NULL || event != GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        return;
    }
    
    if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
        
        if ( PlayerInfo->GetUniqueId() == R3D_APP_PTR->GetNetworkManager().GetServer()->GetCurrentPlayer().GetUniqueId() ) {
            
            IsReady = !IsReady;
            R3D_APP_PTR->GetNetworkManager().GetServer()->SetReady( IsReady );
            
            GetObjectForIdentifier( ButtonId )->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_Green );
        }
        else {
            //Kick Action
            R3D_APP_PTR->GetNetworkManager().GetServer()->RejectPlayer( PlayerInfo->GetNetworkConnexion() );
            GetObjectForIdentifier( ButtonId )->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_Yellow );
        }
    }
    else {
        if ( PlayerInfo->GetUniqueId() == R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer().GetUniqueId() ) {
            
            IsReady = !IsReady;
            R3D_APP_PTR->GetNetworkManager().GetClient()->SendReadyCommand( IsReady );
            
            GetObjectForIdentifier( ButtonId )->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( IsReady ? CORE_COLOR_Green : CORE_COLOR_Red );
        }
    }
}

void NETWORK_SETUP_PLAYER_CELL::SetPlayerInfo(NETWORK_PLAYER * info) {
    
    if (info->GetName().size() ) {
        PlayerInfo = info;
        
        GetObjectForIdentifier( ButtonId )->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( PlayerInfo->Ready() ? CORE_COLOR_Green : CORE_COLOR_Red );
    }
}

void NETWORK_SETUP_PLAYER_CELL::NotifyPropertyChanged( CORE_DATA_MODEL * PlayerInfo ) {
    
}

GRAPHIC_UI_ELEMENT * NETWORK_SETUP_PLAYER_CELL::Copy() {
    
    return GRAPHIC_UI_FRAME::InnerCopy( new NETWORK_SETUP_PLAYER_CELL() );
}

void NETWORK_SETUP_PLAYER_CELL::OnViewAppearing() {
    
}

CORE_HELPERS_IDENTIFIER NETWORK_SETUP_PLAYER_CELL::ButtonId( "CellButton" );
