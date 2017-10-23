//
//  CORE_MATH_SHAPE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_SHAPE.h"
#include "CORE_MATH_SHAPE_BOX.h"
#include "CORE_MATH_SHAPE_SPHERE.h"
#include "CORE_MEMORY.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_MATH_SHAPE )
    XS_DEFINE_ClassMember( CORE_MATH_VECTOR, Position )
    XS_DEFINE_ClassMember( CORE_MATH_VECTOR, HalfDiagonal )
    XS_DEFINE_ClassMember( CORE_MATH_SHAPE_TYPE, Type )
    XS_DEFINE_ClassMember( CORE_MATH_QUATERNION, Orientation )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_MATH_SHAPE::CORE_MATH_SHAPE() :
    Position(),
    Orientation(),
    HalfDiagonal(),
    Type( CORE_MATH_SHAPE_TYPE_Sphere ) {
    
}

CORE_MATH_SHAPE::CORE_MATH_SHAPE( const CORE_MATH_SHAPE & other ) :
    Position( other.Position ),
    Orientation( other.Orientation ),
    HalfDiagonal( other.HalfDiagonal ),
    Type( other.Type ) {
    
}

CORE_MATH_SHAPE::~CORE_MATH_SHAPE() {

}

bool CORE_MATH_SHAPE::GetIntersection( const CORE_MATH_SHAPE & other ) {
    
    CORE_MATH_VECTOR intersection;
    
    return false;
}

bool CORE_MATH_SHAPE::GetIntersection( const CORE_MATH_RAY & ray ) {
    
    CORE_MATH_VECTOR intersection;
    
    switch (Type) {
        case CORE_MATH_SHAPE_TYPE_Box: {
            
            CORE_RUNTIME_Abort();
            
            break;
        }
            
        case CORE_MATH_SHAPE_TYPE_Sphere: {
            
            return CORE_MATH_SHAPE_SPHERE_GetIntersection( ray, Position, HalfDiagonal, intersection );
            
            break;
        }
            
        case CORE_MATH_SHAPE_TYPE_Custom: {
            
            CORE_RUNTIME_Abort();
            
            break;
        }
            
        default:
            break;
    }
    
    return false;
}
