//
//  APPLICATION_MAIN_WINDOW.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_MAIN_WINDOW.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GRAPHIC_RENDERER.h"
#include "Application.h"
#include "SERVICE_LOGGER.h"
#include "GRAPHIC_UI_TEXT_ADAPTER.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "CORE_PARALLEL.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "APPLICATION_NETWORK_BROWSER.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h"
#include "GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER.h"

APPLICATION_MAIN_WINDOW::APPLICATION_MAIN_WINDOW() :
    GRAPHIC_UI_FRAME(),
    Shape( NULL ),
    TextElement( NULL ),
    TextElement2( NULL ),
    Presenter( NULL ),
    DefaultRenderStyle( NULL ),
    HooveredRenderStyle( NULL ) {
    
}

APPLICATION_MAIN_WINDOW::~APPLICATION_MAIN_WINDOW() {
    
    CORE_MEMORY_ObjectSafeDeallocation( Presenter );
    CORE_MEMORY_ObjectSafeDeallocation( DefaultRenderStyle );
    CORE_MEMORY_ObjectSafeDeallocation( HooveredRenderStyle );
}

void APPLICATION_MAIN_WINDOW::Initialize() {
    
    #ifdef __UNIT_TESTING__
        return;
    #endif
    
    Presenter = new MAIN_MENU_WINDOW_PRESENTER;
    Presenter->Initialize( this );
    
    GetPlacement().SetSize(CORE_MATH_VECTOR(600.0f, 300.0f));
    
    CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "main_window", "lua", "SCRIPTS" );
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().PageFrameRenderStyle );
    
    GRAPHIC_UI_HELPER::DefaultFont = font;
    GRAPHIC_UI_HELPER::TextureAtlas = &GLOBAL_RESOURCES::GetInstance().UITextureAtlas;
    Shape = GLOBAL_RESOURCES::GetInstance().UIPlanObject;
    
    GRAPHIC_UI_ELEMENT * start_lobby_button = new GRAPHIC_UI_ELEMENT( IdStartLobby );
    DefaultRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    HooveredRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    
    DefaultRenderStyle->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 1.0f, 1.0f ) );
    DefaultRenderStyle->SetShape( Shape );
    DefaultRenderStyle->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) ) );
    
    //Uncomment for debugging  Shadow texture :
    //GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK;
    //tb->SetTexture( ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetShadowMapRenderTarget().TargetTexture );
    //default_render_style->SetTextureBlock( tb );
    
    HooveredRenderStyle->SetColor( CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    HooveredRenderStyle->SetShape( Shape );
    HooveredRenderStyle->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "fireButton" ) ) );
    
    start_lobby_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
    start_lobby_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, HooveredRenderStyle );
    
    start_lobby_button->GetPlacement().Initialize( &GetPlacement(),
                                                  CORE_MATH_VECTOR( 200.0f, -64.0f, 0.0f, 1.0f ),
                                                  CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                  GRAPHIC_UI_TopLeft );
    
    start_lobby_button->SetVisible( true );
    
    GRAPHIC_UI_ELEMENT * start_server_button = new GRAPHIC_UI_ELEMENT(IdStartServer);
    
    start_server_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
    start_server_button->GetPlacement().Initialize( &GetPlacement(),
                              CORE_MATH_VECTOR( -128.0f, 0.0f, 0.0f, 1.0f ),
                              CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                              GRAPHIC_UI_Center );
    start_server_button->SetVisible( false );
    
    GRAPHIC_UI_ELEMENT * start_client_button = new GRAPHIC_UI_ELEMENT(IdStartClient);
    
    start_client_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
    start_client_button->GetPlacement().Initialize( &GetPlacement(),
                                                   CORE_MATH_VECTOR( 128.0f, 0.0f, 0.0f, 1.0f ),
                                                   CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                   GRAPHIC_UI_Center );
    start_client_button->SetVisible( false );
    
    GRAPHIC_UI_ELEMENT * stop_lobby_button = new GRAPHIC_UI_ELEMENT(IdStopLobby);
    
    stop_lobby_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
    stop_lobby_button->GetPlacement().Initialize( &GetPlacement(),
                                                   CORE_MATH_VECTOR::Zero,
                                                   CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                   GRAPHIC_UI_BottomLeft );
    stop_lobby_button->SetVisible( false );
    
    GRAPHIC_UI_ELEMENT * send_command_button = new GRAPHIC_UI_ELEMENT( IdSendCommand );
    
    send_command_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
    send_command_button->GetPlacement().Initialize( &GetPlacement(),
                                                 CORE_MATH_VECTOR(-128.0f,0.0f,0.0f,1.0f),
                                                 CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                 GRAPHIC_UI_BottomRight );
    
    send_command_button->SetVisible( false );
    
    TextElement = new GRAPHIC_UI_TEXT;
    TextElement->SetFont( font );
    TextElement->SetColor(CORE_COLOR_Red);
    TextElement->SetText( "Server" );
    TextElement->SetSize( 1.0f );
    
    TextElement2 = new GRAPHIC_UI_TEXT;
    TextElement2->SetFont( font );
    TextElement2->SetColor(CORE_COLOR_Red);
    TextElement2->SetText( "Client" );
    TextElement2->SetSize( 1.0f );
    
    TextElement->GetPlacement().Initialize( &GetPlacement(),
                                            CORE_MATH_VECTOR( -64.0f, 16.0f, 0.0f, 1.0f ),
                                            CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
                                            GRAPHIC_UI_Center );
    TextElement2->GetPlacement().Initialize( &GetPlacement(),
        CORE_MATH_VECTOR( -64.0f, -16.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    auto test_button = new GRAPHIC_UI_ELEMENT();
    
    test_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
    test_button->GetPlacement().Initialize( &GetPlacement(),
                                                 CORE_MATH_VECTOR( 0.0f, -256.0f, 0.0f, 1.0f ),
                                                 CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                 GRAPHIC_UI_BottomLeft );
    
    /*GRAPHIC_UI_ELEMENT * text_client = new GRAPHIC_UI_ELEMENT;
    GRAPHIC_UI_RENDER_STYLE * text2_render_style = new GRAPHIC_UI_RENDER_STYLE;
    text2_render_style->SetColor( CORE_MATH_VECTOR(1.0f, 1.0f, 0.0f, 1.0f ) );*/
    
    /*TextShape2->SetTextureBlock( text_texture_block );
    text2_render_style->SetShape( TextShape2 );
    text2_render_style->SetTextureBlock( text_texture_block );
    text_client->SetAdapter( (GRAPHIC_UI_BASE_ADAPTER * ) new GRAPHIC_UI_TEXT_ADAPTER() );
    text_render_style->SetColor( CORE_MATH_VECTOR(0.0f, 1.0f, 1.0f, 1.0f ) );
    
    text_client->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, text2_render_style );
    text_client->GetPlacement().Initialize( &GetPlacement(),
                                    CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
                                    TextShape2->GetTextSize(),
                                    GRAPHIC_UI_Center );
    
    text_client->SetEnabled( false );*/
    
    SetAdapter( new GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER() );
    
    //start_lobby_button->SetVisible( false );
    AddObject( test_button );
    AddObject( TextElement );
    AddObject( TextElement2 );
    AddObject( start_lobby_button );
    AddObject( start_server_button );
    AddObject( start_client_button );
    AddObject( stop_lobby_button );
    AddObject( send_command_button );
    
    OnPlacementPropertyChanged();
    
    Presenter->BindAction( start_lobby_button,
        new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_WINDOW_PRESENTER::StartLobbyButtonClicked >, Presenter) );
    Presenter->BindAction( start_server_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_WINDOW_PRESENTER::StartLobbyButtonClicked >, Presenter) );
    Presenter->BindAction( start_lobby_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_WINDOW_PRESENTER::StartServerButtonClicked >, Presenter) );
    Presenter->BindAction( start_client_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_WINDOW_PRESENTER::StartClientButtonClicked >, Presenter) );
    Presenter->BindAction( stop_lobby_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_WINDOW_PRESENTER::StopLobbyButtonClicked >, Presenter) );
    Presenter->BindAction( send_command_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &MAIN_MENU_WINDOW_PRESENTER::SendCommandButtonClicked >, Presenter) );
    
    GRAPHIC_UI_FRAME::Initialize();
}

void APPLICATION_MAIN_WINDOW::Update( const float time_step ) {
    
    //GetAnimation().Update( time_step );
    //ElementTable[ IdStartLobby ]->GetAnimation().Update( time_step );
    
    GRAPHIC_UI_FRAME::Update( time_step );
}

CORE_HELPERS_IDENTIFIER
    APPLICATION_MAIN_WINDOW::IdStartLobby( "MW:start_lobby_button" ),
    APPLICATION_MAIN_WINDOW::IdText( "MW:first_text" ),
    APPLICATION_MAIN_WINDOW::IdTextClient( "MW:second_text" ),
    APPLICATION_MAIN_WINDOW::IdStartServer( "MW:start_server_button" ),
    APPLICATION_MAIN_WINDOW::IdStartClient( "MW:start_client_button" ),
    APPLICATION_MAIN_WINDOW::IdStopLobby( "MW:stop_lobby_button" ),
    APPLICATION_MAIN_WINDOW::IdSendCommand( "MW:send_command_button" );
