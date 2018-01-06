//
//  UI_GARAGE.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_GARAGE.h"
#include "UI_GARAGE_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_GARAGE_SHIPS_ADAPTER.h"
#include "UI_GARAGE_SHIP_CELL.h"
#include "R3D_GAUGE.h"

UI_GARAGE::UI_GARAGE() :
    R3D_UI_FRAME() {
    
    SetPresenter( new UI_GARAGE_PRESENTER( this ) );
}

void UI_GARAGE::Initialize() {
    
    R3D_UI_FRAME::Initialize();
    
    auto text = GRAPHIC_UI_HELPER::CreateTextElement( CORE_HELPERS_IDENTIFIER( "Texttest" ), L"Garage\0" );
    text->Initialize();
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    auto button = GRAPHIC_UI_HELPER::CreateElement( "BackButton" );
    button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 64.0f ) );
    
    auto ship_frame = GRAPHIC_UI_HELPER:: CreateFrame( "ShipsContainer" );
    auto adapter = new R3D_GARAGE_SHIPS_ADAPTER( ship_frame );
    adapter->SetHorizontal();
    ship_frame->GetPlacement().SetSize(CORE_MATH_VECTOR( 768.0f, 256.0f ) );
    ship_frame->SetAdapter( adapter );
    ((UI_GARAGE_PRESENTER::PTR)GetPresenter())->SetShipsListAdapter( adapter );
    ship_frame->Initialize();
    
    GRAPHIC_UI_HELPER::CreateElementStyleWithContentTexture(button, CORE_COLOR_White, CORE_HELPERS_IDENTIFIER( "frameBorder3" ) );
    button->Initialize();
    ((R3D_BASE_PRESENTER::PTR) Presenter)->BindAction<R3D_BASE_PRESENTER, &R3D_BASE_PRESENTER::Back>(button, (R3D_BASE_PRESENTER*) Presenter);
    
    CreateStatsFrame();
    
    AddObject( button );
    AddObject( text );
    AddObject( ship_frame );
    
    button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
}

void UI_GARAGE::CreateStatsFrame() {
    
    auto stats = GRAPHIC_UI_HELPER::CreateFrame( Stats );
    stats->GetPlacement().SetSize( CORE_MATH_VECTOR( 512.0f, 256.0f ) );
    stats->GetPlacement().SetAnchor( GRAPHIC_UI_Bottom );
    
    auto g = new R3D_GAUGE;
    g->Initialize();
    g->SetPercent( 1.0f );
    
    stats->AddObject( g );
    AddObject( stats );
}

CORE_HELPERS_IDENTIFIER
    UI_GARAGE::Stats( "stats" );
