//
//  SELECT_LEVEL_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 30/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "SELECT_LEVEL_PRESENTER.h"
#include "RUN3D_APPLICATION.h"
#include "UI_GARAGE.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "NETWORK_BROWSER_PAGE.h"
#include "UI_INGAME.h"

SELECT_LEVEL_PRESENTER::SELECT_LEVEL_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ),
    GRAPHIC_UI_GRID_ADAPTER( view, new LEVEL_CELL() ),
    LevelTable() {
    
    SetCellDimension( CORE_MATH_VECTOR( 128.0f, 128.0f ) );
}

void SELECT_LEVEL_PRESENTER::Configure() {
    
    LevelTable = R3D_APP_PTR->GetGame()->GetLevelManager().GetAllLevels();
    
    OnLayoutFrame( GetFrame() );
}

int SELECT_LEVEL_PRESENTER::GetItemsCount() {
    
    return (int) LevelTable.size();
}

int SELECT_LEVEL_PRESENTER::GetSpacing() {
    
    return 10;
}

void SELECT_LEVEL_PRESENTER::ConfigureItemLayoutFor( int index , GRAPHIC_UI_ELEMENT * element) {
    
    auto cell = (LEVEL_CELL::PTR) element;
    
    BindAction<SELECT_LEVEL_PRESENTER, &SELECT_LEVEL_PRESENTER::OnLevelSelected >( cell, (SELECT_LEVEL_PRESENTER*) this);
    
    cell->SetLevelModel( LevelTable[ index ] );
}

void SELECT_LEVEL_PRESENTER::OnBaseIndexChanged( int index ) {
    
}

void SELECT_LEVEL_PRESENTER::OnLevelSelected( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        auto cell = (LEVEL_CELL::PTR) element;
        
        OpenAnimated< UI_INGAME >( "UI_INGAME" );
        
        std::vector< GAME_PLAYER_MODEL >
            players_model;

        players_model.resize( 1 );
        players_model[ 0 ].GamePlayer = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer();
        players_model[ 0 ].Identifier = R3D_APP_PTR->GetGame()->GetThisPlayerIndex();
        //players_model[ 1 ].GamePlayer = new R3D_PLAYER();
        //players_model[ 1 ].Identifier = CORE_HELPERS_UNIQUE_IDENTIFIER( "BOT0" );

        R3D_APP_PTR->GetGame()->SelectLevel( cell->GetLevelModel() );
        R3D_APP_PTR->GetGame()->SetPlayers( players_model );
        R3D_APP_PTR->GetGame()->Restart();
    }
}
