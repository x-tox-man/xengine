//
//  NETWORK_BROWSER_PRESENTER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_BROWSER_PRESENTER_hpp
#define NETWORK_BROWSER_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"
#include "SERVICE_NETWORK_COMMAND.h"
#include "NETWORK_REMOTE_SERVER_INFO.h"
#include "NETWORK_CLIENT.h"
#include "NETWORK_BROWSER_LIST_ADAPTER.h"
#include "R3D_BASE_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_BROWSER_PRESENTER, R3D_BASE_PRESENTER )

    NETWORK_BROWSER_PRESENTER( GRAPHIC_UI_FRAME * view );
    virtual ~NETWORK_BROWSER_PRESENTER();

    virtual void Configure() override;

    void SetMessage( CORE_TIMELINE_EVENT * last_message ) { LastMessage = last_message; MessageReceivedCount++; }
    void SetServer( SERVICE_NETWORK_COMMAND * server_connection );
    void ConnectToServer( NETWORK_REMOTE_SERVER_INFO * );
    inline void SetListAdapter( NETWORK_BROWSER_LIST_ADAPTER * adapter ) { ListAdapter = adapter; }
    void OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event );
    void OnStartLobbyButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event );

private:

    bool
        NavigationIsRequested;
    int
        MessageReceivedCount;
    std::vector< NETWORK_REMOTE_SERVER_INFO * >
        ServersList;
    CORE_TIMELINE_EVENT
        * LastMessage;
    NETWORK_BROWSER_LIST_ADAPTER
        * ListAdapter;
    NETWORK_CLIENT
        * Client;

XS_CLASS_END

#endif /* NETWORK_BROWSER_PRESENTER_hpp */
