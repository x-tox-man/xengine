//
//  ASSET_SCREEN.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef ASSET_SCREEN_hpp
#define ASSET_SCREEN_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(ASSET_SCREEN, GRAPHIC_UI_FRAME)

    ASSET_SCREEN();
    virtual ~ASSET_SCREEN();

    virtual void Initialize() override;

    static GRAPHIC_TEXTURE * CreateTextureFromImagePath(const char * image_path);
    static GRAPHIC_OBJECT_SHAPE_PLAN * CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect );

XS_CLASS_END

#endif /* ASSET_SCREEN_hpp */
