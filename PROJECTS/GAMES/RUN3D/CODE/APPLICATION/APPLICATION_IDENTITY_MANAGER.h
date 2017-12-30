//
//  APPLICATION_IDENTITY_MANAGER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 29/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef APPLICATION_IDENTITY_MANAGER_hpp
#define APPLICATION_IDENTITY_MANAGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "R3D_PLAYER.h"

XS_CLASS_BEGIN( APPLICATION_IDENTITY_MANAGER )

    APPLICATION_IDENTITY_MANAGER();

    inline R3D_PLAYER::PTR GetCurrentPlayer() { return Player; }

private:

    R3D_PLAYER::PTR
        Player;

XS_CLASS_END

#endif /* APPLICATION_IDENTITY_MANAGER_hpp */
