//
//  GAMEPLAY_COMPONENT_SYSTEM_PICKING.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_PICKING__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_PICKING__

#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_MESH_ANIMATION.h"
#include "CORE_MATH_RAY.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_RENDERER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_PICKING, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_PICKING();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_PICKING();

    virtual void Initialize() override;
    virtual void Update( void * ecs_base_pointer, float time_step) override;
    virtual void Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

    const CORE_MATH_RAY & GetRay() const { return Ray; };

    void SetOnPickedCallback( CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * > * callback ) { OnPickedCallback = callback; };

private :

    void ComputeRay( const CORE_MATH_VECTOR & origin, const GRAPHIC_CAMERA & camera );

    CORE_MATH_RAY
        Ray;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >
        * OnPickedCallback;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_PICKING__) */
