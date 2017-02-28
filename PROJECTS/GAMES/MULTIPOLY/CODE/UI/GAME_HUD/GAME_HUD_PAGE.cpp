//
//  GAME_HUD_PAGE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAME_HUD_PAGE.h"
#include "GLOBAL_RESOURCES.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "MULTIPOLY_APPLICATION.h"

GAME_HUD_PAGE::GAME_HUD_PAGE() :
    Presenter() {
    
    Presenter.Initialize( this );
}

GAME_HUD_PAGE::~GAME_HUD_PAGE() {
    
}

void GAME_HUD_PAGE::Initialize() {
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
    auto ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"),
                                                                                CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
    
    ui_textured_shader_effect->Initialize(GRAPHIC_SHADER_BIND_PositionNormalTexture);
    
    auto render_style = new GRAPHIC_UI_RENDER_STYLE;
    auto roll_dice_render_style = new GRAPHIC_UI_RENDER_STYLE;
    auto buy_property_render_style = new GRAPHIC_UI_RENDER_STYLE;
    auto end_button_render_style = new GRAPHIC_UI_RENDER_STYLE;
    
    auto pause_tb = new GRAPHIC_TEXTURE_BLOCK;
    pause_tb->SetTexture( GLOBAL_RESOURCES::CreateTextureFromImagePath("pause_button") );
    pause_tb->Initialize();
    
    auto dice_tb = new GRAPHIC_TEXTURE_BLOCK;
    dice_tb->SetTexture( GLOBAL_RESOURCES::CreateTextureFromImagePath("dice_button") );
    dice_tb->Initialize();
    
    auto buy_property_tb = new GRAPHIC_TEXTURE_BLOCK;
    buy_property_tb->SetTexture( GLOBAL_RESOURCES::CreateTextureFromImagePath("euro_symbol") );
    buy_property_tb->Initialize();
    
    auto end_button_tb = new GRAPHIC_TEXTURE_BLOCK;
    end_button_tb->SetTexture( GLOBAL_RESOURCES::CreateTextureFromImagePath("end_button") );
    end_button_tb->Initialize();
    
    

    render_style->SetShape( GLOBAL_RESOURCES::GetInstance().CreateUIPlanShape( ui_textured_shader_effect ) );
    render_style->SetTextureBlock( pause_tb );
    
    
    roll_dice_render_style->SetShape( GLOBAL_RESOURCES::GetInstance().CreateUIPlanShape( ui_textured_shader_effect ) );
    roll_dice_render_style->SetTextureBlock( dice_tb );
    roll_dice_render_style->SetColor( CORE_COLOR_White );
    
    buy_property_render_style->SetShape( GLOBAL_RESOURCES::GetInstance().CreateUIPlanShape( ui_textured_shader_effect ) );
    buy_property_render_style->SetTextureBlock( buy_property_tb );
    buy_property_render_style->SetColor( CORE_COLOR_White );
    
    end_button_render_style->SetShape( GLOBAL_RESOURCES::GetInstance().CreateUIPlanShape( ui_textured_shader_effect ) );
    end_button_render_style->SetTextureBlock( end_button_tb );
    end_button_render_style->SetColor( CORE_COLOR_White );
    
    auto pause_button = new GRAPHIC_UI_ELEMENT();
    pause_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, render_style );
    pause_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_BottomRight );
    
    auto roll_dice_button = new GRAPHIC_UI_ELEMENT( GAME_HUD_PAGE::RollDiceButtonId );
    roll_dice_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, roll_dice_render_style );
    roll_dice_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Center );
    
    roll_dice_button->SetVisible( false );
    roll_dice_button->Disable();
    
    auto buy_property_button = new GRAPHIC_UI_ELEMENT( GAME_HUD_PAGE::BuyPropertyButtonId );
    buy_property_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, buy_property_render_style );
    buy_property_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_TopRight );
    
    buy_property_button->SetVisible( false );
    buy_property_button->Disable();
    
    auto end_turn_button = new GRAPHIC_UI_ELEMENT( GAME_HUD_PAGE::EndTurnButtonId );
    end_turn_button->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, end_button_render_style );
    end_turn_button->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 128.0f, 128.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_BottomLeft );
    
    end_turn_button->SetVisible( false );
    end_turn_button->Disable();
    
    
    auto dice_roll_result_text = new GRAPHIC_UI_TEXT;
    dice_roll_result_text->SetFont( font );
    dice_roll_result_text->SetIdentifier( DiceRollResultId );
    dice_roll_result_text->SetColor(CORE_COLOR_Red);
    dice_roll_result_text->SetText( "" );
    dice_roll_result_text->SetSize( 1.0f );
    
    dice_roll_result_text->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, -32.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Top );
    
    std::vector<GAMEPLAY_PLAYER *> players = ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetGame().GetPlayerTable();
    
    CORE_HELPERS_IDENTIFIER * id_array[4];
    
    id_array[0] = &Player1FrameId;
    id_array[1] = &Player2FrameId;
    id_array[2] = &Player3FrameId;
    id_array[3] = &Player4FrameId;
    
    AddObject( pause_button );
    AddObject( roll_dice_button );
    AddObject( dice_roll_result_text );
    AddObject( buy_property_button );
    AddObject( end_turn_button );
    
    OnPlacementPropertyChanged();
    
    for ( int i = 0; i < players.size(); i++ ) {
        
        CreatePlayerInfoFrames( players[ i ], *id_array[i], i );
    }
    
    Presenter.BindAction( pause_button,
                          new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<GAME_HUD_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &GAME_HUD_PRESENTER::OnPauseClicked >, &Presenter) );
    Presenter.BindAction( roll_dice_button,
                         new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<GAME_HUD_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &GAME_HUD_PRESENTER::OnRollDiceButtonPressed >, &Presenter) );
    Presenter.BindAction( buy_property_button,
                         new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<GAME_HUD_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &GAME_HUD_PRESENTER::OnBuyPropertyButtonPressed >, &Presenter) );
    Presenter.BindAction( end_turn_button,
                         new CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>( &Wrapper2<GAME_HUD_PRESENTER, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE, &GAME_HUD_PRESENTER::OnEndGameButtonPressed >, &Presenter) );
    
    Presenter.Configure();
    
    GRAPHIC_UI_FRAME::Initialize();
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
}

