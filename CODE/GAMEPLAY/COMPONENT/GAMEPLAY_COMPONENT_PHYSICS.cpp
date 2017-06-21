//
//  GAMEPLAY_COMPONENT_PHYSICS.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"

GAMEPLAY_COMPONENT_PHYSICS::GAMEPLAY_COMPONENT_PHYSICS() :
    GAMEPLAY_COMPONENT()
#ifdef __BULLET_PHYSICS__
    ,Shape(),
    BulletShape()
#endif
{
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btSphereShape( 1 );
    #endif
}

GAMEPLAY_COMPONENT_PHYSICS::~GAMEPLAY_COMPONENT_PHYSICS() {

}

void * GAMEPLAY_COMPONENT_PHYSICS::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY_P > * iv = InternalVector = InitializeMemory<INTERNAL_ARRAY_P, GAMEPLAY_COMPONENT_PHYSICS>();
    
    LastIndex = ( *InternalVector)[ 0 ].LastIndex + 1;
    LastOffset = 0;
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_PHYSICS::operator delete  ( void* ptr ) {
    
}


void GAMEPLAY_COMPONENT_PHYSICS::ConfigureShapeSphere( const CORE_MATH_VECTOR & position ) {
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btSphereShape(1);
        
        btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
        btScalar mass = 1;
        btVector3 fallInertia(0, 0, 0);
        BulletShape->calculateLocalInertia(mass, fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, BulletShape, fallInertia);
        BulletRigidBody = new btRigidBody(fallRigidBodyCI);
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ConfigureShapePlane( const CORE_MATH_VECTOR & position ) {
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, BulletShape, btVector3(0, 0, 0));
        BulletRigidBody = new btRigidBody(groundRigidBodyCI);
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ApplyMotionModificator(
                                                        const CORE_MATH_VECTOR & position,
                                                        const CORE_MATH_VECTOR & direction) {
    
    #ifdef __BULLET_PHYSICS__
        BulletRigidBody->getMotionState()->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ForcePosition( const CORE_MATH_VECTOR & position ) {
    
    #ifdef __BULLET_PHYSICS__
        BulletRigidBody->getMotionState()->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::Clear() {
    
    LastIndex = -1;
    LastOffset = -1;
    InternalVector->clear();
}

void GAMEPLAY_COMPONENT_PHYSICS::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector ) {
        
        stream << InternalVector->size();
        
        for ( int i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_PHYSICS) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            stream << (*InternalVector)[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_PHYSICS::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( int i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY_P, GAMEPLAY_COMPONENT_PHYSICS>( *InternalVector, i );
        
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_PHYSICS) * GAMEPLAY_COMPONENT_BASE_COUNT );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}


std::vector< GAMEPLAY_COMPONENT_PHYSICS::INTERNAL_ARRAY_P> * GAMEPLAY_COMPONENT_PHYSICS::InternalVector =  NULL;
int GAMEPLAY_COMPONENT_PHYSICS::LastIndex = -1;
int GAMEPLAY_COMPONENT_PHYSICS::LastOffset = -1;
