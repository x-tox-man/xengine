//
//  GAMEPLAY_LIGHT.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_LIGHT_hpp
#define GAMEPLAY_LIGHT_hpp


#include "GRAPHIC_SHADER_LIGHT.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY(GAMEPLAY_LIGHT, GAMEPLAY_COMPONENT_ENTITY )

    GAMEPLAY_LIGHT();
    ~GAMEPLAY_LIGHT();

    void Initialize();

    inline GRAPHIC_SHADER_LIGHT & GetLight() { return Light; }

    virtual GAMEPLAY_COMPONENT_ENTITY * Clone() const override {
        
        return new GAMEPLAY_LIGHT( *this );
    }

private:

    GRAPHIC_SHADER_LIGHT
        Light;

XS_CLASS_END

#endif /* GAMEPLAY_LIGHT_hpp */
