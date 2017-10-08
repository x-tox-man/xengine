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

struct PHYSICS_COLLISION_FILTER : public btOverlapFilterCallback
{
    // return true when pairs need collision
    virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
    {
        bool collides = (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);
        //add some additional logic here that modified 'collides'
        
        if ( collides ) {
            
            unsigned int r = proxy0->m_collisionFilterGroup & PHYSICS_COLLISION_TYPE_TARGET;
            
            if ( r == PHYSICS_COLLISION_TYPE_TARGET ) {
                printf( "hit PHYSICS_COLLISION_TYPE_TARGET\n" );
                
                GAMEPLAY_COMPONENT_ENTITY * entity = ((GAMEPLAY_COMPONENT_ENTITY*)((btCollisionObject *) proxy0->m_clientObject)->getUserPointer());
                
                entity->CollidesWith( ((GAMEPLAY_COMPONENT_ENTITY*)((btCollisionObject *) proxy1->m_clientObject)->getUserPointer()) );
                
                return false;
            }
        }
        
        return collides;
    }
};

#endif /* PHYSICS_COLLISION_FILTER_hpp */

