//
//  GRAPHIC_UI_PLACEMENT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_UI_PLACEMENT__
#define __GAME_ENGINE_REBORN__GRAPHIC_UI_PLACEMENT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_UI_PLACEMENT_ANCHOR.h"

XS_CLASS_BEGIN( GRAPHIC_UI_PLACEMENT )

GRAPHIC_UI_PLACEMENT();

inline const CORE_MATH_VECTOR & GetPosition() const { return RelativePosition; }
inline const CORE_MATH_VECTOR & GetSize() const { return Size; }

inline void SetPosition( const CORE_MATH_VECTOR & position ) { RelativePosition = position; }
inline void SetSize( const CORE_MATH_VECTOR & size ) { Size = size; }

inline void SetAnchor( int anchor ) { Anchor = anchor; }

private:

CORE_MATH_VECTOR
    RelativePosition,
    AbsolutePosition,
    Size,
    Offset;
int
    Anchor;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_PLACEMENT__) */
