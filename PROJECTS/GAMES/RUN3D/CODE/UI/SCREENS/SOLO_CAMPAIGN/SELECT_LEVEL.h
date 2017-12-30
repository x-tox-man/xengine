//
//  SELECT_LEVEL.hpp
//  Run3d
//
//  Created by Christophe Bernard on 30/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef SELECT_LEVEL_hpp
#define SELECT_LEVEL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_UI_PRESENTER.h"
#include "R3D_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( SELECT_LEVEL, R3D_UI_FRAME )

    SELECT_LEVEL();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* SELECT_LEVEL_hpp */
