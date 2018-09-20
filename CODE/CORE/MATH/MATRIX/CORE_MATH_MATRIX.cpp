//
//  CORE_MATH_MATRIX.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_MATRIX.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_MATH_MATRIX )
    XS_DEFINE_ClassMemberArray( "Value", float , (float*) Value, 16 )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_MATH_MATRIX::CORE_MATH_MATRIX( const  CORE_MATH_MATRIX  & other ) {

    memcpy( Value, other.Value, 16 * sizeof( float ) );
}

CORE_MATH_MATRIX::CORE_MATH_MATRIX() {
    
    GLOBAL_IDENTITY_MATRIX( Value );
}

CORE_MATH_MATRIX::~CORE_MATH_MATRIX() {

}

void CORE_MATH_MATRIX::Translate( float translation[3] )  {
    
    Value[3] += translation[0];
    Value[7] += translation[1];
    Value[11] += translation[2];
}

void CORE_MATH_MATRIX::Translate( const float translation[3] ) {
    
    Value[3] += translation[0];
    Value[7] += translation[1];
    Value[11] += translation[2];
}

void CORE_MATH_MATRIX::Translate( const CORE_MATH_VECTOR & translation ) {
    
    Value[3] += translation[0];
    Value[7] += translation[1];
    Value[11] += translation[2];
}

void CORE_MATH_MATRIX::XRotate( const float angle ) {
    
    CORE_MATH_MATRIX rotation( Identity );
    
    rotation[4] = 0.0f;
    rotation[5] = cosf( angle );
    rotation[6] = -sinf( angle );
    rotation[7] = 0.0f;
    
    rotation[8] = 0.0f;
    rotation[9] = sinf( angle );
    rotation[10] = cosf( angle );
    rotation[11] = 0.0f;
    
    *this *= rotation;
}

void CORE_MATH_MATRIX::YRotate( const float angle ) {
    
    CORE_MATH_MATRIX rotation( Identity );
    
    rotation[0] = cosf( angle );
    rotation[1] = 0.0f;
    rotation[2] = sinf( angle );
    rotation[3] = 0.0f;
    
    rotation[8] = -sinf( angle );
    rotation[9] = 0.0f;
    rotation[10] = cosf( angle );
    rotation[11] = 0.0f;
    
    *this *= rotation;
}

void CORE_MATH_MATRIX::ZRotate( const float angle ) {
    
    CORE_MATH_MATRIX rotation( Identity );
    
    rotation[0] = cosf( angle );
    rotation[1] = -sinf( angle );
    rotation[2] = 0.0f;
    rotation[3] = 0.0f;
    
    rotation[4] = sinf( angle );
    rotation[5] = cosf( angle );
    rotation[6] = 0.0f;
    rotation[7] = 0.0f;
    
    *this *= rotation;
}

void CORE_MATH_MATRIX::Scale( const CORE_MATH_VECTOR & scale_vector ) {
    
    CORE_MATH_MATRIX scaling( Identity );
    
    scaling[0] = scale_vector[0];
    scaling[5] = scale_vector[1];
    scaling[10] = scale_vector[2];
    
    *this *= scaling;
}

void CORE_MATH_MATRIX::Scale( const float scale_x, const float scale_y, const float scale_z ) {
    
    CORE_MATH_MATRIX scaling( Identity );
    
    scaling[0] = scale_x;
    scaling[5] = scale_y;
    scaling[10] = scale_z;
    
    *this *= scaling;
}

