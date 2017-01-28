//
//  CORE_MATH_POSE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_POSE__
#define __GAME_ENGINE_REBORN__CORE_MATH_POSE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_QUATERNION.h"

XS_CLASS_BEGIN( CORE_MATH_POSE )

CORE_MATH_POSE();

XS_DEFINE_SERIALIZABLE

CORE_MATH_POSE( CORE_MATH_POSE & other );

void FromMatrix( CORE_MATH_MATRIX & matrix );
void ToMatrix( float * matrix );
void Lerp( const CORE_MATH_POSE & other, CORE_MATH_POSE & result, float percentage );

float * GetPosition() { return Position; }
CORE_MATH_QUATERNION & GetOrientation() { return Orientation; }
const float * GetPosition() const { return Position; }
const CORE_MATH_QUATERNION & GetOrientation() const { return Orientation; }

private :

float Position[4];
CORE_MATH_QUATERNION Orientation;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_POSE__) */
