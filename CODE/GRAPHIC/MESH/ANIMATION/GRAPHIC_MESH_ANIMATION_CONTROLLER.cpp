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
    ThisFrameAnimationMatrixArrayTable() {
    
}

GRAPHIC_MESH_ANIMATION_CONTROLLER::GRAPHIC_MESH_ANIMATION_CONTROLLER( const GRAPHIC_MESH_ANIMATION_CONTROLLER & other ) :
    CurrentTimeFrame( other.CurrentTimeFrame ),
    CurrentTimeFrameIndex( other.CurrentTimeFrameIndex ),
    MeshAnimationTable( other.MeshAnimationTable ),
    ThisFrameAnimationMatrixArrayTable() {
    
    Initialize();
}

GRAPHIC_MESH_ANIMATION_CONTROLLER::~GRAPHIC_MESH_ANIMATION_CONTROLLER() {
    
    std::vector< GRAPHIC_MESH_ANIMATION * >::iterator it = MeshAnimationTable.begin();
    std::vector< float * >::iterator it2 = ThisFrameAnimationMatrixArrayTable.begin();
    
    while ( it != MeshAnimationTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        it++;
    }
    
    MeshAnimationTable.clear();
    
    while ( it2 != ThisFrameAnimationMatrixArrayTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it2 );
        
        it2++;
    }
    
    ThisFrameAnimationMatrixArrayTable.clear();
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Initialize() {
    
    ThisFrameAnimationMatrixArrayTable.resize( MeshAnimationTable.size() );
    
    for ( size_t i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        ThisFrameAnimationMatrixArrayTable[ i ] = (float *) CORE_MEMORY_ALLOCATOR::Allocate( MeshAnimationTable[i]->GetJointTable().size() * sizeof(float) * 16 );
    }
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Load( const CORE_FILESYSTEM_PATH & path ) {
    
    MeshAnimationTable.resize( MeshAnimationTable.size() + 1 );
    MeshAnimationTable[ MeshAnimationTable.size() -1 ] = new GRAPHIC_MESH_ANIMATION();
    
    CORE_DATA_LOADER< GRAPHIC_MESH_ANIMATION >::Load( MeshAnimationTable[ MeshAnimationTable.size() -1 ], path );
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Update( const float time, GRAPHIC_MESH_SKELETON_JOINT * skeleton ) {
    
    CurrentTimeFrame += time;
    
    for ( size_t i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        float * frame_reference = ThisFrameAnimationMatrixArrayTable[ i ];
        MeshAnimationTable[i]->ComputeSkinningMatrixTableForFrameIndex( skeleton, GetFrameIndex(), frame_reference );
    }
    
    //skeleton->print(0);
    
    //TODO: Average animations?
    for ( size_t i = 0; i < MeshAnimationTable.size(); i++ ) {
        
    }
}

inline unsigned int GRAPHIC_MESH_ANIMATION_CONTROLLER::GetFrameIndex() {
    
    float * ptr = (float*) MeshAnimationTable[0]->GetTimeTableBuffer().getpointerAtIndex(0, 0) + CurrentTimeFrameIndex;
    
    for (int i = 0; i < MeshAnimationTable[0]->GetTimeTableBuffer().GetSize() / 4; i++ ) {
        
        if ( CurrentTimeFrame > *ptr  ) {
            
            CurrentTimeFrameIndex++;
            ptr++;
            continue;
        }
        break;
    }
    
    return CurrentTimeFrameIndex;
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Reset() {
    
    CurrentTimeFrame = 0.0f;
    CurrentTimeFrameIndex = 0;
    
    /*for ( size_t i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        MeshAnimationTable[i]->ComputeSkinningMatrixTableForFrameIndex( CurrentTimeFrame, ThisFrameAnimationMatrixArrayTable[ i ] );
    }*/
}
