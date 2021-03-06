//
//  CORE_MATH_QUATERNION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/02/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_MATH_QUATERNION )
    XS_DEFINE_ClassMemberArray( "Value", float , (float*) Value, 4 )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( CORE_MATH_QUATERNION )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_QUATERNION, GetX )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_QUATERNION, GetY )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_QUATERNION, GetZ )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( float , CORE_MATH_QUATERNION, GetW )

    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, X, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, Y, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, Z, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, W, float )

    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, RotateX, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, RotateY, float )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(CORE_MATH_QUATERNION, RotateZ, float )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( CORE_MATH_QUATERNION )

/*
 qw= √(1 + m00 + m11 + m22) /2
 qx = (m21 - m12)/( 4 *qw)
 qy = (m02 - m20)/( 4 *qw)
 qz = (m10 - m01)/( 4 *qw)
 */

CORE_MATH_QUATERNION::CORE_MATH_QUATERNION( const CORE_MATH_QUATERNION & other ) {
    
    X( other.X() );
    Y( other.Y() );
    Z( other.Z() );
    W( other.W() );
}

CORE_MATH_QUATERNION::~CORE_MATH_QUATERNION() {

}

void CORE_MATH_QUATERNION::FromMatrix( const float * matrix  ) {
    
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
    /**
     * qw= √(1 + m00 + m11 + m22) /2
     * qx = (m21 - m12)/( 4 *qw)
     * qy = (m02 - m20)/( 4 *qw)
     * qz = (m10 - m01)/( 4 *qw)
     */
    
    Value[3] = sqrtf( 1.0f + matrix[0] + matrix[5] + matrix[10] ) * 0.5f;
    double w4 = (4.0 * (double)Value[3]);
    
    Value[0] = ( float ) ( ( (double)matrix[6] - (double)matrix[9] ) / w4 );
    Value[1] = ( float ) ( ( (double)matrix[8] - (double)matrix[2] ) / w4 );
    Value[2] = ( float ) ( ( (double)matrix[1] - (double)matrix[4] ) / w4 );
}

void CORE_MATH_QUATERNION::FromVector( const CORE_MATH_VECTOR & vector ) {
    
    //float theta = (float)(sqrt((vector.X()*vector.X() + vector.Y()*vector.Y() + vector.Z()*vector.Z())*180.0f/M_PI);
    
    Value[0] = vector.X();
    Value[1] = vector.Y();
    Value[2] = vector.Z();
    Value[3] = 0.0f;
}

/*
 1 - 2*qy2 - 2*qz2	2*qx*qy - 2*qz*qw	2*qx*qz + 2*qy*qw
 2*qx*qy + 2*qz*qw	1 - 2*qx2 - 2*qz2	2*qy*qz - 2*qx*qw
 2*qx*qz - 2*qy*qw	2*qy*qz + 2*qx*qw	1 - 2*qx2 - 2*qy2
 */

void CORE_MATH_QUATERNION::ToMatrix( float * matrix  ) const {
    
    GLOBAL_IDENTITY_MATRIX( matrix );
    
    CORE_MATH_MATRIX rot_matrix( CORE_MATH_MATRIX::Identity );
    
    #if DEBUG
        float mag2 = Value[3] * Value[3] + Value[0] * Value[0] + Value[1] * Value[1] + Value[2] * Value[2];
    
        const float TOLERANCE = 0.1f;
        
        if (fabs(mag2) > TOLERANCE && fabs(mag2 - 1.0f) > TOLERANCE) {
            //assert( false );
        }
    #endif
    
    // TODO: test if quaternion is not normalized
    //if ( is_normalized != 1.0f ) {
        
        /*float n = sqrtf(quaternion[0]*quaternion[0] + quaternion[1]*quaternion[1] + quaternion[2]*quaternion[2] + quaternion[3]*quaternion[3]);
        
        quaternion[0] /= n;
        quaternion[1] /= n;
        quaternion[2] /= n;
        quaternion[3] /= n;*/
    //}
    
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
    /*1 - 2*qy2 - 2*qz2	2*qx*qy - 2*qz*qw	2*qx*qz + 2*qy*qw
    2*qx*qy + 2*qz*qw	1 - 2*qx2 - 2*qz2	2*qy*qz - 2*qx*qw
    2*qx*qz - 2*qy*qw	2*qy*qz + 2*qx*qw	1 - 2*qx2 - 2*qy2*/
    
    rot_matrix[0] =  1.0f - 2.0f * Y() * Y() - 2.0f * Z() * Z();
    rot_matrix[4] =  2.0f * X() * Y() - ( 2.0f * Z() * W());
    rot_matrix[8] =  (2.0f * X() * Z()) + ( 2.0f * Y() * W());
    
    rot_matrix[1] =  2.0f * X() * Y() + ( 2.0f * Z() * W());
    rot_matrix[5] =  1.0f - 2.0f * X() * X() - 2.0f * Z() * Z();
    rot_matrix[9] =  ( 2.0f * Y() * Z() ) - ( 2.0f * X() * W() );
    
    rot_matrix[2] =  ( 2.0f * X() * Z() ) - ( 2.0f * Y() * W() );
    rot_matrix[6] =  ( 2.0f * Y() * Z() ) + ( 2.0f * X() * W() );
    rot_matrix[10] = 1.0f - 2.0f * X() * X() - 2.0f * Y() * Y();
    
    memcpy(matrix, rot_matrix.GetRow(0), 16* sizeof(float) );
}

