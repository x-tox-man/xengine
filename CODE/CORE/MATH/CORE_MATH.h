//
//  MATH.h
//  MULTIPOLY
//
//  Created by Christophe Bernard on 23/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MATH_h
#define MATH_h

template <typename __LERPABLE_CLASS__>
__LERPABLE_CLASS__ CORE_MATH_GetLerpInterpolation(__LERPABLE_CLASS__ first, __LERPABLE_CLASS__ second, float percentage) {
    
    return first.LerpInterpolate( second, percentage );
}

#endif /* MATH_h */
