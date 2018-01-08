//
//  GRAPHIC_UI_FRAM_SCROLLVIEW_ADAPTER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_FRAM_SCROLLVIEW_ADAPTER_hpp
#define GRAPHIC_UI_FRAM_SCROLLVIEW_ADAPTER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_BASE_ADAPTER.h"
#include "GRAPHIC_UI_FRAME_ADAPTER.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_UI_ELEMENT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER, GRAPHIC_UI_FRAME_ADAPTER )

    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER();
    virtual ~GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER();

    virtual void OnResize( GRAPHIC_UI_ELEMENT * ) override;
    virtual void OnLayoutFrame( GRAPHIC_UI_FRAME * ) override;
    virtual void OnDragged(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & ) override;
    virtual void OnScrolled(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & ) override;

    virtual void UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force);
    virtual void OnDragEnd() override;

    inline void SetHorizontal() { Horizontal = true; }
    inline void SetVerticlal() { Horizontal = false; }
    inline bool IsHorizontal() const { return Horizontal; }

protected:

    const CORE_MATH_VECTOR & GetScrollZone() const { return ScrollZone;}
    const CORE_MATH_VECTOR & GetTotalScrollOffset() const { return TotalScrollOffset;}
    const CORE_MATH_VECTOR & GetOverallFrameDimension() const { return OverallFrameDimension;}

    inline CORE_MATH_VECTOR & GetTotalScrollOffset() { return TotalScrollOffset;}
    inline void SetTotalOffset( CORE_MATH_VECTOR & offset ) { TotalScrollOffset = offset; }


private:

    CORE_MATH_VECTOR
        TotalScrollOffset,
        ScrollZone,
        OverallFrameDimension,
        DragOffset;
    bool
        Horizontal;

XS_CLASS_END

#endif /* GRAPHIC_UI_FRAM_SCROLLVIEW_ADAPTER_hpp */
