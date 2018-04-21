//
//  PHYSICS_UTILS.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/09/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "PHYSICS_UTILS.h"

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
#endif

#ifdef __BULLET_PHYSICS__
bool PHYSICS_UTILS::FindCollisionInRayFromWorld( btDiscreteDynamicsWorld * world, CORE_MATH_VECTOR & result, CORE_MATH_VECTOR & normal, const CORE_MATH_RAY_SEGMENT & ray ) {
    
    btVector3 start = ray.GetOrigin().toBt();
    btVector3 end = ray.GetDestination().toBt();
    
    btCollisionWorld::ClosestRayResultCallback result_callback( start, end );
    
    // Perform raycast
    world->rayTest( start, end, result_callback );
    
    if( result_callback.hasHit() ) {
        // Do some clever stuff here
        
        result[0] = result_callback.m_hitPointWorld.x();
        result[1] = result_callback.m_hitPointWorld.y();
        result[2] = result_callback.m_hitPointWorld.z();
        
        normal[0] = result_callback.m_hitNormalWorld.x();
        normal[1] = result_callback.m_hitNormalWorld.y();
        normal[2] = result_callback.m_hitNormalWorld.z();
        
        return true;
    }
    
    return false;
}
#endif

