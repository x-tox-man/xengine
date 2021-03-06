//
//  GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING_hpp
#define GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT_DEFERRED, GRAPHIC_SHADER_EFFECT )

    GRAPHIC_SHADER_EFFECT_DEFERRED( GRAPHIC_SHADER_EFFECT::PTR effect );
    virtual ~GRAPHIC_SHADER_EFFECT_DEFERRED();

    virtual void Apply( GRAPHIC_RENDERER &, const char * material_name ) override;
    virtual void BindAttributes() override;

    static CORE_HELPERS_IDENTIFIER
        PreviousCameraWorldPositionIdentifier,
        PreviousrojectionIdentifier;
    GRAPHIC_CAMERA::PTR
        PreviousCamera;

XS_CLASS_END

#endif /* GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING_hpp */
