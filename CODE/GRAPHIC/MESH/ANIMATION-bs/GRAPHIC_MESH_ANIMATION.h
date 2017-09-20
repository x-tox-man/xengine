//
//  GRAPHIC_MESH_ANIMATION.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_MESH_ANIMATION_JOINT.h"
#include "GRAPHIC_MESH_ANIMATION_MODE.h"
#include "GRAPHIC_MESH_ANIMATION_SKELETON.h"

#include "assert.h"
#include <stdlib.h>

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH_ANIMATION )

    GRAPHIC_MESH_ANIMATION();
    ~GRAPHIC_MESH_ANIMATION();

    XS_DEFINE_SERIALIZABLE

    void Initialize( std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & joint_table, int vectorSize );

    std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & GetJointTable() { return JointTable; }
    std::vector<int> & GetIndexTable() { return IndexTable; }

    void ComputeSkinningMatrixTableForTime( const float time, float * matrix_buffer );

    CORE_DATA_BUFFER & GetInverseBindMatrixes() { return InverseBindMatrixes; }
    CORE_SCALAR & GetBindShapeMatrix() { return BindShapeMatrix; }
    CORE_DATA_BUFFER & GetJointIndexTable() { return JointIndexTable; }
    void SetAnimationName( const std::string & name ) { AnimationName = name; }
    const std::string & GetAnimationName() { return AnimationName; }
    GRAPHIC_MESH_ANIMATION_SKELETON & GetSkeleton() { return Skeleton; };

    #if __COMPILE_WITH__COLLADA__
        void print() {
            
            //Skeleton.print();
        }

        void SetBindShapeMatrix( const float * shape_matrix_data ){
            
            memcpy( (void*)BindShapeMatrix.Value.FloatMatrix4x4, (void*)shape_matrix_data, 16 * sizeof(float) );
        }

        void SetJointIndexTable( int * joint_index_table, int size ) { JointIndexTable.InitializeWithMemory(size, 0, joint_index_table); }
    #endif

    private :

    std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> JointTable;
    std::vector<int> IndexTable;
    GRAPHIC_MESH_ANIMATION_MODE Mode;
    GRAPHIC_MESH_ANIMATION_SKELETON Skeleton;
    CORE_DATA_BUFFER JointIndexTable;
    std::string AnimationName;
    CORE_SCALAR BindShapeMatrix;
    CORE_DATA_BUFFER InverseBindMatrixes;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION__) */
