//
//  GAMEPLAY_ACTION_BUY_HOUSE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 11/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_ACTION_BUY_HOUSE_hpp
#define GAMEPLAY_ACTION_BUY_HOUSE_hpp

#include "GAMEPLAY_ACTION.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_ACTION_BUY_HOUSE, GAMEPLAY_ACTION )

    GAMEPLAY_ACTION_BUY_HOUSE();
    ~GAMEPLAY_ACTION_BUY_HOUSE();

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_ACTION_BUY_HOUSE, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_Custom_3 )

    virtual void Apply() override;

    SimpleTrickForSerialization()

    int
        CellIndex;

XS_CLASS_END

#endif /* GAMEPLAY_ACTION_BUY_HOUSE_hpp */