void CORE_MATH_QUATERNION::RotateX( float angle ) {
    
    CORE_MATH_MATRIX mat( CORE_MATH_MATRIX::Identity );
    
    mat.XRotate( angle );
    
    CORE_MATH_QUATERNION quaternion;
    
    quaternion.FromMatrix( mat.GetRow( 0 ) );
    
    quaternion.Normalize();
    
    *this *= quaternion;
}

void CORE_MATH_QUATERNION::RotateY( float angle ) {
    
    /*CORE_MATH_QUATERNION quaternion( 0.0f, sinf( angle / 2.0 ), 0.0f, cos( angle / 2.0 ) );
    
    quaternion.Normalize();*/
    
    CORE_MATH_MATRIX mat( CORE_MATH_MATRIX::Identity );
    
    mat.YRotate( angle );
    
    CORE_MATH_QUATERNION quaternion;
    
    quaternion.FromMatrix( mat.GetRow( 0 ) );
    
    quaternion.Normalize();
    
    
    *this *= quaternion;
}

void CORE_MATH_QUATERNION::RotateZ( float angle ) {
    
    /*CORE_MATH_QUATERNION quaternion( 0.0f, 0.0f, sinf( angle / 2.0 ), cos( angle / 2.0 ) );
    
    quaternion.Normalize();*/
    
    CORE_MATH_MATRIX mat( CORE_MATH_MATRIX::Identity );
    
    mat.ZRotate( angle );
    
    CORE_MATH_QUATERNION quaternion;
    
    quaternion.FromMatrix( mat.GetRow( 0 ) );
    
    quaternion.Normalize();
    
    *this *= quaternion;
}

void CORE_MATH_QUATERNION::Normalize() {
    
    // TODO: test if quaternion is not normalized
    //if ( is_normalized != 1.0f ) {
    
    float n = sqrtf(Value[0]*Value[0] + Value[1]*Value[1] + Value[2]*Value[2] + Value[3]*Value[3]);
     
     Value[0] /= n;
     Value[1] /= n;
     Value[2] /= n;
     Value[3] /= n;
}

void CORE_MATH_QUATERNION::ConjugateMultiply(const CORE_MATH_QUATERNION & other) {

    X(X());
    Y(-Y());
    Z(-Z());
    W(-W());
    
    *this *= other;
}

