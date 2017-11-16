//
//  NETWORK_BROWSER_LIST_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_BROWSER_LIST_ADAPTER.h"
#include "APPLICATION_NETWORK_REMOTE_SERVER_INFO.h"
#include "NETWORK_PLAYER_LOBBY_CELL.h"

NETWORK_BROWSER_LIST_ADAPTER::NETWORK_BROWSER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template) :
    GRAPHIC_UI_FRAME_LIST_ADAPTER( frame, ui_template ),
    ItemsTable( NULL ) {
    
}

int NETWORK_BROWSER_LIST_ADAPTER::GetItemsCount() {
    
    return (int) ItemsTable->size();
}

int NETWORK_BROWSER_LIST_ADAPTER::GetSpacing() {
    
    return 32;
}

void NETWORK_BROWSER_LIST_ADAPTER::ConfigureItemLayoutFor(int row, GRAPHIC_UI_ELEMENT * item) {
    
    NETWORK_PLAYER_LOBBY_CELL * cell = (NETWORK_PLAYER_LOBBY_CELL*) item;
    cell->GetOnClickedCallback() = ActionCallback;
    cell->GetObjectAtIndex(0)->GetActionCallback().SetObject(cell);
    cell->SetServerInfo( ItemsTable->at(row) );
}
