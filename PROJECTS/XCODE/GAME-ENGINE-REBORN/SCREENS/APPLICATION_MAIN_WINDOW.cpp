//
//  APPLICATION_MAIN_WINDOW.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_MAIN_WINDOW.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_TEXTURE.h"
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

APPLICATION_MAIN_WINDOW::APPLICATION_MAIN_WINDOW() :
    GRAPHIC_UI_FRAME(),
    Shape( NULL ),
    TextShape( NULL ),
    TextShape2( NULL ),
    Text(),
    StartLobbyButtonClickedCallback( NULL ),
    StartServerButtonClickedCallback( NULL ),
    StartClientButtonClickedCallback( NULL ),
    StopLobbyButtonClickedCallback( NULL ),
    Server( NULL ),
    Client( NULL ),
    IsClient( false ){
    
}

APPLICATION_MAIN_WINDOW::~APPLICATION_MAIN_WINDOW() {
    
    
}

void APPLICATION_MAIN_WINDOW::Initialize() {
    
    #ifdef __UNIT_TESTING__
        return;
    #endif
    
    GetPlacement().SetSize(CORE_MATH_VECTOR(600.0f, 300.0f));
    
    CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "main_window", "lua", "SCRIPTS" );
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().PageFrameRenderStyle );
    
    GRAPHIC_UI_HELPER::DefaultFont = font;
    GRAPHIC_UI_HELPER::TextureAtlas = &GLOBAL_RESOURCES::GetInstance().UITextureAtlas;
    Shape = GLOBAL_RESOURCES::GetInstance().UIPlanObject;
    
    StartLobbyButtonClickedCallback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< APPLICATION_MAIN_WINDOW, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &APPLICATION_MAIN_WINDOW::StartLobbyButtonClicked>, this );
    StartServerButtonClickedCallback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< APPLICATION_MAIN_WINDOW, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &APPLICATION_MAIN_WINDOW::StartServerButtonClicked>, this );
    StartClientButtonClickedCallback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< APPLICATION_MAIN_WINDOW, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &APPLICATION_MAIN_WINDOW::StartClientButtonClicked >, this );
    StopLobbyButtonClickedCallback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< APPLICATION_MAIN_WINDOW, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &APPLICATION_MAIN_WINDOW::StopLobbyButtonClicked>, this );
    SendCommandButtonClickedCallback = new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( Wrapper2< APPLICATION_MAIN_WINDOW, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE , &APPLICATION_MAIN_WINDOW::SendCommandButtonClicked>, this );
    
    GRAPHIC_UI_ELEMENT * start_lobby_button = new GRAPHIC_UI_ELEMENT( IdStartLobby );
    GRAPHIC_UI_RENDER_STYLE * default_render_style = new GRAPHIC_UI_RENDER_STYLE;
    GRAPHIC_UI_RENDER_STYLE * hoovered_render_style = new GRAPHIC_UI_RENDER_STYLE;
    
    default_render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 1.0f, 1.0f ) );
    default_render_style->SetShape( Shape );
    default_render_style->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) ) );
    
    //Uncomment for debugging  Shadow texture :
    //GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK;
    //tb->SetTexture( ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetShadowMapRenderTarget().TargetTexture );
    //default_render_style->SetTextureBlock( tb );
    
    hoovered_render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    hoovered_render_style->SetShape( Shape );
    hoovered_render_style->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "fireButton" ) ) );
    
    start_lobby_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    start_lobby_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, hoovered_render_style );
    
    start_lobby_button->SetActionCallback( *StartLobbyButtonClickedCallback );
    start_lobby_button->GetPlacement().Initialize( &GetPlacement(),
                                                  CORE_MATH_VECTOR( 200.0f, -64.0f, 0.0f, 1.0f ),
                                                  CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                  GRAPHIC_UI_TopLeft );
    
    start_lobby_button->SetVisible( true );
    
    GRAPHIC_UI_ELEMENT * start_server_button = new GRAPHIC_UI_ELEMENT(IdStartServer);
    
    start_server_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    start_server_button->SetActionCallback( *StartServerButtonClickedCallback );
    start_server_button->GetPlacement().Initialize( &GetPlacement(),
                              CORE_MATH_VECTOR( -128.0f, 0.0f, 0.0f, 1.0f ),
                              CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                              GRAPHIC_UI_Center );
    start_server_button->SetVisible( false );
    
    GRAPHIC_UI_ELEMENT * start_client_button = new GRAPHIC_UI_ELEMENT(IdStartClient);
    
    start_client_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    start_client_button->SetActionCallback( *StartClientButtonClickedCallback );
    start_client_button->GetPlacement().Initialize( &GetPlacement(),
                                                   CORE_MATH_VECTOR( 128.0f, 0.0f, 0.0f, 1.0f ),
                                                   CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                   GRAPHIC_UI_Center );
    start_client_button->SetVisible( false );
    
    GRAPHIC_UI_ELEMENT * stop_lobby_button = new GRAPHIC_UI_ELEMENT(IdStopLobby);
    
    stop_lobby_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    stop_lobby_button->SetActionCallback( *StopLobbyButtonClickedCallback );
    stop_lobby_button->GetPlacement().Initialize( &GetPlacement(),
                                                   CORE_MATH_VECTOR::Zero,
                                                   CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                   GRAPHIC_UI_BottomLeft );
    stop_lobby_button->SetVisible( false );
    
    GRAPHIC_UI_ELEMENT * send_command_button = new GRAPHIC_UI_ELEMENT(IdSendCommand);
    
    send_command_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_render_style );
    send_command_button->SetActionCallback( *SendCommandButtonClickedCallback );
    send_command_button->GetPlacement().Initialize( &GetPlacement(),
                                                 CORE_MATH_VECTOR(-128.0f,0.0f,0.0f,1.0f),
                                                 CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
                                                 GRAPHIC_UI_BottomRight );
    
    send_command_button->SetVisible( false );
    
    GRAPHIC_FONT_MANAGER::GetInstance().LoadFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ), CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "fxb", "FONTS/" ), CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "png", "FONTS/" ) );
    
    TextShape = new GRAPHIC_TEXT;
    
    TextShape->Initialize( "Server", *font, 1.0f, Shape->GetShaderTable()[0] );
    
    TextShape2 = new GRAPHIC_TEXT;
    TextShape2->Initialize( "Client", *font, 1.0f, Shape->GetShaderTable()[0] );
    
    GRAPHIC_TEXTURE_BLOCK * text_texture_block = new GRAPHIC_TEXTURE_BLOCK;
    
    text_texture_block->SetTexture( font->Texture );
    
    GRAPHIC_UI_ELEMENT * text = new GRAPHIC_UI_ELEMENT;
    GRAPHIC_UI_RENDER_STYLE * text_render_style = new GRAPHIC_UI_RENDER_STYLE;
    text_render_style->SetColor( CORE_MATH_VECTOR(1.0f, 0.0f, 0.0f, 1.0f ) );
    
    TextShape->SetTextureBlock( text_texture_block );
    
    text_render_style->SetShape( TextShape );
    text_render_style->SetTextureBlock( text_texture_block );
    
    text->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, text_render_style );
    text->GetPlacement().Initialize( &GetPlacement(),
                                CORE_MATH_VECTOR( -256.0f, 0.0f, 0.0f, 1.0f ),
                                TextShape->GetTextSize(),
                                GRAPHIC_UI_Center );
    text->SetEnabled( false );
    
    GRAPHIC_UI_ELEMENT * text_client = new GRAPHIC_UI_ELEMENT;
    GRAPHIC_UI_RENDER_STYLE * text2_render_style = new GRAPHIC_UI_RENDER_STYLE;
    text2_render_style->SetColor( CORE_MATH_VECTOR(1.0f, 1.0f, 0.0f, 1.0f ) );
    
    TextShape2->SetTextureBlock( text_texture_block );
    text2_render_style->SetShape( TextShape2 );
    text2_render_style->SetTextureBlock( text_texture_block );
    text_client->SetAdapter( (GRAPHIC_UI_BASE_ADAPTER * ) new GRAPHIC_UI_TEXT_ADAPTER() );
    text_render_style->SetColor( CORE_MATH_VECTOR(0.0f, 1.0f, 1.0f, 1.0f ) );
    
    text_client->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, text2_render_style );
    text_client->GetPlacement().Initialize( &GetPlacement(),
                                    CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
                                    TextShape2->GetTextSize(),
                                    GRAPHIC_UI_Center );
    
    text_client->SetEnabled( false );
    
    AddObject( text );
    AddObject( text_client );
    AddObject( start_lobby_button );
    AddObject( start_server_button );
    AddObject( start_client_button );
    AddObject( stop_lobby_button );
    AddObject( send_command_button );
    
    //GetAnimation().Initialize( path, this );
    
    OnPlacementPropertyChanged();
}

