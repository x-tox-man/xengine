//
//  GRAPHIC_UI_PLACEMENT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_PLACEMENT.h"

GRAPHIC_UI_PLACEMENT::GRAPHIC_UI_PLACEMENT() :
    RelativePosition( CORE_MATH_VECTOR::Zero ),
    AbsolutePosition( CORE_MATH_VECTOR::Zero ),
    Size( CORE_MATH_VECTOR::Zero ),
    ScrollOffset( CORE_MATH_VECTOR::Zero ),
    Anchor( GRAPHIC_UI_Center ),
    Rotation( 0.0f ),
    Parent( NULL ) {
    
}

GRAPHIC_UI_PLACEMENT::~GRAPHIC_UI_PLACEMENT() {

}

void GRAPHIC_UI_PLACEMENT::Initialize( const GRAPHIC_UI_PLACEMENT * ParentPlacement, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor ) {
    
    RelativePosition = position;
    Size = size;
    Anchor = anchor;
    
    Parent = ParentPlacement;
    
    OnPlacementPropertyChanged();
}

void GRAPHIC_UI_PLACEMENT::OnPlacementPropertyChanged() {

    CORE_MATH_VECTOR
        ParentSize;
    
    if ( Parent ) {
        
        AbsolutePosition = Parent->GetAbsolutePosition();
        ParentSize = Parent->GetSize();
    }
    else {
        
        AbsolutePosition = CORE_MATH_VECTOR::Zero;
        ParentSize = CORE_MATH_VECTOR::Zero;
    }

    if ( Anchor & GRAPHIC_UI_PLACEMENT_ANCHOR_Left ) {
        
        AbsolutePosition[0] -= (ParentSize[0] - Size[0]) * 0.5f;
    }
    else if ( Anchor & GRAPHIC_UI_PLACEMENT_ANCHOR_Right ) {
        
        AbsolutePosition[0] += (ParentSize[0] - Size[0]) * 0.5f;
    }
    /*else if ( Anchor & GRAPHIC_UI_PLACEMENT_ANCHOR_CenterX ) {
       
        //Useless
        AbsolutePosition[0] += 0.0f;
    }*/
    
    if ( Anchor & GRAPHIC_UI_PLACEMENT_ANCHOR_Top ) {
        
        AbsolutePosition[1] += (ParentSize[1] - Size[1]) * 0.5f;
    }
    else if ( Anchor & GRAPHIC_UI_PLACEMENT_ANCHOR_Bottom ) {
        
        AbsolutePosition[1] -= (ParentSize[1] - Size[1]) * 0.5f;
    }
    /*else if ( Anchor & GRAPHIC_UI_PLACEMENT_ANCHOR_CenterY ) {
        
        //Useless
        AbsolutePosition[1] += 0.0f;
    }*/
    
    if ( Parent && Parent->GetScrollOffset()[0] != 0.0f )
    {
        AbsolutePosition[0] += Parent->GetScrollOffset()[0];
    }
    
    if ( Parent && Parent->GetScrollOffset()[1] != 0.0f )
    {
        AbsolutePosition[1] += Parent->GetScrollOffset()[1];
    }
    
    AbsolutePosition += RelativePosition;
}

void GRAPHIC_UI_PLACEMENT::Copy( GRAPHIC_UI_PLACEMENT & other ) {

    other.RelativePosition = RelativePosition;
    other.AbsolutePosition = AbsolutePosition;
    other.Size = Size;
    other.Anchor = Anchor;
    other.Rotation = Rotation;
    other.Parent = Parent;
}
