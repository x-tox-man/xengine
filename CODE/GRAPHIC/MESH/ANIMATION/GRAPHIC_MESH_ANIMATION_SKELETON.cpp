//
//  GRAPHIC_MESH_ANIMATION_SKELETON.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/02/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION_SKELETON.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

// TODO: Move GRAPHIC_MESH_SKELETON_JOINT to own class

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION_SKELETON )
    XS_DEFINE_ClassMember( "RootSubSkeleton", GRAPHIC_MESH_SKELETON_JOINT, RootSubSkeleton )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MESH_ANIMATION_SKELETON::GRAPHIC_MESH_ANIMATION_SKELETON() :
    RootSubSkeleton() {
    
}

GRAPHIC_MESH_ANIMATION_SKELETON::~GRAPHIC_MESH_ANIMATION_SKELETON() {

}

void SetupWorldMatrix( GRAPHIC_MESH_SKELETON_JOINT & sub_skeletton, float * world_matrix, const float time) {
    
    for ( int i = 0; i < sub_skeletton.ChildCount; i++ ) {
        
        CORE_SCALAR sub_world_matrix;
        
        float * joint =  (float*) sub_skeletton.SubJointTable[i].Joint.YieldFloatMatrixBufferForTime( time );
        
        memcpy( (void *)sub_world_matrix.Value.FloatMatrix4x4, world_matrix, 16 * sizeof( float ) );
        
        GLOBAL_MULTIPLY_MATRIX(sub_world_matrix.Value.FloatMatrix4x4, joint);
        
        sub_skeletton.SubJointTable[i].Joint.SetWorldMatrix( sub_world_matrix.Value.FloatMatrix4x4 );
        sub_skeletton.SubJointTable[i].Joint.SetSkinningMatrix(sub_world_matrix.Value.FloatMatrix4x4 );
        
        SetupWorldMatrix( sub_skeletton.SubJointTable[i], sub_world_matrix.Value.FloatMatrix4x4, time);
    }
}

void SetupWorldPose( GRAPHIC_MESH_SKELETON_JOINT & sub_skeletton, CORE_MATH_POSE & world_pose, const float time) {
    
    for ( int i = 0; i < sub_skeletton.ChildCount; i++ ) {
        
        CORE_MATH_POSE
            pose,
            temporary;
        
        sub_skeletton.SubJointTable[i].Joint.YieldPoseForTime( time, pose );
    
        temporary.CopyFrom( world_pose * pose );
        
        sub_skeletton.SubJointTable[i].Joint.SetWorldPose( temporary );
        sub_skeletton.SubJointTable[i].Joint.SetSkinningPose( temporary );
        
        SetupWorldPose( sub_skeletton.SubJointTable[i], temporary, time);
    }
}

void GRAPHIC_MESH_ANIMATION_SKELETON::ComputeWorldMatrix( const float time ) {
    
    //in case of multiple root nodes :
    for ( int i = 0; i < RootSubSkeleton.ChildCount; i++ ) {
        
        float * ptr = (float *) RootSubSkeleton.SubJointTable[i].Joint.YieldFloatMatrixBufferForTime( time );
        
        CORE_MATH_MATRIX identity;
        
        RootSubSkeleton.SubJointTable[i].Joint.SetWorldMatrix( identity.GetRow(0) );
        RootSubSkeleton.SubJointTable[i].Joint.SetSkinningMatrix( ptr );
        
        SetupWorldMatrix( RootSubSkeleton.SubJointTable[i], ptr, time );
    }
}

void GRAPHIC_MESH_ANIMATION_SKELETON::ComputeWorldPose( const float time ) {
    
    //in case of multiple root nodes :
    for ( int i = 0; i < RootSubSkeleton.ChildCount; i++ ) {
        
        CORE_MATH_POSE pose;
        
        RootSubSkeleton.SubJointTable[i].Joint.YieldPoseForTime( time, pose );
        
        RootSubSkeleton.SubJointTable[i].Joint.SetWorldPose( pose );
        RootSubSkeleton.SubJointTable[i].Joint.SetSkinningPose( pose );
        
        SetupWorldPose( RootSubSkeleton.SubJointTable[i], pose, time );
    }
}