void CORE_MATH_MATRIX::GetInverse( CORE_MATH_MATRIX & inverse ) const {
    
    float det;
    int i;
    
    inverse[0] = Value[5]  * Value[10] * Value[15] -
    Value[5]  * Value[11] * Value[14] -
    Value[9]  * Value[6]  * Value[15] +
    Value[9]  * Value[7]  * Value[14] +
    Value[13] * Value[6]  * Value[11] -
    Value[13] * Value[7]  * Value[10];
    
    inverse[4] = -Value[4]  * Value[10] * Value[15] +
    Value[4]  * Value[11] * Value[14] +
    Value[8]  * Value[6]  * Value[15] -
    Value[8]  * Value[7]  * Value[14] -
    Value[12] * Value[6]  * Value[11] +
    Value[12] * Value[7]  * Value[10];
    
    inverse[8] = Value[4]  * Value[9] * Value[15] -
    Value[4]  * Value[11] * Value[13] -
    Value[8]  * Value[5] * Value[15] +
    Value[8]  * Value[7] * Value[13] +
    Value[12] * Value[5] * Value[11] -
    Value[12] * Value[7] * Value[9];
    
    inverse[12] = -Value[4]  * Value[9] * Value[14] +
    Value[4]  * Value[10] * Value[13] +
    Value[8]  * Value[5] * Value[14] -
    Value[8]  * Value[6] * Value[13] -
    Value[12] * Value[5] * Value[10] +
    Value[12] * Value[6] * Value[9];
    
    inverse[1] = -Value[1]  * Value[10] * Value[15] +
    Value[1]  * Value[11] * Value[14] +
    Value[9]  * Value[2] * Value[15] -
    Value[9]  * Value[3] * Value[14] -
    Value[13] * Value[2] * Value[11] +
    Value[13] * Value[3] * Value[10];
    
    inverse[5] = Value[0]  * Value[10] * Value[15] -
    Value[0]  * Value[11] * Value[14] -
    Value[8]  * Value[2] * Value[15] +
    Value[8]  * Value[3] * Value[14] +
    Value[12] * Value[2] * Value[11] -
    Value[12] * Value[3] * Value[10];
    
    inverse[9] = -Value[0]  * Value[9] * Value[15] +
    Value[0]  * Value[11] * Value[13] +
    Value[8]  * Value[1] * Value[15] -
    Value[8]  * Value[3] * Value[13] -
    Value[12] * Value[1] * Value[11] +
    Value[12] * Value[3] * Value[9];
    
    inverse[13] = Value[0]  * Value[9] * Value[14] -
    Value[0]  * Value[10] * Value[13] -
    Value[8]  * Value[1] * Value[14] +
    Value[8]  * Value[2] * Value[13] +
    Value[12] * Value[1] * Value[10] -
    Value[12] * Value[2] * Value[9];
    
    inverse[2] = Value[1]  * Value[6] * Value[15] -
    Value[1]  * Value[7] * Value[14] -
    Value[5]  * Value[2] * Value[15] +
    Value[5]  * Value[3] * Value[14] +
    Value[13] * Value[2] * Value[7] -
    Value[13] * Value[3] * Value[6];
    
    inverse[6] = -Value[0]  * Value[6] * Value[15] +
    Value[0]  * Value[7] * Value[14] +
    Value[4]  * Value[2] * Value[15] -
    Value[4]  * Value[3] * Value[14] -
    Value[12] * Value[2] * Value[7] +
    Value[12] * Value[3] * Value[6];
    
    inverse[10] = Value[0]  * Value[5] * Value[15] -
    Value[0]  * Value[7] * Value[13] -
    Value[4]  * Value[1] * Value[15] +
    Value[4]  * Value[3] * Value[13] +
    Value[12] * Value[1] * Value[7] -
    Value[12] * Value[3] * Value[5];
    
    inverse[14] = -Value[0]  * Value[5] * Value[14] +
    Value[0]  * Value[6] * Value[13] +
    Value[4]  * Value[1] * Value[14] -
    Value[4]  * Value[2] * Value[13] -
    Value[12] * Value[1] * Value[6] +
    Value[12] * Value[2] * Value[5];
    
    inverse[3] = -Value[1] * Value[6] * Value[11] +
    Value[1] * Value[7] * Value[10] +
    Value[5] * Value[2] * Value[11] -
    Value[5] * Value[3] * Value[10] -
    Value[9] * Value[2] * Value[7] +
    Value[9] * Value[3] * Value[6];
    
    inverse[7] = Value[0] * Value[6] * Value[11] -
    Value[0] * Value[7] * Value[10] -
    Value[4] * Value[2] * Value[11] +
    Value[4] * Value[3] * Value[10] +
    Value[8] * Value[2] * Value[7] -
    Value[8] * Value[3] * Value[6];
    
    inverse[11] = -Value[0] * Value[5] * Value[11] +
    Value[0] * Value[7] * Value[9] +
    Value[4] * Value[1] * Value[11] -
    Value[4] * Value[3] * Value[9] -
    Value[8] * Value[1] * Value[7] +
    Value[8] * Value[3] * Value[5];
    
    inverse[15] = Value[0] * Value[5] * Value[10] -
    Value[0] * Value[6] * Value[9] -
    Value[4] * Value[1] * Value[10] +
    Value[4] * Value[2] * Value[9] +
    Value[8] * Value[1] * Value[6] -
    Value[8] * Value[2] * Value[5];
    
    det = ComputeDeterminant();
    
    if (det == 0.0f) {
        
        CORE_RUNTIME_Abort();
    }
    
    det = 1.0f / det;
    
    for (i = 0; i < 16; i++)
        inverse[i] = inverse[i] * det;
}

