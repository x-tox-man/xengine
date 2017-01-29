//
//  GAMEPLAY_COMPONENT_RENDER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_HELPERS_SCALAR.h"
#include "GRAPHIC_OBJECT.h"
#include "CORE_MATH_SHAPE.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_RENDER();
    virtual ~GAMEPLAY_COMPONENT_RENDER();

    void * operator new(size_t size);

    CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Render)

    void Render( GRAPHIC_RENDERER &renderer, GAMEPLAY_COMPONENT_POSITION * component );

    struct INTERNAL_ARRAY{
        int LastIndex;
        GAMEPLAY_COMPONENT_RENDER * MemoryArray;
    };

    void SetObject( GRAPHIC_OBJECT * object ) { Object = object; }
    GRAPHIC_OBJECT * GetObject() { return Object; }

private :

    static std::vector< INTERNAL_ARRAY > InternalVector;

    GRAPHIC_OBJECT
        * Object;
    CORE_MATH_SHAPE
        * BoundingObject;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__) */
