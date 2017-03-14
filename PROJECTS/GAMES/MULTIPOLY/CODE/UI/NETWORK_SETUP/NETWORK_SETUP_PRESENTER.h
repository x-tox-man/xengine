//
//  NETWORK_SETUP_PRESENTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_SETUP_PRESENTER_hpp
#define NETWORK_SETUP_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"
#include "NETWORK_PLAYER.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_CLIENT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_SETUP_PRESENTER, GRAPHIC_UI_PRESENTER)

    NETWORK_SETUP_PRESENTER();
    virtual ~NETWORK_SETUP_PRESENTER();

    virtual void Configure() override;
    void Update( const float step );

    void GameStarted( std::vector<NETWORK_PLAYER *> & players);

    void StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );

    void OnClientConnected(NETWORK_PLAYER * player);
    void OnClientDisconnected(NETWORK_PLAYER * player);
    void OnChatMessageReceived(NETWORK_PLAYER * player, const char * message);
    void OnGameStarting();
    void OnStoppedGameStarting();

private:

    bool
        NavigationIsRequested,
        GameIsStarting;
    float
        CountDown;
    NETWORK_SERVER
        * Server;
    NETWORK_CLIENT
        * Client;

XS_CLASS_END

#endif /* NETWORK_SETUP_PRESENTER_hpp */
