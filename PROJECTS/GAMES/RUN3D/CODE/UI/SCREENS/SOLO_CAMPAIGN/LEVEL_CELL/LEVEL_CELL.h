//
//  LEVEL_CELL.hpp
//  Run3d
//
//  Created by Christophe Bernard on 20/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef LEVEL_CELL_hpp
#define LEVEL_CELL_hpp

#include "R3D_GAME_LEVEL_INFO.h"
#include "GRAPHIC_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( LEVEL_CELL, GRAPHIC_UI_FRAME )

    LEVEL_CELL();
    virtual ~LEVEL_CELL();

    virtual void Initialize() override;
    virtual GRAPHIC_UI_ELEMENT * Copy() override;

    void SetLevelModel( R3D_GAME_LEVEL_INFO::PTR info );
    R3D_GAME_LEVEL_INFO::PTR GetLevelModel() { return LevelModel; }

private:

    R3D_GAME_LEVEL_INFO::PTR
        LevelModel;
    static CORE_HELPERS_IDENTIFIER
        Element,
        BestTime,
        LevelName;
XS_CLASS_END

#endif /* LEVEL_CELL_hpp */
