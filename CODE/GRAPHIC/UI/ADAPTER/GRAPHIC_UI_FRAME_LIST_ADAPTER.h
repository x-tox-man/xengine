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
#include "GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_FRAME_LIST_ADAPTER, GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER )

    GRAPHIC_UI_FRAME_LIST_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template );
    virtual ~GRAPHIC_UI_FRAME_LIST_ADAPTER();

    virtual void OnResize( GRAPHIC_UI_ELEMENT * ) override;
    virtual void OnLayoutFrame( GRAPHIC_UI_FRAME * ) override;
    virtual void OnDragged(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & ) override;
    virtual void OnScrolled(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & ) override;
    virtual void OnCollectionChanged();
    virtual void OnDragEnd() override;

protected:

    virtual int GetItemsCount() = 0;
    virtual int GetSpacing() = 0;
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) = 0;

private:

    int CalculateVisibleItemsCount(GRAPHIC_UI_FRAME * );
    virtual CORE_MATH_VECTOR CalculateFrameDimension( GRAPHIC_UI_ELEMENT * ) override;
    void UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force = false) override;

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
        CellDimension;

XS_CLASS_END


#endif /* GRAPHIC_UI_FRAME_LIST_ADAPTER_hpp */
