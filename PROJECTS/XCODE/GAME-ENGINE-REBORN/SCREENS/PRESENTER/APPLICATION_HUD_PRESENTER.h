//
//  APPLICATION_HUD_PRESENTER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_HUD_PRESENTER_hpp
#define APPLICATION_HUD_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(APPLICATION_HUD_PRESENTER, GRAPHIC_UI_PRESENTER)

    APPLICATION_HUD_PRESENTER();
    virtual ~APPLICATION_HUD_PRESENTER();

    virtual void Update( const float);

    virtual void Configure() = 0;

private :

protected :

XS_CLASS_END

#endif /* APPLICATION_HUD_PRESENTER_hpp */
