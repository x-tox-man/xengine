//
//  GRAPHIC_UI_FRAME_ADAPTER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_FRAME_ADAPTER_hpp
#define GRAPHIC_UI_FRAME_ADAPTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_BASE_ADAPTER.h"

class GRAPHIC_UI_FRAME;

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_FRAME_ADAPTER, GRAPHIC_UI_BASE_ADAPTER )

GRAPHIC_UI_FRAME_ADAPTER();

virtual void OnLayoutItems( GRAPHIC_UI_FRAME * );
virtual void OnResize( GRAPHIC_UI_ELEMENT * );
virtual void OnMove( GRAPHIC_UI_ELEMENT * );
virtual void OnDragged(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & );
virtual void OnScrolled(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & );

XS_CLASS_END

#endif /* GRAPHIC_UI_FRAME_ADAPTER_hpp */
