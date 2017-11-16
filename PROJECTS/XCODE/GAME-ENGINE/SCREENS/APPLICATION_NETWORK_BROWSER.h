//
//  APPLICATION_NETWORK_BROWSER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_NETWORK_BROWSER_hpp
#define APPLICATION_NETWORK_BROWSER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "CORE_TIMELINE_EVENT.h"
#include "APPLICATION_NETWORK_REMOTE_SERVER_INFO.h"
#include "NETWORK_BROWSER_LIST_ADAPTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_NETWORK_BROWSER, GRAPHIC_UI_FRAME )

    APPLICATION_NETWORK_BROWSER();
    virtual ~APPLICATION_NETWORK_BROWSER();

    virtual void Initialize() override;
    virtual void Finalize() override;

    void OnShow();
    void OnHide();

    void SetMessage( CORE_TIMELINE_EVENT * last_message ) { LastMessage = last_message; MessageReceivedCount++; }
    void SetServer( SERVICE_NETWORK_COMMAND * server_connection );
    void ConnectToServer(APPLICATION_NETWORK_REMOTE_SERVER_INFO *);

private :

    void StartServer();

    std::vector< APPLICATION_NETWORK_REMOTE_SERVER_INFO * >
        ServersList;
    int
        MessageReceivedCount;
    CORE_TIMELINE_EVENT
        * LastMessage;
    NETWORK_CLIENT
        * Client;
    NETWORK_BROWSER_LIST_ADAPTER
        * ListAdapter;

    static CORE_HELPERS_IDENTIFIER
        IdServerList;

XS_CLASS_END

#endif /* APPLICATION_NETWORK_BROWSER_hpp */
