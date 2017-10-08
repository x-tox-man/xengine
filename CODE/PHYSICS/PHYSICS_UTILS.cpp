//
//  PHYSICS_UTILS.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/09/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "PHYSICS_UTILS.h"

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
#endif

#ifdef __BULLET_PHYSICS__
bool PHYSICS_UTILS::FindCollisionInRayFromWorld( btDiscreteDynamicsWorld * world, CORE_MATH_VECTOR & result, const CORE_MATH_RAY_SEGMENT & ray ) {
    
    btVector3 start = ray.GetOrigin().toBt();
    btVector3 end = ray.GetDestination().toBt();
    
    btCollisionWorld::ClosestRayResultCallback result_callback( start, end );
    
    // Perform raycast
    world->rayTest( start, end, result_callback );
    
    if( result_callback.hasHit() ) {
        
        btVector3 end_pos = result_callback.m_hitPointWorld;
        btVector3 end_normal = result_callback.m_hitNormalWorld;
        
        // Do some clever stuff here
        
        result[0] = end_pos.x();
        result[1] = end_pos.y();
        result[2] = end_pos.z();
        
        return true;
    }
    
    return false;
}
#endif

