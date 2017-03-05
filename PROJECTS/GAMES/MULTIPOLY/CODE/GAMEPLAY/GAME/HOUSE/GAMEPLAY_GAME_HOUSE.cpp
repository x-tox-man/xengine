//
//  GAMEPLAY_GAME_HOUSE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 4/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME_HOUSE.h"
#include "GLOBAL_RESOURCES.h"
#include "CORE_MATH.h"

GAMEPLAY_GAME_HOUSE::GAMEPLAY_GAME_HOUSE() :
    AnimationTimer( 0.0f ),
    ItIsAnimating( false ),
    Color(),
    AnimationStartupPosition(),
    AnimationDestinationPosition(),
    AnimationStartupOrientation(),
    AnimationDestinationOrientation() {
    
}

GAMEPLAY_GAME_HOUSE::~GAMEPLAY_GAME_HOUSE() {
    
}

void GAMEPLAY_GAME_HOUSE::Initialize(
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_VECTOR & size,
    const CORE_MATH_QUATERNION & orientation,
    GAMEPLAY_SCENE * scene,
    const CORE_HELPERS_COLOR & color ) {
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("HouseShader"), CORE_FILESYSTEM_PATH::FindFilePath("BasicGeometryShader", "vsh", "OPENGL2"));
    
    GRAPHIC_OBJECT::PTR object = GLOBAL_RESOURCES::GetInstance().HouseObject;
    shader->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    
    GLOBAL_RESOURCES::CreateOtherObjectComponent(this, object, &shader->GetProgram(), position, CORE_MATH_QUATERNION(), CORE_MATH_VECTOR(0.2f, 0.2f, 0.0f, 1.0f ), scene );
    
    SetColor( color );
}

void GAMEPLAY_GAME_HOUSE::SetupAnimation( const CORE_MATH_VECTOR & destination, const CORE_MATH_QUATERNION & orientation ) {
    
    auto comp = ((GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
    
    AnimationStartupPosition = comp->GetPosition();
    AnimationStartupOrientation = comp->GetOrientation();
    AnimationDestinationPosition = destination;
    AnimationDestinationOrientation = orientation;
    
    ItIsAnimating = true;
}

void GAMEPLAY_GAME_HOUSE::Update( const float step ) {
    
    if ( ItIsAnimating ) {
        
        AnimationTimer += step;
        
        auto comp = ((GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ));
        
        AnimationTimer = fminf(1.75f, AnimationTimer + step);
        float percentage = AnimationTimer / 1.75f;
        
        if ( percentage == 1.0f ) {
            
            ItIsAnimating = false;
        }
        
        CORE_MATH_VECTOR pos = CORE_MATH_GetLerpInterpolation( AnimationStartupPosition, AnimationDestinationPosition, percentage );
        
        pos.Z( sinf( percentage * M_PI ) );
        
        comp->SetPosition( pos );
        comp->SetOrientation( CORE_MATH_GetLerpInterpolation( AnimationStartupOrientation, AnimationDestinationOrientation, percentage ) );
    }
}

void GAMEPLAY_GAME_HOUSE::ResetPosition() {

}
