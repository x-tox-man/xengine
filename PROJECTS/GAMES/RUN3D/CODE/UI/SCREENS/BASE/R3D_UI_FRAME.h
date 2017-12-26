//
//  R3D_UI_FRAME.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 2/11/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_UI_FRAME_hpp
#define R3D_UI_FRAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "R3D_BASE_PRESENTER.h"
#include "UI_BASE_BUTTON.h"
#include "TOOLS_LOCALE_SYSTEM.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_UI_FRAME, GRAPHIC_UI_FRAME )

    R3D_UI_FRAME();
    ~R3D_UI_FRAME();

    virtual void Initialize() override;
    virtual void OnViewAppearing() override {
        Presenter->Configure();
    }
    virtual void OnViewDisappearing() override {
        
    }

    inline void SetPresenter( R3D_BASE_PRESENTER::PTR presenter ) { Presenter = presenter; }
    inline R3D_BASE_PRESENTER::PTR GetPresenter() { return Presenter; }
    inline void SetBorderLess() { Borderless = true; }

protected :

    R3D_BASE_PRESENTER::PTR
        Presenter;
    bool
        Borderless;

XS_CLASS_END

#endif /* R3D_UI_FRAME_hpp */
