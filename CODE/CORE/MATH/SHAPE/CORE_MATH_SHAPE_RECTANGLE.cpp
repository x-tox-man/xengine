//
//  CORE_MATH_SHAPE_RECTANGLE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_SHAPE_RECTANGLE.h"

CORE_MATH_SHAPE_RECTANGLE::CORE_MATH_SHAPE_RECTANGLE() :
    Center(),
    Size() {
    
}

CORE_MATH_SHAPE_RECTANGLE::~CORE_MATH_SHAPE_RECTANGLE() {

}

CORE_MATH_SHAPE_RECTANGLE::CORE_MATH_SHAPE_RECTANGLE( const CORE_MATH_VECTOR & center, const CORE_MATH_VECTOR & size ) :
    Center( center ),
    Size( size ) {
    
}

bool CORE_MATH_SHAPE_RECTANGLE::Contains( const CORE_MATH_VECTOR & other ) {
    
    return CORE_MATH_SHAPE_RECTANGLE::Contains( Center, Size, other );
}

bool CORE_MATH_SHAPE_RECTANGLE::Contains( const CORE_MATH_VECTOR & rectangle_center,
                                        const CORE_MATH_VECTOR & rectangle_size,
                                        const CORE_MATH_VECTOR & other ) {
    
    if ( rectangle_center[0] - rectangle_size[0] < other[0] && rectangle_center[0] + rectangle_size[0] > other[0] &&
        rectangle_center[1] - rectangle_size[1] < other[1] && rectangle_center[1] + rectangle_size[1] > other[1] ) {
        
        return true;
    }
    
    return false;
}
