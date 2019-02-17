//
//  GAMEPLAY_CAMERA.cpp
//  GAME-ENGINE
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

GAMEPLAY_CAMERA::GAMEPLAY_CAMERA( const GAMEPLAY_CAMERA & other ) :
    GAMEPLAY_COMPONENT_ENTITY( this ),
    Camera( other.Camera ) {
    
}

GAMEPLAY_CAMERA::~GAMEPLAY_CAMERA() {
    
}

void GAMEPLAY_CAMERA::Initialize(float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction, const CORE_MATH_VECTOR & up ) {
    
    CORE_MATH_QUATERNION q;
    
    Camera = new GRAPHIC_CAMERA( near_plane, far_plane, width, height, position, direction, up );
    
    GAMEPLAY_COMPONENT_HANDLE handle;
    handle.Create<GAMEPLAY_COMPONENT_POSITION>( GAMEPLAY_COMPONENT_TYPE_Position );
    
    SetCompononent( handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    q.FromVector( direction );
    
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->AddObserver( this );
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->SetPosition( position );
    handle.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->SetOrientation( q );
}

void GAMEPLAY_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction ) {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_component->SetPosition( position );
    
    GetCamera()->UpdateCamera( position, direction );
    
    position_component->SetOrientation( GetCamera()->GetOrientation() );
    
#if DEBUG
    if ( direction.ComputeDotProduct( CORE_MATH_VECTOR::YAxis ) == 0.0f) {
        
        abort();
    }
#endif
}

void GAMEPLAY_CAMERA::NotifyPropertyChanged(GAMEPLAY_COMPONENT_POSITION * position ) {
    
    abort();
    /*
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    CORE_MATH_VECTOR & pos = position_component->GetPosition();
    CORE_MATH_VECTOR & quat = position_component->GetDirection();
    
    GetCamera()->UpdateCamera(pos, quat );*/
}
