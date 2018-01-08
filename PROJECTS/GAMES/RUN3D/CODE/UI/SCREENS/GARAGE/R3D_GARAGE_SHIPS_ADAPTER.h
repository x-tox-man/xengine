//
//  R3D_GARAGE_SHIPS_ADAPTER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GARAGE_SHIPS_ADAPTER_hpp
#define R3D_GARAGE_SHIPS_ADAPTER_hpp

#include "GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER.h"
#include "UI_GARAGE_SHIP_CELL.h"
#include "R3D_PLAYER_SHIP_MODEL.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_GARAGE_SHIPS_ADAPTER, GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER )

    R3D_GARAGE_SHIPS_ADAPTER( GRAPHIC_UI_FRAME * frame );
    virtual ~R3D_GARAGE_SHIPS_ADAPTER();

    virtual int GetItemsCount() override;
    virtual int GetSpacing() override;
    virtual void ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) override;
    virtual void OnBaseIndexChanged( int index ) override;

    virtual GRAPHIC_UI_ELEMENT::PTR CreateItem() override {
        return new UI_GARAGE_SHIP_CELL;
    }

    inline void SetPlayerShips( std::vector< R3D_PLAYER_SHIP_MODEL::PTR > * ships ) { PlayerShips = ships; OnCollectionChanged(); }

private:

    GRAPHIC_UI_ELEMENT::PTR CreateTemplate();

    std::vector< R3D_PLAYER_SHIP_MODEL::PTR >
        * PlayerShips;

XS_CLASS_END

#endif /* R3D_GARAGE_SHIPS_ADAPTER_hpp */
