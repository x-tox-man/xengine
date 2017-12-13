//
//  UI_BASE_BUTTON.hpp
//  Run3d
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_BASE_BUTTON_hpp
#define UI_BASE_BUTTON_hpp

#include "GRAPHIC_UI_FRAME.h"
#include "TOOLS_LOCALE_STRING.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_BASE_BUTTON, GRAPHIC_UI_FRAME )

    UI_BASE_BUTTON();

    virtual void Initialize() override;
    void SetTitle( const TOOLS_LOCALE_STRING & title );

private:

    TOOLS_LOCALE_STRING
        Title;

XS_CLASS_END

#endif /* UI_BASE_BUTTON_hpp */
