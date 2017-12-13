//
//  UI_GARAGE_PRESENTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_GARAGE_PRESENTER_hpp
#define UI_GARAGE_PRESENTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_BASE_PRESENTER.h"
#include "R3D_PLAYER_SHIP.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_GARAGE_PRESENTER, R3D_BASE_PRESENTER )

    UI_GARAGE_PRESENTER( GRAPHIC_UI_FRAME * view );

    virtual void Configure() override;

    void OnClick(GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );

private:

std::vector< R3D_PLAYER_SHIP::PTR >
    PlayerShips;

XS_CLASS_END

#endif /* UI_GARAGE_PRESENTER_hpp */
