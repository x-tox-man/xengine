//
//  GAMEPLAY_COMPONENT_ANIMATION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "CORE_MEMORY.h"

GAMEPLAY_COMPONENT_ANIMATION::GAMEPLAY_COMPONENT_ANIMATION() :
    GAMEPLAY_COMPONENT( sizeof( GAMEPLAY_COMPONENT_ANIMATION ) ),
    Animation() {
    
}

GAMEPLAY_COMPONENT_ANIMATION::GAMEPLAY_COMPONENT_ANIMATION( const GAMEPLAY_COMPONENT_ANIMATION & other ) :
    GAMEPLAY_COMPONENT( sizeof( GAMEPLAY_COMPONENT_ANIMATION ) ),
    Animation( other.Animation ) {
    
}

GAMEPLAY_COMPONENT_ANIMATION::~GAMEPLAY_COMPONENT_ANIMATION() {
    
}

void GAMEPLAY_COMPONENT_ANIMATION::operator =( const GAMEPLAY_COMPONENT_ANIMATION & other ) {
    
    Animation = other.Animation;
}

void GAMEPLAY_COMPONENT_ANIMATION::Update( float time_step, GRAPHIC_MESH_SKELETON_JOINT * skeleton ) {
    
    if ( time_step + Animation.GetCurrentTimeFrame() < Animation.GetAnimation( 0 )->GetDuration() ) {
        
        Animation.Update( time_step, skeleton );
    }
    else {
        
        Animation.Reset();
    }
}
