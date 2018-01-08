//
//  UI_GARAGE.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_GARAGE_hpp
#define UI_GARAGE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_UI_PRESENTER.h"
#include "R3D_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_GARAGE, R3D_UI_FRAME )

    UI_GARAGE();

    virtual void Initialize() override;

    static CORE_HELPERS_IDENTIFIER
        Stats;

private:

    void CreateStatsFrame();

XS_CLASS_END

#endif /* UI_GARAGE_hpp */
