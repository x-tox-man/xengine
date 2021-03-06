//
//  NETWORK_BROWSER_LIST_ADAPTER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_BROWSER_LIST_ADAPTER_hpp
#define NETWORK_BROWSER_LIST_ADAPTER_hpp

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"
#include "NETWORK_REMOTE_SERVER_INFO.h"
#include "NETWORK_BROWSER_LOBBY_CELL.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(NETWORK_BROWSER_LIST_ADAPTER, GRAPHIC_UI_FRAME_LIST_ADAPTER )
    
    NETWORK_BROWSER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template);
    virtual ~NETWORK_BROWSER_LIST_ADAPTER();
    
    inline void SetCollection(std::vector< NETWORK_REMOTE_SERVER_INFO * > * collection) {
        ItemsTable = collection;
    }
    
    inline void SetServerSelectedCallback( CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO * > & callback) {
        ActionCallback = callback;
    }
    virtual int GetItemsCount() override;
    virtual int GetSpacing() override;
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) override;
    virtual GRAPHIC_UI_ELEMENT::PTR CreateItem() override {
        return new NETWORK_BROWSER_LOBBY_CELL;
    }

    virtual void OnBaseIndexChanged( int index ) override {}
    
private:
    
    std::vector< NETWORK_REMOTE_SERVER_INFO * >
        * ItemsTable;
    CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO *>
        ActionCallback;

XS_CLASS_END

#endif /* NETWORK_BROWSER_LIST_ADAPTER_hpp */
