//
//  GAMEPLAY_COMPONENT_SYSTEM_LIGHTING.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_SYSTEM_LIGHTING_hpp
#define GAMEPLAY_COMPONENT_SYSTEM_LIGHTING_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_LIGHT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_LIGHTING, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_LIGHTING();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_LIGHTING();

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;
    virtual void Render( GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

XS_CLASS_END


#endif /* GAMEPLAY_COMPONENT_SYSTEM_LIGHTING_hpp */
