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

XS_DEFINE_SERIALIZABLE

void Initialize( int vectorSize );

std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & getJointTable() { return JointTable; }
float * YieldSkinningMatrixTableForTime( const float time );
void setCurrentTimeFrame( const float time ) { CurrentTimeFrame = time; }
CORE_DATA_BUFFER & getInverseBindMatrixes() { return InverseBindMatrixes; }
CORE_SCALAR & getBindShapeMatrix() { return BindShapeMatrix; }
void setBindShapeMatrix( const float * shape_matrix_data );
float getCurrentTimeFrame() { return CurrentTimeFrame; }
void setJointIndexTable( int * joint_index_table, int size ) { JointIndexTable.InitializeWithMemory(size, 0, joint_index_table); }
CORE_DATA_BUFFER & getJointIndexTable() { return JointIndexTable; }
void setAnimationName( const std::string & name ) { AnimationName = name; }
const std::string & getAnimationName() { return AnimationName; }
GRAPHIC_MESH_ANIMATION_SKELETON & getSkeleton() { return Skeleton; };

private :

std::vector<GRAPHIC_MESH_ANIMATION_JOINT *>
    JointTable;
GRAPHIC_MESH_ANIMATION_MODE
    Mode;
float *
    TimeTable;
float
    CurrentTimeFrame;
CORE_SCALAR
    BindShapeMatrix;
CORE_DATA_BUFFER
    InverseBindMatrixes;
CORE_DATA_BUFFER
    JointIndexTable;
std::string
    AnimationName;
GRAPHIC_MESH_ANIMATION_SKELETON
    Skeleton;

private :

void InterpolateMatrixForTimeTableIndex( int frame_index, float percentage );
void InterpolateMatrixForTimeTableIndex( int frame_index );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION__) */
