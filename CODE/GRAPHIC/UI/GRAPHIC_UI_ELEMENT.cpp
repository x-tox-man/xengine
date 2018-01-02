//
//  GRAPHIC_UI_ELEMENT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_ELEMENT.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "CORE_ABSTRACT_FUNCTION.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"

typedef CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT > XS_UI_CALLBACK;

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GRAPHIC_UI_ELEMENT )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, Click, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, Hover, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_MATH_VECTOR &, GRAPHIC_UI_ELEMENT, GetPosition )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_MATH_VECTOR &, GRAPHIC_UI_ELEMENT, GetSize )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, SetPosition, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( GRAPHIC_UI_ELEMENT, SetTextValue, const CORE_DATA_UTF8_TEXT & )

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
    Adapter( NULL ),
    Opacity( 1.0f ) {
    
}

GRAPHIC_UI_ELEMENT::GRAPHIC_UI_ELEMENT(const CORE_HELPERS_IDENTIFIER & identifier) :
    Placement(),
    ActionCallback(),
    RenderStyleTable(),
    Identifier( identifier ),
    CurrentState( GRAPHIC_UI_ELEMENT_STATE_Default ),
    Enabled( true ),
    Visible( true ),
    Adapter( NULL ),
    Opacity( 1.0f ) {

}

GRAPHIC_UI_ELEMENT::~GRAPHIC_UI_ELEMENT() {

    CORE_MEMORY_ObjectSafeDeallocation( Adapter );
    
    std::array< GRAPHIC_UI_RENDER_STYLE *, 4 >::iterator it = RenderStyleTable.begin();
    
    while (it != RenderStyleTable.end() ) {
        
        *it = NULL;
        it++;
    }
}

void GRAPHIC_UI_ELEMENT::Finalize() {
    
    ActionCallback.Disconnect();
    OnTextChangedCallback.Disconnect();
    
    if ( RenderStyleTable[0] != NULL ) {
        CORE_MEMORY_ObjectSafeDeallocation( RenderStyleTable[0] );
    }
    if ( RenderStyleTable[1] != NULL ) {
        CORE_MEMORY_ObjectSafeDeallocation( RenderStyleTable[0] );
    }
    if ( RenderStyleTable[2] != NULL ) {
        CORE_MEMORY_ObjectSafeDeallocation( RenderStyleTable[0] );
    }
    if ( RenderStyleTable[3] != NULL ) {
        CORE_MEMORY_ObjectSafeDeallocation( RenderStyleTable[0] );
    }
}

void GRAPHIC_UI_ELEMENT::SetActionCallback( CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT > & action_callback ) {
    
    ActionCallback = action_callback;
}

void GRAPHIC_UI_ELEMENT::Update( const float time_step ) {
    
    switch ( CurrentState ) {

        case GRAPHIC_UI_ELEMENT_STATE_Default:
            
            break;
            
        case GRAPHIC_UI_ELEMENT_STATE_Pressed:
            
            if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonReleased() ) {
                
                CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
                
                ActionCallback( this, GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut );
            }
            
            break;
            
        default:
            break;
    }
}

void GRAPHIC_UI_ELEMENT::Render( GRAPHIC_RENDERER & renderer ) {
    
    if ( IsVisible() ) {
        
        if (  RenderStyleTable[ (unsigned int) CurrentState ] != NULL ) {
            
            RenderStyleTable[ CurrentState ]->Apply( renderer, Placement, Opacity );
        }
        else {
            
            for (int i = 0; i< RenderStyleTable.size(); i++) {
                
                if ( RenderStyleTable[ i ] != NULL ) {
                    
                    RenderStyleTable[ i ]->Apply( renderer, Placement, Opacity );
                    
                    break;
                }
            }
        }
    }
}

void GRAPHIC_UI_ELEMENT::Click( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( CurrentState != GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        CurrentState = GRAPHIC_UI_ELEMENT_STATE_Pressed;
        
        ActionCallback( this, GRAPHIC_UI_ELEMENT_EVENT_OnTouchIn );
    }
}

void GRAPHIC_UI_ELEMENT::Hover( const CORE_MATH_VECTOR & cursor_position ) {
    
    bool contains = Contains( cursor_position );
    
    if ( CurrentState != GRAPHIC_UI_ELEMENT_STATE_Hovered && CurrentState != GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        if ( contains && IsVisible() && IsEnabled() ) {
            
            CurrentState = GRAPHIC_UI_ELEMENT_STATE_Hovered;
            
            ActionCallback( this, GRAPHIC_UI_ELEMENT_EVENT_OnHoveredIn );
        }
    }
    else if ( CurrentState == GRAPHIC_UI_ELEMENT_STATE_Hovered && CurrentState != GRAPHIC_UI_ELEMENT_STATE_Default ) {
        
        if ( !contains && IsVisible() ) {
            
            CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
            
            ActionCallback( this, GRAPHIC_UI_ELEMENT_EVENT_OnHoveredOut );
        }
    }
}

void GRAPHIC_UI_ELEMENT::Drag( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( Adapter ) {
        
        Adapter->OnDragged( this, cursor_position );
    }
}

void GRAPHIC_UI_ELEMENT::Hover( const bool force_hover ) {
    
    if ( ( CurrentState & GRAPHIC_UI_ELEMENT_STATE_Hovered) == GRAPHIC_UI_ELEMENT_STATE_Hovered ) {
        
        if ( IsVisible() ) {
            
            CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
            
            ActionCallback( this, GRAPHIC_UI_ELEMENT_EVENT_OnHoveredOut );
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
    
    return newElement;
}
