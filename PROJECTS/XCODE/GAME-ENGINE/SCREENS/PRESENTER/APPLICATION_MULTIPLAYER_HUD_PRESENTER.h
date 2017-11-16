//
//  APPLICATION_MULTIPLAYER_HUD_PRESENTER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_MULTIPLAYER_HUD_PRESENTER_hpp
#define APPLICATION_MULTIPLAYER_HUD_PRESENTER_hpp

#include "APPLICATION_HUD_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(APPLICATION_MULTIPLAYER_HUD_PRESENTER, APPLICATION_HUD_PRESENTER)

    APPLICATION_MULTIPLAYER_HUD_PRESENTER();
    virtual ~APPLICATION_MULTIPLAYER_HUD_PRESENTER();

    virtual void Update( const float) override;
    virtual void Configure() override;

private :

protected :

XS_CLASS_END

#endif /* APPLICATION_MULTIPLAYER_HUD_PRESENTER_hpp */
