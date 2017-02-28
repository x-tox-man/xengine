//
//  GAMEPLAY_RULE_JUMP_TO.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_JUMP_TO_hpp
#define GAMEPLAY_RULE_JUMP_TO_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"

class GAMEPLAY_GAME_BOARD_CELL;
class GAMEPLAY_PLAYER;

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_JUMP_TO, GAMEPLAY_RULE )

    GAMEPLAY_RULE_JUMP_TO( int cell_index_to_remove );
    ~GAMEPLAY_RULE_JUMP_TO();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

private :

    int
        CellOffset;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_JUMP_TO_hpp */
