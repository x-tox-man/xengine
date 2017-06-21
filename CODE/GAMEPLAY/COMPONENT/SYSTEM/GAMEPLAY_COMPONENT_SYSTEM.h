//
//  GAMEPLAY_COMPONENT_SYSTEM.h
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM();

    XS_DEFINE_SERIALIZABLE

    virtual void Initialize();

    virtual void Update( float time_step );
    virtual void Render();

    virtual void Finalize();

    void Clear() {
        
        EntitiesTable.clear();
    }

    virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity );
    virtual void RemoveEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity );

    void SaveToStream( CORE_DATA_STREAM & stream );
    void LoadFromStream( CORE_DATA_STREAM & stream );

    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >
        EntitiesTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM__) */
