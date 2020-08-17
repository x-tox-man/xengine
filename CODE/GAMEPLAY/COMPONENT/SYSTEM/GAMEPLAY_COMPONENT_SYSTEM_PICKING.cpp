//
//  GAMEPLAY_COMPONENT_SYSTEM_PICKING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "CORE_MATH_RAY.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_ACTION.h"

#include "CORE_MEMORY.h"

GAMEPLAY_COMPONENT_SYSTEM_PICKING::GAMEPLAY_COMPONENT_SYSTEM_PICKING() :
    Ray(),
    OnPickedCallback() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_PICKING::~GAMEPLAY_COMPONENT_SYSTEM_PICKING() {

    CORE_MEMORY_ObjectSafeDeallocation( OnPickedCallback );
}

void GAMEPLAY_COMPONENT_SYSTEM_PICKING::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_PICKING::Update( void * ecs_base_pointer, float time_step ) {
    
    ComputeRay( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetScreenCoordinates(), *GRAPHIC_RENDERER::GetInstance().GetCamera() );
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) ecs_base_pointer) + it->GetOffset());
        
        GAMEPLAY_COMPONENT_POSITION * position = entity->GetComponent<GAMEPLAY_COMPONENT_POSITION>();
        GAMEPLAY_COMPONENT_PHYSICS * physics = entity->GetComponent<GAMEPLAY_COMPONENT_PHYSICS>();
        
        physics->GetShape().SetHalfDiagonal( CORE_MATH_VECTOR(0.5f,0.5f,0.5f,1.0f) );
        physics->GetShape().SetPosition( position->GetPosition() );
        
        if ( physics->GetShape().GetIntersection( Ray ) && PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonClicked() ) {
            
            GAMEPLAY_COMPONENT_ACTION * action = (( GAMEPLAY_COMPONENT_ENTITY *) (((int*) ecs_base_pointer) + it->GetOffset()))->GetComponent<GAMEPLAY_COMPONENT_ACTION>();
            
            action->operator()( entity );
        }
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_PICKING::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_PICKING::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

/**
 * @link: http://antongerdelan.net/opengl/raycasting.html
 */
void GAMEPLAY_COMPONENT_SYSTEM_PICKING::ComputeRay( const CORE_MATH_VECTOR & origin, const GRAPHIC_CAMERA & camera ) {
    
    CORE_MATH_VECTOR temp( (origin[0] - 0.5f) *4.0f, (origin[1] - 0.5f) * 4.0f, 1.0f, 1.0f);
    CORE_MATH_MATRIX inverse;
    
    camera.GetProjectionMatrix().GetInverse( inverse );
    
    CORE_MATH_VECTOR ray_eye = temp * inverse;

    camera.GetViewMatrix().GetInverse( inverse );
    
    Ray.SetOrigin( camera.GetPosition() * inverse );
    
    CORE_MATH_VECTOR ray_wor = ray_eye * camera.GetViewMatrix();
    
    ray_wor[3] = 0.0f;
    
    ray_wor.Normalize();
    
    Ray.SetDirection( ray_wor );
}
