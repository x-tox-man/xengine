//
//  CORE_MATH_SHAPE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_SHAPE.h"
#include "CORE_MATH_SHAPE_BOX.h"
#include "CORE_MATH_SHAPE_SPHERE.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_MATH_SHAPE )
    XS_DEFINE_ClassMember( "Position", CORE_MATH_VECTOR, Position )
    XS_DEFINE_ClassMember( "HalfDiagonal", CORE_MATH_VECTOR, HalfDiagonal )
    XS_DEFINE_ClassMember( "Type", CORE_MATH_SHAPE_TYPE, Type )
    XS_DEFINE_ClassMember( "Orientation", CORE_MATH_QUATERNION, Orientation )
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

void CORE_MATH_SHAPE::AggregateWithBox( const CORE_MATH_SHAPE & other ) {
    
    float x_min = fmin( Position.X() - HalfDiagonal.X(), other.GetPosition().X() - other.GetHalfDiagonal().X() );
    float y_min = fmin( Position.Y() - HalfDiagonal.Y(), other.GetPosition().Y() - other.GetHalfDiagonal().Y() );
    float z_min = fmin( Position.Z() - HalfDiagonal.Z(), other.GetPosition().Z() - other.GetHalfDiagonal().Z() );
    
    float x_max = fmax( Position.X() + HalfDiagonal.X(), other.GetPosition().X() + other.GetHalfDiagonal().X() );
    float y_max = fmax( Position.Y() + HalfDiagonal.Y(), other.GetPosition().Y() + other.GetHalfDiagonal().Y() );
    float z_max = fmax( Position.Z() + HalfDiagonal.Z(), other.GetPosition().Z() + other.GetHalfDiagonal().Z() );
    
    Position.X( ( x_max + x_min ) * 0.5f );
    Position.Y( ( y_max + y_min ) * 0.5f );
    Position.Z( ( z_max + z_min ) * 0.5f );
    
    HalfDiagonal.X( fabs( x_max - x_min ) * 0.5f);
    HalfDiagonal.Y( fabs( y_max - y_min ) * 0.5f);
    HalfDiagonal.Z( fabs( y_max - z_min ) * 0.5f);
}

void CORE_MATH_SHAPE::ComputeMinMax( CORE_MATH_VECTOR & min, CORE_MATH_VECTOR & max ) const {
    
    min.Set( Position.X() - HalfDiagonal.X(), Position.Y() - HalfDiagonal.Y(), Position.Z() - HalfDiagonal.Z(), 0.0f );
    
    max.Set( Position.X() + HalfDiagonal.X(), Position.Y() + HalfDiagonal.Y(),Position.Z() + HalfDiagonal.Z(), 0.0f );
}

bool CORE_MATH_SHAPE::ContainsBox( const CORE_MATH_SHAPE & other ) {
    
    return Position.X() - HalfDiagonal.X() <= other.GetPosition().X() - other.GetHalfDiagonal().X() &&
            Position.Y() - HalfDiagonal.Y()<= other.GetPosition().Y() - other.GetHalfDiagonal().Y() &&
            Position.Z() - HalfDiagonal.Z()<= other.GetPosition().Z() - other.GetHalfDiagonal().Z() &&
            Position.X() + HalfDiagonal.X() >= other.GetPosition().X() + other.GetHalfDiagonal().X() &&
            Position.Y() + HalfDiagonal.Y() >= other.GetPosition().Y() + other.GetHalfDiagonal().Y() &&
            Position.Z() + HalfDiagonal.Z() >= other.GetPosition().Z() + other.GetHalfDiagonal().Z();
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
