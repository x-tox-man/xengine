//
//  GRAPHIC_UI_ELEMENT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_UI_ELEMENT__
#define __GAME_ENGINE_REBORN__GRAPHIC_UI_ELEMENT__

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_UI_RENDER_STYLE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_UI_PLACEMENT.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "GRAPHIC_UI_ELEMENT_SCRIPTED.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "GRAPHIC_UI_BASE_ADAPTER.h"

XS_CLASS_BEGIN( GRAPHIC_UI_ELEMENT )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GRAPHIC_UI_ELEMENT );

    GRAPHIC_UI_ELEMENT();
    GRAPHIC_UI_ELEMENT(const CORE_HELPERS_IDENTIFIER &);
    virtual ~GRAPHIC_UI_ELEMENT();

    virtual void Initialize() {}
    virtual void Finalize() {}

    virtual void Update( const float );
    virtual void Render( GRAPHIC_RENDERER & );
    virtual void Click( const CORE_MATH_VECTOR & cursor_position );
    virtual void Hover( const CORE_MATH_VECTOR & cursor_position );
    virtual void Hover( const bool force_hover );

    virtual int GetChildCount() { return -1; }

    virtual GRAPHIC_UI_ELEMENT * Contains( const CORE_MATH_VECTOR & cursor_position );
    virtual GRAPHIC_UI_ELEMENT * GetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & );

    inline CORE_MATH_VECTOR & GetPosition() { return Placement.GetAbsolutePosition(); }
    inline CORE_MATH_VECTOR & GetSize() { return Placement.GetSize(); }

    inline const CORE_MATH_VECTOR & GetPosition() const { return Placement.GetAbsolutePosition(); }
    inline const CORE_MATH_VECTOR & GetSize() const { return Placement.GetSize(); }
    inline const GRAPHIC_UI_PLACEMENT & GetPlacement() const { return Placement; }
    inline const GRAPHIC_UI_ELEMENT_SCRIPTED & GetAnimation() const { return Animation; }
    inline const CORE_HELPERS_IDENTIFIER & GetIdentifier() { return Identifier; }

    inline GRAPHIC_UI_PLACEMENT & GetPlacement() { return Placement; }
    inline GRAPHIC_UI_ELEMENT_SCRIPTED & GetAnimation() { return Animation; }

    inline void SetPosition( const CORE_MATH_VECTOR & position ) { Placement.SetRelativePosition( position );OnPlacementPropertyChanged(); }

    inline bool IsEnabled() const { return Enabled; }
    inline bool IsVisible() const { return Visible; }

    inline void Enable() { Enabled = true; }
    inline void Disable() { Enabled = false; }

    inline void SetEnabled( const bool enabled ) { Enabled = enabled; }

    inline void Show() { Visible = true; }
    inline void Hide() { Visible = false; }

    inline void SetVisible( bool visible ) { Visible = visible; }
    void SetActionCallback( CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > & action_callback );
    CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT * , GRAPHIC_UI_ELEMENT_STATE > & GetActionCallback() { return ActionCallback; }

    inline GRAPHIC_UI_ELEMENT_STATE GetCurrentState() const { return CurrentState; }

    inline const GRAPHIC_UI_RENDER_STYLE * GetRenderStyleForState( const GRAPHIC_UI_ELEMENT_STATE state ) const { return RenderStyleTable[ state ]; }
    inline GRAPHIC_UI_RENDER_STYLE * GetRenderStyleForState( const GRAPHIC_UI_ELEMENT_STATE state ) { return RenderStyleTable[ state ]; }
    inline void SetRenderStyleForState( const GRAPHIC_UI_ELEMENT_STATE state, GRAPHIC_UI_RENDER_STYLE * style ) { RenderStyleTable[ state ] = style; }
    inline const void SetIdentifier( const CORE_HELPERS_IDENTIFIER & other) { Identifier = other; }

    virtual void OnPlacementPropertyChanged() {};

    inline void SetTextValue( const char * text) {
        
        Adapter->OnTextPropertyChanged( this, text );
    }

    inline void SetAdapter( GRAPHIC_UI_BASE_ADAPTER * adapter ) {
        
        Adapter = adapter;
    }

    virtual GRAPHIC_UI_ELEMENT * Copy();

    virtual void SetOpacity( float opacity ) { Opacity = opacity; }

    friend class GRAPHIC_UI_PRESENTER;

protected:

    GRAPHIC_UI_PLACEMENT
        Placement;
    CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT * , GRAPHIC_UI_ELEMENT_STATE >
        ActionCallback;
    CORE_HELPERS_CALLBACK_1< const char * >
        OnTextChangedCallback;
    CORE_HELPERS_IDENTIFIER
        Identifier;
    GRAPHIC_UI_ELEMENT_STATE
        CurrentState;
    GRAPHIC_UI_ELEMENT_SCRIPTED
        Animation;
    std::array< GRAPHIC_UI_RENDER_STYLE *, GRAPHIC_UI_ELEMENT_STATE_Count >
        RenderStyleTable;
    GRAPHIC_UI_BASE_ADAPTER
        * Adapter;
    bool
        Enabled,
        Visible;
    float
        Opacity;
XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_ELEMENT__) */
