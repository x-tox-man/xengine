//
//  GAMEPLAY_COMPONENT_PHYSICS.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH.h"

#ifdef __BULLET_PHYSICS__
    #include "btHeightfieldTerrainShape.h"
#endif

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GAMEPLAY_COMPONENT_PHYSICS )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GAMEPLAY_COMPONENT_PHYSICS, SetPosition, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GAMEPLAY_COMPONENT_PHYSICS, SetVelocity, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_MATH_VECTOR &, GAMEPLAY_COMPONENT_PHYSICS, GetVelocity )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_COMPONENT_PHYSICS )

GAMEPLAY_COMPONENT_PHYSICS::GAMEPLAY_COMPONENT_PHYSICS() :
    GAMEPLAY_COMPONENT(),
    Restitution( 1.0f ),
    Friction( 1.0f ),
    Velocity(),
    RollingFriction( 1.0f ),
    SpinningFriction( 1.0f ),
    Shape(),
    Mass(  1.0f )
#ifdef __BULLET_PHYSICS__

    ,BulletShape( NULL ),
    BulletRigidBody( NULL ),
    TriangleMesh( NULL )
#endif
{
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btSphereShape( 1 );
    #endif
}

GAMEPLAY_COMPONENT_PHYSICS::GAMEPLAY_COMPONENT_PHYSICS( const GAMEPLAY_COMPONENT_PHYSICS & other ) :
    GAMEPLAY_COMPONENT(),
    Restitution( other.Restitution ),
    Friction( other.Friction ),
    RollingFriction( other.RollingFriction ),
    SpinningFriction( other.SpinningFriction ),
    Mass(  other.Mass ),
    Shape( other.Shape ),
    Velocity( other.Velocity )
    #ifdef __BULLET_PHYSICS__
        ,BulletShape( other.BulletShape ),
        BulletRigidBody( NULL )
    #endif
{
    
    #ifdef __BULLET_PHYSICS__
        CreateRigidBody( other );
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

void GAMEPLAY_COMPONENT_PHYSICS::ConfigureShapeSphere( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_Sphere );
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btSphereShape(0.05f);
        BulletShape->setMargin( 0.1f );
        
        btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(btQuaternion(orientation[0], orientation[1], orientation[2], orientation[3]), btVector3(position[0], position[1], position[2])));
        btScalar mass = 1.0f;
        btVector3 fall_inertia(0.0f, 0.0f, 0.0f);
    
        if ( mass > 0.0f )
            BulletShape->calculateLocalInertia(mass, fall_inertia);
    
        btRigidBody::btRigidBodyConstructionInfo construction_info( mass, motion_state, BulletShape, fall_inertia );
        BulletRigidBody = new btRigidBody( construction_info );
        BulletRigidBody->setRestitution( 0.0f );
        BulletRigidBody->setFriction( 0.0f );
        BulletRigidBody->setRollingFriction( 0.0f );
        BulletRigidBody->setSpinningFriction( 0.0f );
        BulletRigidBody->setAngularFactor( 0.0f );
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ConfigureShapeBox(  const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & half_extent, const CORE_MATH_QUATERNION & orientation ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_Box );
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btBoxShape( btVector3(half_extent[0], half_extent[1], half_extent[2]) );
        BulletShape->setMargin( 0.01f );
        
        btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(position[0], position[1], position[2])));
        btScalar mass = 1.0f;
        btVector3 fall_inertia(0.0f, 0.0f, 0.0f);
    
        if ( mass > 0.0f )
            BulletShape->calculateLocalInertia(mass, fall_inertia);
    
        btRigidBody::btRigidBodyConstructionInfo construction_info( mass, motion_state, BulletShape, fall_inertia);
    
        BulletRigidBody = new btRigidBody( construction_info );
        BulletRigidBody->setRestitution( 0.0f );
        BulletRigidBody->setFriction( 0.0f );
        BulletRigidBody->setRollingFriction( 0.0f );
        BulletRigidBody->setSpinningFriction( 0.0f );
        BulletRigidBody->setAngularFactor( 0.0f );
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ConfigureShapeCylinder(const CORE_MATH_VECTOR & position, float radius, float width, const CORE_MATH_QUATERNION & orientation ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_Cylinder );
    
