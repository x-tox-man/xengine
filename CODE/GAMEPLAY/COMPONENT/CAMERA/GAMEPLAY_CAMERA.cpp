//
//  GAMEPLAY_CAMERA.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_CAMERA.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

GAMEPLAY_CAMERA::GAMEPLAY_CAMERA() :
    Entity( NULL ),
    Camera( NULL ) {
        
}

GAMEPLAY_CAMERA::~GAMEPLAY_CAMERA() {
    
}

void GAMEPLAY_CAMERA::Initialize(float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat) {
    
    Entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    Camera = new GRAPHIC_CAMERA( near_plane, far_plane, width, height, position, lookat );
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    Entity->SetCompononent( position_component, GAMEPLAY_COMPONENT_TYPE_Position );
    position_component->InitializeObservable();

    position_component->AddObserver( this );
    
    position_component->SetPosition( position );
    position_component->SetOrientation( lookat );
}

void GAMEPLAY_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & rotation_quat ) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) Entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPosition( position );
    position_component->SetOrientation( rotation_quat );
}

void GAMEPLAY_CAMERA::NotifyPropertyChanged(GAMEPLAY_COMPONENT_POSITION * position ) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) Entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    CORE_MATH_VECTOR & pos = position_component->GetPosition();
    CORE_MATH_QUATERNION & quat = position_component->GetOrientation();
    
    GetCamera()->UpdateCamera(pos, quat );
}
