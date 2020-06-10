//
//  GRAPHIC_MESH_ANIMATION_JOINT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION_JOINT.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION_JOINT )
    XS_DEFINE_ClassMember( "FloatMatrixBuffer", CORE_DATA_BUFFER, FloatMatrixBuffer )
    XS_DEFINE_ClassMember( "PoseBuffer", CORE_DATA_BUFFER, PoseBuffer )
    XS_DEFINE_ClassMember( "WorldMatrix", CORE_SCALAR, WorldMatrix )
    XS_DEFINE_ClassMember( "WorldPose", CORE_MATH_POSE, WorldPose )
    XS_DEFINE_ClassMemberArray( "Name", char, Name, (size_t) 256 )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION_JOINT )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION_JOINT * )

GRAPHIC_MESH_ANIMATION_JOINT::GRAPHIC_MESH_ANIMATION_JOINT() :
    FloatMatrixBuffer(),
    InterPolatedMatrix(),
    InterpolatedPose(),
    WorldMatrix(),
    WorldPose(),
    Name(),
    SkeletonJoint( NULL ) {
}

GRAPHIC_MESH_ANIMATION_JOINT::~GRAPHIC_MESH_ANIMATION_JOINT() {
    
}

GRAPHIC_MESH_ANIMATION_JOINT::GRAPHIC_MESH_ANIMATION_JOINT( const GRAPHIC_MESH_ANIMATION_JOINT & other ) {
    
}

void GRAPHIC_MESH_ANIMATION_JOINT::Initialize( int matrix_size, int count ) {
    
    FloatMatrixBuffer.Initialize( matrix_size * count * sizeof(float) );
    PoseBuffer.Initialize( count * sizeof( CORE_MATH_POSE ) );
}

void GRAPHIC_MESH_ANIMATION_JOINT::YieldFloatMatrixBufferForIndex( GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX matrix_index, CORE_MATH_MATRIX & matrix ) {
    
    /*int matrix_index = 0;
    
    assert(time >= 0.0f );
    
    for ( size_t i = 1; i < TimeTableBuffer.GetSize(); i++ ) {
        
        float min = *((float*) TimeTableBuffer.getpointerAtIndex( matrix_index * sizeof(float), 0));
        float max = *((float*) TimeTableBuffer.getpointerAtIndex( ( matrix_index + 1 ) * sizeof(float), 0));
        
        if ( max >= time ) {
            
            // TODO: float percentage = (time - min) / (max - min);
            
            return (float*) FloatMatrixBuffer.getpointerAtIndex(matrix_index * sizeof(float) * 16, 0);
        }
        else if ( min == time ) {

            return FloatMatrixBuffer.getpointerAtIndex(matrix_index * sizeof(float) * 16, 0);
        }
        
        ++matrix_index;
    }
    
    assert(matrix_index == TimeTableBuffer.GetSize() -1 );*/
    
    float * ptr1 = (float *) FloatMatrixBuffer.getpointerAtIndex( matrix_index.FrameIndex * sizeof(float) * 16, 0);
    float * ptr2 = (float *) FloatMatrixBuffer.getpointerAtIndex( (matrix_index.NextFrameIndex ) * sizeof(float) * 16, 0);
    
    for (int i = 0; i < 16; i++ ) {
        
        matrix[i] = *ptr1 * matrix_index.Percentage + *ptr2 * (1.0f - matrix_index.Percentage);
        ++ptr1;
        ++ptr2;
    }
    
    //matrix = CORE_MATH_MATRIX( (float *) FloatMatrixBuffer.getpointerAtIndex( matrix_index.FrameIndex * sizeof(float) * 16, 0) );
}

void GRAPHIC_MESH_ANIMATION_JOINT::YieldPoseForTime( const int pose_index, CORE_MATH_POSE & pose ) {
    
    /*int pose_index = 0;
    
    assert(time >= 0.0f );
    
    for ( size_t i = 1; i < TimeTableBuffer.GetSize(); i++ ) {
        
        float min = *((float*) TimeTableBuffer.getpointerAtIndex(pose_index * sizeof(float), 0));
        float max = *((float*) TimeTableBuffer.getpointerAtIndex( ( pose_index + 1 ) * sizeof(float), 0));
        
        if ( max >= time ) {
            
            // TODO: float percentage = (time - min) / (max - min);
            
            CORE_MATH_POSE * first = ( CORE_MATH_POSE *) PoseBuffer.getpointerAtIndex( pose_index * sizeof( CORE_MATH_POSE ), 0 );
            //CORE_MATH_POSE * second = ( CORE_MATH_POSE *) PoseBuffer.getpointerAtIndex( pose_index + 1 * sizeof( CORE_MATH_POSE ), 0 );
            
            pose.CopyFrom( *first );
            // TODO:
            //first->Lerp( *second, pose, percentage );
            
            return;
        }
        else if ( min == time ) {
            
            pose.CopyFrom(  *(( CORE_MATH_POSE *) PoseBuffer.getpointerAtIndex( pose_index * sizeof( CORE_MATH_POSE ), 0) ));
            
            return;
        }
        
        ++pose_index;
    }
    
    assert(pose_index == TimeTableBuffer.GetSize() -1 );*/
    
    pose.CopyFrom(  *(( CORE_MATH_POSE *) PoseBuffer.getpointerAtIndex( pose_index * sizeof( CORE_MATH_POSE ), 0) ));
}
