//
//  CORE_MATH_MATRIX.h
//  GAME-ENGINE
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
#include "CORE_RUNTIME_ENVIRONMENT.h"

#define MATRIX_TOLERANCE 0.0001f

XS_CLASS_BEGIN_WITH_COPY( CORE_MATH_MATRIX )

XS_DEFINE_SERIALIZABLE

    CORE_MATH_MATRIX();
    ~CORE_MATH_MATRIX();

    explicit CORE_MATH_MATRIX( const float array[ 16 ] ) {
        
        memcpy( Value, array, 16 * sizeof( float ) );
    }

    CORE_MATH_MATRIX( float v00, float v01, float v02, float v03,
                     float v10, float v11, float v12, float v13,
                     float v20, float v21, float v22, float v23,
                     float v30, float v31, float v32, float v33) {
        
        Value[0] = v00;
        Value[1] = v01;
        Value[2] = v02;
        Value[3] = v03;
        
        Value[4] = v10;
        Value[5] = v11;
        Value[6] = v12;
        Value[7] = v13;
        
        Value[8] = v20;
        Value[9] = v21;
        Value[10] = v22;
        Value[11] = v23;
        
        Value[12] = v30;
        Value[13] = v31;
        Value[14] = v32;
        Value[15] = v33;
    }

    bool IsIdentity() const {
        
        return Value[0] == 1.0f && Value[15] == 1.0f && Value[5] == 1.0f && Value[10] == 1.0f &&
            Value[1] == 0.0f && Value[2] == 0.0f && Value[3] == 0.0f && Value[4] == 0.0f
            && Value[6] == 0.0f && Value[7] == 0.0f && Value[8] == 0.0f && Value[9] == 0.0f
            && Value[11] == 0.0f && Value[12] == 0.0f && Value[13] == 0.0f && Value[14] == 0.0f;
    }

    bool FastyIsIdentity() {
        
        const bool ide = Value[0] == 1.0f && Value[15] == 1.0f && Value[5] == 1.0f && Value[10] == 1.0f;
        
        return ide;
    }

    void SetIdentity() {
        
        memcpy( Value, Identity, 16 * sizeof( float ) );
    }

    void Translate( float translation[3] );

    void Translate( const float translation[3] );

    void Translate( const CORE_MATH_VECTOR & translation );

    void XRotate( const float angle );

    void YRotate( const float angle );

    void ZRotate( const float angle );

    void Scale( const CORE_MATH_VECTOR & scale_vector );

    void Scale( const float scale_x, const float scale_y, const float scale_z );

    void GetInverse( CORE_MATH_MATRIX & inverse) const;

    float ComputeDeterminant() const;

    void Print() const {
        SERVICE_LOGGER_Error( "%f %f %f %f\n", Value[0], Value[1], Value[2], Value[3]);
        SERVICE_LOGGER_Error( "%f %f %f %f\n", Value[4], Value[5], Value[6], Value[7]);
        SERVICE_LOGGER_Error( "%f %f %f %f\n", Value[8], Value[9], Value[10], Value[11]);
        SERVICE_LOGGER_Error( "%f %f %f %f\n", Value[12], Value[13], Value[14], Value[15]);
    }

    inline float * GetRow( int row ) {
        
        #if DEBUG
            assert( row >= 0 && row < 4 );
        #endif
        
        return Value + row * 4;
    }

    inline float GetAtRowCol( int row, int col ) const {
        
        return *(Value + (row * 4 + col));
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

    friend inline CORE_MATH_MATRIX operator * ( const CORE_MATH_MATRIX & lhs, const CORE_MATH_MATRIX & rhs );
    friend inline CORE_SCALAR operator * ( float vector[4], const CORE_MATH_MATRIX & rhs );
    friend inline CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_MATRIX & rhs );
    friend inline CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & rhs, const CORE_MATH_MATRIX & lhs );
    //friend inline CORE_MATH_MATRIX operator + ( const CORE_MATH_MATRIX & lhs, const CORE_MATH_MATRIX & rhs );
    //friend inline CORE_MATH_MATRIX operator * ( const CORE_MATH_MATRIX & lhs, const CORE_MATH_VECTOR & rhs );

    static float Identity[16];

    private:

    float detCol( int col );

    float
        Value[16];

XS_CLASS_END

inline CORE_MATH_MATRIX operator * ( const CORE_MATH_MATRIX & lhs, const CORE_MATH_MATRIX & rhs ) {
    
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

inline CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_MATRIX & rhs ) {
    
    CORE_MATH_VECTOR result;
    
    for (int c = 0 ; c < 4; c ++ ) {
        
        result[ c ]  = vector[ 0 ] * rhs[ c + ( 4 * 0 ) ];
        result[ c ] += vector[ 1 ] * rhs[ c + ( 4 * 1 ) ];
        result[ c ] += vector[ 2 ] * rhs[ c + ( 4 * 2 ) ];
        result[ c ] += vector[ 3 ] * rhs[ c + ( 4 * 3 ) ];
    }
    
    return result;
}

inline CORE_MATH_VECTOR operator * ( const CORE_MATH_MATRIX & lhs, const CORE_MATH_VECTOR & vector ) {
    
    CORE_MATH_VECTOR result;
    
    for (int c = 0 ; c < 4; c ++ ) {
        
        result[ c ]  = lhs[ 4 * c + 0 ] * vector[ 0 ];
        result[ c ] += lhs[ 4 * c + 1 ] * vector[ 1 ];
        result[ c ] += lhs[ 4 * c + 2 ] * vector[ 2 ];
        result[ c ] += lhs[ 4 * c + 3 ] * vector[ 3 ];
    }
    
    return result;
}

inline CORE_MATH_MATRIX operator + ( const CORE_MATH_MATRIX & lhs, const CORE_MATH_MATRIX & rhs ) {
    
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
