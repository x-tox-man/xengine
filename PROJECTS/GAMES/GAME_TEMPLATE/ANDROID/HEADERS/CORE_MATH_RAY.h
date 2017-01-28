//
//  CORE_MATH_RAY.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_RAY__
#define __GAME_ENGINE_REBORN__CORE_MATH_RAY__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"

XS_CLASS_BEGIN( CORE_MATH_RAY )

CORE_MATH_RAY();

void SetOrigin( const CORE_MATH_VECTOR & origin ) { Origin = origin; }
void SetDirection( const CORE_MATH_VECTOR & direction ) { Direction = direction; }

const CORE_MATH_VECTOR & GetOrigin() const { return Origin; }
const CORE_MATH_VECTOR & GetDirection() const { return Direction; }

CORE_MATH_VECTOR & GetOrigin() { return Origin; }
CORE_MATH_VECTOR & GetDirection() { return Direction; }

private :

CORE_MATH_VECTOR Origin;
CORE_MATH_VECTOR Direction;

float Lenght;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_RAY__) */
