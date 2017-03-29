//
//  PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT.h"

PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT::PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT( float duration ) :
    Duration( duration ),
    Timer( 0.0f ),
    Done( false ) {
    
}

PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT::~PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT() {
    
}

void PERIPHERIC_INTERRACTION_VIBRATOR_EFFECT::Update( const float step ) {
    
    Timer += step;
    
    if ( Timer >+ Duration ) {
        
        Done = true;
    }
    else {
        
    }
}
