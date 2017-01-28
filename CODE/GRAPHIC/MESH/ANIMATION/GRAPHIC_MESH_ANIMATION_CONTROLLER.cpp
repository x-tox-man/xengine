//
//  GRAPHIC_MESH_ANIMATION_CONTROLLER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"
#include "CORE_DATA_LOADER.h"

#define MAX_ANIMATION 32

GRAPHIC_MESH_ANIMATION_CONTROLLER::GRAPHIC_MESH_ANIMATION_CONTROLLER() :
    CurrentTimeFrame( 0.0f ),
    MeshAnimationTable(),
    ThisFrameAnimationMatrixArrayTable() {
    
}

GRAPHIC_MESH_ANIMATION_CONTROLLER::~GRAPHIC_MESH_ANIMATION_CONTROLLER() {
    
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Initialize() {
    
    ThisFrameAnimationMatrixArrayTable.resize( MeshAnimationTable.size() );
    
    for ( int i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        ThisFrameAnimationMatrixArrayTable[ i ] = (float *) CORE_MEMORY_ALLOCATOR::Allocate( MeshAnimationTable[i]->GetJointTable().size() * sizeof(float) * 16 );
    }
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Load( const CORE_FILESYSTEM_PATH & path ) {
    
    MeshAnimationTable.resize( MeshAnimationTable.size() + 1 );
    MeshAnimationTable[ MeshAnimationTable.size() -1 ] = new GRAPHIC_MESH_ANIMATION();
    
    CORE_DATA_LOADER< GRAPHIC_MESH_ANIMATION >::Load( MeshAnimationTable[ MeshAnimationTable.size() -1 ], path );
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Update( const float time ) {
    
    CurrentTimeFrame += time;
    
    for ( int i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        MeshAnimationTable[i]->ComputeSkinningMatrixTableForTime( CurrentTimeFrame, ThisFrameAnimationMatrixArrayTable[ i ] );
    }
}

void GRAPHIC_MESH_ANIMATION_CONTROLLER::Reset() {
    
    CurrentTimeFrame = 0.0f;
    
    for ( int i = 0; i < MeshAnimationTable.size(); i++ ) {
        
        MeshAnimationTable[i]->ComputeSkinningMatrixTableForTime( CurrentTimeFrame, ThisFrameAnimationMatrixArrayTable[ i ] );
    }
}
