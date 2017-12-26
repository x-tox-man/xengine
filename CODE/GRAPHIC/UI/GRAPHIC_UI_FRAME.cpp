    //
//  GRAPHIC_UI_FRAME.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_UI_FRAME_ADAPTER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "GRAPHIC_SYSTEM.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GRAPHIC_UI_FRAME )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_FRAME, Contains, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_FRAME, GetElement, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GRAPHIC_UI_FRAME, AddObject, GRAPHIC_UI_ELEMENT * )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GRAPHIC_UI_FRAME )

GRAPHIC_UI_FRAME::GRAPHIC_UI_FRAME() :
    GRAPHIC_UI_ELEMENT(),
    ElementTable(),
    NamedElementTable() {
    
}

GRAPHIC_UI_FRAME::~GRAPHIC_UI_FRAME() {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    do {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        
        it++;
        
    } while ( it != ElementTable.end() );
    
    ElementTable.clear();
    NamedElementTable.clear();
}

void GRAPHIC_UI_FRAME::Initialize() {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    OnPlacementPropertyChanged();
    
    while ( it != ElementTable.end() ) {
        
        (*it)->OnPlacementPropertyChanged();
        
        it++;
        
    }
    
    if ( Adapter ) {
        
        ((GRAPHIC_UI_FRAME_ADAPTER *) Adapter)->OnLayoutFrame( this );
    }
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::Contains( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( GRAPHIC_UI_ELEMENT::Contains( cursor_position ) ) {
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            GRAPHIC_UI_ELEMENT * element = (*it)->Contains( cursor_position );
            
            if( element && element->GetActionCallback().IsConnected() ) {
                
                return element;
            }
            
            it++;
            
        }
        
        return this;
    }
    
    return NULL;
}

void GRAPHIC_UI_FRAME::Update( const float time_step ) {
    
    if ( IsEnabled() ) {
        
        GRAPHIC_UI_ELEMENT::Update( time_step );
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Update( time_step );
            
            it++;
        }
    }
}

void GRAPHIC_UI_FRAME::Render( GRAPHIC_RENDERER & renderer ) {
    
    if ( IsVisible() ) {
        
        int base_x = GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().X() * 0.5f + (GetPlacement().GetAbsolutePosition().X() - GetPlacement().GetSize().X() * 0.5f );
        int base_y = GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().Y() * 0.5f + (GetPlacement().GetAbsolutePosition().Y() - GetPlacement().GetSize().Y() * 0.5f );
        
        GRAPHIC_UI_ELEMENT::Render( renderer );
        
        bool scissor_is_enabled = renderer.IsScissorEnabled();
        CORE_MATH_VECTOR scissor_rectangle = renderer.GetScissorRectangle();
        
        
        renderer.SetScissorRectangle(CORE_MATH_VECTOR(base_x, base_y, GetPlacement().GetSize().X(), GetPlacement().GetSize().Y() ) );
        renderer.EnableScissor( false );
        
        GRAPHIC_SYSTEM::SetScissorRectangle(base_x, base_y, GetPlacement().GetSize().X(), GetPlacement().GetSize().Y());
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Render( renderer );
            
            it++;
        }
        
        renderer.SetScissorRectangle(scissor_rectangle);
        renderer.EnableScissor( scissor_is_enabled );
    }
}

void GRAPHIC_UI_FRAME::Click( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( Adapter ) {
        printf( "test" );
    }
    
    if ( GRAPHIC_UI_ELEMENT::Contains( cursor_position ) ) {
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        GRAPHIC_UI_ELEMENT::Click( cursor_position );
        
        while ( it != ElementTable.end() ) {
            
            GRAPHIC_UI_ELEMENT * element = (*it)->Contains( cursor_position );
            
            if( element != NULL && element->IsEnabled() && element->IsVisible() ) {
                
                if ( element->GetCurrentState() != GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
                    
                    element->Click( cursor_position );
                    break;
                }
                else if ( element->GetCurrentState() == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
                    
                    element->Drag( cursor_position );
                }
            }
            
            it++;
        }
    }
}

