//
//  GAMEPLAY_GAME_CARD.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 27/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME_CARD.h"
#include "GLOBAL_RESOURCES.h"
#include "GAMEPLAY_PLAYER.h"
#include "CORE_MATH.h"

GAMEPLAY_GAME_CARD::GAMEPLAY_GAME_CARD() :
    GAMEPLAY_COMPONENT_ENTITY(),
    Rule( NULL ),
    AnimationTimer( 0.0f ),
    RuleIsApplied( false ), // todo reset
    AnimationStartupPosition() {
    
}

GAMEPLAY_GAME_CARD::~GAMEPLAY_GAME_CARD() {
    
}

void GAMEPLAY_GAME_CARD::Initialize(
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_VECTOR & size,
    const CORE_MATH_QUATERNION & orientation,
    GAMEPLAY_SCENE * scene,
    GRAPHIC_TEXTURE_BLOCK * block ) {
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("CardShader"), CORE_FILESYSTEM_PATH::FindFilePath("UIShaderTextured", "vsh", "OPENGL2"));
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = GLOBAL_RESOURCES::CreateUIPlanShape( shader );
    shader->Initialize( shape->GetShaderBindParameter() );
    shape->SetTextureBlock( block );
    
    GLOBAL_RESOURCES::CreatePlanComponent(
        this,
        shape,
        &shader->GetProgram(),
        position,
        orientation,
        size,
        scene,
        CORE_HELPERS_CALLBACK_1<GAMEPLAY_COMPONENT_ENTITY *>());
    
    RuleIsApplied = false;
}

void GAMEPLAY_GAME_CARD::SetupAnimation() {
    
    auto comp = ((GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
    
    AnimationTimer = 0.0f;
    AnimationStartupPosition = comp->GetPosition();
    AnimationStartupOrientation = comp->GetOrientation();
}

void GAMEPLAY_GAME_CARD::ResetPosition() {
    
    auto comp = ((GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
    
    comp->SetPosition( AnimationStartupPosition );
    comp->SetOrientation( AnimationStartupOrientation );
}

bool GAMEPLAY_GAME_CARD::Update( const float step, GAMEPLAY_PLAYER * player ) {
    
    auto comp = ((GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
    
    const CORE_MATH_VECTOR animation_destination( 5.0f, 5.0f, -10.0f, 0.0f );
    const CORE_MATH_QUATERNION  animation_orientation( 1.0f, 1.0f, 0.0f, 0.0f );
    
    AnimationTimer = fminf(1.75f, AnimationTimer + step);
    float percentage = AnimationTimer / 1.75f;
    
    comp->SetPosition( CORE_MATH_GetLerpInterpolation( AnimationStartupPosition, animation_destination, percentage ) );
    comp->SetOrientation( CORE_MATH_GetLerpInterpolation( AnimationStartupOrientation, animation_orientation, percentage ) );
    
    return percentage == 1.0f;
}

bool GAMEPLAY_GAME_CARD::ApplyRule(GAMEPLAY_PLAYER * player) {
    
    if( !RuleIsApplied ) {
        
        RuleIsApplied = true;
        return Rule->Apply( NULL, player );
    }
    
    return false;
}
