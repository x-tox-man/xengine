//
//  GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT_hpp
#define GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT_hpp

#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT();

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;
    virtual void Render() override;
    virtual void Finalize() override;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT_hpp */
