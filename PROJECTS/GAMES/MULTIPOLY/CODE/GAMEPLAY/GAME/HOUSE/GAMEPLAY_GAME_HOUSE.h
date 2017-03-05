//
//  GAMEPLAY_GAME_HOUSE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 4/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_GAME_HOUSE_hpp
#define GAMEPLAY_GAME_HOUSE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_MATH_QUATERNION.h"
#include "GAMEPLAY_PLAYER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GAMEPLAY_RULE.h"
#include "GLOBAL_RESOURCES.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

class GAMEPLAY_PLAYER;

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_GAME_HOUSE, GAMEPLAY_COMPONENT_ENTITY)

    GAMEPLAY_GAME_HOUSE();
    ~GAMEPLAY_GAME_HOUSE();

    void Initialize(
        const CORE_MATH_VECTOR & position,
        const CORE_MATH_VECTOR & size,
        const CORE_MATH_QUATERNION & orientation,
        GAMEPLAY_SCENE * scene,
        const CORE_HELPERS_COLOR & color );

    void SetupAnimation( const CORE_MATH_VECTOR & destination, const CORE_MATH_QUATERNION & orientation );
    void SetColor(const CORE_HELPERS_COLOR & color) {
        
        Color = color;
        
        auto comp = ((GAMEPLAY_COMPONENT_RENDER * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Render ));
        auto program = comp->GetProgram();
        
        GRAPHIC_OBJECT::PTR object = GLOBAL_RESOURCES::GetInstance().HouseObject;
        
        auto attribute = &program->getShaderAttribute(GRAPHIC_SHADER_PROGRAM::GeometryColor );
        
        attribute->AttributeValue.Value.FloatArray4[0] = color.X();
        attribute->AttributeValue.Value.FloatArray4[1] = color.Y();
        attribute->AttributeValue.Value.FloatArray4[2] = color.Z();
        attribute->AttributeValue.Value.FloatArray4[3] = color.W();
    }

    void Update( const float step );
    void ResetPosition();

private:

    float
        AnimationTimer;
    bool
        ItIsAnimating;
    CORE_HELPERS_COLOR
        Color;
    CORE_MATH_VECTOR
        AnimationStartupPosition,
        AnimationDestinationPosition;
    CORE_MATH_QUATERNION
        AnimationStartupOrientation,
        AnimationDestinationOrientation;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_HOUSE_hpp */
