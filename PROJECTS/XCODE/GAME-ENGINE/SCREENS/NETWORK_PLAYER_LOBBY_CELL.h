//
//  NETWORK_PLAYER_LOBBY_CELL.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_PLAYER_LOBBY_CELL_hpp
#define NETWORK_PLAYER_LOBBY_CELL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GLOBAL_RESOURCES.h"
#include "APPLICATION_NETWORK_REMOTE_SERVER_INFO.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_PLAYER_LOBBY_CELL, GRAPHIC_UI_FRAME )

    NETWORK_PLAYER_LOBBY_CELL();
    virtual ~NETWORK_PLAYER_LOBBY_CELL();

    virtual void Initialize() override;
    virtual GRAPHIC_UI_ELEMENT * Copy() override;

    void ServerSelected( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE);
    CORE_HELPERS_CALLBACK_1<APPLICATION_NETWORK_REMOTE_SERVER_INFO *> & GetOnClickedCallback() { return OnClickedCallback; }
    void SetServerInfo(APPLICATION_NETWORK_REMOTE_SERVER_INFO * info);

private:

    APPLICATION_NETWORK_REMOTE_SERVER_INFO
        *ServerInfo;
    CORE_HELPERS_CALLBACK_1<APPLICATION_NETWORK_REMOTE_SERVER_INFO *>
        OnClickedCallback;
    GRAPHIC_UI_RENDER_STYLE
        * DefaultRenderStyle;

XS_CLASS_END

#endif /* NETWORK_PLAYER_LOBBY_CELL_hpp */
