//
//  GRAPHIC_UI_ELEMENT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_ELEMENT.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "CORE_ABSTRACT_FUNCTION.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"

typedef CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > XS_UI_CALLBACK;

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GRAPHIC_UI_ELEMENT )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, Click, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, Hover, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_MATH_VECTOR &, GRAPHIC_UI_ELEMENT, GetPosition )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_MATH_VECTOR &, GRAPHIC_UI_ELEMENT, GetSize )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, SetPosition, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, SetTextValue, const char * )

    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, SetActionCallback, XS_UI_CALLBACK & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( const CORE_HELPERS_IDENTIFIER &, GRAPHIC_UI_ELEMENT, GetIdentifier)

CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GRAPHIC_UI_ELEMENT )

GRAPHIC_UI_ELEMENT::GRAPHIC_UI_ELEMENT() :
    Placement(),
    ActionCallback(),
    RenderStyleTable(),
    Identifier( CORE_HELPERS_IDENTIFIER::Empty ),
    CurrentState( GRAPHIC_UI_ELEMENT_STATE_Default ),
    Enabled( true ),
    Visible( true ),
    Adapter( NULL ) {
    
}

GRAPHIC_UI_ELEMENT::GRAPHIC_UI_ELEMENT(const CORE_HELPERS_IDENTIFIER & identifier) :
    Placement(),
    ActionCallback(),
    RenderStyleTable(),
    Identifier( identifier ),
    CurrentState( GRAPHIC_UI_ELEMENT_STATE_Default ),
    Enabled( true ),
    Visible( true ),
    Adapter( NULL ) {

}

GRAPHIC_UI_ELEMENT::~GRAPHIC_UI_ELEMENT() {

}

void GRAPHIC_UI_ELEMENT::SetActionCallback( CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > & action_callback ) {
    
    ActionCallback = action_callback;
    
    // TODO : FIX!!!!
    /*if ( action_callback.IsConnected() ) {
        
        ActionCallback = *(CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > *) ((void *)action_callback.CallbackFunction);
    }*/
}

void GRAPHIC_UI_ELEMENT::Update( const float time_step ) {
    
    switch ( CurrentState ) {

        case GRAPHIC_UI_ELEMENT_STATE_Default:
            
            break;
            
        case GRAPHIC_UI_ELEMENT_STATE_Pressed:
            
            if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonReleased() ) {
                
                CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
                
                ActionCallback( this, CurrentState );
            }
            
            break;
            
        default:
            break;
    }
}

void GRAPHIC_UI_ELEMENT::Render( const GRAPHIC_RENDERER & renderer ) {
    
    if ( IsVisible() && RenderStyleTable[ CurrentState ] ) {
        
        RenderStyleTable[ CurrentState ]->Apply( renderer, Placement );
    }
}

void GRAPHIC_UI_ELEMENT::Click( const CORE_MATH_VECTOR & cursor_position ) {
    
    CurrentState = GRAPHIC_UI_ELEMENT_STATE_Pressed;
    
    ActionCallback( this, CurrentState );
}

void GRAPHIC_UI_ELEMENT::Hover( const CORE_MATH_VECTOR & cursor_position ) {
    
    bool contains = GRAPHIC_UI_ELEMENT::Contains( cursor_position );
    
    if ( CurrentState != GRAPHIC_UI_ELEMENT_STATE_Hovered && CurrentState != GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        if ( contains && IsVisible() && IsEnabled() ) {
            
            CurrentState = GRAPHIC_UI_ELEMENT_STATE_Hovered;
            
            ActionCallback( this, CurrentState );
        }
    }
    else if ( CurrentState == GRAPHIC_UI_ELEMENT_STATE_Hovered ) {
        
        if ( !contains && IsVisible() ) {
            
            CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
            
            ActionCallback( this, CurrentState );
        }
    }
}

void GRAPHIC_UI_ELEMENT::Hover( const bool force_hover ) {
    
    if ( CurrentState == GRAPHIC_UI_ELEMENT_STATE_Hovered ) {
        
        if ( IsVisible() ) {
            
            CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
            
            ActionCallback( this, CurrentState );
        }
    }
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_ELEMENT::Contains( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( IsVisible() && CORE_MATH_SHAPE_RECTANGLE::Contains( GetPosition(), GetSize() * 0.5f, cursor_position ) ) {
        
        return this;
    }
    
    return NULL;
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_ELEMENT::GetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    return ( Identifier == identifier ) ? this : NULL;
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_ELEMENT::Copy() {
    
    GRAPHIC_UI_ELEMENT * newElement = new GRAPHIC_UI_ELEMENT();
    
    Placement.Copy( newElement->Placement );
    newElement->RenderStyleTable = RenderStyleTable;
    
    newElement->Identifier = Identifier;
    newElement->CurrentState = CurrentState;
    newElement->Enabled = Enabled;
    newElement->Visible = Visible;
    newElement->Adapter = Adapter;
    Animation.Copy(newElement->Animation );
    
    newElement->ActionCallback = ActionCallback;
    newElement->ActionCallback.SetObject(newElement);
    
    return newElement;
}
