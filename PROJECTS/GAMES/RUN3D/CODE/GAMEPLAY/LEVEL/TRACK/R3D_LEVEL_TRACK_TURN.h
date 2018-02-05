//
//  R3D_LEVEL_TRACK_TURN.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 17/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef R3D_LEVEL_TRACK_TURN_hpp
#define R3D_LEVEL_TRACK_TURN_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

//Should be a component
XS_CLASS_BEGIN_WITH_ANCESTOR(R3D_LEVEL_TRACK_TURN, GAMEPLAY_COMPONENT_ENTITY )

    R3D_LEVEL_TRACK_TURN();

    void Initialize( const CORE_MATH_VECTOR & position );
    void AddToSystems();

    virtual GAMEPLAY_COMPONENT_ENTITY * Clone() const override {
        
        return new GAMEPLAY_COMPONENT_ENTITY();
    }

XS_CLASS_END

//Should be a component
XS_CLASS_BEGIN_WITH_ANCESTOR(R3D_LEVEL_TRACK_JUMP, GAMEPLAY_COMPONENT_ENTITY )

    R3D_LEVEL_TRACK_JUMP();

    void Initialize( const CORE_MATH_VECTOR & position );
    void AddToSystems();

    virtual GAMEPLAY_COMPONENT_ENTITY * Clone() const override {
        
        return new GAMEPLAY_COMPONENT_ENTITY();
    }

XS_CLASS_END

#endif /* R3D_LEVEL_TRACK_TURN_hpp */
