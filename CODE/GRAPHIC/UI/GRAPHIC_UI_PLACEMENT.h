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

inline const CORE_MATH_VECTOR & GetRelativePosition() const { return RelativePosition; }
inline const CORE_MATH_VECTOR & GetAbsolutePosition() const { return AbsolutePosition; }
inline const CORE_MATH_VECTOR & GetSize() const { return Size; }
inline const int GetAnchor() const { return Anchor; }
inline const int GetRotation() const { return Rotation; }
inline void SetParent(const GRAPHIC_UI_PLACEMENT * parent ) { Parent = parent; }

inline CORE_MATH_VECTOR & GetRelativePosition() { return RelativePosition; }
inline CORE_MATH_VECTOR & GetAbsolutePosition() { return AbsolutePosition; }
inline CORE_MATH_VECTOR & GetSize() { return Size; }
inline int GetAnchor() { return Anchor; }
inline int GetRotation() { return Rotation; }

void Initialize( const GRAPHIC_UI_PLACEMENT * ParentPlacement, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor );

inline void SetRelativePosition( const CORE_MATH_VECTOR & position ) { RelativePosition = position; OnPlacementPropertyChanged(); }
inline void SetRelativePosition( const CORE_MATH_VECTOR & position, int anchor ) { RelativePosition = position; Anchor = anchor;OnPlacementPropertyChanged(); }
inline void SetSize( const CORE_MATH_VECTOR & size ) { Size = size; OnPlacementPropertyChanged(); }

inline void SetAnchor( int anchor ) { Anchor = anchor; OnPlacementPropertyChanged(); }
inline void SetRotation( int rotation ) { Rotation = rotation; OnPlacementPropertyChanged(); }

void OnPlacementPropertyChanged();

void Copy( GRAPHIC_UI_PLACEMENT & other );

private:

CORE_MATH_VECTOR
    RelativePosition,
    AbsolutePosition,
    Size;
int
    Anchor;
float
    Rotation;

const GRAPHIC_UI_PLACEMENT
    * Parent;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_PLACEMENT__) */
