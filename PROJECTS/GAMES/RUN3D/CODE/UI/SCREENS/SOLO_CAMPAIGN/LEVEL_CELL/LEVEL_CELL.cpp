//
//  LEVEL_CELL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 20/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "LEVEL_CELL.h"
#include "GRAPHIC_UI_HELPER.h"

LEVEL_CELL::LEVEL_CELL() {
    
}
LEVEL_CELL::~LEVEL_CELL() {
    
}

void LEVEL_CELL::Initialize() {
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        picto( "Level1_picto" );
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( true );
    
    GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 128.0f ) );
    
    auto element = GRAPHIC_UI_HELPER::CreateElement( Element );
    element->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 128.0f ) );
    element->Initialize();
    
    auto text = GRAPHIC_UI_HELPER::CreateTextElement( LevelName, CORE_DATA_UTF8_TEXT( L"Level 01") );
    text->GetPlacement().SetAnchor( GRAPHIC_UI_Bottom );
    text->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, 16.0f ) );
    text->Initialize();
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    auto time = GRAPHIC_UI_HELPER::CreateTextElement( BestTime, L"Null" );
    time->GetPlacement().SetAnchor( GRAPHIC_UI_Top );
    time->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, -16.0f ) );
    time->Initialize();
    time->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    time->SetVisible( false );

    GRAPHIC_UI_HELPER::CreateElementStyleWithContentTexture(element, CORE_COLOR_White, CORE_HELPERS_IDENTIFIER( "Level1_picto" ) );
    
    AddObject( element );
    AddObject( text );
    AddObject( time );
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( false );
}

GRAPHIC_UI_ELEMENT * LEVEL_CELL::Copy() {
    
    return new LEVEL_CELL();
}

void LEVEL_CELL::SetLevelModel( R3D_GAME_LEVEL_INFO::PTR info ) {

    LevelModel = info;
    
    CORE_PARALLEL_TASK_BEGIN(this)
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
            CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( true );
            if ( LevelModel->PlayerBest != -1.0f ) {
                GetObjectForIdentifier( BestTime )->SetTextValue( CORE_DATA_UTF8_TEXT( L"%.2f").Format( LevelModel->PlayerBest ) );
                GetObjectForIdentifier( BestTime )->SetVisible( true );
            }
            GetObjectForIdentifier( LevelName )->SetTextValue( LevelModel->LevelName );
            CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( false );
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    CORE_PARALLEL_TASK_END()
}

CORE_HELPERS_IDENTIFIER
    LEVEL_CELL::Element( "Image" ),
    LEVEL_CELL::BestTime( "BestTime" ),
    LEVEL_CELL::LevelName( "LevelName" );
