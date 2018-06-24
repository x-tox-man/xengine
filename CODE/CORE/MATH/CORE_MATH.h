//
//  MATH.h
//  MULTIPOLY
//
//  Created by Christophe Bernard on 23/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MATH_h
#define MATH_h

#include <math.h>
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_POSE.h"

#define TOLERANCE 0.001f
const float DEG_TO_RAD = M_PI / 180.0f;

template <typename __LERPABLE_CLASS__>
__LERPABLE_CLASS__ CORE_MATH_GetLerpInterpolation(__LERPABLE_CLASS__ first, __LERPABLE_CLASS__ second, float percentage) {
    
    return first.LerpInterpolate( second, percentage );
}

bool MATH_IsRougthlyEqual( const float first, const float second );

bool MATH_IsRougthlyEqual( const CORE_MATH_VECTOR & first, const CORE_MATH_VECTOR & second );

bool MATH_IsRougthlyEqual( const CORE_MATH_QUATERNION & first, const CORE_MATH_QUATERNION & second );


bool MATH_IsRougthlyEqual( const CORE_MATH_MATRIX & first, const CORE_MATH_MATRIX & second );

bool MATH_IsRougthlyEqual( const CORE_MATH_POSE & first, const CORE_MATH_POSE & second );

float CORE_MATH_ToRadians( float degrees );

#endif /* MATH_h */
