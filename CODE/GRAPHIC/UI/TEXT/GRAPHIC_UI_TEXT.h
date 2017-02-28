//
//  GRAPHIC_UI_TEXT.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_TEXT_hpp
#define GRAPHIC_UI_TEXT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_FONT.h"
#include "CORE_HELPERS_COLOR.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_UI_TEXT, GRAPHIC_UI_ELEMENT)

    GRAPHIC_UI_TEXT();
    virtual ~GRAPHIC_UI_TEXT();

    virtual void Initialize() override;

    void UpdateText( const char * text );
    void SetText( const char * text ) { Text.SetText( text ); }
    void SetColor( const CORE_HELPERS_COLOR & color ) { Color = color; }
    void SetFont( GRAPHIC_FONT * font ) { Text.SetFont( font ); }
    void SetSize( float text_size ) { Text.SetTextSize( text_size ); }

    virtual GRAPHIC_UI_ELEMENT * Contains( const CORE_MATH_VECTOR & cursor_position ) override;

private :

    GRAPHIC_TEXT
        Text;
    CORE_HELPERS_COLOR
        Color;
    GRAPHIC_UI_RENDER_STYLE
        * RenderStyle;
    CORE_MATH_SHAPE_RECTANGLE
        TextRectangle;

XS_CLASS_END

#endif /* GRAPHIC_UI_TEXT_hpp */
