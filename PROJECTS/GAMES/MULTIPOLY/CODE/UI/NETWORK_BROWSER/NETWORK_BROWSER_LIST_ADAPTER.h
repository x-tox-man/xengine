//
//  NETWORK_BROWSER_LIST_ADAPTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_BROWSER_LIST_ADAPTER_hpp
#define NETWORK_BROWSER_LIST_ADAPTER_hpp

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"
#include "NETWORK_REMOTE_SERVER_INFO.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(NETWORK_BROWSER_LIST_ADAPTER, GRAPHIC_UI_FRAME_LIST_ADAPTER )
    
    NETWORK_BROWSER_LIST_ADAPTER(GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template);
    virtual ~NETWORK_BROWSER_LIST_ADAPTER();
    
    void SetCollection(std::vector< NETWORK_REMOTE_SERVER_INFO * > * collection) {
        ItemsTable = collection;
    }
    
    void SetServerSelectedCallback( CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO * > & callback) {
        ActionCallback = callback;
    }
    virtual int GetItemsCount();
    virtual int GetSpacing();
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *);
    
private:
    
    std::vector< NETWORK_REMOTE_SERVER_INFO * >
        * ItemsTable;
    CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO *>
        ActionCallback;

XS_CLASS_END

#endif /* NETWORK_BROWSER_LIST_ADAPTER_hpp */
