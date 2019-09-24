//
//  R3D_GAMEPLAY_SYSTEM_PLAYERS.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 23/05/2019.
//  Copyright © 2019 IGZ. All rights reserved.
//

#ifndef R3D_GAMEPLAY_SYSTEM_PLAYERS_hpp
#define R3D_GAMEPLAY_SYSTEM_PLAYERS_hpp

#include "GAMEPLAY_COMPONENT_SYSTEM.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_GAMEPLAY_SYSTEM_PLAYERS, GAMEPLAY_COMPONENT_SYSTEM )

    R3D_GAMEPLAY_SYSTEM_PLAYERS();
    virtual ~R3D_GAMEPLAY_SYSTEM_PLAYERS();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step ) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer )override;
    virtual void Finalize() override;

XS_CLASS_END

#endif /* R3D_GAMEPLAY_SYSTEM_PLAYERS_hpp */
