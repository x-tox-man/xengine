//
//  NETWORK_PLAYER_LOBBY_CELL.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_PLAYER_LOBBY_CELL_hpp
#define NETWORK_PLAYER_LOBBY_CELL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "NETWORK_REMOTE_SERVER_INFO.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_BROWSER_LOBBY_CELL, GRAPHIC_UI_FRAME )

    NETWORK_BROWSER_LOBBY_CELL();
    virtual ~NETWORK_BROWSER_LOBBY_CELL();

    virtual void Initialize() override;
    virtual GRAPHIC_UI_ELEMENT * Copy() override;

    CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO * > & GetOnClickedCallback() { return OnClickedCallback; }
    void SetOnClickedCallback( const CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO * > & callback) { OnClickedCallback = callback; }
    void SetServerInfo( NETWORK_REMOTE_SERVER_INFO * info);

private:

    void ServerSelected( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT);

    NETWORK_REMOTE_SERVER_INFO
        * ServerInfo;
    CORE_HELPERS_CALLBACK_1< NETWORK_REMOTE_SERVER_INFO * >
        OnClickedCallback;
    CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT>
        Callback;

XS_CLASS_END

#endif /* NETWORK_PLAYER_LOBBY_CELL_hpp */