#ifdef __BULLET_PHYSICS__
    BulletShape = new btCylinderShape( btVector3( radius, width, radius) );
    
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(position[0], position[1], position[2])));
    btScalar mass = 1.0f;
    btVector3 fall_inertia( 0.0f, 0.0f, 0.0f );
    
    if ( mass > 0.0f )
        BulletShape->calculateLocalInertia( mass, fall_inertia );
    
    btRigidBody::btRigidBodyConstructionInfo construction_info( mass, motion_state, BulletShape, fall_inertia );
    BulletRigidBody = new btRigidBody( construction_info );
    BulletRigidBody->setRestitution( 0.1f );
    BulletRigidBody->setFriction( 1.0f );
    BulletRigidBody->setRollingFriction( 0.1f );
    BulletRigidBody->setSpinningFriction( 0.0f );
    BulletRigidBody->setAngularFactor( 0.0f );
#endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ConfigureShapePlane( const CORE_MATH_VECTOR & position, float constant ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_Plane );
    
    #ifdef __BULLET_PHYSICS__
        BulletShape = new btStaticPlaneShape(btVector3(0, 0, 1), constant);
    
        btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
        btRigidBody::btRigidBodyConstructionInfo construction_info(0, motion_state, BulletShape, btVector3(0, 0, 0));
    
        BulletRigidBody = new btRigidBody( construction_info );
        BulletRigidBody->setRestitution( 0.1f );
        BulletRigidBody->setFriction( 0.1f );
        BulletRigidBody->setRollingFriction( 0.0f );
        BulletRigidBody->setSpinningFriction( 0.0f );
        BulletRigidBody->setAngularFactor( 0.0f );
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::BulletConfigureConvexHullShape( const CORE_MATH_VECTOR & position, GRAPHIC_OBJECT * object ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_TriangleList );
    
    /*for ( int i = 0; i < object->GetMeshTable().size(); i++ ) {
        
        int size = object->GetMeshTable()[i]->GetVertexCoreBuffer()->GetSize();
        
        for (int j = 0; j < size / 4; j++) {
            
            object->GetMeshTable()[i]->GetVertexCoreBuffer()->getpointerAtIndex( 0 );
        }
    }*/
    
#ifdef __BULLET_PHYSICS__
    
    btTriangleMesh* trimesh = new btTriangleMesh();
    
    BulletShape = new btBvhTriangleMeshShape( trimesh, true );
    
    //BulletShape = new btConvexHullShape( (btScalar*)object->GetMeshTable()[0]->GetVertexCoreBuffer()->getpointerAtIndex( 0 ), object->GetMeshTable()[0]->GetVertexCoreBuffer()->GetSize() / 16 );
    
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.X(), position.Y(), position.Z())));

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, BulletShape, btVector3(0, 0, 0));

    BulletRigidBody = new btRigidBody(groundRigidBodyCI);
#endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ConfigureHeightMap( const CORE_MATH_VECTOR & position, int width, int lenght, const void * heights, float spacing, float scale ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_Heights );
    
#ifdef __BULLET_PHYSICS__
    
    BulletShape = new btHeightfieldTerrainShape( width, lenght, heights, scale, -100.0f, 100.0f, 2, PHY_ScalarType::PHY_UCHAR, false );
    BulletShape->setLocalScaling( btVector3(spacing,spacing,1.0f));
    BulletShape->setMargin( 0.01f );
    
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.X(), position.Y(), position.Z())));
    
    btRigidBody::btRigidBodyConstructionInfo construction_info(0, motion_state, BulletShape, btVector3(0, 0, 0));
    
    BulletRigidBody = new btRigidBody( construction_info );
    BulletRigidBody->setRestitution( 1.0f );
    BulletRigidBody->setFriction( 1.0f );
    BulletRigidBody->setRollingFriction( 1.0f );
    BulletRigidBody->setSpinningFriction( 1.0f );
    BulletRigidBody->setAngularFactor( 0.0f );
#endif
}

