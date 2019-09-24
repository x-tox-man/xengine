//
//  FustrumCollider.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 13/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef FustrumCollider_h
#define FustrumCollider_h

#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"

class FustrumCollider {
    
public:
    FustrumCollider() :
        Amount( 0 ) {
        
    }
    
    void Collide( AABBNode * node ) {
        Amount++;
    }
    
    int Amount;
};

#endif /* FustrumCollider_h */
