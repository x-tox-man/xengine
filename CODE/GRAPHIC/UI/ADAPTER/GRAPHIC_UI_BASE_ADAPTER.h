//
//  GRAPHIC_UI_BASE_ADAPTER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_BASE_ADAPTER_h
#define GRAPHIC_UI_BASE_ADAPTER_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_DATA_UTF8_TEXT.h"

class GRAPHIC_UI_ELEMENT;
class GRAPHIC_UI_FRAME;

XS_CLASS_BEGIN( GRAPHIC_UI_BASE_ADAPTER )

    GRAPHIC_UI_BASE_ADAPTER();
    virtual ~GRAPHIC_UI_BASE_ADAPTER();

    virtual void OnTextPropertyChanged( GRAPHIC_UI_ELEMENT * element, const CORE_DATA_UTF8_TEXT & text );
    virtual void OnLayoutFrame( GRAPHIC_UI_FRAME * );
    virtual void OnResize( GRAPHIC_UI_ELEMENT * );
    virtual void OnMove( GRAPHIC_UI_ELEMENT * );
    virtual CORE_MATH_VECTOR CalculateFrameContentDimension( GRAPHIC_UI_ELEMENT * );
    virtual void OnDragEnd();
    virtual void OnDragged(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & );
    virtual void OnScrolled(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & );

XS_CLASS_END

#endif /* GRAPHIC_UI_BASE_ADAPTER_h */
