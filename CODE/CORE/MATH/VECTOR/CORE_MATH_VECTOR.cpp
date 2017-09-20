//
//  CORE_MATH_VECTOR.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_VECTOR.h"
#include "CORE_DATA_STREAM.h"


XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_MATH_VECTOR )
    XS_DEFINE_ClassMember( float , Value[0] )
    XS_DEFINE_ClassMember( float , Value[1] )
    XS_DEFINE_ClassMember( float , Value[2] )
    XS_DEFINE_ClassMember( float , Value[3] )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( CORE_MATH_VECTOR )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_VECTOR, GetX )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_VECTOR, GetY )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_VECTOR, GetZ )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_VECTOR, GetW )

    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_VECTOR, X, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_VECTOR, Y, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_VECTOR, Z, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_VECTOR, W, float )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( CORE_MATH_VECTOR )

CORE_MATH_VECTOR::CORE_MATH_VECTOR() :
    Value() {
    
}

CORE_MATH_VECTOR::~CORE_MATH_VECTOR() {

}

CORE_MATH_VECTOR::CORE_MATH_VECTOR( const CORE_MATH_VECTOR & other ) :
    Value() {
    
    Value[0] = other.Value[0];
    Value[1] = other.Value[1];
    Value[2] = other.Value[2];
    Value[3] = other.Value[3];
}

CORE_MATH_VECTOR::CORE_MATH_VECTOR(
    const float x,
    const float y,
    const float z,
    const float w) :
    Value() {
        
        Value[0] = x;
        Value[1] = y;
        Value[2] = z;
        Value[3] = w;
}

CORE_MATH_VECTOR::CORE_MATH_VECTOR( const float x, const float y ) :
    Value() {
    
    Value[0] = x;
    Value[1] = y;
    Value[2] = 0.0f;
    Value[3] = 1.0f;
}

CORE_MATH_VECTOR::CORE_MATH_VECTOR( const float x, const float y, const float z ) :
Value() {
    
    Value[0] = x;
    Value[1] = y;
    Value[2] = z;
    Value[3] = 1.0f;
}


CORE_MATH_VECTOR::CORE_MATH_VECTOR( const float array[3] ) {
    
    Value[0] = array[0];
    Value[1] = array[1];
    Value[2] = array[2];
    Value[3] = 1.0f;
}


CORE_MATH_VECTOR CORE_MATH_VECTOR::Zero( 0.0f, 0.0f, 0.0f, 0.0f );
CORE_MATH_VECTOR CORE_MATH_VECTOR::One( 1.0f, 1.0f, 1.0f, 1.0f );
CORE_MATH_VECTOR CORE_MATH_VECTOR::XAxis( 1.0f, 0.0f, 0.0f, 0.0f );
CORE_MATH_VECTOR CORE_MATH_VECTOR::YAxis( 0.0f, 1.0f, 0.0f, 0.0f );
CORE_MATH_VECTOR CORE_MATH_VECTOR::ZAxis( 0.0f, 0.0f, 1.0f, 0.0f );
CORE_MATH_VECTOR CORE_MATH_VECTOR::WAxis( 0.0f, 0.0f, 0.0f, 1.0f );
