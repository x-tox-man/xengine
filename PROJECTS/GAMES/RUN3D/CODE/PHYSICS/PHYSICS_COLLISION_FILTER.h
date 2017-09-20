//
//  PHYSICS_COLLISION_FILTER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 19/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef PHYSICS_COLLISION_FILTER_hpp
#define PHYSICS_COLLISION_FILTER_hpp

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
            printf( "collides\n" );
        }
        
        return collides;
    }
};

#endif /* PHYSICS_COLLISION_FILTER_hpp */

