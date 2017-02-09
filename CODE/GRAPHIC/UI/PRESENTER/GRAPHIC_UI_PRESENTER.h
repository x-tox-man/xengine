//
//  GRAPHIC_UI_PRESENTER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_PRESENTER_h
#define GRAPHIC_UI_PRESENTER_h

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "CORE_HELPERS_CALLBACK.h"

XS_CLASS_BEGIN(GRAPHIC_UI_PRESENTER)

    GRAPHIC_UI_PRESENTER();
    virtual ~GRAPHIC_UI_PRESENTER();

    void Initialize( GRAPHIC_UI_FRAME * view ) {
        
        View = view;
        
        Configure();
    }

    virtual void Configure() = 0;

    void BindAction( GRAPHIC_UI_ELEMENT * element, CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE> * callback ) {
        
        element->SetActionCallback( *callback );
        
        CORE_MEMORY_ObjectSafeDeallocation( callback );
    }

protected :

    inline GRAPHIC_UI_FRAME * GetView() { return View; }

private:

    GRAPHIC_UI_FRAME
        * View;

XS_CLASS_END

#endif /* CORE_HELPERS_PRESENTER_h */
