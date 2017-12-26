//
//  R3D_GAMEPLAY_GAME_DELEGATE.hpp
//  Run3d
//
//  Created by Christophe Bernard on 26/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GAMEPLAY_GAME_DELEGATE_hpp
#define R3D_GAMEPLAY_GAME_DELEGATE_hpp

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN( R3D_GAMEPLAY_GAME_DELEGATE )

    R3D_GAMEPLAY_GAME_DELEGATE();
    virtual ~R3D_GAMEPLAY_GAME_DELEGATE() {
        
    }

    virtual void InternalUpdateGame( const float step ) {
        
    }
    virtual void InitializePlayers() {
        
    }

XS_CLASS_END

#endif /* R3D_GAMEPLAY_GAME_DELEGATE_hpp */
