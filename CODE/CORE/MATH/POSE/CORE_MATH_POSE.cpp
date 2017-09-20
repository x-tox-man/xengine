//
//  CORE_MATH_POSE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_POSE.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT(CORE_MATH_POSE)

XS_END_INTERNAL_MEMORY_LAYOUT

CORE_MATH_POSE::CORE_MATH_POSE() :
    Position(),
    Orientation() {
    
}

CORE_MATH_POSE::~CORE_MATH_POSE() {

}

CORE_MATH_POSE::CORE_MATH_POSE( CORE_MATH_POSE & other ) :
    Position(),
    Orientation() {
    
    Position[0] = other.GetPosition()[0];
    Position[1] = other.GetPosition()[1];
    Position[2] = other.GetPosition()[2];
    Position[3] = other.GetPosition()[3];
        
    Orientation[0] = other.GetOrientation()[0];
    Orientation[1] = other.GetOrientation()[1];
    Orientation[2] = other.GetOrientation()[2];
    Orientation[3] = other.GetOrientation()[3];
}

void CORE_MATH_POSE::FromMatrix( const float * mat ) {
    
    //http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
    CORE_MATH_MATRIX matrix;
    CORE_MATH_VECTOR vec;
    
    // mat0  mat1  mat2  mat3
    // mat4  mat5  mat6  mat7
    // mat8  mat9  mat10 mat11
    // mat12 mat13 mat14 mat15
    
    /*
     (m11 - 1)*m22 - m12*m21	m02*m21 - m01*(m22 - 1)	m01*m12 - m02*(m11 - 1)
     m12*m20 - m10*(m22 - 1)	m00*(m22 - 1) - m02*m20	m02*m10 - (m00 - 1)*m12
     m10*m21 - (m11 - 1)*m20	m01*m20 - (m00 - 1)*m21	m00*(m11 - 1) - m01*m10
     
     m03
     m13
     m23
     */
    
    /*matrix[0]= ( mat[5] - 1.0f ) * mat[10] - ( mat[6] * mat[9] );
     matrix[1]= ( mat[2] * mat[9] ) - mat[1] * ( mat[10] - 1.0f );
     matrix[2]= ( mat[1] * mat[6] ) - mat[2] * (mat[5] - 1.0f);
     
     matrix[4]= mat[6] * mat[8] - mat[4]*(mat[10] - 1.0f);
     matrix[5]= (mat[0] * (mat[10] - 1.0f)) - mat[2] * mat[8];
     matrix[6]= mat[2] * mat[4] - ((mat[0] - 1.0f) * mat[6]);
     
     matrix[8]= mat[4] * mat[9] - ( (mat[5] - 1.0f) * mat[8] );
     matrix[9]= mat[1] * mat[8] - ( (mat[0] - 1.0f) * mat[9] );
     matrix[10] = ( mat[0] * (mat[5] - 1.0f) ) - (mat[1] * mat[4]);
     
     vec[0] = mat[3];
     vec[1] = mat[7];
     vec[2] = mat[11];
     vec[3] = 1.0f;
     
     float det = mat.ComputeDeterminant();
     
     if ( det == 0.0f ) {
     
     CORE_RUNTIME_Abort();
     }
     else if ( det > 1.10f || det < 0.9f )
     {
     printf( "test" );
     }
     
     Position = ((CORE_MATH_VECTOR)vec)*((const CORE_MATH_MATRIX)matrix) * (1.0f / det);
     Position[3] = 1.0f;*/
    
    Orientation.FromMatrix( mat );
    
    Position.X( mat[3]);
    Position.Y( mat[7]);
    Position.Z( mat[11]);
}

void CORE_MATH_POSE::FromMatrix( const CORE_MATH_MATRIX & mat ) {
    
    //http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
    CORE_MATH_MATRIX matrix;
    CORE_MATH_VECTOR vec;
    
    // mat0  mat1  mat2  mat3
    // mat4  mat5  mat6  mat7
    // mat8  mat9  mat10 mat11
    // mat12 mat13 mat14 mat15
    
    /*
     (m11 - 1)*m22 - m12*m21	m02*m21 - m01*(m22 - 1)	m01*m12 - m02*(m11 - 1)
     m12*m20 - m10*(m22 - 1)	m00*(m22 - 1) - m02*m20	m02*m10 - (m00 - 1)*m12
     m10*m21 - (m11 - 1)*m20	m01*m20 - (m00 - 1)*m21	m00*(m11 - 1) - m01*m10
     
     m03
     m13
     m23
     */
    
    /*matrix[0]= ( mat[5] - 1.0f ) * mat[10] - ( mat[6] * mat[9] );
    matrix[1]= ( mat[2] * mat[9] ) - mat[1] * ( mat[10] - 1.0f );
    matrix[2]= ( mat[1] * mat[6] ) - mat[2] * (mat[5] - 1.0f);
    
    matrix[4]= mat[6] * mat[8] - mat[4]*(mat[10] - 1.0f);
    matrix[5]= (mat[0] * (mat[10] - 1.0f)) - mat[2] * mat[8];
    matrix[6]= mat[2] * mat[4] - ((mat[0] - 1.0f) * mat[6]);
    
    matrix[8]= mat[4] * mat[9] - ( (mat[5] - 1.0f) * mat[8] );
    matrix[9]= mat[1] * mat[8] - ( (mat[0] - 1.0f) * mat[9] );
    matrix[10] = ( mat[0] * (mat[5] - 1.0f) ) - (mat[1] * mat[4]);
    
    vec[0] = mat[3];
    vec[1] = mat[7];
    vec[2] = mat[11];
    vec[3] = 1.0f;
    
    float det = mat.ComputeDeterminant();
    
    if ( det == 0.0f ) {
        
        CORE_RUNTIME_Abort();
    }
    else if ( det > 1.10f || det < 0.9f )
    {
        printf( "test" );
    }
    
    Position = ((CORE_MATH_VECTOR)vec)*((const CORE_MATH_MATRIX)matrix) * (1.0f / det);
    Position[3] = 1.0f;*/
    
    Orientation.FromMatrix( &mat[0] );
    
    Position.X( mat[3]);
    Position.Y( mat[7]);
    Position.Z( mat[11]);
    Position.W( mat[15]);
}

