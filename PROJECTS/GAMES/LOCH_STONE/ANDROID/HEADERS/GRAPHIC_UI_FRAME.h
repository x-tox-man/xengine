//
//  GRAPHIC_UI_FRAME.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_UI_FRAME__
#define __GAME_ENGINE_REBORN__GRAPHIC_UI_FRAME__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_FRAME, GRAPHIC_UI_ELEMENT )

GRAPHIC_UI_FRAME();

GRAPHIC_UI_ELEMENT * Contains( const CORE_MATH_VECTOR & cursor_position );

virtual void Update( const float );
virtual void Render( const GRAPHIC_RENDERER & );
virtual void Click( const CORE_MATH_VECTOR & cursor_position );

virtual GRAPHIC_UI_ELEMENT * GetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & );

protected:

std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_ELEMENT * > ElementTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_FRAME__) */
