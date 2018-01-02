//
//  SELECT_LEVEL_PRESENTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 30/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef SELECT_LEVEL_PRESENTER_hpp
#define SELECT_LEVEL_PRESENTER_hpp

#include "R3D_BASE_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( SELECT_LEVEL_PRESENTER, R3D_BASE_PRESENTER )

    SELECT_LEVEL_PRESENTER( GRAPHIC_UI_FRAME * view );

    virtual void Configure() override;

XS_CLASS_END

#endif /* SELECT_LEVEL_PRESENTER_hpp */
