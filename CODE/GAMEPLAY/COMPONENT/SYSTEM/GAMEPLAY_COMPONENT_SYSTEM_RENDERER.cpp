//
//  GAMEPLAY_COMPONENT_SYSTEM_RENDERER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"

GAMEPLAY_COMPONENT_SYSTEM_RENDERER::GAMEPLAY_COMPONENT_SYSTEM_RENDERER() :
    GAMEPLAY_COMPONENT_SYSTEM(),
    Renderer( NULL ),
    Tree( 0.1f ),
    CustomRenderComponentIndex( GAMEPLAY_COMPONENT_TYPE_Render ){
    
}

GAMEPLAY_COMPONENT_SYSTEM_RENDERER::~GAMEPLAY_COMPONENT_SYSTEM_RENDERER() {

}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Initialize() {
    
    /*std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
    
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEcsBasePointer() ) + it->GetOffset());
        AddEntity( entity );
        it++;
    }*/
    
    std::for_each(
                  EntitiesTable.begin(),
                  EntitiesTable.end(),
                  [this](GAMEPLAY_COMPONENT_ENTITY_HANDLE & item)
    {
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEcsBasePointer() ) + item.GetOffset());
        Tree.Insert( entity );
    });
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Update( void * ecs_base_pointer, float time_step ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::RenderFrontToBack( GAMEPLAY_COMPONENT_AABB_NODE * node ) {
    
    GAMEPLAY_COMPONENT_RENDER * renderable = node->GetEntity()->GetComponent< GAMEPLAY_COMPONENT_RENDER >( CustomRenderComponentIndex );
    GAMEPLAY_COMPONENT_POSITION * located = node->GetEntity()->GetComponent< GAMEPLAY_COMPONENT_POSITION >();
    GAMEPLAY_COMPONENT_ANIMATION * animation = node->GetEntity()->GetComponent< GAMEPLAY_COMPONENT_ANIMATION >();
    
    GAMEPLAY_COMPONENT_ENTITY_HANDLE handle = node->GetEntity()->GetParentHandle();
    
    if ( animation != NULL ) {
        renderable->GetObject().GetResource<GRAPHIC_OBJECT>()->SetAnimationController( &animation->GetAnimation() );
    }
    
    if ( handle.IsValid() ) {
    
        GAMEPLAY_COMPONENT_POSITION * parent_located = GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEntity( handle )->GetComponent<GAMEPLAY_COMPONENT_POSITION>();
        
        renderable->Render( *Renderer, located, parent_located );
    }
    else {
        
        renderable->Render( *Renderer, located );
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER
        collider;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > callback( Wrapper1<GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER, GAMEPLAY_COMPONENT_AABB_NODE *, &GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER::Collide>, &collider );
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > callback_render( Wrapper1<GAMEPLAY_COMPONENT_SYSTEM_RENDERER, GAMEPLAY_COMPONENT_AABB_NODE *, &GAMEPLAY_COMPONENT_SYSTEM_RENDERER::RenderFrontToBack>, this );
    
    Renderer = &renderer;
    Tree.Update();
    
    Renderer->GetCamera()->ActivateForRender();
    Tree.QueryTopToBottom( Renderer->GetCamera()->GetFustrum(), callback );
    collider.RenderFrontToBack( callback_render );
    
    /*std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    while (it != EntitiesTable.end() ) {

        GAMEPLAY_COMPONENT_ENTITY * entity = it->second->GetEntity();

        GAMEPLAY_COMPONENT_RENDER * renderable = (GAMEPLAY_COMPONENT_RENDER * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        GAMEPLAY_COMPONENT_POSITION * located = (GAMEPLAY_COMPONENT_POSITION * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );

        float d = renderable->GetObject().GetResource<GRAPHIC_OBJECT>()->GetMeshTable()[0]->GetBoundingShape().GetHalfDiagonal().X();

        //if ( fustrum.SphereInFrustum( located->GetPosition(), ( d > 0.0f) ? d : 1.0f ) ) {
        
            if ( entity->GetParent()) {
                renderable->Render( *Renderer, located, (GAMEPLAY_COMPONENT_POSITION * ) entity->GetParent()->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ) );
            }
            else {
                renderable->Render( *Renderer, located, NULL );
            }
        //}

        it++;
    }*/
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_SYSTEM::AddEntity( entity );
    
    Tree.Insert( entity );
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER::RemoveEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_SYSTEM::RemoveEntity( entity );
    
    Tree.Remove( entity );
}
