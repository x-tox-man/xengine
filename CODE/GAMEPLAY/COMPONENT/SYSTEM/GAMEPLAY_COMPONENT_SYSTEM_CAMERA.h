//
//  GAMEPLAY_COMPONENT_SYSTEM_CAMERA.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/05/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_SYSTEM_CAMERA_hpp
#define GAMEPLAY_COMPONENT_SYSTEM_CAMERA_hpp

#include "GAMEPLAY_COMPONENT_SYSTEM.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_CAMERA, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_CAMERA();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_CAMERA();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_SYSTEM_CAMERA_hpp */
