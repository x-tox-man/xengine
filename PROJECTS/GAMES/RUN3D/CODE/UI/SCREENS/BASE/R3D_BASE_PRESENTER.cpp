//
//  R3D_BASE_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_BASE_PRESENTER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "R3D_UI_FRAME_ANIMATION.h"

R3D_BASE_PRESENTER::R3D_BASE_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    GRAPHIC_UI_PRESENTER() {
    
    Initialize( view );
}

void R3D_BASE_PRESENTER::Back( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        BackAnimated();
    }
}

void R3D_BASE_PRESENTER::BackAnimated() {
    
    std::function<void (GRAPHIC_UI_ELEMENT *, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > &, float)>
    update = R3D_UI_FRAME_ANIMATION_Update;
    std::function<void (GRAPHIC_UI_ELEMENT *)>
    begin = R3D_UI_FRAME_ANIMATION_CollapseInit,
    begin_open = R3D_UI_FRAME_ANIMATION_AppearInit,
    end = R3D_UI_FRAME_ANIMATION_AppearFinish;
    GRAPHIC_UI_ANIMATION
    close_animation(
                    GetView(),
                    update,
                    4.0f,
                    begin ),
    open_animation( NULL,
                   update,
                   4.0f,
                   begin_open,
                   end);
    
    GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA
    data,
    data_open;
    CORE_MATH_VECTOR
    c( GetView()->GetPlacement().GetSize().X(), 0.0f );
    
    data.From.FloatArray4[0] = GetView()->GetPlacement().GetSize()[0];
    data.From.FloatArray4[1] = GetView()->GetPlacement().GetSize()[1];
    
    data.To.FloatArray4[0] = c[0];
    data.To.FloatArray4[1] = c[1];
    
    data_open.From.FloatArray4[0] = c[0];
    data_open.From.FloatArray4[1] = c[1];
    
    data_open.To.FloatArray4[0] = GetView()->GetPlacement().GetSize()[0];
    data_open.To.FloatArray4[1] = GetView()->GetPlacement().GetSize()[1];
    
    close_animation.GetInterpolationData().push_back( data );
    open_animation.GetInterpolationData().push_back( data_open );
    
    GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateBackAsyncWithAnimation( close_animation, open_animation );
    
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
    
    AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
}

