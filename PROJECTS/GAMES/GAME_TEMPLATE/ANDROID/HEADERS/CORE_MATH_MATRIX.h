//
//  CORE_MATH_MATRIX.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_MATRIX__
#define __GAME_ENGINE_REBORN__CORE_MATH_MATRIX__

#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_VECTOR.h"

#define MATRIX_TOLERANCE 0.00001f

XS_CLASS_BEGIN_WITH_COPY( CORE_MATH_MATRIX )

CORE_MATH_MATRIX() {

}

explicit CORE_MATH_MATRIX( const float array[ 16 ] ) {
    
    memcpy( Value, array, 16 * sizeof( float ) );
}

void Translate( float translation[3] );

void Translate( const float translation[3] );

void Translate( const CORE_MATH_VECTOR & translation );

void XRotate( const float angle );

void YRotate( const float angle );

void ZRotate( const float angle );

void Scale( const float scale_x, const float scale_y, const float scale_z );

void GetInverse( CORE_MATH_MATRIX & inverse) const;

void * operator new(size_t size) {
    
    abort();
    
    return NULL;
}

inline CORE_MATH_MATRIX & operator = ( CORE_MATH_MATRIX & rhs ) {
    
    memcpy( Value, rhs.Value, 16 * sizeof( float ) );
    
    return *this;
}

inline CORE_MATH_MATRIX & operator = ( const CORE_MATH_MATRIX & rhs ) {
    
    memcpy( Value, rhs.Value, 16 * sizeof( float ) );
    
    return *this;
}

inline CORE_MATH_MATRIX & operator *= ( const CORE_MATH_MATRIX & rhs ) {
    
    float lhs[16];
    
    memcpy( lhs, Value, 16 * sizeof( float ) );
    
    for (int r = 0 ; r < 4; r ++ ) {
        
        for (int c = 0 ; c < 4; c ++ ) {
            
            int offset = ( r * 4 ) + c;
            
            Value[ offset ]  = lhs[ ( r * 4 ) + 0 ] * rhs[ c + ( 4 * 0 ) ];
            Value[ offset ] += lhs[ ( r * 4 ) + 1 ] * rhs[ c + ( 4 * 1 ) ];
            Value[ offset ] += lhs[ ( r * 4 ) + 2 ] * rhs[ c + ( 4 * 2 ) ];
            Value[ offset ] += lhs[ ( r * 4 ) + 3 ] * rhs[ c + ( 4 * 3 ) ];
        }
    }
    
    return *this;
}

inline CORE_MATH_MATRIX & operator += ( CORE_MATH_MATRIX & rhs ) {
    
    for ( int i = 0; i < 16; i++ ) {
        
        Value[ i ] = Value[ i ] + rhs[ 0 ];
    }
    
    return *this;
}

inline bool operator == ( CORE_MATH_MATRIX & rhs ) {
    
    for ( int i = 0; i < 16; i++ ) {
        
        if ( fabs( Value[ i ] - rhs[ i ] ) > MATRIX_TOLERANCE ) {

            return false;
        }
    }
    
    return true;
}

inline bool operator != ( CORE_MATH_MATRIX & rhs ) {
    
    for ( int i = 0; i < 16; i++ ) {
        
        if ( fabs( Value[ i ] - rhs[ i ] ) > MATRIX_TOLERANCE ) {
            
            return true;
        }
    }
    
    return false;
}

inline float & operator [] ( const int index ) {
    
    #if DEBUG
        assert( index < 16 && index >= 0 );
    #endif
    
    return Value[index];
}

inline const float & operator [] ( const int index ) const {
    
#if DEBUG
    assert( index < 16 && index >= 0 );
#endif
    
    return Value[index];
}

friend inline CORE_MATH_MATRIX operator * ( CORE_MATH_MATRIX & lhs, CORE_MATH_MATRIX & rhs );
friend inline CORE_SCALAR operator * ( float vector[4], CORE_MATH_MATRIX & rhs );
friend inline const CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_MATRIX & rhs );
friend inline CORE_MATH_MATRIX operator + ( CORE_MATH_MATRIX & lhs, CORE_MATH_MATRIX & rhs );

static float Identity[16];

private:

float Value[16];

XS_CLASS_END

inline CORE_MATH_MATRIX operator * ( CORE_MATH_MATRIX & lhs, CORE_MATH_MATRIX & rhs ) {
    
    CORE_MATH_MATRIX result;

    for (int r = 0 ; r < 4; r ++ ) {
        
        for (int c = 0 ; c < 4; c ++ ) {
            
            int offset = ( r * 4 ) + c;
            
            result[ offset ]  = lhs[ ( r * 4 ) + 0 ] * rhs[ c + ( 4 * 0 ) ];
            result[ offset ] += lhs[ ( r * 4 ) + 1 ] * rhs[ c + ( 4 * 1 ) ];
            result[ offset ] += lhs[ ( r * 4 ) + 2 ] * rhs[ c + ( 4 * 2 ) ];
            result[ offset ] += lhs[ ( r * 4 ) + 3 ] * rhs[ c + ( 4 * 3 ) ];
        }
    }
    
    return result;
}

inline CORE_SCALAR operator * ( float vector[4], CORE_MATH_MATRIX & rhs ) {
    
    CORE_SCALAR result;
    
    for (int c = 0 ; c < 4; c ++ ) {
        
        result.Value.FloatArray4[ c ]  = vector[ 0 ] * rhs[ c + ( 4 * 0 ) ];
        result.Value.FloatArray4[ c ] += vector[ 1 ] * rhs[ c + ( 4 * 1 ) ];
        result.Value.FloatArray4[ c ] += vector[ 2 ] * rhs[ c + ( 4 * 2 ) ];
        result.Value.FloatArray4[ c ] += vector[ 3 ] * rhs[ c + ( 4 * 3 ) ];
    }
    
    return result;
}

inline const CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_MATRIX & rhs ) {
    
    CORE_MATH_VECTOR result;
    
    for (int c = 0 ; c < 4; c ++ ) {
        
        result[ c ]  = vector[ 0 ] * rhs[ c + ( 4 * 0 ) ];
        result[ c ] += vector[ 1 ] * rhs[ c + ( 4 * 1 ) ];
        result[ c ] += vector[ 2 ] * rhs[ c + ( 4 * 2 ) ];
        result[ c ] += vector[ 3 ] * rhs[ c + ( 4 * 3 ) ];
    }
    
    return result;
}

inline CORE_MATH_MATRIX operator + ( CORE_MATH_MATRIX & lhs, CORE_MATH_MATRIX & rhs ) {
    
    CORE_MATH_MATRIX result;
    
    for ( int i = 0; i < 16; i++ ) {
        
        result[i] = lhs[ i ] + rhs[ 0 ];
    }
    
    return result;
}

float * GLOBAL_MULTIPLY_MATRIX(float *lhs, float *rhs);

void GLOBAL_IDENTITY_MATRIX(float * matrix);
void GLOBAL_COPY_MATRIX(float * dest, float * source );
bool GLOBAL_EQUALS_MATRIX(float * lhs, float * rhs );

void GLOBAL_ROTATE_MATRIX( float * matrix, float rotate_x, float rotate_y, float rotate_z );
void GLOBAL_TRANSLATE_MATRIX(float * matrix, float * vector );

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_MATRIX__) */

#undef MATRIX_TOLERANCE
