//
//  UI_SCREEN_LOADER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 25/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_SCREEN_LOADER_hpp
#define UI_SCREEN_LOADER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_SCREEN_LOADER, GRAPHIC_UI_FRAME )

    UI_SCREEN_LOADER();
    virtual ~UI_SCREEN_LOADER();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* UI_SCREEN_LOADER_hpp */
