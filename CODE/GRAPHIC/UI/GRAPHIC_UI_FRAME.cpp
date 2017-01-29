    //
//  GRAPHIC_UI_FRAME.cpp
//  GAME-ENGINE-REBORN
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
        
        delete (*it);
        
        it++;
        
    } while ( it != ElementTable.end() );
    
    ElementTable.clear();
    NamedElementTable.clear();
}

void GRAPHIC_UI_FRAME::Initialize() {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    do {
        
        (*it)->Initialize();
        
        it++;
        
    } while ( it != ElementTable.end() );
    
    if ( Adapter ) {
        
        ((GRAPHIC_UI_FRAME_ADAPTER *) Adapter)->OnLayoutItems( this );
    }
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::Contains( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( GRAPHIC_UI_ELEMENT::Contains( cursor_position ) ) {
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            GRAPHIC_UI_ELEMENT * element = (*it)->Contains( cursor_position );
            
            if( element ) {
                
                return element;
            }
            
            it++;
            
        }
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

void GRAPHIC_UI_FRAME::Render( const GRAPHIC_RENDERER & renderer ) {
    
    if ( IsVisible() ) {
        
        GRAPHIC_SYSTEM::EnableScissor( true );
        
        
        int base_x = GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().X() * 0.5f + (GetPlacement().GetAbsolutePosition().X() - GetPlacement().GetSize().X() * 0.5f );
        int base_y = GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().Y() * 0.5f + (GetPlacement().GetAbsolutePosition().Y() - GetPlacement().GetSize().Y() * 0.5f );
        
        GRAPHIC_SYSTEM::SetScissorRectangle(base_x, base_y, GetPlacement().GetSize().X(), GetPlacement().GetSize().Y());
        
        GRAPHIC_UI_ELEMENT::Render( renderer );
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Render( renderer );
            
            it++;
        }
        
        GRAPHIC_SYSTEM::EnableScissor( false );
    }
}

void GRAPHIC_UI_FRAME::Click( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( Contains( cursor_position ) ) {
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            GRAPHIC_UI_ELEMENT * element = (*it)->Contains( cursor_position );
            
            if( element != NULL && element->IsEnabled() && element->IsVisible() ) {
                
                if ( element->GetCurrentState() != GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
                    
                    element->Click( cursor_position );
                }
                
                return;
            }
            
            it++;
            
        }
        
        ActionCallback( this, CurrentState );
    }
}

void GRAPHIC_UI_FRAME::Hover( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( GRAPHIC_UI_ELEMENT::Contains( cursor_position ) ) {
        
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Hover( cursor_position );
            
            it++;
            
        }
        
        ActionCallback( this, CurrentState );
    }
    else {
        std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
        
        while ( it != ElementTable.end() ) {
            
            (*it)->Hover( false );
            
            it++;
            
        }
    }
}

void GRAPHIC_UI_FRAME::Hover( const bool force_hover ) {
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    while ( it != ElementTable.end() ) {
        
        (*it)->Hover( force_hover );
        
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

void GRAPHIC_UI_FRAME::RemoveObject( GRAPHIC_UI_ELEMENT * ) {
    
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

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_FRAME::Copy() {
    
    GRAPHIC_UI_FRAME * otherFrame = new GRAPHIC_UI_FRAME();
    Placement.Copy( otherFrame->Placement );
    
    otherFrame->RenderStyleTable = RenderStyleTable;
    
    //otherFrame->Identifier = Identifier; //Fordidden
    otherFrame->CurrentState = GRAPHIC_UI_ELEMENT_STATE_Default;
    otherFrame->Enabled = Enabled;
    otherFrame->Visible = Visible;
    otherFrame->Adapter = Adapter;
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = ElementTable.begin();
    
    while ( it != ElementTable.end() ) {
        
        auto new_item = (*it)->Copy();
        new_item->GetPlacement().SetParent(&otherFrame->GetPlacement() );
        otherFrame->ElementTable.push_back( new_item );
        
        it++;
    }
    
    return otherFrame;
}
