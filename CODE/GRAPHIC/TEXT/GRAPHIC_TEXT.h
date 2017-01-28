//
//  GRAPHIC_TEXT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_TEXT__
#define __GAME_ENGINE_REBORN__GRAPHIC_TEXT__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_FONT.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_TEXT, GRAPHIC_OBJECT_SHAPE )

CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GRAPHIC_TEXT );

GRAPHIC_TEXT();

void Initialize( const char * text, GRAPHIC_FONT & font, float size_factor, GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader, bool left_to_right = true);
virtual void Render( const GRAPHIC_RENDERER & renderer );

inline CORE_MATH_VECTOR & GetTextSize() { return Size; }
void UpdateText( const char * text, float size_factor = 1.0f, bool left_to_right = true );

GRAPHIC_FONT *
    Font;
CORE_MATH_VECTOR
    Size;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_TEXT__) */
