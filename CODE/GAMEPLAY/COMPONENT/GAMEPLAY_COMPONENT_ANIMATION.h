//
//  GAMEPLAY_COMPONENT_ANIMATION_CONTROLLER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ANIMATION__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ANIMATION__

#include "GAMEPLAY_COMPONENT.h"
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GAMEPLAY_COMPONENT_ANIMATION, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_ANIMATION();
    virtual ~GAMEPLAY_COMPONENT_ANIMATION();

    void * operator new(size_t size);
    void operator delete( void* ptr );

    CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_ANIMATION, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Animation)

    struct INTERNAL_ARRAY_A{
        int LastIndex;
        GAMEPLAY_COMPONENT_ANIMATION * MemoryArray;
    };

    void UpdateAnimation( float time_step );

    void SetAnimation( const GRAPHIC_MESH_ANIMATION_CONTROLLER & animation ) { Animation = animation; }

    virtual GAMEPLAY_COMPONENT * GetComponentAt( int index, int offset ) {
        
        return (GAMEPLAY_COMPONENT *) &(*InternalVector)[index].MemoryArray[offset];
    }

    static void Clear();

    static void SaveToStream( CORE_DATA_STREAM & stream );
    static void LoadFromStream( CORE_DATA_STREAM & stream );

    static int
        LastIndex,
        LastOffset;

private :

    GRAPHIC_MESH_ANIMATION_CONTROLLER
        Animation;
    static std::vector< INTERNAL_ARRAY_A >
        * InternalVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ANIMATION__) */
