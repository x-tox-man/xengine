//
//  NETWORK_BROWSER_LIST_ADAPTER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 20/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_BROWSER_LIST_ADAPTER_hpp
#define NETWORK_BROWSER_LIST_ADAPTER_hpp

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "APPLICATION_NETWORK_REMOTE_SERVER_INFO.h"

class NETWORK_BROWSER_LIST_ADAPTER : public GRAPHIC_UI_FRAME_LIST_ADAPTER {
    
    
public:
    
    NETWORK_BROWSER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template);
    
    void SetCollection(std::vector< APPLICATION_NETWORK_REMOTE_SERVER_INFO * > * collection) {
        ItemsTable = collection;
    }
    
    void SetServerSelectedCallback( CORE_HELPERS_CALLBACK_1<APPLICATION_NETWORK_REMOTE_SERVER_INFO *> & callback) {
        ActionCallback = callback;
    }
    virtual int GetItemsCount();
    virtual int GetSpacing();
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *);
    
private:
    
    std::vector< APPLICATION_NETWORK_REMOTE_SERVER_INFO * >
        * ItemsTable;
    CORE_HELPERS_CALLBACK_1<APPLICATION_NETWORK_REMOTE_SERVER_INFO *>
        ActionCallback;
};

#endif /* NETWORK_BROWSER_LIST_ADAPTER_hpp */
