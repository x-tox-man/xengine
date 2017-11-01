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
    
    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    
    const GRAPHIC_CAMERA_FUSTRUM & fustrum = Renderer->GetCamera().GetFustrum();
    
    #if DEBUG
        int zapped = 0;
    #endif
    
    while (it != EntitiesTable.end() ) {
        
        GAMEPLAY_COMPONENT_ENTITY * entity = it->second->GetEntity();
        
        GAMEPLAY_COMPONENT_RENDER * renderable = (GAMEPLAY_COMPONENT_RENDER * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        GAMEPLAY_COMPONENT_POSITION * located = (GAMEPLAY_COMPONENT_POSITION * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        float d = renderable->GetObject().GetResource<GRAPHIC_OBJECT>()->GetMeshTable()[0]->GetBoundingShape().GetHalfDiagonal().X();
        if ( fustrum.SphereInFrustum( located->GetPosition(), ( d > 0.0f) ? d : 1.0f ) ) {
            
            renderable->Render( *Renderer, located );
        }
        #if DEBUG
        else
            zapped++;
        #endif
        
        it++;
    }
    
#if DEBUG
    printf( "eliminated from render :%d\n", zapped );
#endif
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Finalize() {
    
}