void GRAPHIC_UI_FRAME::Hover( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( GRAPHIC_UI_ELEMENT::Contains( cursor_position ) ) {
        
        GRAPHIC_UI_ELEMENT::Hover( cursor_position );
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Hover( cursor_position );
            
            it++;
            
        }
        
        if ( Adapter && PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonReleased() ) {
            
            //TODO
            Adapter->OnDragEnd();
        }
    }
    else {
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        GRAPHIC_UI_ELEMENT::Hover( false );
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Hover( false );
            
            it++;
        }
    }
}

void GRAPHIC_UI_FRAME::Hover( const bool force_hover ) {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    GRAPHIC_UI_ELEMENT::Hover( false );
    
    while ( it != ElementTable.end() ) {
        
        (*it)->Hover( force_hover );
        
        it++;
    }
}

void GRAPHIC_UI_FRAME::Drag( const CORE_MATH_VECTOR & cursor_position ) {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    GRAPHIC_UI_ELEMENT::Drag( cursor_position );
    
    while ( it != ElementTable.end() ) {
        
        (*it)->Drag( cursor_position );
        
        it++;
    }
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::GetObjectAtIndex(int index ) {
    
#if DEBUG
    assert( index < ElementTable.size() );
#endif
    
    return ElementTable[index];
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::GetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    if ( Identifier == identifier ) {
        
        return this;
    }
    
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_ELEMENT *>::iterator it = NamedElementTable.begin();
    
    while ( it != NamedElementTable.end() ) {
        
        if( it->first == identifier ) {
            
            return it->second;
        }
        
        it++;
    }
    
    return NULL;
}

void GRAPHIC_UI_FRAME::SetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & identifier, GRAPHIC_UI_ELEMENT * element ) {
    
    element->SetIdentifier(identifier);
    AddObject(element);
}

void GRAPHIC_UI_FRAME::AddObject( GRAPHIC_UI_ELEMENT * element ) {
    
#if DEBUG
    
    if( ElementTable.size() ) {
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        do {
            
            assert( &(*(*it)) != &(*element) );
            
            ++it;
            
        } while ( it != ElementTable.end() );
    }
#endif
    
    ElementTable.push_back( element );
    element->GetPlacement().SetParent( &this->GetPlacement() );
    
    if ( element->GetIdentifier() != CORE_HELPERS_IDENTIFIER::Empty) {
        NamedElementTable[ element->GetIdentifier() ] = element;
    }
}

void GRAPHIC_UI_FRAME::RemoveObject( GRAPHIC_UI_ELEMENT * element ) {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    while ( it != ElementTable.end() ) {
        
        if ( (*it ) == element ) {
            
            ElementTable.erase( it );
            
            break;
        }
        
        it++;
    }
}

void GRAPHIC_UI_FRAME::RemoveObjects() {
    
    NamedElementTable.clear();
    ElementTable.clear();
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::GetElement( const char * element_name ) {
    
    CORE_HELPERS_IDENTIFIER identifier ( element_name );
    
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_ELEMENT *>::iterator it = NamedElementTable.begin();
    
     while ( it != NamedElementTable.end() ) {
        
        if( it->first == identifier ) {
            
            return it->second;
        }
        
        it++;
        
    }
    
    return NULL;
}

void GRAPHIC_UI_FRAME::OnPlacementPropertyChanged() {

    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    while ( it != ElementTable.end() ) {
        
        (*it)->GetPlacement().OnPlacementPropertyChanged();
        
        it++;
    }
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::InnerCopy(GRAPHIC_UI_FRAME * other_frame ) {
    
    Placement.Copy( other_frame->Placement );
    
    other_frame->RenderStyleTable = RenderStyleTable;
    
    //otherFrame->Identifier = Identifier; //Fordidden
    other_frame->CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
    other_frame->Enabled = Enabled;
    other_frame->Visible = Visible;
    other_frame->Adapter = Adapter;
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    while ( it != ElementTable.end() ) {
        
        auto new_item = (*it)->Copy();
        new_item->GetPlacement().SetParent(&other_frame->GetPlacement() );
        other_frame->ElementTable.push_back( new_item );
        
        it++;
    }
    
    return other_frame;
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::Copy() {
    
    return InnerCopy( new GRAPHIC_UI_FRAME() );
}

void GRAPHIC_UI_FRAME::SetOpacity( float opacity ) {
    
    GRAPHIC_UI_ELEMENT::SetOpacity( opacity );
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    while ( it != ElementTable.end() ) {
        
        (*it)->SetOpacity( opacity );
        
        it++;
    }
}
