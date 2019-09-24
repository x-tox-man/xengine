//
//  GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP_hpp
#define GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP_hpp

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GAMEPLAY_COMPONENT_PARTICLE_SYSTEM.h"
#include "CORE_MATH.h"

#define MAX_NUM_CASCADES        3
#define NUM_FRUSTUM_CORNERS 8

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP, GRAPHIC_RENDERER_TECHNIQUE )

    struct CASCADE_PROJECTION_INFO {
        float
        Left,
        Right,
        Top,
        Bottom,
        Far,
        Near;
    };

    GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    void UpdateCameras( const CORE_MATH_VECTOR & position , const CORE_MATH_VECTOR & direction, const CORE_MATH_VECTOR & up );

    void CalculateCascadeOrthoProjection( GRAPHIC_RENDERER & renderer );

    void DebugFustrum( GRAPHIC_RENDERER & renderer );

    GRAPHIC_CAMERA::PTR
        Camera;
    CASCADE_PROJECTION_INFO
        CascadeProjectionInfo[ MAX_NUM_CASCADES ];
    GRAPHIC_CAMERA_ORTHOGONAL
        * LightShadowCamera[ MAX_NUM_CASCADES ];
    int
        CascadeCount;
    GRAPHIC_RENDER_TARGET::PTR
        PrimaryRenderTarget,
        ShadowMapRenderTarget1,
        ShadowMapRenderTarget2,
        ShadowMapRenderTarget3;
XS_CLASS_END


#endif /* GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP_hpp */
