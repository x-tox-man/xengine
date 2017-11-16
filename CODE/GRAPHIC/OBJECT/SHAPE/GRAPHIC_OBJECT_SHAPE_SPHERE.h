//
//  GRAPHIC_OBJECT_SHAPE_SPHERE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_SPHERE__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_SPHERE__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "GRAPHIC_SYSTEM.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE_SPHERE, GRAPHIC_OBJECT_SHAPE)

    GRAPHIC_OBJECT_SHAPE_SPHERE();
    GRAPHIC_OBJECT_SHAPE_SPHERE( int sphere_rings );
    virtual ~GRAPHIC_OBJECT_SHAPE_SPHERE();

    virtual void InitializeShape() override;

private :

    void computePoint( float * data_pointer, float longi_ratio, float lati_ratio, int point_index );

    int
        SphereRings;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_SPHERE__) */
