//
//  GAMEPLAY_CAMERA.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_CAMERA.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

GAMEPLAY_CAMERA::GAMEPLAY_CAMERA() :
    GAMEPLAY_COMPONENT_ENTITY(),
    Camera( NULL ) {
        
}

GAMEPLAY_CAMERA::~GAMEPLAY_CAMERA() {
    
}

void GAMEPLAY_CAMERA::Initialize(float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    SetCompononent( position_component, GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPosition( position );
    position_component->SetOrientation( lookat );
    
    Camera = new GRAPHIC_CAMERA( near_plane, far_plane, width, height, position, lookat );
}


void GAMEPLAY_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & rotation_quat ) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPosition( position );
    position_component->SetOrientation( rotation_quat );
    
    GetCamera()->UpdateCamera(position, rotation_quat );
}
