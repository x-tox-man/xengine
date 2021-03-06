//
//  CORE_MATH_VECTOR.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_VECTOR__
#define __GAME_ENGINE_REBORN__CORE_MATH_VECTOR__

#include <math.h>
#include <assert.h>

#include "CORE_HELPERS_CLASS.h"

#define VECTOR_TOLERANCE 0.00001f

XS_CLASS_BEGIN_WITH_COPY( CORE_MATH_VECTOR )

XS_DEFINE_SERIALIZABLE

CORE_MATH_VECTOR();

CORE_MATH_VECTOR(
    const float x,
    const float y,
    const float z,
    const float w);

CORE_MATH_VECTOR( const float x, const float y);

void * operator new(size_t size) {
    
    abort();
    
    return NULL;
}

friend inline const CORE_MATH_VECTOR operator + ( const CORE_MATH_VECTOR & lhs, const CORE_MATH_VECTOR & rhs );
friend inline const CORE_MATH_VECTOR operator - ( const CORE_MATH_VECTOR & lhs, const CORE_MATH_VECTOR & rhs );
friend inline const CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & lhs, const float value );
friend inline const CORE_MATH_VECTOR operator / ( const CORE_MATH_VECTOR & lhs, const float value );

inline CORE_MATH_VECTOR & operator = ( CORE_MATH_VECTOR & rhs ) {
    
    memcpy( Value, rhs.Value, 4 * sizeof( float ) );
    
    return *this;
}

inline CORE_MATH_VECTOR & operator = ( const CORE_MATH_VECTOR & rhs ) {
    
    memcpy( Value, rhs.Value, 4 * sizeof( float ) );
    
    return *this;
}

inline CORE_MATH_VECTOR & operator *= ( CORE_MATH_VECTOR & rhs ) {
            
    abort();
    
    return *this;
}

inline const CORE_MATH_VECTOR & operator += ( const CORE_MATH_VECTOR & rhs ) {
    
    Value[ 0 ] += rhs[ 0 ];
    Value[ 1 ] += rhs[ 1 ];
    Value[ 2 ] += rhs[ 2 ];
    
    return *this;
}

inline const CORE_MATH_VECTOR & operator -= ( const CORE_MATH_VECTOR & rhs ) {
    
    Value[ 0 ] -= rhs[ 0 ];
    Value[ 1 ] -= rhs[ 1 ];
    Value[ 2 ] -= rhs[ 2 ];
    
    return *this;
}

inline bool operator == ( const CORE_MATH_VECTOR & rhs ) {
    
    for ( int i = 0; i < 4; i++ ) {
        float delta = fabs( Value[ i ] - rhs[ i ] );
                           
        if ( delta > VECTOR_TOLERANCE ) {
            
            return false;
        }
    }
    
    return true;
}

inline bool operator != ( CORE_MATH_VECTOR & rhs ) {
    
    for ( int i = 0; i < 4; i++ ) {
        
        if ( fabs( Value[ i ] - rhs[ i ] ) > VECTOR_TOLERANCE ) {
            
            return true;
        }
    }
    
    return false;
}

inline float & operator [] ( const int index ) {
    
#if DEBUG
    assert( index < 4 && index >= 0 );
#endif
    
    return Value[index];
}

inline const float & operator [] ( const int index ) const {
    
#if DEBUG
    assert( index < 4 && index >= 0 );
#endif
    
    return Value[index];
}

void Set( const float x, const float y, const float z, const float w ) {
    
    Value[0] = x;
    Value[1] = y;
    Value[2] = z;
    Value[3] = w;
}

const float ComputeSquareLength() const {
    
    float square_length;
    
    square_length = Value[0] * Value[0];
    square_length += Value[1] * Value[1];
    square_length += Value[2] * Value[2];
    
    return square_length;
}

const float ComputeLength() const {
    
    float square_length;
    
    square_length = Value[0] * Value[0];
    square_length += Value[1] * Value[1];
    square_length += Value[2] * Value[2];
    
    return sqrt( square_length );
}

const float ComputeDotProduct( const CORE_MATH_VECTOR & other ) const {
    
    float dot_product;
    
    dot_product = Value[0] * other.Value[0];
    dot_product += Value[1] * other.Value[1];
    dot_product += Value[2] * other.Value[2];
    dot_product += Value[3] * other.Value[3];
    
    return dot_product;
}

void Normalize() {
    
    float acc = sqrt( Value[2] * Value[2] + Value[1] * Value[1] + Value[0] * Value[0] );
    
    Value[0] /= acc;
    Value[1] /= acc;
    Value[2] /= acc;
}

static CORE_MATH_VECTOR
    Zero,
    One,
    XAxis,
    YAxis,
    ZAxis,
    WAxis;

private :

float Value[4];

XS_CLASS_END

inline const CORE_MATH_VECTOR operator + ( const CORE_MATH_VECTOR & lhs, const CORE_MATH_VECTOR & rhs ) {
    
    CORE_MATH_VECTOR result;
    
    result[0] = lhs[0] + rhs[0];
    result[1] = lhs[1] + rhs[1];
    result[2] = lhs[2] + rhs[2];
    result[3] = lhs[3] + rhs[3];
    
    return result;
}

inline const CORE_MATH_VECTOR operator - ( const CORE_MATH_VECTOR & lhs, const CORE_MATH_VECTOR & rhs ) {
    
    CORE_MATH_VECTOR result;
    
    result[0] = lhs[0] - rhs[0];
    result[1] = lhs[1] - rhs[1];
    result[2] = lhs[2] - rhs[2];
    result[3] = lhs[3] - rhs[3];
    
    return result;
}

inline const CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & lhs, const float value ) {
    
    CORE_MATH_VECTOR result;
    
    result[0] = lhs[0] * value;
    result[1] = lhs[1] * value;
    result[2] = lhs[2] * value;
    result[3] = lhs[3] * value;
    
    return result;
}

inline const CORE_MATH_VECTOR operator / ( const CORE_MATH_VECTOR & lhs, const float value ) {
    
    CORE_MATH_VECTOR result;
    
    result[0] = lhs[0] / value;
    result[1] = lhs[1] / value;
    result[2] = lhs[2] / value;
    result[3] = lhs[3] / value;
    
    return result;
}

#undef VECTOR_TOLERANCE

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_VECTOR__) */
