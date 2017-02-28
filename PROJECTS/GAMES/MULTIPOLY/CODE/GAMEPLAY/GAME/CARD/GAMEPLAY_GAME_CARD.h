//
//  GAMEPLAY_GAME_CARD.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 27/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_GAME_CARD_hpp
#define GAMEPLAY_GAME_CARD_hpp

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

class GAMEPLAY_PLAYER;

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_GAME_CARD, GAMEPLAY_COMPONENT_ENTITY)

    GAMEPLAY_GAME_CARD();
    ~GAMEPLAY_GAME_CARD();

    void Initialize(
                    const CORE_MATH_VECTOR & position,
                    const CORE_MATH_VECTOR & size,
                    const CORE_MATH_QUATERNION & orientation,
                    GAMEPLAY_SCENE * scene,
                    GRAPHIC_TEXTURE_BLOCK * block );

    void SetRule( GAMEPLAY_RULE * rule ) { Rule = rule; }
    GAMEPLAY_RULE * GetRule() { return Rule; }

    void SetupAnimation();
    bool Update( const float step, GAMEPLAY_PLAYER * player );
    bool ApplyRule( GAMEPLAY_PLAYER * player );
    void ResetPosition();

private:

    GAMEPLAY_RULE
        * Rule;
    float
        AnimationTimer;
    bool
        RuleIsApplied;
    CORE_MATH_VECTOR
        AnimationStartupPosition;
    CORE_MATH_QUATERNION
        AnimationStartupOrientation;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_CARD_hpp */
