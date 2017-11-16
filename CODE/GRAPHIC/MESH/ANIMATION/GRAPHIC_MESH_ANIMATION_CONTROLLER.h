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
#include "GRAPHIC_MESH_ANIMATION.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"

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

    void Update( const float time );
    void Reset();

    float GetCurrentTimeFrame() { return CurrentTimeFrame; }
    GRAPHIC_MESH_ANIMATION * GetAnimation( int index ) { return MeshAnimationTable[ index ]; }
    const GRAPHIC_MESH_ANIMATION * GetAnimation( int index ) const { return MeshAnimationTable[ index ]; }

    inline float * GetCurrentSkinningForAnimation( int index ) { return ThisFrameAnimationMatrixArrayTable[ index ]; }

private :

    std::vector< GRAPHIC_MESH_ANIMATION * > MeshAnimationTable;
    std::vector< float * > ThisFrameAnimationMatrixArrayTable;
    float CurrentTimeFrame;

XS_CLASS_END

#endif /* GRAPHIC_MESH_ANIMATION_CONTROLLER_hpp */
