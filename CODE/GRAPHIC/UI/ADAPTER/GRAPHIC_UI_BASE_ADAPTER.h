//
//  GRAPHIC_UI_BASE_ADAPTER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_BASE_ADAPTER_h
#define GRAPHIC_UI_BASE_ADAPTER_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"

class GRAPHIC_UI_ELEMENT;
class GRAPHIC_UI_FRAME;

XS_CLASS_BEGIN( GRAPHIC_UI_BASE_ADAPTER )

GRAPHIC_UI_BASE_ADAPTER();
virtual ~GRAPHIC_UI_BASE_ADAPTER();

virtual void OnTextPropertyChanged( GRAPHIC_UI_ELEMENT * element, const char * text );
virtual void OnLayoutItems( GRAPHIC_UI_FRAME * );
virtual void OnResize( GRAPHIC_UI_ELEMENT * );
virtual void OnMove( GRAPHIC_UI_ELEMENT * );

XS_CLASS_END

#endif /* GRAPHIC_UI_BASE_ADAPTER_h */
