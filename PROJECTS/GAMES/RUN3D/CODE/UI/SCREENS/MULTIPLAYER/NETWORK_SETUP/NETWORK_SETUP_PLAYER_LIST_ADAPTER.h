//
//  NETWORK_GAME_PLAYER_LIST_ADAPTER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_GAME_PLAYER_LIST_ADAPTER_hpp
#define NETWORK_GAME_PLAYER_LIST_ADAPTER_hpp

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "NETWORK_SETUP_PLAYER_CELL.h"
#include "NETWORK_PLAYER.h"
#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"
#include "NETWORK_REMOTE_SERVER_INFO.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_SETUP_PLAYER_LIST_ADAPTER, GRAPHIC_UI_FRAME_LIST_ADAPTER )

    
    NETWORK_SETUP_PLAYER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template);
    
    void SetCollection(std::vector< NETWORK_PLAYER * > * collection) {
        ItemsTable = collection;
    }
    
    void SetServerSelectedCallback( CORE_HELPERS_CALLBACK_1<NETWORK_PLAYER *> & callback) {
        ActionCallback = callback;
    }
    virtual int GetItemsCount();
    virtual int GetSpacing();
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *);
    
private:
    
    std::vector< NETWORK_PLAYER * >
        * ItemsTable;
    CORE_HELPERS_CALLBACK_1<NETWORK_PLAYER *>
        ActionCallback;
};

#endif /* NETWORK_GAME_PLAYER_LIST_ADAPTER_hpp */
