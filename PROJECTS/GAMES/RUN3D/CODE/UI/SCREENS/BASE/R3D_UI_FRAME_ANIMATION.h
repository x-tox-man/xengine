//
//  R3D_UI_FRAME_ANIMATION.hpp
//  Run3d
//
//  Created by Christophe Bernard on 9/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef R3D_UI_FRAME_ANIMATION_hpp
#define R3D_UI_FRAME_ANIMATION_hpp

#include "GRAPHIC_UI_ANIMATION.h"

class GRAPHIC_UI_ELEMENT;

void R3D_UI_FRAME_ANIMATION_CollapseInit( GRAPHIC_UI_ELEMENT * element );
void R3D_UI_FRAME_ANIMATION_Update( GRAPHIC_UI_ELEMENT * element, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & data, float percent );

void R3D_UI_FRAME_ANIMATION_AppearInit( GRAPHIC_UI_ELEMENT * element );
void R3D_UI_FRAME_ANIMATION_AppearFinish( GRAPHIC_UI_ELEMENT * element );


#endif /* R3D_UI_FRAME_ANIMATION_hpp */