void GAME_HUD_PAGE::CreatePlayerInfoFrames( GAMEPLAY_PLAYER * player, CORE_HELPERS_IDENTIFIER & identifier, int offset ) {
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ) );
    
    auto money_left = new GRAPHIC_UI_TEXT;
    money_left->SetFont( font );
    money_left->SetIdentifier( MoneyId );
    money_left->SetColor(CORE_COLOR_Red);
    money_left->SetText( "Hellow" );
    money_left->SetSize( 1.0f );
    
    money_left->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f ),
        CORE_MATH_VECTOR( 1.0f, 1.0f, 0.0f, 1.0f ),
        GRAPHIC_UI_Left );
    
    auto frame = new GRAPHIC_UI_FRAME;
    frame->SetIdentifier( identifier );
    frame->AddObject( money_left );
    
    frame->GetPlacement().Initialize(
        &GetPlacement(),
        CORE_MATH_VECTOR( 0.0f, 150.0f - (offset * 150.0f) ),
        CORE_MATH_VECTOR( 150.0f, 64.0f ),
        GRAPHIC_UI_Left );
    
    frame->OnPlacementPropertyChanged();
    
    AddObject( frame );
}

CORE_HELPERS_IDENTIFIER
    GAME_HUD_PAGE::Player1FrameId( "Player1FrameId" ),
    GAME_HUD_PAGE::Player2FrameId( "Player2FrameId" ),
    GAME_HUD_PAGE::Player3FrameId( "Player3FrameId" ),
    GAME_HUD_PAGE::Player4FrameId( "Player4FrameId" ),
    GAME_HUD_PAGE::RollDiceButtonId( "RollDiceButtonId" ),
    GAME_HUD_PAGE::DiceRollResultId( "DiceRollResultId" ),
    GAME_HUD_PAGE::MoneyId( "MoneyId" ),
    GAME_HUD_PAGE::BuyPropertyButtonId( "BuyPropertyButtonId" ),
    GAME_HUD_PAGE::EndTurnButtonId( "EndTurnButtonId" );
