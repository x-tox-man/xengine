//
//  UI_INGAME.hpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef UI_INGAME_hpp
#define UI_INGAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_UI_PRESENTER.h"
#include "R3D_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( UI_INGAME, R3D_UI_FRAME )

    UI_INGAME();
    ~UI_INGAME();

    virtual void SetSpeed( float speed );
    virtual void SetEllapsedTime( float time );

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;

private:
    static CORE_HELPERS_IDENTIFIER
        SpeedText,
        TimeText,
        FPSText;

XS_CLASS_END

#endif /* UI_INGAME_hpp */
