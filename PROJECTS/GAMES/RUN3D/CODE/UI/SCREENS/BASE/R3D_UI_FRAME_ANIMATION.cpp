//
//  R3D_UI_FRAME_ANIMATION.cpp
//  Run3d
//
//  Created by Christophe Bernard on 9/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_UI_FRAME_ANIMATION.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_UI_FRAME.h"

void R3D_UI_FRAME_ANIMATION_CollapseInit( GRAPHIC_UI_ELEMENT * element ) {
    
    auto frame_element = ( GRAPHIC_UI_FRAME::PTR ) element;
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = frame_element->GetElementTable().begin();
    
    while ( it != frame_element->GetElementTable().end() ) {
        
        (*it)->SetVisible( false );
        
        it++;
    }
}

void R3D_UI_FRAME_ANIMATION_Update( GRAPHIC_UI_ELEMENT * element, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > & data, float percent ) {
    
    SCALAR & s_from = data[ 0 ].From;
    SCALAR & s_to = data[ 0 ].To;
    
    element->GetPlacement().SetSize( CORE_MATH_VECTOR( s_from.FloatArray4[ 0 ], s_from.FloatArray4[ 1 ] ) * (1.0f - percent ) + CORE_MATH_VECTOR( s_to.FloatArray4[ 0 ], s_to.FloatArray4[ 1 ] ) * percent );
}

void R3D_UI_FRAME_ANIMATION_AppearInit( GRAPHIC_UI_ELEMENT * element ) {
    
    auto frame_element = ( GRAPHIC_UI_FRAME::PTR ) element;
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = frame_element->GetElementTable().begin();
    
    while ( it != frame_element->GetElementTable().end() ) {
        
        (*it)->SetVisible( false );
        
        it++;
    }
}

void R3D_UI_FRAME_ANIMATION_AppearFinish( GRAPHIC_UI_ELEMENT * element ) {
    
    auto frame_element = ( GRAPHIC_UI_FRAME::PTR ) element;
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = frame_element->GetElementTable().begin();
    
    while ( it != frame_element->GetElementTable().end() ) {
        
        (*it)->SetVisible( true );
        
        it++;
    }
}
