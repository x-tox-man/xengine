//
//  OPTIONS_PAGE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef OPTIONS_PAGE_hpp
#define OPTIONS_PAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"
#include "OPTIONS_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( OPTIONS_PAGE, GRAPHIC_UI_FRAME )

    OPTIONS_PAGE();
    virtual ~OPTIONS_PAGE();

    virtual void Initialize() override;
    virtual void Update( const float ) override;

private :

    OPTIONS_PRESENTER
        Presenter;

XS_CLASS_END

#endif /* OPTIONS_PAGE_hpp */
