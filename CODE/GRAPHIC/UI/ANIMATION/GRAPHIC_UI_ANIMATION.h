//
//  GRAPHIC_UI_ANIMATION.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_ANIMATION_hpp
#define GRAPHIC_UI_ANIMATION_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_HELPERS_SCALAR.h"

class GRAPHIC_UI_ELEMENT;

struct GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA {
    SCALAR
        From,
        To;
};

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_UI_ANIMATION )

    GRAPHIC_UI_ANIMATION();
    GRAPHIC_UI_ANIMATION(
        GRAPHIC_UI_ELEMENT * element,
        std::function<void (GRAPHIC_UI_ELEMENT *, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > &, float)> update,
        float time_modulator = 1.0f,
        std::function<void (GRAPHIC_UI_ELEMENT *)> begin = std::function<void (GRAPHIC_UI_ELEMENT *)>(),
        std::function<void (GRAPHIC_UI_ELEMENT *)> end = std::function<void (GRAPHIC_UI_ELEMENT *)>() );

    ~GRAPHIC_UI_ANIMATION();

    void operator = ( const GRAPHIC_UI_ANIMATION & other ) {
        
        Element = other.Element;
        Percentage = other.Percentage;
        TimeModulator = other.TimeModulator;
        
        UpdateFunction = other.UpdateFunction;
        BeginFunction = other.BeginFunction;
        EndFunction = other.EndFunction;
        
        InterpolationData = other.InterpolationData;
        
        EndAnimationCallback = other.EndAnimationCallback;
    }

    void Update( float time_step );
    inline void SetCallback( CORE_HELPERS_CALLBACK_1<GRAPHIC_UI_ANIMATION *> & callback ) { EndAnimationCallback = callback; }
    inline std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & GetInterpolationData() { return InterpolationData; }

private :

    float
        Percentage,
        TimeModulator;
    GRAPHIC_UI_ELEMENT *
        Element;
    std::function<void (GRAPHIC_UI_ELEMENT *, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > &, float)>
        UpdateFunction;
    std::function<void (GRAPHIC_UI_ELEMENT *)>
        BeginFunction,
        EndFunction;
    CORE_HELPERS_CALLBACK_1<GRAPHIC_UI_ANIMATION *>
        EndAnimationCallback;
    std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA >
        InterpolationData;

XS_CLASS_END


#endif /* GRAPHIC_UI_ANIMATION_hpp */
