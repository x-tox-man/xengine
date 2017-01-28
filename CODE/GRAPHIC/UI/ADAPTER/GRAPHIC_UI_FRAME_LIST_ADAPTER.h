//
//  GRAPHIC_UI_FRAME_LIST_ADAPTER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_FRAME_LIST_ADAPTER_hpp
#define GRAPHIC_UI_FRAME_LIST_ADAPTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_BASE_ADAPTER.h"
#include "GRAPHIC_UI_FRAME_ADAPTER.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_UI_ELEMENT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_FRAME_LIST_ADAPTER, GRAPHIC_UI_FRAME_ADAPTER )

GRAPHIC_UI_FRAME_LIST_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template );

virtual void OnResize( GRAPHIC_UI_ELEMENT * );
virtual void OnLayoutItems( GRAPHIC_UI_FRAME * );
virtual void OnDragged(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & );
virtual void OnScrolled(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & );
virtual void OnCollectionChanged();
protected:

virtual int GetItemsCount() = 0;
virtual int GetSpacing() = 0;
virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) = 0;

private:

int CalculateItemsCount(GRAPHIC_UI_FRAME * );
CORE_MATH_VECTOR CalculateListViewDimension();
void UpdateOffsetAndCheckBounds( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force = false);

GRAPHIC_UI_FRAME
    * Frame;
GRAPHIC_UI_ELEMENT
    * UITemplate;
std::vector<GRAPHIC_UI_ELEMENT *>
    VisibleItemsTable;
int
    VisibleItemsCount,
    Spacing;
CORE_MATH_VECTOR
    TotalScrollOffset,
    CellDimension,
    OverallFrameDimension;

XS_CLASS_END


#endif /* GRAPHIC_UI_FRAME_LIST_ADAPTER_hpp */
