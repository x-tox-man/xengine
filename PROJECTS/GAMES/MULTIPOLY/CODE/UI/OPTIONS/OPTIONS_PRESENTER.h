//
//  OPTIONS_PRESENTER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef OPTIONS_PRESENTER_hpp
#define OPTIONS_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(OPTIONS_PRESENTER, GRAPHIC_UI_PRESENTER)

OPTIONS_PRESENTER();
virtual ~OPTIONS_PRESENTER();

virtual void Configure() override;


XS_CLASS_END

#endif /* OPTIONS_PRESENTER_hpp */
