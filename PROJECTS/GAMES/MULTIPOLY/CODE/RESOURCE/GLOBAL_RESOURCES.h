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
#include "GRAPHIC_TEXTURE_BLOCK.h"

class GLOBAL_RESOURCES {
    
public:
    
    ~GLOBAL_RESOURCES();
    
    XS_DEFINE_UNIQUE( GLOBAL_RESOURCES )
    
    void Initialize();
    
    static GRAPHIC_TEXTURE * CreateTextureFromImagePath(const char * image_path);
    static GRAPHIC_TEXTURE_BLOCK * CreateTextureBlockFromImagePath(const char * image_path);
    
    static GRAPHIC_OBJECT_SHAPE_PLAN * CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect );
    
    GRAPHIC_SHADER_LIGHT
        * DirectionalLight,
        * PointLightOne,
        * PointLightTwo,
        * SpotLightOne,
        * SpotLightTwo;
};

#endif /* RESOURCE_hpp */
