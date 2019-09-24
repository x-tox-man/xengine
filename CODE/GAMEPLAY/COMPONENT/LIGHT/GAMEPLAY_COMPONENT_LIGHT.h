//
//  GAMEPLAY_LIGHT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_LIGHT_hpp
#define GAMEPLAY_LIGHT_hpp

#include "GRAPHIC_SHADER_LIGHT.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GRAPHIC_SHADER_LIGHT.h"

class GAMEPLAY_COMPONENT_SYSTEM_LIGHTING;

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GAMEPLAY_COMPONENT_LIGHT, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_LIGHT();
    virtual ~GAMEPLAY_COMPONENT_LIGHT();

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT_LIGHT );

    friend class GAMEPLAY_COMPONENT_SYSTEM_LIGHTING;

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_COMPONENT_LIGHT, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Light )

    static void Clear();
    static void SaveToStream( CORE_DATA_STREAM & stream );
    static void LoadFromStream( CORE_DATA_STREAM & stream );

    inline GRAPHIC_SHADER_LIGHT * GetLight() { return Light; }
    inline void SetLight( GRAPHIC_SHADER_LIGHT::PTR light ) { Light = light; }

private :

    GRAPHIC_SHADER_LIGHT::PTR
        Light;

XS_CLASS_END

#endif /* GAMEPLAY_LIGHT_hpp */
