//
//  NETWORK_GAME_PLAYER_LIST_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "NETWORK_GAME_PLAYER_LIST_ADAPTER.h"
#include "NETWORK_GAME_PLAYER_CELL.h"

NETWORK_GAME_PLAYER_LIST_ADAPTER::NETWORK_GAME_PLAYER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template) :
    GRAPHIC_UI_FRAME_LIST_ADAPTER( frame, ui_template ),
    ItemsTable( NULL ) {
    
}

int NETWORK_GAME_PLAYER_LIST_ADAPTER::GetItemsCount() {
    
    return (int) ItemsTable->size();
}

int NETWORK_GAME_PLAYER_LIST_ADAPTER::GetSpacing() {
    
    return 32;
}

void NETWORK_GAME_PLAYER_LIST_ADAPTER::ConfigureItemLayoutFor(int row, GRAPHIC_UI_ELEMENT * item) {
    
    NETWORK_GAME_PLAYER_CELL * cell = (NETWORK_GAME_PLAYER_CELL*) item;

    cell->GetObjectAtIndex(0)->GetActionCallback().SetObject(cell);
    cell->SetPlayerInfo( ItemsTable->at(row) );
}