void APPLICATION_MAIN_WINDOW::Update( const float time_step ) {
    
    //GetAnimation().Update( time_step );
    //ElementTable[ IdStartLobby ]->GetAnimation().Update( time_step );
    
    GRAPHIC_UI_FRAME::Update( time_step );
}

void APPLICATION_MAIN_WINDOW::StartLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {

        NamedElementTable[ IdStartLobby ]->SetVisible( false );
        NamedElementTable[ IdStartServer ]->SetVisible( true );
        NamedElementTable[ IdStartClient ]->SetVisible( true );
    }
}

void APPLICATION_MAIN_WINDOW::StartServerButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Server->Initialize(1.0f / 25.0f );
        IsClient = false;
        
        ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->SetItIsClient( false );
        ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->SetItIsServer( true );
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_MULTIPLAYER_GAME_CONFIGURATION>( "NetworkGameRoom" );
        
        NamedElementTable[ IdStartLobby ]->SetVisible( true );
        NamedElementTable[ IdStartServer ]->SetVisible( false );
        NamedElementTable[ IdStartClient ]->SetVisible( false );
        
        /*NamedElementTable[ IdStartServer ]->SetVisible( false );
        NamedElementTable[ IdStartClient ]->SetVisible( false );
        NamedElementTable[ IdStopLobby ]->SetVisible( true );
        NamedElementTable[ IdSendCommand ]->SetVisible( true );*/
    }
}

