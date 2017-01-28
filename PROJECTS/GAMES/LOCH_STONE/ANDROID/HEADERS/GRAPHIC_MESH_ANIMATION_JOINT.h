//
//  GRAPHIC_MESH_ANIMATION_JOINT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_JOINT__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_JOINT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_DATA_BUFFER.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_POSE.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH_ANIMATION_JOINT )

XS_DEFINE_SERIALIZABLE

GRAPHIC_MESH_ANIMATION_JOINT();

void Initialize( int matrix_size, int count );

float * getMatrixBuffer() {
    
    return (float *) FloatMatrixBuffer.getpointerAtIndex( 0, 0 );
}

void * geFramedtMatrix( float frameTime ) {
    
    int FirstMatrixIndex = 0;
    
    float * first_matrix = (float *) FloatMatrixBuffer.getpointerAtIndex( FirstMatrixIndex * 16 * sizeof(float), 0 );
    float * second_matrix = (float *) FloatMatrixBuffer.getpointerAtIndex( (FirstMatrixIndex +1) * 16 * sizeof(float), 0 );
    
    return first_matrix;
}

void * getMatrixInterpolated( int FirstMatrixIndex ) {
    
    float * first_matrix = (float *) FloatMatrixBuffer.getpointerAtIndex( FirstMatrixIndex * 16 * sizeof(float), 0 );
    float * second_matrix = (float *) FloatMatrixBuffer.getpointerAtIndex( (FirstMatrixIndex +1) * 16 * sizeof(float), 0 );
    
    return first_matrix;
}

void setJointName( const std::string & name ) {
    
    JointName = name;
}

void * getFloatMatrixBuffer( int offset = 0 ) { return FloatMatrixBuffer.getpointerAtIndex( offset, 0); }
CORE_DATA_BUFFER &  getTimeTableBuffer() { return TimeTableBuffer; }

void * getInterPolatedMatrix() { return InterPolatedMatrix.Value.FloatMatrix4x4; };

void setWorldMatrix( float * world_matrix ) { memcpy( (void *) WorldMatrix.Value.FloatMatrix4x4, (void*) world_matrix, 16*sizeof(float) ); }
void setSkinningMatrix( float * skinning_matrix ) { memcpy( (void *) InterPolatedMatrix.Value.FloatMatrix4x4, (void*) skinning_matrix, 16*sizeof(float)); }

void SetWorldPose( CORE_MATH_POSE & pose ) { abort(); }
void SetPose( CORE_MATH_POSE & pose ) { abort(); }

void * yieldFloatMatrixBufferForTime( const float time );
void * yieldMatrixForTime( const float time );

private:

CORE_DATA_BUFFER
    FloatMatrixBuffer;
CORE_DATA_BUFFER
    PoseBuffer;
CORE_SCALAR
    InterPolatedMatrix;
CORE_MATH_POSE
    InterpolatedPose;
CORE_SCALAR
    WorldMatrix;
CORE_MATH_POSE
    WorldPose;
CORE_DATA_BUFFER
    TimeTableBuffer;
std::string
    JointName;
CORE_SCALAR
    BindShapeMatrix;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_JOINT__) */
