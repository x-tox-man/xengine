//
//  APPLICATION_MAIN_WINDOW.h
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_MAIN_WINDOW, GRAPHIC_UI_FRAME )

APPLICATION_MAIN_WINDOW();

void Initialize();

void OnObjectClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );

void SetShape( GRAPHIC_OBJECT_SHAPE * shape ) { Shape = shape; }

virtual void Update( const float );

private:

GRAPHIC_OBJECT_SHAPE
    * Shape;

XS_CLASS_END


#endif /* defined(__GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__) */