#ifdef __BULLET_PHYSICS__
void GAMEPLAY_COMPONENT_PHYSICS::BulletConfigureBvhTriangleMeshShape( const CORE_MATH_VECTOR & position, btTriangleMesh * collision_mesh ) {
    
    Shape.SetType( CORE_MATH_SHAPE_TYPE_TriangleList );
    
    TriangleMesh = collision_mesh;
    
    BulletShape = new btBvhTriangleMeshShape( collision_mesh, true );
    BulletShape->setMargin( 0.01f );
    
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
    
    btRigidBody::btRigidBodyConstructionInfo construction_info(1.0, motion_state, BulletShape, btVector3(0, 0, 0));

    BulletRigidBody = new btRigidBody( construction_info );
    BulletRigidBody->setRestitution( 1.0f );
    BulletRigidBody->setFriction( 1.0f );
    BulletRigidBody->setRollingFriction( 1.0f );
    BulletRigidBody->setSpinningFriction( 1.0f );
    BulletRigidBody->setAngularFactor( 0.0f );
}
#endif

#ifdef __BULLET_PHYSICS__
btTriangleMesh * GAMEPLAY_COMPONENT_PHYSICS::CreateBvhTriangleMesh( GRAPHIC_OBJECT * object ) {

    btTriangleMesh* collision_mesh = new btTriangleMesh();
    
    for ( size_t i = 0; i < object->GetMeshTable().size(); i++ ) {
        
        size_t size = object->GetMeshTable()[i]->GetIndexCoreBuffer()->GetSize() / sizeof( unsigned int );
        int * indice_ptr = object->GetMeshTable()[i]->GetIndexCoreBuffer()->getpointerAtIndex( 0 );
        float * vertex_ptr = (float * )object->GetMeshTable()[i]->GetVertexCoreBuffer()->getpointerAtIndex( 0 );
        
        GRAPHIC_SHADER_BIND bind = object->GetMeshTable()[i]->GetVertexComponent();
        int stride = GRAPHIC_MESH::ComputeVertexStride( bind );

        for ( size_t j = 0; j < size ; j += 3 ) {
            
            float x1 = vertex_ptr[(indice_ptr[j] * stride ) + 0];
            float y1 = vertex_ptr[(indice_ptr[j] * stride ) + 1];
            float z1 = vertex_ptr[(indice_ptr[j] * stride ) + 2];
            
            float x2 = vertex_ptr[(indice_ptr[j + 1] * stride ) + 0];
            float y2 = vertex_ptr[(indice_ptr[j + 1] * stride ) + 1];
            float z2 = vertex_ptr[(indice_ptr[j + 1] * stride ) + 2];
            
            float x3 = vertex_ptr[(indice_ptr[j + 2] * stride ) + 0];
            float y3 = vertex_ptr[(indice_ptr[j + 2] * stride ) + 1];
            float z3 = vertex_ptr[(indice_ptr[j + 2] * stride ) + 2];
            
            const CORE_MATH_VECTOR
            p1( x1, y1, z1, 1.0f ),
            p2( x2, y2, z2, 1.0f ),
            p3( x3, y3, z3, 1.0f );
            
            CORE_MATH_VECTOR pt1 = ::operator*(object->GetMeshTable()[i]->GetTransform(), p1);
            CORE_MATH_VECTOR pt2 = ::operator*(object->GetMeshTable()[i]->GetTransform(), p2);
            CORE_MATH_VECTOR pt3 = ::operator*(object->GetMeshTable()[i]->GetTransform(), p3);
            
            collision_mesh->addTriangle(btVector3(pt1[0], pt1[1], pt1[2]), btVector3(pt2[0], pt2[1], pt2[2]), btVector3(pt3[0], pt3[1], pt3[2]));
        }
    }
    
    return collision_mesh;
}
#endif

