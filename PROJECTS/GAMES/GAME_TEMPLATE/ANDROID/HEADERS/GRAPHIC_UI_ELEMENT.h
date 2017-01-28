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

XS_CLASS_BEGIN( GRAPHIC_UI_ELEMENT )

GRAPHIC_UI_ELEMENT();

virtual void Update( const float );
virtual void Render( const GRAPHIC_RENDERER & );
virtual void Click( const CORE_MATH_VECTOR & cursor_position );

virtual GRAPHIC_UI_ELEMENT * Contains( const CORE_MATH_VECTOR & cursor_position );
virtual GRAPHIC_UI_ELEMENT * GetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & );

inline const CORE_MATH_VECTOR & GetPosition() const { return Placement.GetPosition(); }
inline const CORE_MATH_VECTOR & GetSize() const { return Placement.GetSize(); }
inline const GRAPHIC_UI_PLACEMENT & GetPlacement() const { return Placement; }
inline GRAPHIC_UI_PLACEMENT & GetPlacement() { return Placement; }

inline bool IsEnabled() const { return Enabled; }
inline bool IsVisible() const { return Visible; }

inline void Enable() { Enabled = true; }
inline void Disable() { Enabled = false; }

inline void SetEnabled( const bool enabled ) { Enabled = enabled; }

inline void Show() { Visible = true; }
inline void Hide() { Visible = false; }

inline void SetVisible( const bool visible ) { Visible = visible; }
inline void SetActionCallback( CORE_HELPER_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > & action_callback ) { ActionCallback = action_callback; }

inline const GRAPHIC_UI_RENDER_STYLE * GetRenderStyleForState( const GRAPHIC_UI_ELEMENT_STATE state ) const { return RenderStyleTable[ state ]; }
inline GRAPHIC_UI_RENDER_STYLE * GetRenderStyleForState( const GRAPHIC_UI_ELEMENT_STATE state ) { return RenderStyleTable[ state ]; }
inline void SetRenderStyleForState( const GRAPHIC_UI_ELEMENT_STATE state, GRAPHIC_UI_RENDER_STYLE * style ) { RenderStyleTable[ state ] = style; }

protected:

GRAPHIC_UI_PLACEMENT
    Placement;
CORE_HELPER_CALLBACK_2< GRAPHIC_UI_ELEMENT * , GRAPHIC_UI_ELEMENT_STATE >
    ActionCallback;
CORE_HELPERS_IDENTIFIER
    Identifier;
GRAPHIC_UI_ELEMENT_STATE
    CurrentState;
std::array< GRAPHIC_UI_RENDER_STYLE *, GRAPHIC_UI_ELEMENT_STATE_Count >
    RenderStyleTable;
bool
    Enabled,
    Visible;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_ELEMENT__) */
