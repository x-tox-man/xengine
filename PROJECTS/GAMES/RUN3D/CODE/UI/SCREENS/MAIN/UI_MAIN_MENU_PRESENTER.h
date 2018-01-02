//
//  UI_MAIN_MENU_PRESENTER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 4/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_MAIN_MENU_PRESENTER_hpp
#define UI_MAIN_MENU_PRESENTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_BASE_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_MAIN_MENU_PRESENTER, R3D_BASE_PRESENTER )

    UI_MAIN_MENU_PRESENTER( GRAPHIC_UI_FRAME * view );

    virtual void Configure() override;

    void OnClickToGarage(GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );
    void OnNetworkButtonPressed(GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );
    void OnClickStartGame( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );

XS_CLASS_END

#endif /* UI_MAIN_MENU_PRESENTER_hpp */
