//
//  GAMEPLAY_CAMERA.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_CAMERA.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

GAMEPLAY_COMPONENT_CAMERA::GAMEPLAY_COMPONENT_CAMERA() :
    Camera() {
        
}

GAMEPLAY_COMPONENT_CAMERA::GAMEPLAY_COMPONENT_CAMERA( const GAMEPLAY_COMPONENT_CAMERA & other ) :
    Camera() {
    
    CORE_RUNTIME_Abort();
}

GAMEPLAY_COMPONENT_CAMERA::~GAMEPLAY_COMPONENT_CAMERA() {
    
}

void GAMEPLAY_COMPONENT_CAMERA::Initialize(float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction, const CORE_MATH_VECTOR & up ) {
    
    CORE_MATH_QUATERNION q;
    
    Camera.Reset( near_plane, far_plane, width, height, position, direction, up );
    
    //TODO: 
    /*handle.Create<GAMEPLAY_COMPONENT_POSITION>( GAMEPLAY_COMPONENT_TYPE_Position );
    
    SetCompononent( handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    q.FromVector( direction );
    
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->AddObserver( this );
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->SetPosition( position );
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->SetOrientation( q );*/
}

void GAMEPLAY_COMPONENT_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction ) {
    
    CORE_RUNTIME_Abort();
    /*auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPosition( position );
    
    Camera.UpdateCamera( position, direction );
    
    position_component->SetOrientation( Camera.GetOrientation() );
    
#if DEBUG
    if ( direction.ComputeDotProduct( CORE_MATH_VECTOR::YAxis ) == 0.0f) {
        
        CORE_RUNTIME_Abort();
    }
#endif*/
}

int GAMEPLAY_COMPONENT_CAMERA::ComponentType = GAMEPLAY_COMPONENT_TYPE_Camera;
