//
//  APPLICATION_MAIN_WINDOW.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__
#define __GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_FONT.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_CLIENT.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GLOBAL_RESOURCES.h"
#include "MAIN_MENU_WINDOW_PRESENTER.h"
#include "GRAPHIC_UI_TEXT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_MAIN_WINDOW, GRAPHIC_UI_FRAME )

    APPLICATION_MAIN_WINDOW();
    virtual ~APPLICATION_MAIN_WINDOW();

    virtual void Initialize() override;

    void SetShape( GRAPHIC_OBJECT_SHAPE * shape ) { Shape = shape; }

    virtual void Update( const float ) override;

private:

    GRAPHIC_OBJECT_SHAPE
        * Shape;
    GRAPHIC_UI_TEXT
        * TextElement,
        * TextElement2;
    MAIN_MENU_WINDOW_PRESENTER
        * Presenter;
    GRAPHIC_UI_RENDER_STYLE
        * DefaultRenderStyle,
        * HooveredRenderStyle;

public:
    static CORE_HELPERS_IDENTIFIER
        IdStartLobby,
        IdText,
        IdTextClient,
        IdStartServer,
        IdStartClient,
        IdStopLobby,
        IdSendCommand;

XS_CLASS_END


#endif /* defined(__GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__) */
