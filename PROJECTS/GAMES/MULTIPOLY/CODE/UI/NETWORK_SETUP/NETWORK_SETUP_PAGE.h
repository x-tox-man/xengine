//
//  NETWORK_SETUP_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_SETUP_PAGE_hpp
#define NETWORK_SETUP_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "NETWORK_PLAYER.h"
#include "NETWORK_SETUP_PLAYER_LIST_ADAPTER.h"
#include "NETWORK_SETUP_PRESENTER.h"

class NETWORK_SETUP_PRESENTER;

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_SETUP_PAGE, GRAPHIC_UI_FRAME )

    NETWORK_SETUP_PAGE();
    virtual ~NETWORK_SETUP_PAGE();

    virtual void Initialize() override;
    virtual void Update( const float) override;

    inline NETWORK_SETUP_PLAYER_LIST_ADAPTER * GetPlayersListAdapter() { return PlayersListAdapter; }
    inline std::vector< NETWORK_PLAYER * > & GetPlayersList() { return PlayersList; }

private :

    NETWORK_SETUP_PLAYER_LIST_ADAPTER
        * PlayersListAdapter;
    std::vector< NETWORK_PLAYER * >
        PlayersList;
    NETWORK_SETUP_PRESENTER
        Presenter;

XS_CLASS_END

#endif /* NETWORK_SETUP_PAGE_hpp */
