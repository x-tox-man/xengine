//
//  UI_INGAME_PRESENTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_INGAME_PRESENTER_hpp
#define UI_INGAME_PRESENTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_BASE_PRESENTER.h"
#include "R3D_PLAYER_SHIP.h"
#include "R3D_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_INGAME_PRESENTER, R3D_BASE_PRESENTER )

    UI_INGAME_PRESENTER( GRAPHIC_UI_FRAME * view );

    virtual void Configure() override;

    void OnPauseButtonPressed( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );

private:

XS_CLASS_END

#endif /* UI_INGAME_PRESENTER_hpp */
