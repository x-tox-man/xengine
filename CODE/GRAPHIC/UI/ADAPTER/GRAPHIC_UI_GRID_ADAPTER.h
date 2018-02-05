//
//  GRAPHIC_UI_GRID_ADAPTER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/01/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_GRID_ADAPTER_hpp
#define GRAPHIC_UI_GRID_ADAPTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_BASE_ADAPTER.h"
#include "GRAPHIC_UI_FRAME_ADAPTER.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_GRID_ADAPTER, GRAPHIC_UI_FRAME_LIST_ADAPTER )

    GRAPHIC_UI_GRID_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template );
    virtual ~GRAPHIC_UI_GRID_ADAPTER();

    virtual void UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force) override;
    virtual int CalculateVisibleItemsCount(GRAPHIC_UI_FRAME * ) override;

private:

    void ComputeLineItemCount();

    int
        LineItemCount;

XS_CLASS_END

#endif /* GRAPHIC_UI_GRID_ADAPTER_hpp */
