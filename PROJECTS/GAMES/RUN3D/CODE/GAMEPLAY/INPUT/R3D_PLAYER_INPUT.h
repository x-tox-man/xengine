//
//  R3D_PLAYER_INPUT.hpp
//  Run3d
//
//  Created by Christophe Bernard on 13/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_INPUT_hpp
#define R3D_PLAYER_INPUT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"

XS_CLASS_BEGIN( R3D_PLAYER_INPUT )

    XS_DEFINE_UNIQUE( R3D_PLAYER_INPUT )

    void SetNormalizedDirection( const float percentage ) { NormalizedDirection = percentage; }
    void SetNormalizedAcceleration( const float percentage ) { NormalizedAcceleration = percentage; }

    float GetNormalizedDirection() const { return NormalizedDirection; }
    float GetNormalizedAcceleration() const { return NormalizedAcceleration; }

private:

    float
        NormalizedDirection,
        NormalizedAcceleration;

XS_CLASS_END


#endif /* R3D_PLAYER_INPUT_hpp */
