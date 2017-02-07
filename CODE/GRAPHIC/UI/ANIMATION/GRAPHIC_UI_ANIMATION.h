//
//  GRAPHIC_UI_ANIMATION.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_ANIMATION_hpp
#define GRAPHIC_UI_ANIMATION_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_HELPERS_CALLBACK.h"

XS_CLASS_BEGIN( GRAPHIC_UI_ANIMATION )

    GRAPHIC_UI_ANIMATION(
        GRAPHIC_UI_ELEMENT * element,
        std::function<void (GRAPHIC_UI_ELEMENT *)> begin,
        std::function<void (GRAPHIC_UI_ELEMENT *, float)> update,
        std::function<void (GRAPHIC_UI_ELEMENT *)> end,
        float time_modulator = 1.0f);
    virtual    ~GRAPHIC_UI_ANIMATION();

    void Update( float time_step );

    void SetCallback( CORE_HELPERS_CALLBACK_1<GRAPHIC_UI_ANIMATION *> & callback ) { EndAnimationCallback = callback; }

private :

    float
        Percentage,
        TimeModulator;
    GRAPHIC_UI_ELEMENT *
        Element;
    std::function<void (GRAPHIC_UI_ELEMENT *, float)>
        UpdateFunction;
    std::function<void (GRAPHIC_UI_ELEMENT *)>
        BeginFunction,
        EndFunction;
    CORE_HELPERS_CALLBACK_1<GRAPHIC_UI_ANIMATION *>
        EndAnimationCallback;

XS_CLASS_END


#endif /* GRAPHIC_UI_ANIMATION_hpp */
