//
//  PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT_hpp
#define PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT_hpp

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN( PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT )

    PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT(float duration);
    ~PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT();

    void Update( const float step );
    inline bool IsDone() { return Done; }

private:

float
    Duration,
    Timer;
bool
    Done;

XS_CLASS_END

#endif /* PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT_hpp */
