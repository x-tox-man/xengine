//
//  CORE_MATH_RAY_SEGMENT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/09/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef CORE_MATH_RAY_SEGMENT_hpp
#define CORE_MATH_RAY_SEGMENT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"

XS_CLASS_BEGIN( CORE_MATH_RAY_SEGMENT )

    CORE_MATH_RAY_SEGMENT();
    ~CORE_MATH_RAY_SEGMENT();

    inline void SetOrigin( const CORE_MATH_VECTOR & origin ) { Origin = origin; }
    inline void SetDestination( const CORE_MATH_VECTOR & destination ) { Destination = destination; }

    inline const CORE_MATH_VECTOR & GetOrigin() const { return Origin; }
    inline const CORE_MATH_VECTOR & GetDestination() const { return Destination; }

    inline CORE_MATH_VECTOR & GetOrigin() { return Origin; }
    inline CORE_MATH_VECTOR & GetDestination() { return Destination; }

private :

    CORE_MATH_VECTOR
        Origin,
        Destination;

XS_CLASS_END

#endif /* CORE_MATH_RAY_SEGMENT_hpp */
