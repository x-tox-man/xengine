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
    Renderer(),
    Gravity()
#ifdef __BULLET_PHYSICS__
    ,DynamicsWorld()
    #if DEBUG
        ,Debugger()
    #endif
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
        
        DynamicsWorld->setGravity(btVector3(0, 0, Gravity));
    
        #if DEBUG
            Debugger.Initialize();
            Debugger.setDebugMode(btIDebugDraw::DBG_DrawWireframe); // so does this
    
            DynamicsWorld->setDebugDrawer(&Debugger);
            //And finally, I render the debug draw after I render the bullet bodies like this:
        #endif
    
    #endif
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::DebugDrawWorld() {
    
    #ifdef __BULLET_PHYSICS__
        DynamicsWorld->debugDrawWorld();
    #endif
}

/**
 * http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World
 */
void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Update( float time_step ) {
    
    #ifdef __BULLET_PHYSICS__
        btTransform transformation;
        
        DynamicsWorld->stepSimulation(time_step, 0);
    
        std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    
        while (it != EntitiesTable.end() ) {
            
            GAMEPLAY_COMPONENT_PHYSICS * physics = ( GAMEPLAY_COMPONENT_PHYSICS *) (it->second)->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
            
            physics->GetBulletRigidBody()->getMotionState()->getWorldTransform( transformation );
            
            (it->second)->GetEntity()->SetPosition(CORE_MATH_VECTOR(transformation.getOrigin().getX(), transformation.getOrigin().getY(), transformation.getOrigin().getZ(), 1.0f));
            btQuaternion q = transformation.getRotation();
            (it->second)->GetEntity()->SetOrientation( CORE_MATH_QUATERNION( q.getX(), q.getZ(), q.getY(), q.getW() ) );
            
            it++;
        }
    #endif
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Render() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Finalize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::AddEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity, int group, int mask ) {
    
    GAMEPLAY_COMPONENT_SYSTEM::AddEntity( handle, entity );
    
    GAMEPLAY_COMPONENT_PHYSICS * physics = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics);
    
    #ifdef __BULLET_PHYSICS__
        physics->GetBulletRigidBody()->setUserPointer( (void*) entity );
        DynamicsWorld->addRigidBody( physics->GetBulletRigidBody(), group, mask );
    #endif
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::AddStaticEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity, int group, int mask ) {
    
    GAMEPLAY_COMPONENT_PHYSICS * physics = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics);
    
#ifdef __BULLET_PHYSICS__
    physics->GetBulletRigidBody()->setUserPointer( (void*) entity );
    DynamicsWorld->addRigidBody( physics->GetBulletRigidBody(), group, mask );
#endif
}

#ifdef __BULLET_PHYSICS__
    void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::SetCollisionFilter( btOverlapFilterCallback * callback ) {
        
        DynamicsWorld->getPairCache()->setOverlapFilterCallback( callback );
    }
#endif
