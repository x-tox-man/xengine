//
//  GAMEPLAY_COMPONENT_SYSTEM_RENDERER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"

GAMEPLAY_COMPONENT_SYSTEM_RENDERER::GAMEPLAY_COMPONENT_SYSTEM_RENDERER() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_RENDERER::~GAMEPLAY_COMPONENT_SYSTEM_RENDERER() {

}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Update( float time_step ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Render() {
    
    for ( int i = 0; i < EntitiesVector.size(); i++ ) {
        
        GAMEPLAY_COMPONENT_ENTITY * entity = EntitiesVector[ i ];
        
        GAMEPLAY_COMPONENT_RENDER * renderable = (GAMEPLAY_COMPONENT_RENDER * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        GAMEPLAY_COMPONENT_POSITION * located = (GAMEPLAY_COMPONENT_POSITION * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        renderable->Render( *Renderer, located );
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Finalize() {
    
}