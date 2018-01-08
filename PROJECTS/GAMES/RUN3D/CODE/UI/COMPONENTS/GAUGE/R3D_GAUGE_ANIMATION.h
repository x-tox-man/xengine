//
//  R3D_GAUGE_ANIMATION.hpp
//  Run3d
//
//  Created by Christophe Bernard on 7/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef R3D_GAUGE_ANIMATION_hpp
#define R3D_GAUGE_ANIMATION_hpp

#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_UI_ANIMATION.h"

void R3D_GAUGE_ANIMATION_UpdateColor( GRAPHIC_UI_ELEMENT * element, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & data, float percent );
void R3D_GAUGE_ANIMATION_UpdateSize( GRAPHIC_UI_ELEMENT * element, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & data, float percent );

#endif /* R3D_GAUGE_ANIMATION_hpp */
