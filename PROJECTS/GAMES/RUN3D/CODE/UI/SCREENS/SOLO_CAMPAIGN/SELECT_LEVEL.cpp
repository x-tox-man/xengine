//
//  SELECT_LEVEL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 30/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "SELECT_LEVEL.h"
#include "SELECT_LEVEL_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "TOOLS_LOCALE_SYSTEM.h"

SELECT_LEVEL::SELECT_LEVEL() :
    R3D_UI_FRAME() {
    
    SetPresenter( new SELECT_LEVEL_PRESENTER( this ) );
}

void SELECT_LEVEL::Initialize() {
    
    R3D_UI_FRAME::Initialize();
}
