//
//  GRAPHIC_UI_PRESENTER.h
//  GAME-ENGINE
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
    }

    virtual void Configure() = 0;

    void BindAction( GRAPHIC_UI_ELEMENT * element, CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT> & callback ) {
        
        element->SetActionCallback( callback );
    }

    template <typename __CLASS__, void  ( __CLASS__::*CALLBACK_FUNCTION)( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT )>
    void BindAction( GRAPHIC_UI_ELEMENT * element, __CLASS__ * destination ) {
        
        CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT>
            action_callback( &Wrapper2<__CLASS__, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_EVENT, CALLBACK_FUNCTION>, destination);
        
        element->SetActionCallback( action_callback );
    }

protected :

    inline GRAPHIC_UI_FRAME * GetView() { return View; }

private:

    GRAPHIC_UI_FRAME
        * View;

XS_CLASS_END

#endif /* CORE_HELPERS_PRESENTER_h */
