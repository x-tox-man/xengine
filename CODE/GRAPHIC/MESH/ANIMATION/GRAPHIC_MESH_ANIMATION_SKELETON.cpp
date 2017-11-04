//
//  GRAPHIC_MESH_ANIMATION_SKELETON.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/02/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION_SKELETON.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_DATA_STREAM.h"

//TODO: Move GRAPHIC_MESH_SUB_SKELETON to own class

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION_SKELETON )
    XS_DEFINE_ClassMember( "RootSubSkeleton", GRAPHIC_MESH_SUB_SKELETON, RootSubSkeleton )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MESH_ANIMATION_SKELETON::GRAPHIC_MESH_ANIMATION_SKELETON() :
    RootSubSkeleton() {
    
}

GRAPHIC_MESH_ANIMATION_SKELETON::~GRAPHIC_MESH_ANIMATION_SKELETON() {

}

void GRAPHIC_MESH_ANIMATION_SKELETON::Initialize( const std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & table ) {
    
    for (int i = 0; i < RootSubSkeleton.ChildCount; i++ ) {
        
        RootSubSkeleton.SubSkelettonTable[i].Initialize( table );
    }
}

void SetupWorldMatrix( GRAPHIC_MESH_SUB_SKELETON & sub_skeletton, float * world_matrix, const float time) {
    
    for ( int i = 0; i < sub_skeletton.ChildCount; i++ ) {
        
        CORE_SCALAR sub_world_matrix;
        
        float * joint =  (float*) sub_skeletton.SubSkelettonTable[i].Joint->YieldFloatMatrixBufferForTime( time );
        
        memcpy( (void *)sub_world_matrix.Value.FloatMatrix4x4, world_matrix, 16 * sizeof( float ) );
        
        GLOBAL_MULTIPLY_MATRIX(sub_world_matrix.Value.FloatMatrix4x4, joint);
        
        sub_skeletton.SubSkelettonTable[i].Joint->SetWorldMatrix( sub_world_matrix.Value.FloatMatrix4x4 );
        sub_skeletton.SubSkelettonTable[i].Joint->SetSkinningMatrix(sub_world_matrix.Value.FloatMatrix4x4 );
        
        SetupWorldMatrix( sub_skeletton.SubSkelettonTable[i], sub_world_matrix.Value.FloatMatrix4x4, time);
    }
}

void SetupWorldPose( GRAPHIC_MESH_SUB_SKELETON & sub_skeletton, CORE_MATH_POSE & world_pose, const float time) {
    
    for ( int i = 0; i < sub_skeletton.ChildCount; i++ ) {
        
        CORE_MATH_POSE
            pose,
            temporary;
        
        sub_skeletton.SubSkelettonTable[i].Joint->YieldPoseForTime( time, pose );
    
        temporary.CopyFrom( world_pose * pose );
        
        sub_skeletton.SubSkelettonTable[i].Joint->SetWorldPose( temporary );
        sub_skeletton.SubSkelettonTable[i].Joint->SetSkinningPose( temporary );
        
        SetupWorldPose( sub_skeletton.SubSkelettonTable[i], temporary, time);
    }
}

void GRAPHIC_MESH_ANIMATION_SKELETON::ComputeWorldMatrix( const float time ) {
    
    //in case of multiple root nodes :
    for ( int i = 0; i < RootSubSkeleton.ChildCount; i++ ) {
        
        float * ptr = (float *) RootSubSkeleton.SubSkelettonTable[i].Joint->YieldFloatMatrixBufferForTime( time );
        
        RootSubSkeleton.SubSkelettonTable[i].Joint->SetWorldMatrix( ptr );
        RootSubSkeleton.SubSkelettonTable[i].Joint->SetSkinningMatrix( ptr );
        
        SetupWorldMatrix( RootSubSkeleton.SubSkelettonTable[i], ptr, time );
    }
}

void GRAPHIC_MESH_ANIMATION_SKELETON::ComputeWorldPose( const float time ) {
    
    //in case of multiple root nodes :
    for ( int i = 0; i < RootSubSkeleton.ChildCount; i++ ) {
        
        CORE_MATH_POSE pose;
        
        RootSubSkeleton.SubSkelettonTable[i].Joint->YieldPoseForTime( time, pose );
        
        RootSubSkeleton.SubSkelettonTable[i].Joint->SetWorldPose( pose );
        RootSubSkeleton.SubSkelettonTable[i].Joint->SetSkinningPose( pose );
        
        SetupWorldPose( RootSubSkeleton.SubSkelettonTable[i], pose, time );
    }
}