float CORE_MATH_MATRIX::ComputeDeterminant() const
{
    /*
     m0  m1  m2  m3
     m4  m5  m6  m7
     m8  m9  m10 m11
     m12 m13 m14 m15
     */
    
    /*
     m5  m6  m7
     m9  m10 m11
     m13 m14 m15
     */
    float detA =    Value[5]*(Value[10]*Value[15] - Value[14]*Value[11])
                    - Value[6] * (Value[9]*Value[15] - Value[13]*Value[11])
                    + Value[7]*(Value[9]*Value[14] - Value[13]*Value[10]);
    
    /*
     m4  m6  m7
     m8  m10 m11
     m12 m14 m15
     */
    float detB =    Value[4]*(Value[10]*Value[15] - Value[14]*Value[11])
                    - Value[6] * (Value[8]*Value[15] - Value[12]*Value[11])
                    + Value[7]*(Value[8]*Value[14] - Value[12]*Value[10]);
    
    /*
     m4  m5  m7
     m8  m9  m11
     m12 m13 m15
     */
    float detC =    Value[4]*(Value[9]*Value[15] - Value[13]*Value[11])
                    - Value[5] * (Value[8]*Value[15] - Value[12]*Value[11])
                    + Value[7]*(Value[8]*Value[13] - Value[12]*Value[9]);
    
    /*
     m4  m5  m6
     m8  m9  m10
     m12 m13 m14
     */
    float detD =    Value[4]*(Value[9]*Value[14] - Value[13]*Value[10])
                    - Value[5] * (Value[8]*Value[14] - Value[12]*Value[10])
                    + Value[6]*(Value[8]*Value[13] - Value[12]*Value[9]);
    
    return Value[0] * detA - Value[1] * detB + Value[2] * detC + Value[3] * detD;
}

float * GLOBAL_MULTIPLY_MATRIX(float *lhs, float *rhs) {

    float temp[16];

    memcpy(temp, lhs, 4*4*4);
    
    for (int r = 0 ; r < 4; r ++ )
        for (int c = 0 ; c < 4; c ++ )
            *(temp + ( r * 4 ) + c) = 0.0f;
    
    for (int r = 0 ; r < 4; r ++ )
        for (int c = 0 ; c < 4; c ++ ) {
            *(temp + ( r * 4 ) + c) += (*(lhs + ( r * 4 ) + 0) ) * (*(rhs + c + ( 4 * 0 )) );
            *(temp + ( r * 4 ) + c) += (*(lhs + ( r * 4 ) + 1) ) * (*(rhs + c + ( 4 * 1 )) );
            *(temp + ( r * 4 ) + c) += (*(lhs + ( r * 4 ) + 2) ) * (*(rhs + c + ( 4 * 2 )) );
            *(temp + ( r * 4 ) + c) += (*(lhs + ( r * 4 ) + 3) ) * (*(rhs + c + ( 4 * 3 )) );
        }
    
    memcpy(lhs, temp, 4*4*4);
    
    return lhs;
}

void GLOBAL_IDENTITY_MATRIX(float * matrix) {
    
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    
    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;
    
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void GLOBAL_COPY_MATRIX(float * dest, float * source ) {
    
    memcpy(dest, source, 16);
}

bool GLOBAL_EQUALS_MATRIX(float * lhs, float * rhs ) {
    
    for (int i = 0; i < 16; i++ ){
        
        if( fabsf(lhs[i] - rhs[i] ) > 0.000001f ) {
            
            return false;
        }
    }
    
    return true;
}

void GLOBAL_ROTATE_MATRIX( float * matrix, float rotate_x, float rotate_y, float rotate_z ) {
    
    CORE_SCALAR rotation_matrix;
    
    float *rotation = rotation_matrix.Value.FloatMatrix4x4;
    
    if ( rotate_x != 0) {
        
        GLOBAL_IDENTITY_MATRIX( rotation );
        
        rotation[4] = 0.0f;
        rotation[5] = cosf( rotate_x );
        rotation[6] = -sinf( rotate_x );
        rotation[7] = 0.0f;
        
        rotation[8] = 0.0f;
        rotation[9] = sinf( rotate_x );
        rotation[10] = cosf( rotate_x );
        rotation[11] = 0.0f;
        
        GLOBAL_MULTIPLY_MATRIX( matrix, rotation );
    }
    
    if ( rotate_y != 0) {
        
        GLOBAL_IDENTITY_MATRIX( rotation );
        
        rotation[0] = cosf( rotate_y );
        rotation[1] = 0.0f;
        rotation[2] = -sinf( rotate_y );
        rotation[3] = 0.0f;
        
        rotation[8] = sinf( rotate_y );
        rotation[9] = 0.0f;
        rotation[10] = cosf( rotate_y );
        rotation[11] = 0.0f;
        
        GLOBAL_MULTIPLY_MATRIX( matrix, rotation );
    }
    
    if ( rotate_z != 0) {
        
        GLOBAL_IDENTITY_MATRIX( rotation );
        
        rotation[0] = cosf( rotate_z );
        rotation[1] = -sinf( rotate_z );
        rotation[2] = 0.0f;
        rotation[3] = 0.0f;
        
        rotation[4] = sinf( rotate_z );
        rotation[5] = cosf( rotate_z );
        rotation[6] = 0.0f;
        rotation[7] = 0.0f;
        
        GLOBAL_MULTIPLY_MATRIX( matrix, rotation );
    }
}

void GLOBAL_TRANSLATE_MATRIX(float * matrix, float * vector ) {
    
    matrix[3] += vector[0];
    matrix[7] += vector[1];
    matrix[11] += vector[2];
}

float CORE_MATH_MATRIX::Identity[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                                         0.0f, 1.0f, 0.0f, 0.0f,
                                         0.0f, 0.0f, 1.0f, 0.0f,
                                         0.0f, 0.0f, 0.0f, 1.0f};
