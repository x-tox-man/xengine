//
//  R3D_GAUGE_ANIMATION.cpp
//  Run3d
//
//  Created by Christophe Bernard on 7/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_GAUGE_ANIMATION.h"

void R3D_GAUGE_ANIMATION_UpdateColor( GRAPHIC_UI_ELEMENT * element, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & data, float percent ) {
    
}

void R3D_GAUGE_ANIMATION_UpdateSize( GRAPHIC_UI_ELEMENT * element, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & data, float percent ) {
    
    SCALAR & s_from = data[ 0 ].From;
    SCALAR & s_to = data[ 0 ].To;
    
    element->GetPlacement().SetSize( CORE_MATH_VECTOR( s_from.FloatArray4[ 0 ], s_from.FloatArray4[ 1 ] ) * (1.0f - percent ) + CORE_MATH_VECTOR( s_to.FloatArray4[ 0 ], s_to.FloatArray4[ 1 ] ) * percent );
}
