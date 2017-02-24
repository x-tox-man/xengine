//
//  SPLASH.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef SPLASH_hpp
#define SPLASH_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_UI_TEXT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( SPLASH, GRAPHIC_UI_FRAME )

SPLASH();
virtual ~SPLASH();

virtual void Initialize() override;
virtual void Update( const float ) override;

private:

float
    AccumulatedTime;

XS_CLASS_END

#endif /* SPLASH_hpp */
