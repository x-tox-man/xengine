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

// TODO: std::string AnimationName;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION )
    XS_DEFINE_ClassMember( "Mode", GRAPHIC_MESH_ANIMATION_MODE, Mode )
    XS_DEFINE_ClassMember( "Name", std::string, Name )
    XS_DEFINE_ClassMember( "BindShapeMatrix", CORE_SCALAR, BindShapeMatrix )
    XS_DEFINE_ClassMember( "InverseBindMatrixes", CORE_DATA_BUFFER, InverseBindMatrixes )
    XS_DEFINE_ClassMember( "TimeTableBuffer", CORE_DATA_BUFFER, TimeTableBuffer )
    XS_DEFINE_ClassMember( "JointTable", std::vector<GRAPHIC_MESH_ANIMATION_JOINT::PTR>, JointTable )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION * )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( int )

GRAPHIC_MESH_ANIMATION::GRAPHIC_MESH_ANIMATION() :
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
    
}

void GRAPHIC_MESH_ANIMATION::SetupWorldMatrix( GRAPHIC_MESH_SKELETON_JOINT * skeletton, const int animation_step_index, float ** ptr_index, CORE_MATH_MATRIX & world_matrix ) {

    CORE_MATH_MATRIX
        mat,
        final_world_mat;
    
    if ( JointTable[ skeletton->Index ] != NULL ) {
        
        assert( strcmp( skeletton->GetName(), JointTable[ skeletton->Index ]->GetName() )  == 0 );
        mat = CORE_MATH_MATRIX( JointTable[ skeletton->Index ]->YieldFloatMatrixBufferForIndex( animation_step_index ) );
    }
    
    final_world_mat = mat * world_matrix;
    
    memcpy( (void*) ((float *) (*ptr_index) + skeletton->Index * 16), final_world_mat.GetRow(0), 64);

    for ( int i = 0; i < skeletton->ChildCount; i++ ) {
        
        SetupWorldMatrix( &skeletton->ChildJointTable[i], animation_step_index, ptr_index, final_world_mat );
    }
}

void GRAPHIC_MESH_ANIMATION::ComputeSkinningMatrixTableForFrameIndex( GRAPHIC_MESH_SKELETON_JOINT * skeletton, const int animation_step_index, float * matrix_buffer ) {
    
    float * matrix_ptr = NULL;
    CORE_MATH_MATRIX mat, identity;
    
    if ( JointTable[ skeletton->Index ] != NULL ) {
        
        assert( strcmp( skeletton->GetName(), JointTable[ skeletton->Index ]->GetName() )  == 0 );
        matrix_ptr = JointTable[ skeletton->Index ]->YieldFloatMatrixBufferForIndex( animation_step_index );
        mat= CORE_MATH_MATRIX( matrix_ptr );
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
