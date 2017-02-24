//
//  GAMEPLAY_GAME_BOARD.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_GAME_BOARD_hpp
#define GAMEPLAY_GAME_BOARD_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

XS_CLASS_BEGIN(GAMEPLAY_GAME_BOARD)

    GAMEPLAY_GAME_BOARD();
    ~GAMEPLAY_GAME_BOARD();

    void Initialize( GAMEPLAY_SCENE * scene );

    inline GAMEPLAY_GAME_BOARD_CELL * GetCell( int cell_index ) { return CellTable[cell_index]; }

private:

    std::array< GAMEPLAY_GAME_BOARD_CELL *, 40 >
        CellTable;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_BOARD_hpp */
