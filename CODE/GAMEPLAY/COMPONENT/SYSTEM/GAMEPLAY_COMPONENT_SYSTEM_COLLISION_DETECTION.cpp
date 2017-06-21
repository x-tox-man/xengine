//
//  GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION() :
GAMEPLAY_COMPONENT_SYSTEM(),
Renderer()
#ifdef __BULLET_PHYSICS__
    ,DynamicsWorld()
#endif
{
    
}

GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::~GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION() {

}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Initialize() {
    
    #ifdef __BULLET_PHYSICS__
        btBroadphaseInterface* broadphase = new btDbvtBroadphase();
        
        // Set up the collision configuration and dispatcher
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
        
        // The actual physics solver
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        
        // The world.
        DynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
        
        DynamicsWorld->setGravity(btVector3(0, -10, 0));
    #endif
}

/**
 * http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World
 */
void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Update( float time_step ) {
    
    #ifdef __BULLET_PHYSICS__
        btTransform transformation;
        
        DynamicsWorld->stepSimulation(time_step, 10);
        
        for (int i = 0; i < EntitiesVector.size(); i++) {
            
            GAMEPLAY_COMPONENT_PHYSICS * physics = ( GAMEPLAY_COMPONENT_PHYSICS *) EntitiesVector[i]->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
            GAMEPLAY_COMPONENT_POSITION * position = ( GAMEPLAY_COMPONENT_POSITION *) EntitiesVector[i]->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
            
            physics->GetBulletRigidBody()->getMotionState()->getWorldTransform( transformation );
            
            position->SetPosition(CORE_MATH_VECTOR(transformation.getOrigin().getX(), transformation.getOrigin().getY(), transformation.getOrigin().getZ(), 1.0f));
        }
    #endif
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Render() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Finalize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::AddEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    GAMEPLAY_COMPONENT_SYSTEM::AddEntity( handle, entity );
    
    //GAMEPLAY_COMPONENT_PHYSICS * physics = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics);
    
    #ifdef __BULLET_PHYSICS__
        DynamicsWorld->addRigidBody( physics->GetBulletRigidBody() );
    #endif
}
