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
    
    auto text = GRAPHIC_UI_HELPER::CreateTextElement( CORE_HELPERS_IDENTIFIER( "Texttest" ), L"Garage\0" );
    text->Initialize();
    text->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( 0.0f, -32.0f ) );
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    auto back_button = new UI_BASE_BUTTON;
    back_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
    back_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    back_button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( 16.0f, 16.0f ) );
    back_button->SetTitle( TOOLS_LOCALE_SYSTEM::GetInstance().FindTranslation( CORE_HELPERS_UNIQUE_IDENTIFIER( "Back" ) ) );
    back_button->Initialize();
    
    auto ship_frame = GRAPHIC_UI_HELPER:: CreateFrame( "ShipsContainer" );
    auto adapter = new R3D_GARAGE_SHIPS_ADAPTER( ship_frame );
    adapter->SetHorizontal();
    ship_frame->GetPlacement().SetSize(CORE_MATH_VECTOR( 768.0f, 256.0f ) );
    ship_frame->SetAdapter( adapter );
    ((UI_GARAGE_PRESENTER::PTR)GetPresenter())->SetShipsListAdapter( adapter );
    
    ((R3D_BASE_PRESENTER::PTR) Presenter)->BindAction<R3D_BASE_PRESENTER, &R3D_BASE_PRESENTER::Back>( back_button, (R3D_BASE_PRESENTER*) Presenter);
    
    CreateStatsFrame();
    
    AddObject( back_button );
    AddObject( text );
    AddObject( ship_frame );
    
    ship_frame->Initialize();
    
    back_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
    text->GetPlacement().SetAnchor( GRAPHIC_UI_Top );
    
    R3D_UI_FRAME::Initialize();
    
    OnPlacementPropertyChanged();
}

void UI_GARAGE::CreateStatsFrame() {
    
    auto stats = GRAPHIC_UI_HELPER::CreateFrame( Stats );
    stats->GetPlacement().SetSize( CORE_MATH_VECTOR( 256.0f, 256.0f ) );
    stats->GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( 0.0f, -32.0f ) );
    stats->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    
    auto g = new R3D_GAUGE;
    g->GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( 0.0f, 32.0f ) );
    g->Initialize();
    g->SetColor( CORE_HELPERS_COLOR(0.9f, 0.22f, 0.08f, 1.0f ) );
    g->SetPercent( 0.5f );
    
    auto g2 = new R3D_GAUGE;
    g2->GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( 0.0f, 0.0f ) );
    g2->Initialize();
    g2->SetColor( CORE_HELPERS_COLOR(0.34f, 1.0f, 0.55f, 1.0f ) );
    g2->SetPercent( 0.5f );
    
    auto g3 = new R3D_GAUGE;
    g3->GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( 0.0f, -32.0f ) );
    g3->Initialize();
    g3->SetColor( CORE_HELPERS_COLOR(0.7f, 0.3f, 1.0f, 1.0f ) );
    g3->SetPercent( 0.5f );
    
    stats->AddObject( g );
    stats->AddObject( g2 );
    stats->AddObject( g3 );
    
    stats->Initialize();
    stats->OnPlacementPropertyChanged();
    
    SetObjectForIdentifier( Stats, stats );
}

CORE_HELPERS_IDENTIFIER
    UI_GARAGE::Stats( "stats" );
