//
//  NETWORK_BROWSER_LIST_ADAPTER.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_BROWSER_LIST_ADAPTER.h"
#include "NETWORK_BROWSER_LOBBY_CELL.h"

NETWORK_BROWSER_LIST_ADAPTER::NETWORK_BROWSER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template) :
    GRAPHIC_UI_FRAME_LIST_ADAPTER( frame, ui_template ),
    ItemsTable( NULL ),
    ActionCallback() {
    
}

NETWORK_BROWSER_LIST_ADAPTER::~NETWORK_BROWSER_LIST_ADAPTER() {
    
}

int NETWORK_BROWSER_LIST_ADAPTER::GetItemsCount() {
    
    if ( ItemsTable ) {
        return (int) ItemsTable->size();
    }
    
    return 0;
}

int NETWORK_BROWSER_LIST_ADAPTER::GetSpacing() {
    
    return 32;
}

void NETWORK_BROWSER_LIST_ADAPTER::ConfigureItemLayoutFor(int row, GRAPHIC_UI_ELEMENT * item) {
    
    NETWORK_BROWSER_LOBBY_CELL * cell = (NETWORK_BROWSER_LOBBY_CELL*) item;
    
    cell->GetObjectAtIndex(0)->GetActionCallback().SetObject(cell);
    cell->SetOnClickedCallback( ActionCallback );
    cell->SetServerInfo( ItemsTable->at(row) );
}
