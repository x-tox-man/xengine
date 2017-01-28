//
//  CORE_MATH_QUATERNION.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/02/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_QUATERNION__
#define __GAME_ENGINE_REBORN__CORE_MATH_QUATERNION__

#include <math.h>
#include <assert.h>
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

#define QUATERNION_TOLERANCE 0.0001f

class CORE_MATH_VECTOR;

CORE_SCALAR GLOBAL_CORE_MATH_QUATERNION_LERP( float * lhs, float * rhs);

XS_CLASS_BEGIN_WITH_COPY(CORE_MATH_QUATERNION)

    XS_DEFINE_SERIALIZABLE

    CORE_MATH_QUATERNION( CORE_MATH_QUATERNION & other ) {
        
        X( other.X() );
        Y( other.Y() );
        Z( other.Z() );
        W( other.W() );
    }

    CORE_MATH_QUATERNION() : Value() {
        
        X( 0.0f );
        Y( 0.0f );
        Z( 0.0f );
        W( 1.0f );
    }

    CORE_MATH_QUATERNION(const float x, const float y, const float z, const float w) {
        
        X( x );
        Y( y );
        Z( z );
        W( w );
    }

    inline const float & operator [] ( const int index ) const {
        
        return Value[ index ];
    }

    inline float & operator [] ( const int index ) {
        
        return Value[ index ];
    }

    inline CORE_MATH_QUATERNION & operator = ( float value[4] ) {
         
        Value[0] = value[0];
        Value[1] = value[1];
        Value[2] = value[2];
        Value[3] = value[3];
        
        return *this;
    }

    inline CORE_MATH_QUATERNION & operator = ( const CORE_MATH_QUATERNION & other ) {
        
        Value[0] =other.Value[0];
        Value[ 1 ]=other.Value[ 1 ];
        Value[ 2 ]=other.Value[ 2 ];
        Value[ 3 ]=other.Value[ 3 ];
        
        return *this;
    }

    inline CORE_MATH_QUATERNION & operator += ( const CORE_MATH_QUATERNION & rhs ) {
        
        X( X() + rhs.X() );
        Y( Y() + rhs.Y() );
        Z( Z() + rhs.Z() );
        W( W() + rhs.W() );
        
        return *this;
    }

    inline CORE_MATH_QUATERNION & operator -= ( const CORE_MATH_QUATERNION & rhs ) {
        
        X( X() - rhs.X() );
        Y( Y() - rhs.Y() );
        Z( Z() - rhs.Z() );
        W( W() - rhs.W() );
        
        return *this;
    }

    inline CORE_MATH_QUATERNION & operator *= ( const CORE_MATH_QUATERNION & q2 ) {
        
        CORE_MATH_QUATERNION q1 = *this;
        
        /*X( q2.X() * q1.X() - q2.Y() * q1.Y() - q2.Z() * q1.Z() - q2.W() * q1.W() );
        Y( q2.X() * q1.Y() + q2.Y() * q1.X() - q2.Z() * q1.W() + q2.W() * q1.Z() );
        Z( q2.X() * q1.Z() + q2.Y() * q1.W() + q2.Z() * q1.X() - q2.W() * q1.Y() );
        W( q2.X() * q1.W() - q2.Y() * q1.Z() + q2.Z() * q1.Y() + q2.W() * q1.X() );*/
        
        /*qr.scalar = v3_dot(&qa->vector, &qb->vector);
        
        v3_cross(&va, &qa->vector, &qb->vector);
        v3_scalef(&vb, &qa->vector, &qb->scalar);
        v3_scalef(&vc, &qb->vector, &qa->scalar);
        v3_add(&va, &va, &vb);
        v3_add(&qr->vector, &va, &vc);
        
        quaternion_normalise(qr);*/
        
        X(  q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() + q1.W() * q2.X() );
        Y( -q1.X() * q2.Z() + q1.Y() * q2.W() + q1.Z() * q2.X() + q1.W() * q2.Y() );
        Z(  q1.X() * q2.Y() - q1.Y() * q2.X() + q1.Z() * q2.W() + q1.W() * q2.Z() );
        W( -q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() + q1.W() * q2.W() );
        
        /*W(  q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() + q1.W() * q2.X() );
        X( -q1.X() * q2.Z() + q1.Y() * q2.W() + q1.Z() * q2.X() + q1.W() * q2.Y() );
        Y(  q1.X() * q2.Y() - q1.Y() * q2.X() + q1.Z() * q2.W() + q1.W() * q2.Z() );
        Z( -q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() + q1.W() * q2.W() );*/
        
        return *this;
    }

    inline CORE_MATH_QUATERNION & operator *= ( const float rhs ) {
        
        CORE_RUNTIME_Abort();
        
        return *this;
    }

    inline CORE_MATH_QUATERNION & operator /= ( const CORE_MATH_QUATERNION & rhs ) {
        
        CORE_RUNTIME_Abort();
        
        return *this;
    }

    friend inline bool operator == ( const CORE_MATH_QUATERNION & lhs, const CORE_MATH_QUATERNION & rhs );

    friend CORE_MATH_QUATERNION operator * ( const CORE_MATH_QUATERNION & lhs, const CORE_MATH_QUATERNION & rhs );
    friend inline CORE_MATH_QUATERNION operator * ( const CORE_MATH_QUATERNION & lhs, const float rhs );
    friend CORE_MATH_VECTOR operator * ( const CORE_MATH_QUATERNION & q1, const CORE_MATH_VECTOR & vector );
    friend CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_QUATERNION & q2 );
    friend inline CORE_MATH_QUATERNION operator + ( const CORE_MATH_QUATERNION & lhs, const CORE_MATH_QUATERNION & rhs );

    void FromMatrix( const float * matrix );
    void ToMatrix( float * matrix) const;

    void ConjugateMultiply(const CORE_MATH_QUATERNION & other);

    void RotateX( float angle );

    void RotateY( float angle );

    void RotateZ( float angle );

    CORE_MATH_QUATERNION GetConjugate() const {
        
        CORE_MATH_QUATERNION q;
        
        q.Value[0] = -Value[0];
        q.Value[1] = -Value[1];
        q.Value[2] = -Value[2];
        q.Value[3] = -Value[3];
        
        return q;
    }

    void Normalize();

    inline float X() const { return Value[0]; }
    inline float Y() const { return Value[1]; }
    inline float Z() const { return Value[2]; }
    inline float W() const { return Value[3]; }
    
    inline void X(float x) { Value[0] = x; }
    inline void Y(float y) { Value[1] = y; }
    inline void Z(float z) { Value[2] = z; }
    inline void W(float w) { Value[3] = w; }

