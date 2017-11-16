//
//  GRAPHIC_UI_RENDER_STYLE_BUILDER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_RENDER_STYLE_BUILDER_hpp
#define GRAPHIC_UI_RENDER_STYLE_BUILDER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_RENDER_STYLE.h"

XS_CLASS_BEGIN( GRAPHIC_UI_RENDER_STYLE_BUILDER )

    static GRAPHIC_UI_RENDER_STYLE_BUILDER & NewStyle();

    /**
     * Texture must be already loaded in the GRAPHIC_TEXTURE cache
     */
    GRAPHIC_UI_RENDER_STYLE_BUILDER & CreateStyle( const CORE_HELPERS_UNIQUE_IDENTIFIER & texture_name, const CORE_HELPERS_COLOR & color = CORE_COLOR_White );
    /**
     * Same but with colors
     */
    GRAPHIC_UI_RENDER_STYLE_BUILDER & CreateStyle( const char * texture_name, const CORE_HELPERS_COLOR & color );
    GRAPHIC_UI_RENDER_STYLE_BUILDER & CreateStyle( const CORE_HELPERS_COLOR & color );
    GRAPHIC_UI_RENDER_STYLE_BUILDER & CreateDecoratingFrameBorder( const CORE_MATH_VECTOR & frame_size, const CORE_HELPERS_UNIQUE_IDENTIFIER & texture_name, const CORE_HELPERS_COLOR & color = CORE_COLOR_White );

    GRAPHIC_UI_RENDER_STYLE * Build();

private:

    GRAPHIC_UI_RENDER_STYLE_BUILDER() {
        
    }

    GRAPHIC_OBJECT_SHAPE * CreateFrameBorder( float height, float width );

    static GRAPHIC_UI_RENDER_STYLE *
        Style;
    static GRAPHIC_UI_RENDER_STYLE_BUILDER
        ThisBuilder;

XS_CLASS_END

#endif /* GRAPHIC_UI_RENDER_STYLE_BUILDER_hpp */
