//
//  INGAM_OPTIONS_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef INGAME_OPTIONS_PAGE_hpp
#define INGAME_OPTIONS_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "POPUP.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "INGAME_OPTIONS_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( INGAME_OPTIONS_PAGE, POPUP )

    INGAME_OPTIONS_PAGE();
    virtual ~INGAME_OPTIONS_PAGE();

    virtual void Initialize() override;

private:

    INGAME_OPTIONS_PRESENTER
        Presenter;
XS_CLASS_END

#endif /* INGAM_OPTIONS_PAGE_hpp */
