//
//  GRAPHIC_UI_ANIMATION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_ANIMATION.h"
#include "GRAPHIC_UI_ELEMENT.h"

GRAPHIC_UI_ANIMATION::GRAPHIC_UI_ANIMATION() :
    Element( NULL ),
    Percentage( 0.0f ),
    TimeModulator( 0.0f ),
    UpdateFunction(),
    BeginFunction(),
    EndFunction(),
    EndAnimationCallback(),
    InterpolationData() {
    
}

GRAPHIC_UI_ANIMATION::GRAPHIC_UI_ANIMATION(
    GRAPHIC_UI_ELEMENT * element,
    std::function<void (GRAPHIC_UI_ELEMENT *, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > &, float)> update,
    float time_modulator,
    std::function<void (GRAPHIC_UI_ELEMENT *)> begin,
    std::function<void (GRAPHIC_UI_ELEMENT *)> end ) :
        Element( element ),
        Percentage( 0.0f ),
        TimeModulator( time_modulator ),
        UpdateFunction( update ),
        BeginFunction( begin ),
        EndFunction( end ),
        EndAnimationCallback() {
    
}

GRAPHIC_UI_ANIMATION::~GRAPHIC_UI_ANIMATION() {
    BeginFunction = NULL;
    EndFunction = NULL;
    BeginFunction = NULL;
}

void GRAPHIC_UI_ANIMATION::Update( float time_step ) {
    
    if ( Element != NULL && Percentage < 1.0f ) {
        
        if ( Percentage == 0.0f ) {
            
            //BeginFunction( Element );
        }
        
        Percentage += time_step * TimeModulator;
        Percentage = fminf( Percentage, 1.0f );
        
        UpdateFunction( Element, InterpolationData, Percentage );
        
        if ( Percentage == 1.0f ) {
            
            Element = NULL;
            Percentage = 1.0f;
            
            //EndFunction( Element );
            
            //EndAnimationCallback( this );
        }
    }
}
