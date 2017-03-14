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
#include "GRAPHIC_UI_FRAME.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "CORE_TIMELINE_EVENT.h"
#include "NETWORK_BROWSER_LIST_ADAPTER.h"
#include "CORE_MATH_VECTOR.h"
#include "NETWORK_BROWSER_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_BROWSER_PAGE, GRAPHIC_UI_FRAME )

    NETWORK_BROWSER_PAGE();
    virtual ~NETWORK_BROWSER_PAGE();

    virtual void Initialize() override;
    virtual void Finalize() override;
    virtual void OnViewAppearing() override;

private:

    NETWORK_BROWSER_LIST_ADAPTER
        * ListAdapter;
    NETWORK_BROWSER_PRESENTER
        Presenter;
    static CORE_HELPERS_IDENTIFIER
        IdServerList;

XS_CLASS_END

#endif /* APPLICATION_NETWORK_BROWSER_hpp */
