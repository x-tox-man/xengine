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
    GAMEPLAY_COMPONENT_ENTITY( this ),
    Camera( NULL ) {
        
}

GAMEPLAY_CAMERA::~GAMEPLAY_CAMERA() {
    
}

void GAMEPLAY_CAMERA::Initialize(float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat) {
    
    Camera = new GRAPHIC_CAMERA( near_plane, far_plane, width, height, position, lookat );
    
    GAMEPLAY_COMPONENT_HANDLE handle;
    handle.Create<GAMEPLAY_COMPONENT_POSITION>( GAMEPLAY_COMPONENT_TYPE_Position );
    
    SetCompononent( handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->AddObserver( this );
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->SetPosition( position );
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->SetOrientation( lookat );
}

void GAMEPLAY_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & rotation_quat ) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPosition( position );
    position_component->SetOrientation( rotation_quat );
}

void GAMEPLAY_CAMERA::NotifyPropertyChanged(GAMEPLAY_COMPONENT_POSITION * position ) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    CORE_MATH_VECTOR & pos = position_component->GetPosition();
    CORE_MATH_QUATERNION & quat = position_component->GetOrientation();
    
    GetCamera()->UpdateCamera(pos, quat );
}
