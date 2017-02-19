//
//  GAMEPLAY_COMPONENT_PHYSICS.h
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_PHYSICS, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_PHYSICS();
    virtual ~GAMEPLAY_COMPONENT_PHYSICS();

    CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_PHYSICS, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Physics)

    void * operator new(size_t size);

    struct INTERNAL_ARRAY_P{
        int LastIndex;
        GAMEPLAY_COMPONENT_PHYSICS * MemoryArray;
    };

    static std::vector< INTERNAL_ARRAY_P > InternalVector;

    CORE_MATH_SHAPE & GetShape() { return Shape; }

    #ifdef __BULLET_PHYSICS__
        btCollisionShape * GetBulletShape() { return BulletShape; }
        btRigidBody* GetBulletRigidBody() { return BulletRigidBody; }
    #endif

    void ConfigureShapeSphere( const CORE_MATH_VECTOR & position );
    void ConfigureShapePlane( const CORE_MATH_VECTOR & position );

    void ApplyMotionModificator(
                                const CORE_MATH_VECTOR & position,
                                const CORE_MATH_VECTOR & direction);

    void ForcePosition( const CORE_MATH_VECTOR & position );

    static void FinalizeStaticMemory() {
        
        for ( int i = 0; i < InternalVector.size(); i++ ) {
            
            CORE_MEMORY_ALLOCATOR_Free( InternalVector[ i ].MemoryArray );
        }
        
        InternalVector.resize( 0 );
        InternalVector.clear();
    }

private:

    CORE_MATH_SHAPE
        Shape;

#ifdef __BULLET_PHYSICS__
    btCollisionShape * BulletShape;
    btRigidBody* BulletRigidBody;
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_PHYSICS__) */
