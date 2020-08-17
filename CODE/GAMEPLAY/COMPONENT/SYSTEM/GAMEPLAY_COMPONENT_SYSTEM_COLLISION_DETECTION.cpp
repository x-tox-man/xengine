//
//  GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.cpp
//  GAME-ENGINE
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
    Gravity(),
    HasNearCallback( false )
#ifdef __BULLET_PHYSICS__
    ,DynamicsWorld( NULL )
    ,NearCallback( NULL )
    #if DEBUG  && !defined(PLATFORM_WINDOWS)
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

        //collisionConfiguration->setPlaneConvexMultipointIterations();
        btCollisionDispatcher * dispatcher = new btCollisionDispatcher(collisionConfiguration);
    
        if ( HasNearCallback ) {
            
            dispatcher->setNearCallback( NearCallback );
        }
        
        // The actual physics solver
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        
        // The world.
        DynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
        
        DynamicsWorld->setGravity(btVector3(Gravity.X(), Gravity.Y(), Gravity.Z() ) );
    
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
void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Update( void * ecs_base_pointer, float time_step ) {
    
    #ifdef __BULLET_PHYSICS__
        btTransform transformation;
        
        DynamicsWorld->stepSimulation( time_step, 10 );
    
        std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
        while (it != EntitiesTable.end() ) {
            
            auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) ecs_base_pointer) + it->GetOffset());
            
            GAMEPLAY_COMPONENT_PHYSICS * physics = entity->GetComponent<GAMEPLAY_COMPONENT_PHYSICS>();
            
            auto wt = &physics->GetBulletRigidBody()->getWorldTransform();
            
            entity->SetPosition(CORE_MATH_VECTOR(wt->getOrigin().getX(), wt->getOrigin().getY(), wt->getOrigin().getZ(), 1.0f));
            btQuaternion q = wt->getRotation();
            
            CORE_MATH_QUATERNION oq( q.getX(), q.getY(), q.getZ(), q.getW() );
            oq.Normalize();
            
            entity->SetOrientation( oq );
            
            it++;
        }
    #endif
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity, int group, int mask ) {
    
    GAMEPLAY_COMPONENT_SYSTEM::AddEntity( entity );
    
    GAMEPLAY_COMPONENT_PHYSICS * physics = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent<GAMEPLAY_COMPONENT_PHYSICS>();
    
    #ifdef __BULLET_PHYSICS__
        physics->GetBulletRigidBody()->setUserPointer( (void*) entity );
        DynamicsWorld->addRigidBody( physics->GetBulletRigidBody(), group, mask );
    #endif
}

void GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION::AddStaticEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity, int group, int mask ) {
    
    GAMEPLAY_COMPONENT_PHYSICS * physics = entity->GetComponent<GAMEPLAY_COMPONENT_PHYSICS>();
    
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
