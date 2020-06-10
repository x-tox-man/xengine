//
//  GRAPHIC_MESH_ANIMATION.h
//  GAME-ENGINE
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
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX.h"
#include "assert.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH_ANIMATION )

    GRAPHIC_MESH_ANIMATION();
    ~GRAPHIC_MESH_ANIMATION();

    XS_DEFINE_SERIALIZABLE

    std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & GetJointTable() { return JointTable; }

    void ComputeSkinningMatrixTableForFrameIndex( GRAPHIC_MESH_SKELETON_JOINT * skeletton, GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX animation_step_index, float * matrix_buffer );

    CORE_DATA_BUFFER & GetInverseBindMatrixes() { return InverseBindMatrixes; }
    CORE_SCALAR & GetBindShapeMatrix() { return BindShapeMatrix; }
    void SetName( const std::string & name ) { Name = name; }
    const std::string & GetName() { return Name; }

    inline CORE_DATA_BUFFER &  GetTimeTableBuffer() { return TimeTableBuffer; }

    inline float GetDuration() {
        
        return *(float*) TimeTableBuffer.getpointerAtIndex( (TimeTableBuffer.GetSize() / 4 ) - 1 );
    }

    void SetBindShapeMatrix( const float * shape_matrix_data ){
        
        memcpy( (void*)BindShapeMatrix.Value.FloatMatrix4x4, (void*)shape_matrix_data, 16 * sizeof(float) );
    }

    inline GRAPHIC_MESH_SKELETON_JOINT & GetSkeleton() { return Skeleton; }

private :

    void SetupWorldMatrix( GRAPHIC_MESH_SKELETON_JOINT * skeletton, GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX animation_step_index, float ** ptr_index, CORE_MATH_MATRIX & world_matrix );

    std::vector<GRAPHIC_MESH_ANIMATION_JOINT::PTR>
        JointTable;
    GRAPHIC_MESH_SKELETON_JOINT
        Skeleton;
    GRAPHIC_MESH_ANIMATION_MODE
        Mode;
    std::string
        Name;
    CORE_SCALAR
        BindShapeMatrix;
    CORE_DATA_BUFFER
        InverseBindMatrixes,
        TimeTableBuffer;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION__) */
