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

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_UI_TEXT, GRAPHIC_UI_ELEMENT)

    GRAPHIC_UI_TEXT();
    virtual ~GRAPHIC_UI_TEXT();

    void InitializeText(GRAPHIC_FONT & font, float text_size, const char * text);

private :

    GRAPHIC_TEXT
        Text;

XS_CLASS_END

#endif /* GRAPHIC_UI_TEXT_hpp */
