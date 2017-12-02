//
//  R3D_UI_FRAME.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 2/11/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_UI_FRAME_hpp
#define R3D_UI_FRAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_UI_FRAME, GRAPHIC_UI_FRAME )

    R3D_UI_FRAME();
    ~R3D_UI_FRAME();

    virtual void Initialize() override;

    void OnClick( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE );

XS_CLASS_END

#endif /* R3D_UI_FRAME_hpp */
