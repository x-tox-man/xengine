//
//  R3D_GAMEPLAY_SYSTEM_PLAYERS.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 23/05/2019.
//  Copyright © 2019 IGZ. All rights reserved.
//

#include "R3D_GAMEPLAY_SYSTEM_PLAYERS.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_HELPER.h"
#include "R3D_PLAYER.h"
#include "RUN3D_APPLICATION.h"

R3D_GAMEPLAY_SYSTEM_PLAYERS::R3D_GAMEPLAY_SYSTEM_PLAYERS() {
    
}

R3D_GAMEPLAY_SYSTEM_PLAYERS::~R3D_GAMEPLAY_SYSTEM_PLAYERS() {
    
}

void R3D_GAMEPLAY_SYSTEM_PLAYERS::Initialize() {
    
}

void R3D_GAMEPLAY_SYSTEM_PLAYERS::Update( void * ecs_base_pointer, float time_step ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((uint8_t*) ecs_base_pointer) + it->GetOffset());
        GAMEPLAY_COMPONENT_ANIMATION * animation = entity->GetComponentAnimation();
        
        CORE_MATH_VECTOR
            elevation,
            normal,
            velocity,
            x( 0.0f, 0.0f, 1.0f, 0.0f ),
            dir;
        CORE_MATH_QUATERNION
            orientation,
            qr,
            qrtot;
        CORE_MATH_MATRIX
            mm;
        static float
            previous_rotation = 0.0f,
            previous_thrust = 0.0f;
        
        auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
        auto player = (R3D_PLAYER_SHIP::PTR) entity->GetComponent( R3D_GAMEPLAY_COMPONENT_TYPE_PlayerShip );
        
        GAMEPLAY_HELPER::GetElevation( entity, elevation, normal );
        
        velocity = phys->GetVelocity();
        orientation = pos->GetOrientation();
        
        if ( elevation.GetY() <= 1.0f && normal != CORE_MATH_VECTOR::Zero ) {
            
            velocity.X( 0.0f );
            velocity.Y( 2.f * (1.0f - elevation.GetY() ) );
            velocity.Z( 0.0f );
            
            phys->ApplyForce( velocity );
            entity->SetPosition( pos->GetPosition() + CORE_MATH_VECTOR( 0.0f, fmax( 0.0f, 0.15f - elevation.GetY() ), 0.0f, 0.0f ) );
        }
        
        float
        actual_speed = velocity.ComputeLength();
        
        CORE_MATH_MATRIX
        inv;
        
        orientation.ToMatrix( mm.GetRow( 0 ) );
        mm.GetInverse( inv );
        
        dir = x * inv;
        
        phys->ApplyForce( dir * ( player->GetThrust() * (10.0f - actual_speed ) ) );
        velocity = phys->GetVelocity();
        
        qr.RotateY( player->GetRotation() * time_step );
        
        CORE_MATH_QUATERNION reset_pos = pos->GetOrientation();
        
        reset_pos.RotateZ( previous_rotation * 0.1f );
        reset_pos.RotateX( - previous_thrust * 0.1f );
        
        qrtot = reset_pos * qr;
        qrtot.Normalize();
        
        qr.RotateY( -player->GetRotation() * time_step );
        qr.RotateY( -player->GetRotation() * time_step );
        
        qr.ToMatrix( mm.GetRow( 0 ) );
        
        velocity = velocity * mm;
        phys->SetVelocity( velocity );
        
        qrtot.Normalize();
        entity->SetOrientation( qrtot );
        
        qrtot.RotateX( player->GetThrust() * 0.1f );
        qrtot.RotateZ( -player->GetRotation() * 0.1f );
        
        qrtot.Normalize();
        entity->SetOrientation( qrtot );
        
#if DEBUG
        R3D_APP_PTR->SetFrom( pos->GetPosition() );
        R3D_APP_PTR->SetTo( pos->GetPosition() + velocity * 10.0f);
#endif
        
        //Steam.SetPosition( pos->GetPosition() );
        //Steam.SetVelocity( phys->GetVelocity() );
        
        previous_rotation = player->GetRotation();
        previous_thrust = player->GetThrust();
        
        //Steam.Update( time_step );
        
        if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_P ) ) {
            
            //ship->Fire();
        }

        it++;
    }
}

void R3D_GAMEPLAY_SYSTEM_PLAYERS::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
}

void R3D_GAMEPLAY_SYSTEM_PLAYERS::Finalize() {
    
}
