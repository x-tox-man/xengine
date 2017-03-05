//
//  RESOURCE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef RESOURCE_hpp
#define RESOURCE_hpp

#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_OBJECT_SHAPE_FRAME.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_TEXTURE.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"

class GLOBAL_RESOURCES {
    
public:
    
    ~GLOBAL_RESOURCES();
    
    XS_DEFINE_UNIQUE( GLOBAL_RESOURCES )
    
    void Initialize();
    void Finalize();
    
    static GRAPHIC_TEXTURE * CreateTextureFromImagePath(const char * image_path);
    static GRAPHIC_TEXTURE_BLOCK * CreateTextureBlockFromImagePath(const char * image_path);
    
    static GRAPHIC_OBJECT_SHAPE_PLAN * CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect );
    
    static GRAPHIC_OBJECT_SHAPE_FRAME * CreateFrameBorder( float height, float width, GRAPHIC_SHADER_EFFECT::PTR shader );
    
    static GAMEPLAY_COMPONENT_ENTITY * CreatePlanComponent(
        GAMEPLAY_COMPONENT_ENTITY * in_component,
        GRAPHIC_OBJECT_SHAPE_PLAN::PTR object,
        GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
        const CORE_MATH_VECTOR & position,
        const CORE_MATH_QUATERNION & orientation,
        const CORE_MATH_VECTOR & size,
        GAMEPLAY_SCENE * scene,
        const CORE_HELPERS_CALLBACK_1<GAMEPLAY_COMPONENT_ENTITY *> & callback,
        bool picking = false );
    
    static GAMEPLAY_COMPONENT_ENTITY * CreateOtherObjectComponent(
        GAMEPLAY_COMPONENT_ENTITY * in_component,
        GRAPHIC_OBJECT::PTR object,
        GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
        const CORE_MATH_VECTOR & position,
        const CORE_MATH_QUATERNION & orientation,
        const CORE_MATH_VECTOR & size,
        GAMEPLAY_SCENE * scene );
    
    GRAPHIC_SHADER_LIGHT
        * DirectionalLight,
        * PointLightOne,
        * PointLightTwo,
        * SpotLightOne,
        * SpotLightTwo;
    GRAPHIC_OBJECT
        * HouseObject;
    GRAPHIC_OBJECT_SHAPE_LINE
        * Line;
};

#endif /* RESOURCE_hpp */
