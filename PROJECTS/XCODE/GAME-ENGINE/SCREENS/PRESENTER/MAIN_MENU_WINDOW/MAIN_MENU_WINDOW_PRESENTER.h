//
//  MAIN_MENU_WINDOW_PRESENTER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef MAIN_MENU_WINDOW_PRESENTER_hpp
#define MAIN_MENU_WINDOW_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_CLIENT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(MAIN_MENU_WINDOW_PRESENTER, GRAPHIC_UI_PRESENTER)

    MAIN_MENU_WINDOW_PRESENTER();
    virtual ~MAIN_MENU_WINDOW_PRESENTER();

    virtual void Configure() override;

    void StartLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void StartServerButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void StartClientButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void StopLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void SendCommandButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );

    private :

    NETWORK_SERVER
        * Server;
    NETWORK_CLIENT
        * Client;
    bool
        IsClient;

    protected :

XS_CLASS_END

#endif /* MAIN_MENU_WINDOW_PRESENTER_hpp */
