//
//  R3D_GARAGE_SHIPS_ADAPTER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GARAGE_SHIPS_ADAPTER_hpp
#define R3D_GARAGE_SHIPS_ADAPTER_hpp

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_GARAGE_SHIPS_ADAPTER, GRAPHIC_UI_FRAME_LIST_ADAPTER )

    R3D_GARAGE_SHIPS_ADAPTER( GRAPHIC_UI_FRAME * frame );
    virtual ~R3D_GARAGE_SHIPS_ADAPTER();

    virtual int GetItemsCount() override;
    virtual int GetSpacing() override;
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) override;

private:

    GRAPHIC_UI_ELEMENT::PTR CreateTemplate();

XS_CLASS_END

#endif /* R3D_GARAGE_SHIPS_ADAPTER_hpp */
