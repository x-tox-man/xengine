//
//  GRAPHIC_BACKGROUND.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 27/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GRAPHIC_BACKGROUND_hpp
#define GRAPHIC_BACKGROUND_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_BACKGROUND, GAMEPLAY_COMPONENT_ENTITY )

    GRAPHIC_BACKGROUND();
    ~GRAPHIC_BACKGROUND();

    void Initialize( GAMEPLAY_SCENE * scene );

private:

XS_CLASS_END

#endif /* GRAPHIC_BACKGROUND_hpp */