void setRotate( const CORE_MATH_QUATERNION & q ,const CORE_MATH_VECTOR & centre, CORE_MATH_MATRIX & m) {

    float sqw = q.W()*q.W();
    float sqx = q.X()*q.X();
    float sqy = q.Y()*q.Y();
    float sqz = q.Z()*q.Z();
    
    m[0] = sqx - sqy - sqz + sqw; // since sqw + sqx + sqy + sqz =1
    m[5] = -sqx + sqy - sqz + sqw;
    m[10] = -sqx - sqy + sqz + sqw;
    
    float tmp1 = q.X()*q.Y();
    float tmp2 = q.Z()*q.W();
    
    m[4] = 2.0f * (tmp1 + tmp2);
    m[1] = 2.0f * (tmp1 - tmp2);
    
    tmp1 = q.X()*q.Z();
    tmp2 = q.Y()*q.W();
    
    m[8] = 2.0f * (tmp1 - tmp2);
    m[2] = 2.0f * (tmp1 + tmp2);
    
    tmp1 = q.Y()*q.Z();
    tmp2 = q.X()*q.W();
    
    m[9] = 2.0f * (tmp1 + tmp2);
    m[6] = 2.0f * (tmp1 - tmp2);
    
    float a1,a2,a3;
    
    if (centre == CORE_MATH_VECTOR::Zero ) {
        
        a1=a2=a3=0;
    } else {
        
        a1 = centre[0];
        a2 = centre[1];
        a3 = centre[2];
    }
    m[3] = a1 - a1 * m[0] - a2 * m[1] - a3 * m[2];
    m[7] = a2 - a1 * m[4] - a2 * m[5] - a3 * m[6];
    m[11] = a3 - a1 * m[8] - a2 * m[9] - a3 * m[10];
    
    m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
}

void CORE_MATH_POSE::ToMatrix( CORE_MATH_MATRIX & matrix ) const {
    
    Orientation.ToMatrix( matrix.GetRow(0) );
    
    matrix[3] = Position.X();
    matrix[7] = Position.Y();
    matrix[11] = Position.Z();
    
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
    //setRotate( Orientation, Position, matrix );
}


void CORE_MATH_POSE::ToMatrix( float * matrix ) const {
    
    Orientation.ToMatrix( matrix );
    
    matrix[3] = Position.X();
    matrix[7] = Position.Y();
    matrix[11] = Position.Z();
    
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
    //setRotate( Orientation, Position, matrix );
}

void CORE_MATH_POSE::Lerp( const CORE_MATH_POSE & other, CORE_MATH_POSE & result, float percentage ) {
    
    float one_minus_percentage = (1.0f - percentage);
    
    result.GetPosition()[0] = Position[0] * one_minus_percentage + other.GetPosition()[0] * percentage;
    result.GetPosition()[1] = Position[1] * one_minus_percentage + other.GetPosition()[1] * percentage;
    result.GetPosition()[2] = Position[2] * one_minus_percentage + other.GetPosition()[2] * percentage;
    result.GetPosition()[3] = Position[3] * one_minus_percentage + other.GetPosition()[3] * percentage;
    
    result.GetOrientation()[0] = Orientation[0] * one_minus_percentage + other.GetOrientation()[0] * percentage;
    result.GetOrientation()[1] = Orientation[1] * one_minus_percentage + other.GetOrientation()[1] * percentage;
    result.GetOrientation()[2] = Orientation[2] * one_minus_percentage + other.GetOrientation()[2] * percentage;
    result.GetOrientation()[3] = Orientation[3] * one_minus_percentage + other.GetOrientation()[3] * percentage;
}

void CORE_MATH_POSE::CopyFrom( const CORE_MATH_POSE & other ) {
    
    Position = other.GetPosition();
    Orientation = other.GetOrientation();
}

CORE_MATH_POSE & CORE_MATH_POSE::operator *= ( const CORE_MATH_POSE & other) {
    
    Position += other.GetPosition();
    //Orientation.Normalize();
    
    return *this;
}

CORE_MATH_POSE operator * ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs) {
    
    //TODO : proper quaternion * vector math
    
    CORE_MATH_POSE pose;
    CORE_MATH_QUATERNION q;
    
    CORE_MATH_MATRIX m;
    
    lhs.ToMatrix(m);
    
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    
    pose.SetPosition( m * rhs.GetPosition() + lhs.GetPosition());
    pose.GetPosition().W( 1.0f );
    
    q = lhs.GetOrientation() * rhs.GetOrientation();
    
    pose.SetOrientation( q );
    
    return pose;
}

CORE_MATH_POSE & CORE_MATH_POSE::operator = ( const CORE_MATH_POSE & other)
{
    Position[0] = other.GetPosition()[0];
    Position[1] = other.GetPosition()[1];
    Position[2] = other.GetPosition()[2];
    Position[3] = other.GetPosition()[3];
    
    Orientation[0] = other.GetOrientation()[0];
    Orientation[1] = other.GetOrientation()[1];
    Orientation[2] = other.GetOrientation()[2];
    Orientation[3] = other.GetOrientation()[3];
    
    return *this;
}
