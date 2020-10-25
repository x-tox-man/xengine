//
//  GRAPHIC_MESH_ANIMATION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"
#include "GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER.h"

// TODO: std::string AnimationName;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION )
    XS_DEFINE_ClassMember( "Mode", GRAPHIC_MESH_ANIMATION_MODE, Mode )
    XS_DEFINE_ClassMember( "Name", std::string, Name )
    XS_DEFINE_ClassMember( "BindShapeMatrix", CORE_SCALAR, BindShapeMatrix )
    XS_DEFINE_ClassMember( "InverseBindMatrixes", CORE_DATA_BUFFER, InverseBindMatrixes )
    XS_DEFINE_ClassMember( "TimeTableBuffer", CORE_DATA_BUFFER, TimeTableBuffer )
    XS_DEFINE_ClassMember( "JointTable", std::vector<GRAPHIC_MESH_ANIMATION_JOINT::PTR>, JointTable )
    XS_DEFINE_ClassMember( "Skeleton", GRAPHIC_MESH_SKELETON_JOINT, Skeleton )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION * )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( int )

GRAPHIC_MESH_ANIMATION::GRAPHIC_MESH_ANIMATION() :
    GR_A_GRAPHIC_ANIMATION_ANCESTOR_TYPE(),
    JointTable(),
    Mode( GRAPHIC_MESH_ANIMATION_MODE::GRAPHIC_MESH_ANIMATION_MODE_LinearInterpolation ),
    InverseBindMatrixes(),
    Name(),
    TimeTableBuffer() {
    
}

GRAPHIC_MESH_ANIMATION::~GRAPHIC_MESH_ANIMATION() {

    std::vector<GRAPHIC_MESH_ANIMATION_JOINT *>::iterator it = JointTable.begin();
    
    while ( it != JointTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        it++;
    }
    
    JointTable.clear();
}

GRAPHIC_MESH_ANIMATION::GRAPHIC_MESH_ANIMATION( const GRAPHIC_MESH_ANIMATION & other ) {
    
    abort();
}

void GRAPHIC_MESH_ANIMATION::SetupWorldPose( GRAPHIC_MESH_SKELETON_JOINT * skeletton, GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX animation_step_index, float ** ptr_index, CORE_MATH_POSE & pose ) {

    CORE_MATH_MATRIX
        final_world_mat;
    CORE_MATH_POSE
        current_pose,
        final_world_pose;
    
    if ( JointTable[ skeletton->Index ] != NULL ) {
        
        assert( strcmp( skeletton->GetName(), JointTable[ skeletton->Index ]->GetName() )  == 0 );
        JointTable[ skeletton->Index ]->YieldPoseForTime( animation_step_index, pose );
    }
    
    final_world_pose = pose * current_pose;
    final_world_pose.ToMatrix( final_world_mat );
    
    memcpy( (void*) ((float *) (*ptr_index) + skeletton->Index * 16), final_world_mat.GetRow(0), 64);

    for ( int i = 0; i < skeletton->ChildCount; i++ ) {
        
        SetupWorldPose( &skeletton->ChildJointTable[i], animation_step_index, ptr_index, final_world_pose );
    }
}

void GRAPHIC_MESH_ANIMATION::ComputeSkinningMatrixTableForFrameIndex( GRAPHIC_MESH_SKELETON_JOINT * skeletton, GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX animation_step_index, float * matrix_buffer ) {
    
    float * matrix_ptr = NULL;
    CORE_MATH_MATRIX mat, identity;
    CORE_MATH_POSE pose;
    
    if ( JointTable[ skeletton->Index ] != NULL ) {
        
#if DEBUG
        assert( strcmp( skeletton->GetName(), JointTable[ skeletton->Index ]->GetName() )  == 0 );
#endif
        
        //JointTable[ skeletton->Index ]->YieldFloatMatrixBufferForIndex( animation_step_index, mat );
        JointTable[ skeletton->Index ]->YieldPoseForTime( animation_step_index, pose );
        pose.ToMatrix( mat );
        matrix_ptr = mat.GetRow(0);
    }
    
    //Init
    for ( int i = 0; i < JointTable.size(); i++ ) {
        
        memcpy( (void*) (matrix_buffer + i *16), (void*) identity.GetRow( 0 ), 64 );
    }
    
    if ( matrix_ptr != NULL ) {
        memcpy( (void*) ((float*) matrix_buffer + skeletton->Index * 16), (void*) matrix_ptr, 64 );
    }
    
    //Compute the skeletton World matrices to temp buffer
    for ( int i = 0; i < skeletton->ChildCount; i++ ) {
        
        SetupWorldMatrix( &skeletton->ChildJointTable[i], animation_step_index, &matrix_buffer, mat );
    }
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



void GRAPHIC_MESH_ANIMATION::SetupWorldMatrix( GRAPHIC_MESH_SKELETON_JOINT * skeletton, GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX animation_step_index, float ** ptr_index, CORE_MATH_MATRIX & world_matrix ) {

    CORE_MATH_MATRIX
        mat,
        final_world_mat;
    
    if ( JointTable[ skeletton->Index ] != NULL ) {
        
        assert( strcmp( skeletton->GetName(), JointTable[ skeletton->Index ]->GetName() )  == 0 );
        JointTable[ skeletton->Index ]->YieldFloatMatrixBufferForIndex( animation_step_index, mat );
    }
    
    final_world_mat = mat * world_matrix;
    
    memcpy( (void*) ((float *) (*ptr_index) + skeletton->Index * 16), final_world_mat.GetRow(0), 64);

    for ( int i = 0; i < skeletton->ChildCount; i++ ) {
        
        SetupWorldMatrix( &skeletton->ChildJointTable[i], animation_step_index, ptr_index, final_world_mat );
    }
}