void GAMEPLAY_COMPONENT_PHYSICS::SetMass(const float mass) {
    
    Mass = mass;
    
    #ifdef __BULLET_PHYSICS__
        btVector3 v;
    
        BulletRigidBody->setMassProps( mass, v );
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::SetVelocity( const CORE_MATH_VECTOR & velocity ) {
    
#ifdef __BULLET_PHYSICS__
    btVector3 v;
    
    v.setX( velocity[0] );
    v.setY( velocity[1] );
    v.setZ( velocity[2] );
    
    BulletRigidBody->setLinearVelocity( v );
#endif
}

CORE_MATH_VECTOR & GAMEPLAY_COMPONENT_PHYSICS::GetVelocity() {
    
#ifdef __BULLET_PHYSICS__
    const btVector3 & v = BulletRigidBody->getLinearVelocity();
    
    Velocity[0] = v.getX();
    Velocity[1] = v.getY();
    Velocity[2] = v.getZ();
#endif
    
    return Velocity;
}

void GAMEPLAY_COMPONENT_PHYSICS::SetPosition( const CORE_MATH_VECTOR & position ) {
    
    Shape.SetPosition( position );
    
#ifdef __BULLET_PHYSICS__
    btTransform initialTransform;
    
    BulletRigidBody->getMotionState()->getWorldTransform(initialTransform);
    
    btVector3 v;
    v.setX( position[0] );
    v.setY( position[1] );
    v.setZ( position[2] );
    
    initialTransform.setOrigin(v);
    //BulletRigidBody->setWorldTransform(initialTransform);
#endif
}

void GAMEPLAY_COMPONENT_PHYSICS::SetOrientation( const CORE_MATH_QUATERNION & rotation ) {
    
    Shape.SetOrientation( rotation );
    
#ifdef __BULLET_PHYSICS__
    CORE_MATH_MATRIX m;
    rotation.ToMatrix( &m[0] );
    
    btTransform initialTransform;
    
    BulletRigidBody->getMotionState()->getWorldTransform(initialTransform);
    btMatrix3x3 basis;
    basis.setValue(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
    
    initialTransform.setBasis( basis );
    BulletRigidBody->setWorldTransform(initialTransform);
#endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ApplyMotionModificator( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction) {
    
    #ifdef __BULLET_PHYSICS__
        BulletRigidBody->getMotionState()->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::ForcePosition( const CORE_MATH_VECTOR & position ) {
    
    Shape.SetPosition( position );
    
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
        
        for ( size_t i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_PHYSICS) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            stream << (*InternalVector)[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_PHYSICS::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( size_t i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY_P, GAMEPLAY_COMPONENT_PHYSICS>( *InternalVector, i );
        
        size_t b =sizeof(GAMEPLAY_COMPONENT_PHYSICS) * GAMEPLAY_COMPONENT_BASE_COUNT;
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, b );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}

#ifdef __BULLET_PHYSICS__

void GAMEPLAY_COMPONENT_PHYSICS::CreateRigidBody( const GAMEPLAY_COMPONENT_PHYSICS & other ) {
    
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(other.Shape.GetOrientation().X(), other.Shape.GetOrientation().Y(), other.Shape.GetOrientation().Z(), other.Shape.GetOrientation().W() ), btVector3(other.Shape.GetPosition().X(), other.Shape.GetPosition().Y(), other.Shape.GetPosition().Z())));
    btScalar mass = 0;
    btVector3 fallInertia(0.0f, 0.0f, 0.0f);
    
    if ( mass > 0.0f )
        BulletShape->calculateLocalInertia(mass, fallInertia);
    
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, BulletShape, fallInertia);
    BulletRigidBody = new btRigidBody(fallRigidBodyCI);
    BulletRigidBody->setRestitution( other.BulletRigidBody->getRestitution() );
    BulletRigidBody->setFriction( other.BulletRigidBody->getFriction() );
    BulletRigidBody->setRollingFriction( other.BulletRigidBody->getRollingFriction() );
    BulletRigidBody->setSpinningFriction( other.BulletRigidBody->getSpinningFriction() );
    BulletRigidBody->setAngularFactor( other.BulletRigidBody->getAngularFactor() );
}
#endif

void GAMEPLAY_COMPONENT_PHYSICS::Reset() {
    
    #ifdef __BULLET_PHYSICS__
    btVector3 fallInertia(0.0f, 0.0f, 0.0f);
    
    SetVelocity( CORE_MATH_VECTOR::Zero );
    
    if ( Mass > 0.0f )
        BulletShape->calculateLocalInertia( Mass, fallInertia);
    
    BulletRigidBody->activate();
    #endif
}

void GAMEPLAY_COMPONENT_PHYSICS::Enable( bool enable ) {
    
    #ifdef __BULLET_PHYSICS__
        BulletRigidBody->setActivationState( enable ? DISABLE_DEACTIVATION : WANTS_DEACTIVATION );
    #endif
}

std::vector< GAMEPLAY_COMPONENT_PHYSICS::INTERNAL_ARRAY_P> * GAMEPLAY_COMPONENT_PHYSICS::InternalVector =  NULL;
int GAMEPLAY_COMPONENT_PHYSICS::LastIndex = -1;
int GAMEPLAY_COMPONENT_PHYSICS::LastOffset = -1;
