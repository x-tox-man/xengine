//
//  UI_ENDGAME.hpp
//  Run3d
//
//  Created by Christophe Bernard on 28/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_ENDGAME_hpp
#define UI_ENDGAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_UI_PRESENTER.h"
#include "R3D_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_ENDGAME, R3D_UI_FRAME )

    UI_ENDGAME();
    ~UI_ENDGAME();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* UI_ENDGAME_hpp */
