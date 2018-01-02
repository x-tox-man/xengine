//
//  GRAPHIC_UI_HELPER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_HELPER_h
#define GRAPHIC_UI_HELPER_h

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_UI_FRAME.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"

#define ALL_STATES 15

XS_CLASS_BEGIN( GRAPHIC_UI_HELPER )

    GRAPHIC_UI_HELPER();
    ~GRAPHIC_UI_HELPER();

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GRAPHIC_UI_HELPER );

    static GRAPHIC_UI_ELEMENT * CreateElement( const CORE_HELPERS_IDENTIFIER & identifier );
    static GRAPHIC_UI_ELEMENT * CreateElement( const char * identifier );

    static GRAPHIC_UI_FRAME * CreateFrame( const CORE_HELPERS_IDENTIFIER & identifier );
    static GRAPHIC_UI_FRAME * CreateFrame( const char * identifier );

    static void CreateFrameStyleWithBorderAndContentTexture( GRAPHIC_UI_ELEMENT * element, const CORE_HELPERS_IDENTIFIER & content_texture_identifier, const CORE_HELPERS_IDENTIFIER & border_texture_identifier, int state_mask = ALL_STATES );
    static void CreateFrameStyleWithBorderAndContentColor( GRAPHIC_UI_ELEMENT * element, const CORE_HELPERS_COLOR & color, const CORE_HELPERS_IDENTIFIER & border_texture_identifier, int state_mask = ALL_STATES );
    static void CreateElementStyleWithContentTexture( GRAPHIC_UI_ELEMENT * element, const CORE_HELPERS_COLOR & color, const CORE_HELPERS_IDENTIFIER & content_texture_identifier, int state_mask = ALL_STATES );

    static GRAPHIC_UI_ELEMENT * CreateTextElement( const CORE_HELPERS_IDENTIFIER & identifier, const CORE_DATA_UTF8_TEXT & text, int state_mask = ALL_STATES );
    static GRAPHIC_UI_ELEMENT * CreateTextElement( const char * identifier, const CORE_DATA_UTF8_TEXT & text, int state_mask = ALL_STATES );

    static void AddElementToFrame( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_FRAME * frame );

    static GRAPHIC_OBJECT_SHAPE_PLAN
        * DefaultPlanShape;
    static GRAPHIC_TEXTURE_ATLAS
        * TextureAtlas;
    static GRAPHIC_FONT
        * DefaultFont;

private :

    static GRAPHIC_UI_RENDER_STYLE * CreateTextRenderStyle( GRAPHIC_FONT * DefaultFont, GRAPHIC_TEXT *text_shape );

    static void AddStyleToElementWithMask(GRAPHIC_UI_ELEMENT::PTR element, GRAPHIC_UI_RENDER_STYLE::PTR style, int mask ) {
    
        if ( mask & 1 ) {
            
            element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, style );
        }
        
        if ( mask & 2 ) {
            
            element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, style );
        }
        
        if ( mask & 4 ) {
            
            element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, style );
        }
        
        if ( mask & 8 ) {
            
            element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Disabled, style );
        }
    }

XS_CLASS_END

#endif /* GRAPHIC_UI_HELPER_h */
