//
//  GAMEPLAY_COMPONENT_PHYSICS.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_PHYSICS__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_PHYSICS__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_MATH_SHAPE.h"
#include "CORE_MATH_VECTOR.h"

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
#endif

class GRAPHIC_OBJECT;

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_PHYSICS )

    GAMEPLAY_COMPONENT_PHYSICS();
    ~GAMEPLAY_COMPONENT_PHYSICS();

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT_PHYSICS );

    //CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_PHYSICS, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Physics)


    inline CORE_MATH_SHAPE & GetShape() { return Shape; }
    inline const CORE_MATH_SHAPE & GetShape() const { return Shape; }

    #ifdef __BULLET_PHYSICS__
        btCollisionShape * GetBulletShape() { return BulletShape; }
        btRigidBody* GetBulletRigidBody() { return BulletRigidBody; }
    #endif

    void ConfigureShapeSphere( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );
    void ConfigureShapeBox( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & half_extent, const CORE_MATH_QUATERNION & orientation );
    void ConfigureHeightMap( const CORE_MATH_VECTOR & position, int width, int lenght, const void * heights, float spacing, float scale );
    void ConfigureShapeCylinder(const CORE_MATH_VECTOR & position, float radius, float width, const CORE_MATH_QUATERNION & orientation );
    void ConfigureShapePlane( const CORE_MATH_VECTOR & position, float constant = 1.0f );
    void BulletConfigureConvexHullShape( const CORE_MATH_VECTOR & position, GRAPHIC_OBJECT * object );
    void Enable( bool enable );
    void EnableCCD();

#ifdef __BULLET_PHYSICS__
    void BulletConfigureBvhTriangleMeshShape( const CORE_MATH_VECTOR & position, btTriangleMesh * collision_mesh );
#endif

    void ApplyMotionModificator(
                                const CORE_MATH_VECTOR & position,
                                const CORE_MATH_VECTOR & direction);

    void ForcePosition( const CORE_MATH_VECTOR & position );

    void Reset();
    void SetMass( const float mass);
    void SetPosition( const CORE_MATH_VECTOR & position);
    void SetOrientation( const CORE_MATH_QUATERNION & rotation );
    void SetVelocity( const CORE_MATH_VECTOR & velocity);
    CORE_MATH_VECTOR & GetVelocity();

    void ApplyForce( const CORE_MATH_VECTOR & vector ) {
        #ifdef __BULLET_PHYSICS__
            BulletRigidBody->applyCentralForce( btVector3( vector.X(), vector.Y(), vector.Z() ) );
        #endif
    }

    void ApplyTorque( const CORE_MATH_VECTOR & vector ) {
        #ifdef __BULLET_PHYSICS__
            //https://stackoverflow.com/questions/16322080/what-does-having-an-inertia-tensor-of-zero-do-in-bullet
            BulletRigidBody->setAngularVelocity( btVector3( vector.X(), vector.Y(), vector.Z() ) );
        #endif
    }

    #ifdef __BULLET_PHYSICS__
        btTriangleMesh* CreateBvhTriangleMesh( GRAPHIC_OBJECT * object  );
        btTriangleMesh* GetTriangleMesh() const { return TriangleMesh; }

    #endif

    static int
        ComponentType;

private:

    #ifdef __BULLET_PHYSICS__
        void CreateRigidBody( const GAMEPLAY_COMPONENT_PHYSICS & other );
    #endif

    CORE_MATH_SHAPE
        Shape;
    CORE_MATH_VECTOR
        Velocity;
    float
        Restitution,
        Friction,
        RollingFriction,
        SpinningFriction,
        Mass;
#ifdef __BULLET_PHYSICS__
    //TODO: These needs to be a resource
    btCollisionShape
        * BulletShape;
    btRigidBody
        * BulletRigidBody;
    btTriangleMesh
        * TriangleMesh;

#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_PHYSICS__) */
