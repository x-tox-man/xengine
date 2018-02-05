//
//  SELECT_LEVEL_PRESENTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 30/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef SELECT_LEVEL_PRESENTER_hpp
#define SELECT_LEVEL_PRESENTER_hpp

#include "R3D_BASE_PRESENTER.h"
#include "GRAPHIC_UI_GRID_ADAPTER.h"
#include "LEVEL_CELL.h"

XS_CLASS_BEGIN_WITH_ANCESTOR_2( SELECT_LEVEL_PRESENTER, R3D_BASE_PRESENTER, GRAPHIC_UI_GRID_ADAPTER )

    SELECT_LEVEL_PRESENTER( GRAPHIC_UI_FRAME * view );

    virtual void Configure() override;

    void OnLevelSelected( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state );

    virtual int GetItemsCount() override;
    virtual int GetSpacing() override;
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) override;
    virtual void OnBaseIndexChanged( int index ) override;

    virtual GRAPHIC_UI_ELEMENT::PTR CreateItem() override {
        return new LEVEL_CELL;
    }

    std::vector< R3D_GAME_LEVEL_INFO::PTR >
        LevelTable;

XS_CLASS_END

#endif /* SELECT_LEVEL_PRESENTER_hpp */
