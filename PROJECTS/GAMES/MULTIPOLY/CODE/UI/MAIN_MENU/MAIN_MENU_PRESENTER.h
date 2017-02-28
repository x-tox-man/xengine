//
//  MAIN_MENU_PRESENTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MAIN_MENU_PRESENTER_hpp
#define MAIN_MENU_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(MAIN_MENU_PRESENTER, GRAPHIC_UI_PRESENTER)

    MAIN_MENU_PRESENTER();
    virtual ~MAIN_MENU_PRESENTER();

    virtual void Configure() override;

    void StartSingleGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void StartBrowsingMultiplayerButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
    void NavigateToOptions();

private :

    bool
        NavigationIsRequested;

XS_CLASS_END


#endif /* MAIN_MENU_PRESENTER_hpp */
