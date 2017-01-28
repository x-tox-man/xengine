//
//  GRAPHIC_MESH_ANIMATION_SKELETON.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/02/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_SKELETON__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_SKELETON__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_MESH_ANIMATION_JOINT.h"
#include "GRAPHIC_MESH_ANIMATION_MODE.h"
#include "GRAPHIC_MESH_SUB_SKELETON.h"

#include "assert.h"
#include <stdlib.h>

XS_CLASS_BEGIN( GRAPHIC_MESH_ANIMATION_SKELETON )

    XS_DEFINE_SERIALIZABLE

    GRAPHIC_MESH_ANIMATION_SKELETON();

    void Initialize( const std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & table );

    void ComputeWorldMatrix( const float time );
    void ComputeWorldPose( const float time );

    inline GRAPHIC_MESH_SUB_SKELETON & GetRootSubSkeleton() { return RootSubSkeleton; }


    #if DEBUG
        void print() {
            
            for (int i = 0; i < RootSubSkeleton.ChildCount; i++ ) {
                
                RootSubSkeleton.SubSkelettonTable[i].print();
            }
        }
    #endif

private :

    GRAPHIC_MESH_SUB_SKELETON
        RootSubSkeleton;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_SKELETON__) */
