//
//  PHYSICS_COLLISION_NEAR_FILTER.h
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef PHYSICS_COLLISION_NEAR_FILTER_h
#define PHYSICS_COLLISION_NEAR_FILTER_h

void MyNearCallback( btBroadphasePair & collision_pair, btCollisionDispatcher & dispatcher, const btDispatcherInfo & info );
static bool CustomMaterialCombinerCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

#endif /* PHYSICS_COLLISION_NEAR_FILTER_h */
