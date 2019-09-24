//
//  GAMEPLAY_COMPONENT_SYSTEM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_ENTITY_PROXY.h"

enum GAMEPLAY_COMPONENT_SYSTEM_MASK {
    GAMEPLAY_COMPONENT_SYSTEM_MASK_All,
    GAMEPLAY_COMPONENT_SYSTEM_MASK_Transparent,
    GAMEPLAY_COMPONENT_SYSTEM_MASK_Opaque,
    GAMEPLAY_COMPONENT_SYSTEM_MASK_None
};

class GRAPHIC_RENDERER;

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM();

    XS_DEFINE_SERIALIZABLE

    virtual void Initialize();

    virtual void Update( void * ecs_base_pointer, float time_step );
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer );

    virtual void Finalize();

    virtual void Clear() {
        
        EntitiesTable.clear();
    }

    virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    virtual void RemoveEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity );

    void SaveToStream( CORE_DATA_STREAM & stream );
    void LoadFromStream( CORE_DATA_STREAM & stream );

    inline int GetMask() const { return Mask; }
    inline void SetMask( int mask ) { Mask = mask; }

protected:

    //By design Entities must be added and removed in systems the same way they are in the memory layout
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >
        EntitiesTable;
    int
        Mask;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__) */
