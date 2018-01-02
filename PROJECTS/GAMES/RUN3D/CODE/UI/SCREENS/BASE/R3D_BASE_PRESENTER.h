//
//  R3D_BASE_PRESENTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_BASE_PRESENTER_hpp
#define R3D_BASE_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_BASE_PRESENTER, GRAPHIC_UI_PRESENTER )

    R3D_BASE_PRESENTER( GRAPHIC_UI_FRAME * view );

    void Back( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );

XS_CLASS_END

#endif /* R3D_BASE_PRESENTER_hpp */
