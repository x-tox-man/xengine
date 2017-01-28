//
//  CORE_HELPERS_COLOR.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef CORE_HELPERS_COLOR_h
#define CORE_HELPERS_COLOR_h

#include "CORE_MATH_VECTOR.h"

typedef CORE_MATH_VECTOR CORE_HELPERS_COLOR;

const CORE_HELPERS_COLOR CORE_COLOR_Red( 1.0f, 0.0f, 0.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Blue( 0.0f, 0.0f, 1.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Green( 0.0f, 1.0f, 0.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Yellow( 1.0f, 1.0f, 0.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Cyan( 0.0f, 1.0f, 1.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Magenta( 1.0f, 0.0f, 1.0f, 1.0f );

const CORE_HELPERS_COLOR CORE_COLOR_White( 1.0f, 1.0f, 1.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Black( 0.0f, 0.0f, 0.0f, 1.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Transparent( 0.0f, 0.0f, 0.0f, 0.0f );
const CORE_HELPERS_COLOR CORE_COLOR_Grey( 0.5f, 0.5f, 0.5f, 1.0f );

const CORE_HELPERS_COLOR CORE_COLOR_WhiteHalf( 1.0f, 1.0f, 1.0f, 0.0f );

#endif /* CORE_HELPERS_COLOR_h */
