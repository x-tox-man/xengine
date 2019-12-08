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
    XS_DEFINE_ClassMember( "IndexTable", std::vector<int>, IndexTable )
    XS_DEFINE_ClassMember( "Mode", GRAPHIC_MESH_ANIMATION_MODE, Mode )
    XS_DEFINE_ClassMember( "BindShapeMatrix", CORE_SCALAR, BindShapeMatrix )
    XS_DEFINE_ClassMember( "InverseBindMatrixes", CORE_DATA_BUFFER, InverseBindMatrixes )
    XS_DEFINE_ClassMember( "JointIndexTable", CORE_DATA_BUFFER, JointIndexTable )
    XS_DEFINE_ClassMember( "Skeleton", GRAPHIC_MESH_ANIMATION_SKELETON, Skeleton )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_MESH_ANIMATION * )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( int )

GRAPHIC_MESH_ANIMATION::GRAPHIC_MESH_ANIMATION() :
    JointTable(),
    Mode( GRAPHIC_MESH_ANIMATION_MODE::GRAPHIC_MESH_ANIMATION_MODE_Interpolation ),
    InverseBindMatrixes(),
    JointIndexTable(),
    AnimationName() {
    
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

void GRAPHIC_MESH_ANIMATION::Initialize( std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & joints_table, int vectorSize ) {
    
    if ( vectorSize ) {

        JointTable.resize( vectorSize );
        IndexTable.resize( vectorSize );
    }
    else {

        JointTable.resize( IndexTable.size() );
    }
    
    if ( joints_table.size() ) {

        for ( size_t i = 0; i < IndexTable.size(); i++ ) {
            
            JointTable[i] = joints_table[ IndexTable[i] ];
        }
    }
    
    Skeleton.Initialize( joints_table );
}

void GRAPHIC_MESH_ANIMATION::ComputeSkinningMatrixTableForTime( const float time, float * matrix_buffer ) {
    
    int offset = 0;
    
    Skeleton.ComputeWorldPose( time );
    //Skeleton.ComputeWorldMatrix( time );
    
    for ( size_t i = 0; i < JointTable.size(); i++ ) {
        
        float * ptr = (float *)JointTable[i]->GetInterPolatedMatrix();
        const CORE_MATH_POSE & pose = JointTable[i]->GetInterPolatedPose();
        
        // TODO: in place matrix copy
        
        pose.ToMatrix( (float*)( matrix_buffer + offset) );
        
        //memcpy( (void*)(matrix_buffer+offset), (void*)ptr, 16 * sizeof(float));
    
        offset += 16;
    }
}
