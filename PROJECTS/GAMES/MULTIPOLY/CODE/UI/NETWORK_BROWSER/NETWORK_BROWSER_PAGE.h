//
//  NETWORK_BROWSER_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_BROWSER_PAGE_hpp
#define NETWORK_BROWSER_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_BROWSER, GRAPHIC_UI_FRAME )

    NETWORK_BROWSER();
    virtual ~NETWORK_BROWSER();

    virtual void Initialize() override;

XS_CLASS_END

#endif /* NETWORK_BROWSER_PAGE_hpp */
