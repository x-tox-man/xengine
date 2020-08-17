//
//  GRAPHIC_MESH_ANIMATION_CONTROLLER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MESH_ANIMATION_CONTROLLER_h
#define GRAPHIC_MESH_ANIMATION_CONTROLLER_h


#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_MESH_ANIMATION_COLLECTION.h"
#include "GRAPHIC_SHADER_GPU_BUFFER.h"
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH_ANIMATION_CONTROLLER )


    GRAPHIC_MESH_ANIMATION_CONTROLLER();
    ~GRAPHIC_MESH_ANIMATION_CONTROLLER();

    void Initialize();
    void Load( const CORE_FILESYSTEM_PATH & path );

    void operator=(const GRAPHIC_MESH_ANIMATION_CONTROLLER & other ) {
        
        CurrentTimeFrame = other.CurrentTimeFrame;
        MeshAnimationTable = other.MeshAnimationTable;
        
        Initialize();
    }

    void Update( const float time, GRAPHIC_MESH_SKELETON_JOINT * skeleton );
    void Reset();

    inline float GetCurrentTimeFrame() { return CurrentTimeFrame; }
    GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX GetFrameIndex();
    GRAPHIC_MESH_ANIMATION * GetAnimation( int index ) { return MeshAnimationTable[ index ]; }
    const GRAPHIC_MESH_ANIMATION * GetAnimation( int index ) const { return MeshAnimationTable[ index ]; }

    inline float * GetCurrentSkinningForAnimation( int index ) { return (float *) (*ThisFrameAnimationMatrixArrayTable)[ index ].GetGPUBufferDataPointer(); }

    inline GRAPHIC_SHADER_GPU_BUFFER & GetCurrentGPUBuffer( int i ) { return (*ThisFrameAnimationMatrixArrayTable)[i]; }

    void SetMeshAnimationTable( GRAPHIC_MESH_ANIMATION_COLLECTION * collection ) {
        
        MeshAnimationTable.GetAnimationTable().resize( collection->GetAnimationTable().size() );
        
        for (int i = 0; i < collection->GetAnimationTable().size(); i++ ) {
            MeshAnimationTable.GetAnimationTable()[i] = collection->GetAnimationTable()[i];
        }
    }

private :

    GRAPHIC_MESH_ANIMATION_COLLECTION
        MeshAnimationTable;
    std::vector< GRAPHIC_SHADER_GPU_BUFFER >
        * ThisFrameAnimationMatrixArrayTable;
    float
        CurrentTimeFrame;
    int
        CurrentTimeFrameIndex;

XS_CLASS_END

#endif /* GRAPHIC_MESH_ANIMATION_CONTROLLER_hpp */
