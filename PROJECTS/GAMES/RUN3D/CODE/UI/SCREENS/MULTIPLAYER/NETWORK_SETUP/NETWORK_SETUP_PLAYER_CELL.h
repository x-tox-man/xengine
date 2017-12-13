//
//  NETWORK_GAME_PLAYER_CELL.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_GAME_PLAYER_CELL_hpp
#define NETWORK_GAME_PLAYER_CELL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "NETWORK_REMOTE_SERVER_INFO.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_SETUP_PLAYER_CELL, GRAPHIC_UI_FRAME )

    NETWORK_SETUP_PLAYER_CELL();
    virtual ~NETWORK_SETUP_PLAYER_CELL();

    virtual void Initialize() override;
    virtual void OnViewAppearing() override;
    virtual GRAPHIC_UI_ELEMENT * Copy() override;

    void SetPlayerInfo(NETWORK_PLAYER * info);
    void NotifyPropertyChanged( CORE_DATA_MODEL * PlayerInfo );

private :

    NETWORK_PLAYER
        * PlayerInfo;

XS_CLASS_END

#endif /* NETWORK_GAME_PLAYER_CELL_hpp */