void APPLICATION_MAIN_WINDOW::StartClientButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_NETWORK_BROWSER>( "NetworkBrowser" );
        
        Client->Initialize();
        
        IsClient = true;
        
        ((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->SetItIsClient( IsClient );
    
        NamedElementTable[ IdStartLobby ]->SetVisible( true );
        NamedElementTable[ IdStartServer ]->SetVisible( false );
        NamedElementTable[ IdStartClient ]->SetVisible( false );
        
        /*NamedElementTable[ IdStartClient ]->SetVisible( false );
        NamedElementTable[ IdStartServer ]->SetVisible( false );
        NamedElementTable[ IdStopLobby ]->SetVisible( true );
        NamedElementTable[ IdSendCommand ]->SetVisible( true );*/
    }
}

void APPLICATION_MAIN_WINDOW::StopLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        if ( IsClient ) {
            Client->Disconnect();
            Client->Finalize();
        }
        
        NamedElementTable[ IdStopLobby ]->SetVisible( false );
        NamedElementTable[ IdStartLobby ]->SetVisible( true );
    }
}

void APPLICATION_MAIN_WINDOW::SendCommandButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {

    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        abort();
        /*APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY * action = new APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY;

        action->NewPosition = CORE_MATH_VECTOR(10.0f, 1.0f, 1.0f, 1.0f);
        action->EntityToMove = NULL;

        CORE_TIMELINE_EVENT * event = new CORE_TIMELINE_EVENT();

        event->Setup( 10.0f, 0.0f, CORE_HELPERS_UNIQUE_IDENTIFIER( "TESTOUILLE"), action );

        CORE_DATA_STREAM
            stream;

        const char * string = "MOV_COMMAND_1";

        stream.Open();
        stream.InputBytes( string, ( int ) strlen( string ) );
        
        stream.Close();
        stream.ResetOffset();

        //XS_CLASS_SERIALIZER<CORE_MATH_VECTOR>::Serialize< std::true_type >( action->NewPosition, stream );
    
        if ( IsClient ) {
            Client->DispatchMessageToAllPlayers(stream);
        }
        else {
            Server->DispatchMessageToAllPlayers(stream);
        }*/
    }
}

CORE_HELPERS_IDENTIFIER
    APPLICATION_MAIN_WINDOW::IdStartLobby( "MW:start_lobby_button" ),
    APPLICATION_MAIN_WINDOW::IdText( "MW:first_text" ),
    APPLICATION_MAIN_WINDOW::IdTextClient( "MW:second_text" ),
    APPLICATION_MAIN_WINDOW::IdStartServer( "MW:start_server_button" ),
    APPLICATION_MAIN_WINDOW::IdStartClient( "MW:start_client_button" ),
    APPLICATION_MAIN_WINDOW::IdStopLobby( "MW:stop_lobby_button" ),
    APPLICATION_MAIN_WINDOW::IdSendCommand( "MW:send_command_button" );
