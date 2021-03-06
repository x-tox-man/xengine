//
//  PHYSICS_COLLISION_FILTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 19/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef PHYSICS_COLLISION_FILTER_hpp
#define PHYSICS_COLLISION_FILTER_hpp

#include "PHYSICS_COLLISION_TYPE.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
#endif

#define BT_USE_DOUBLE_PRECISION

struct PHYSICS_COLLISION_FILTER : public btOverlapFilterCallback
{
    // return true when pairs need collision
    virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
    {
        bool needsBroadphase = (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask) ||
            (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask);
        //add some additional logic here that modified 'collides'
        
        if ( needsBroadphase ) {
            
            unsigned int r = proxy0->m_collisionFilterGroup & PHYSICS_COLLISION_TYPE_TARGET;
            unsigned int r2 = proxy1->m_collisionFilterMask & PHYSICS_COLLISION_TYPE_TARGET;
            
            if ( r == PHYSICS_COLLISION_TYPE_TARGET && r2 == PHYSICS_COLLISION_TYPE_TARGET ) {
                
                printf( "hit PHYSICS_COLLISION_TYPE_TARGET\n" );
                
                GAMEPLAY_COMPONENT_ENTITY * entity = ((GAMEPLAY_COMPONENT_ENTITY*)((btCollisionObject *) proxy0->m_clientObject)->getUserPointer());
                
                entity->CollidesWith( ((GAMEPLAY_COMPONENT_ENTITY*)((btCollisionObject *) proxy1->m_clientObject)->getUserPointer()) );
                
                return false;
            }
        }
        
        return needsBroadphase;
    }
};

#endif /* PHYSICS_COLLISION_FILTER_hpp */

