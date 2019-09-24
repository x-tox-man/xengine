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
#include "CORE_MATH_VECTOR.h"

//Should be a component
XS_CLASS_BEGIN( R3D_LEVEL_TRACK_TURN )

    R3D_LEVEL_TRACK_TURN();

    void Initialize( const CORE_MATH_VECTOR & position );

XS_CLASS_END

//Should be a component
XS_CLASS_BEGIN(R3D_LEVEL_TRACK_JUMP )

    R3D_LEVEL_TRACK_JUMP();

    void Initialize( const CORE_MATH_VECTOR & position );

XS_CLASS_END

#endif /* R3D_LEVEL_TRACK_TURN_hpp */