private:

float Value[4];

XS_CLASS_END

inline bool operator == ( const CORE_MATH_QUATERNION & lhs, const CORE_MATH_QUATERNION & rhs ) {
    
    return
        ( lhs[0] - rhs[0] < QUATERNION_TOLERANCE ) &&
        ( lhs[1] - rhs[1] < QUATERNION_TOLERANCE ) &&
        ( lhs[2] - rhs[2] < QUATERNION_TOLERANCE ) &&
        ( lhs[3] - rhs[3] < QUATERNION_TOLERANCE );
}

CORE_MATH_QUATERNION operator * ( const CORE_MATH_QUATERNION & q1, const CORE_MATH_QUATERNION & q2 );

inline CORE_MATH_QUATERNION operator * ( const CORE_MATH_QUATERNION & lhs, const float rhs ) {
    
    CORE_MATH_QUATERNION result;
    
    CORE_RUNTIME_Abort();
    
    return result;
}

CORE_MATH_VECTOR operator * ( const CORE_MATH_QUATERNION & q1, const CORE_MATH_VECTOR & vector );
CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_QUATERNION & q2 );

inline CORE_MATH_QUATERNION operator + ( const CORE_MATH_QUATERNION & lhs, const CORE_MATH_QUATERNION & rhs ) {
    
    CORE_MATH_QUATERNION result;
    
     result.X( lhs.X() + rhs.X() );
     result.Y( lhs.Y() + rhs.Y() );
     result.Z( lhs.Z() + rhs.Z() );
     result.W( lhs.W() + rhs.W() );
    
    return result;
}

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_QUATERNION__) */
