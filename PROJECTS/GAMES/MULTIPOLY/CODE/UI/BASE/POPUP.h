//
//  POPUP.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 26/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef POPUP_hpp
#define POPUP_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "GRAPHIC_OBJECT_SHAPE_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( POPUP, GRAPHIC_UI_FRAME )

    POPUP();
    virtual ~POPUP();

    virtual void Initialize() override;

private :

XS_CLASS_END

#endif /* POPUP_hpp */