CORE_MATH_QUATERNION operator * ( const CORE_MATH_QUATERNION & q1, const CORE_MATH_QUATERNION & q2 ) {
    
    CORE_MATH_QUATERNION result;
    
    //http://www.gamedev.net/page/resources/_/technical/math-and-physics/quaternion-powers-r1095
    
    /**
     w = w1w2 - x1x2 - y1y2 - z1z2
     x = w1x2 + x1w2 + y1z2 - z1y2
     y = w1y2 + y1w2 + z1x2 - x1z2
     z = w1z2 + z1w2 + x1y2 - y1x2
     w=w1w2 - x1x2 - y1y2 - z1z2
     x = w1x2 + x1w2 + y1z2 - z1y2
     y = w1y2 + y1w2 + z1x2 - x1z2
     z = w1z2 + z1w2 + x1y2 - y1x2
     */
    
    /*result.X( q1.W() * q2.W() - q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() );
    result.Y( q1.W() * q2.X() + q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() );
    result.Z( q1.W() * q2.Y() + q1.Y() * q2.W() + q1.Z() * q2.X() - q1.X() * q2.Z() );
    result.W( q1.W() * q2.Z() + q1.Z() * q2.W() + q1.X() * q2.Y() - q1.Y() * q2.X() );*/
    
    result.X(  q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() + q1.W() * q2.X() );
    result.Y( -q1.X() * q2.Z() + q1.Y() * q2.W() + q1.Z() * q2.X() + q1.W() * q2.Y() );
    result.Z(  q1.X() * q2.Y() - q1.Y() * q2.X() + q1.Z() * q2.W() + q1.W() * q2.Z() );
    result.W( -q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() + q1.W() * q2.W() );
    
    /*result.X( q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() - q1.W() * q2.W() );
    result.Y( q1.Y() * q2.X() + q1.X() * q2.Y() + q1.Z() * q2.W() - q1.W() * q2.Z() );
    result.Z( q1.Z() * q2.X() + q1.X() * q2.Z() + q1.W() * q2.Y() - q1.Y() * q2.W() );
    result.W( q1.W() * q2.X() + q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() );*/
    
    /*result.X( q2.X() * q1.W() - q2.Y() * q1.Z() + q2.Z() * q1.Y() + q2.W() * q1.X() );
    result.Y( q2.X() * q1.X() - q2.Y() * q1.Y() - q2.Z() * q1.Z() - q2.W() * q1.W() );
    result.Z( q2.X() * q1.Y() + q2.Y() * q1.X() - q2.Z() * q1.W() + q2.W() * q1.Z() );
    result.W( q2.X() * q1.Z() + q2.Y() * q1.W() + q2.Z() * q1.X() - q2.W() * q1.Y() );
    
    result.W( q2.W() * q1.W() - q2.X() * q1.X() - q2.Y() * q1.Y() - q2.Z() * q1.Z() );
    result.X( q2.Y() * q1.Z() - q2.Z() * q1.Y() + q2.W() * q1.X() + q2.X() * q1.W() );
    result.Y( q2.Z() * q1.X() - q2.X() * q1.Z() + q2.W() * q1.Y() + q2.Y() * q1.W() );
    result.Z( q2.X() * q1.Y() - q2.Y() * q1.X() + q2.W() * q1.Z() + q2.Z() * q1.W() );*/
    
    result.Normalize();
    
    return result;
}

CORE_MATH_VECTOR operator * ( const CORE_MATH_QUATERNION & q1, const CORE_MATH_VECTOR & vector )
{
    CORE_MATH_QUATERNION q2(vector[0], vector[1], vector[2], 0.0f);
    CORE_MATH_VECTOR result;
    
    result.X(  q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() + q1.W() * q2.X() );
    result.Y( -q1.X() * q2.Z() + q1.Y() * q2.W() + q1.Z() * q2.X() + q1.W() * q2.Y() );
    result.Z(  q1.X() * q2.Y() - q1.Y() * q2.X() + q1.Z() * q2.W() + q1.W() * q2.Z() );
    result.W( -q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() + q1.W() * q2.W() );
    
    return result;
}

CORE_MATH_VECTOR operator * ( const CORE_MATH_VECTOR & vector, const CORE_MATH_QUATERNION & q2  )
{
    CORE_MATH_QUATERNION q1(vector[0], vector[1], vector[2], 0.0f);
    CORE_MATH_VECTOR result;
    
    result.X(  q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y() + q1.W() * q2.X() );
    result.Y( -q1.X() * q2.Z() + q1.Y() * q2.W() + q1.Z() * q2.X() + q1.W() * q2.Y() );
    result.Z(  q1.X() * q2.Y() - q1.Y() * q2.X() + q1.Z() * q2.W() + q1.W() * q2.Z() );
    result.W( -q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z() + q1.W() * q2.W() );
    
    return result;
}
