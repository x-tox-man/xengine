//
//  UI_GARAGE_SHIP_CELL.hpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_GARAGE_SHIP_CELL_hpp
#define UI_GARAGE_SHIP_CELL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_CAMERA.h"
#include "R3D_PLAYER_SHIP_MODEL.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_GARAGE_SHIP_CELL, GRAPHIC_UI_FRAME )

    UI_GARAGE_SHIP_CELL();
    virtual ~UI_GARAGE_SHIP_CELL();

    virtual void Initialize() override;
    void Update(const float time_step ) override;
    void Render( GRAPHIC_RENDERER & renderer )override;
    virtual GRAPHIC_UI_ELEMENT * Copy() override;

private:

    GRAPHIC_CAMERA
        Camera;
    float
        Accumulated;
    R3D_PLAYER_SHIP_MODEL::PTR
        ShipModel;

XS_CLASS_END

#endif /* UI_GARAGE_SHIP_CELL_hpp */
