//
//  NETWORK_PLAYER_LOBBY_CELL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_BROWSER_LOBBY_CELL.h"

NETWORK_BROWSER_LOBBY_CELL::NETWORK_BROWSER_LOBBY_CELL() :
    ServerInfo( NULL ),
    OnClickedCallback(),
    DefaultRenderStyle( NULL ) {
    
}

NETWORK_BROWSER_LOBBY_CELL::~NETWORK_BROWSER_LOBBY_CELL() {
    
    CORE_MEMORY_ObjectSafeDeallocation( DefaultRenderStyle );
}

void NETWORK_BROWSER_LOBBY_CELL::Initialize() {

    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
        GRAPHIC_SHADER_EFFECT::PTR
            ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
        
        GetPlacement().SetSize(CORE_MATH_VECTOR(500.0f, 32.0f));
        
        DefaultRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
        
        SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().CellRenderStyle );
        
        DefaultRenderStyle->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 1.0f, 1.0f ) );
        DefaultRenderStyle->SetShape( GLOBAL_RESOURCES::GetInstance().CreateUIPlanShape( ui_textured_shader_effect ) );
        DefaultRenderStyle->SetTextureBlock( GLOBAL_RESOURCES::CreateTextureBlockFromImagePath( "button_join" ) );
        
        GRAPHIC_UI_ELEMENT * join_server_button = new GRAPHIC_UI_ELEMENT;
        
        auto callback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< NETWORK_BROWSER_LOBBY_CELL, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &NETWORK_BROWSER_LOBBY_CELL::ServerSelected>, this );
        
        join_server_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
        join_server_button->SetActionCallback( *callback );
        join_server_button->GetPlacement().Initialize( &GetPlacement(),
                                                     CORE_MATH_VECTOR::Zero,
                                                     CORE_MATH_VECTOR( 32.0f, 32, 0.0f, 1.0f ),
                                                      GRAPHIC_UI_BottomLeft );
        
        AddObject(join_server_button);
    
        GRAPHIC_UI_FRAME::Initialize();
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void NETWORK_BROWSER_LOBBY_CELL::ServerSelected( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_STATE state) {
    
    if ( OnClickedCallback.IsConnected() && state == GRAPHIC_UI_ELEMENT_STATE::GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        OnClickedCallback(ServerInfo);
        OnClickedCallback.Disconnect();
    }
}

GRAPHIC_UI_ELEMENT * NETWORK_BROWSER_LOBBY_CELL::Copy() {
    
    return InnerCopy(new NETWORK_BROWSER_LOBBY_CELL());
}

void NETWORK_BROWSER_LOBBY_CELL::SetServerInfo( NETWORK_REMOTE_SERVER_INFO * info) {
    
    ServerInfo = info;
}
