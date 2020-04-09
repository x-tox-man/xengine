//
//  GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::GAMEPLAY_COMPONENT_SYSTEM_ANIMATING() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::~GAMEPLAY_COMPONENT_SYSTEM_ANIMATING() {

}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Update( void * ecs_base_pointer, float time_step ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((uint8_t*) ecs_base_pointer) + it->GetOffset());
        GAMEPLAY_COMPONENT_ANIMATION * animation = entity->GetComponentAnimation();
        GAMEPLAY_COMPONENT_RENDER * render = entity->GetComponentRender();
        
        assert( animation != NULL || render != NULL );
        
        animation->Update( time_step, & render->GetObject().GetResource< GRAPHIC_OBJECT>()->GetSkeleton() );
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    CORE_RUNTIME_Abort();
}
