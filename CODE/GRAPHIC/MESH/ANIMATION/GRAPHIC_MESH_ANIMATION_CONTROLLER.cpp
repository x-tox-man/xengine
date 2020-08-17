//
//  GRAPHIC_MESH_ANIMATION_CONTROLLER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"
#include "CORE_DATA_LOADER.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_OBJECT.h"

#define MAX_ANIMATION 32

GRAPHIC_MESH_ANIMATION_CONTROLLER::GRAPHIC_MESH_ANIMATION_CONTROLLER() :
    CurrentTimeFrame( 0.0f ),
    CurrentTimeFrameIndex( 0 ),
    MeshAnimationTable(),
    ThisFrameAnimationMatrixArrayTable( NULL ) {
    
}

GRAPHIC_MESH_ANIMATION_CONTROLLER::GRAPHIC_MESH_ANIMATION_CONTROLLER( const GRAPHIC_MESH_ANIMATION_CONTROLLER & other ) :
    CurrentTimeFrame( other.CurrentTimeFrame ),
    CurrentTimeFrameIndex( other.CurrentTimeFrameIndex ),
    MeshAnimationTable( other.MeshAnimationTable ),
    ThisFrameAnimationMatrixArrayTable( NULL ) {
    
    Initialize();
}

GRAPHIC_MESH_ANIMATION_CONTROLLER::~GRAPHIC_MESH_ANIMATION_CONTROLLER() {
    
    std::vector< GRAPHIC_MESH_ANIMATION * >::iterator it = MeshAnimationTable.GetAnimationTable().begin();
    
    while ( it != MeshAnimationTable.GetAnimationTable().end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        it++;
    }
    
    MeshAnimationTable.GetAnimationTable().clear();
    
    ThisFrameAnimationMatrixArrayTable->clear();
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Initialize() {

    ThisFrameAnimationMatrixArrayTable = new std::vector< GRAPHIC_SHADER_GPU_BUFFER >();
    ThisFrameAnimationMatrixArrayTable->resize( MeshAnimationTable.GetAnimationTable().size() );
    
    for ( size_t i = 0; i < MeshAnimationTable.GetAnimationTable().size(); i++ ) {
        
        (*ThisFrameAnimationMatrixArrayTable)[ i ] = GRAPHIC_SHADER_GPU_BUFFER();
        (*ThisFrameAnimationMatrixArrayTable)[ i ].Initialize( (unsigned int) MeshAnimationTable[i]->GetJointTable().size() * sizeof(float) * 16 );
    }
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Load( const CORE_FILESYSTEM_PATH & path ) {
    
    abort();
    /*MeshAnimationTable.GetAnimationTable().resize( MeshAnimationTable.GetAnimationTable().size() + 1 );
    MeshAnimationTable.GetAnimationTable()[ MeshAnimationTable.GetAnimationTable().size() -1 ] = new GRAPHIC_MESH_ANIMATION();
    
    CORE_DATA_LOADER< GRAPHIC_MESH_ANIMATION >::Load( MeshAnimationTable[ MeshAnimationTable.GetAnimationTable().size() -1 ], path );*/
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Update( const float time, GRAPHIC_MESH_SKELETON_JOINT * skeleton ) {
    
    CurrentTimeFrame += time;
    
    for ( size_t i = 0; i < MeshAnimationTable.GetAnimationTable().size(); i++ ) {
        
        float * frame_reference = (float *) (*ThisFrameAnimationMatrixArrayTable)[ i ].GetGPUBufferDataPointer();
        MeshAnimationTable[i]->ComputeSkinningMatrixTableForFrameIndex( skeleton, GetFrameIndex(), frame_reference );
        
        int offset = 0;
        float * ptr = (float*) GetAnimation( (int)i )->GetInverseBindMatrixes().getpointerAtIndex(0, 0);
        for ( size_t mi = 0; mi < GetAnimation( (int) i )->GetJointTable().size(); mi++ ) {
            
            GLOBAL_MULTIPLY_MATRIX(frame_reference + offset, ptr + offset );
            offset += 16;
        }
    }
    
    //TODO: Average animations?
    for ( size_t i = 0; i < MeshAnimationTable.GetAnimationTable().size(); i++ ) {
        
    }
}

GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX GRAPHIC_MESH_ANIMATION_CONTROLLER::GetFrameIndex() {
     
    float * ptr = (float*) MeshAnimationTable[0]->GetTimeTableBuffer().getpointerAtIndex(0, 0) + CurrentTimeFrameIndex;
    GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX
        frame_index;
    int size = MeshAnimationTable[0]->GetTimeTableBuffer().GetSize() / 4;
    
    for (int i = 0; i < size; i++ ) {
        
        if ( CurrentTimeFrame > *ptr  ) {
            
            CurrentTimeFrameIndex++;
            ptr++;
            continue;
        }
        
        frame_index.FrameIndex = CurrentTimeFrameIndex;
        
        frame_index.NextFrameIndex = (frame_index.FrameIndex == (size -1)) ? 0 : (frame_index.FrameIndex +1);
        frame_index.Percentage = (*(ptr) - CurrentTimeFrame)/ (*(ptr) - *(ptr - 1));
        
        break;
    }
    
    return frame_index;
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Reset() {
    
    CurrentTimeFrame = 0.0f;
    CurrentTimeFrameIndex = 0;
    
    /*for ( size_t i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        MeshAnimationTable[i]->ComputeSkinningMatrixTableForFrameIndex( CurrentTimeFrame, ThisFrameAnimationMatrixArrayTable[ i ] );
    }*/
}
