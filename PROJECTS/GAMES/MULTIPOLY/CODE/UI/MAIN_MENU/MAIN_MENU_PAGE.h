//
//  MAIN_MENU_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MAIN_MENU_PAGE_hpp
#define MAIN_MENU_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "MAIN_MENU_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( MAIN_MENU_PAGE, GRAPHIC_UI_FRAME )

    MAIN_MENU_PAGE();
    virtual ~MAIN_MENU_PAGE();

    virtual void Initialize() override;
    virtual void OnViewAppearing() override;

private:

    MAIN_MENU_PRESENTER
        * Presenter;

XS_CLASS_END

#endif /* MAIN_MENU_PAGE_hpp */
