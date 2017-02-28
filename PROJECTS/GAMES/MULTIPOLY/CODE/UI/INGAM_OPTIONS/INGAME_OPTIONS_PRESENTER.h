//
//  INGAM_OPTIONS_PRESENTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef INGAM_OPTIONS_PRESENTER_hpp
#define INGAM_OPTIONS_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(INGAME_OPTIONS_PRESENTER, GRAPHIC_UI_PRESENTER)

    INGAME_OPTIONS_PRESENTER();
    virtual ~INGAME_OPTIONS_PRESENTER();

    virtual void Configure() override;

    void OnBackButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );

private:

    bool
        NavigationIsRequested;

XS_CLASS_END


#endif /* INGAM_OPTIONS_PRESENTER_hpp */
