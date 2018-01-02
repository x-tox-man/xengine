//
//  UI_MAIN_MENU.hpp
//  Run3d
//
//  Created by Christophe Bernard on 19/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_MAIN_MENU_hpp
#define UI_MAIN_MENU_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_UI_PRESENTER.h"
#include "R3D_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_MAIN_MENU, R3D_UI_FRAME )

    UI_MAIN_MENU();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* UI_MAIN_MENU_hpp */
