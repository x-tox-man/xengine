//
//  CORE_MATH_SHAPE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_SHAPE__
#define __GAME_ENGINE_REBORN__CORE_MATH_SHAPE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_SHAPE_SPHERE.h"
#include "CORE_MATH_SHAPE_BOX.h"
#include "CORE_MATH_RAY.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_SHAPE_TYPE.h"

XS_CLASS_BEGIN( CORE_MATH_SHAPE )

CORE_MATH_SHAPE();

bool Intersects( const CORE_MATH_SHAPE & other );
bool Intersects( const CORE_MATH_VECTOR & other );

bool GetIntersection( const CORE_MATH_SHAPE & other );
bool GetIntersection( const CORE_MATH_RAY & ray );

const CORE_MATH_VECTOR & GetPosition() const { return Position; };
const CORE_MATH_VECTOR & GetHalfDiagonal() const { return HalfDiagonal; };

CORE_MATH_VECTOR & GetPosition() { return Position; };
CORE_MATH_VECTOR & GetHalfDiagonal() { return HalfDiagonal; };

void SetPosition( const CORE_MATH_VECTOR & position ) { Position = position; }
void SetOrientation( const CORE_MATH_QUATERNION & orientation ) { Orientation = orientation; }
void SetHalfDiagonal( const CORE_MATH_VECTOR & diagonal ) { HalfDiagonal = diagonal; }

private:

CORE_MATH_VECTOR Position;
CORE_MATH_QUATERNION Orientation;
CORE_MATH_VECTOR HalfDiagonal; // Used to represent how a shape that is a square or a sphere should be represented
CORE_MATH_SHAPE_TYPE Type;


XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_SHAPE__) */
