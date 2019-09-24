//
//  GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER.h"

#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"

GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER() :
    GAMEPLAY_COMPONENT_SYSTEM(),
    Renderer( NULL ),
    Tree( 0.1f ),
    Effect( NULL ),
    CustomRenderComponentIndex( GAMEPLAY_COMPONENT_TYPE_Render ),
    MVPMatrix(),
    ModelMatrix(),
    ViewMatrix(),
    TimeModulator(),
    ProjectionMatrix() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::~GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::Update( void * ecs_base_pointer, float time_step ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::RenderFrontToBack( GAMEPLAY_COMPONENT_AABB_NODE * node ) {
    
    GAMEPLAY_COMPONENT_RENDER * renderable = (GAMEPLAY_COMPONENT_RENDER * ) node->GetEntity()->GetComponent( CustomRenderComponentIndex );
    GAMEPLAY_COMPONENT_POSITION * located = (GAMEPLAY_COMPONENT_POSITION * ) node->GetEntity()->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    GRAPHIC_OBJECT::PTR graphic_object = renderable->GetObject().GetResource< GRAPHIC_OBJECT >();
    
    Options.SetPosition( located->GetPosition() + located->GetPositionOffset() );
    Options.SetOrientation( located->GetOrientation() );
    float scale = renderable->GetScaleFactor();
    
    Options.SetScaleFactor( CORE_MATH_VECTOR( scale, scale, scale, 1.0f) );
    Options.SetParent( NULL );
    
    auto parent = node->GetEntity()->GetParent();
    
    if ( parent != NULL ) {
        
        GAMEPLAY_COMPONENT_POSITION * located = (GAMEPLAY_COMPONENT_POSITION * ) parent->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        GAMEPLAY_COMPONENT_RENDER * renderable = (GAMEPLAY_COMPONENT_RENDER * ) node->GetEntity()->GetComponent( CustomRenderComponentIndex );
        
        ParentOptions.SetPosition( located->GetPosition() + located->GetPositionOffset() );
        ParentOptions.SetOrientation( located->GetOrientation() );
        scale = renderable->GetScaleFactor();
        
        ParentOptions.SetScaleFactor( CORE_MATH_VECTOR( scale, scale, scale, 1.0f) );
        
        Options.SetParent( &ParentOptions );
    }
    
    for ( size_t i = 0; i < graphic_object->GetMeshTable().size(); i++ ) {
        
        CORE_MATH_MATRIX
            result,
            object;
        
        //effect->Apply( renderer, renderer.IsLightingEnabled(), options.IsTexturingEnabled() );
        
        graphic_object->ComputeModelViewProjection( Options, graphic_object->GetMeshTable()[i]->GetTransform(), *Renderer, result, object );
        
        if ( MVPMatrix->AttributeIndex >= 0 ) {
            
            GRAPHIC_SYSTEM_ApplyMatrix( MVPMatrix->AttributeIndex, 1, 1, &result[0])
        }
        
        if ( ProjectionMatrix->AttributeIndex >= 0 ) {
            
            GRAPHIC_SYSTEM_ApplyMatrix(ProjectionMatrix->AttributeIndex, 1, 1, &Renderer->GetCamera()->GetProjectionMatrix()[0]);
        }
        
        if ( ModelMatrix->AttributeIndex >= 0 ) {
            
            GRAPHIC_SYSTEM_ApplyMatrix( ModelMatrix->AttributeIndex, 1, 1, &object[0]);
        }
        
        if ( ViewMatrix->AttributeIndex >= 0 ) {
            
            GRAPHIC_SYSTEM_ApplyMatrix( ViewMatrix->AttributeIndex, 1, 1, &Renderer->GetCamera()->GetViewMatrix()[0]);
        }
        
        if ( TimeModulator->AttributeIndex >= 0 ) {
            
            GRAPHIC_SYSTEM_ApplyFloat( TimeModulator->AttributeIndex, TimeModulator->AttributeValue.Value.FloatValue )
        }
        
        for ( int cascade_index = 0; cascade_index < Renderer->GetNumCascade(); cascade_index++ ) {
            
            CORE_MATH_MATRIX
            depthMVP,
            depthBias;
            
            //Depth Textures are always last
            Renderer->GetDepthTexture( cascade_index )->ApplyDepth( Effect->GetMaterial()->GetTextureCount() + cascade_index , Depth[ cascade_index ]->AttributeIndex );
            
            static const CORE_MATH_MATRIX
            biasMatrix(
                       0.5f, 0.0f, 0.0f, 0.5f,
                       0.0f, 0.5f, 0.0f, 0.5f,
                       0.0f, 0.0f, 0.5f, 0.5f,
                       0.0f, 0.0f, 0.0f, 1.0f );
            
            depthMVP = Renderer->GetShadowMapCamera( cascade_index ).GetProjectionMatrix() * Renderer->GetShadowMapCamera( cascade_index ).GetViewMatrix() * object;
            
            depthBias = biasMatrix * depthMVP;
            
            float cascade_end[8];
            
            ShadowmapMVP = &Effect->GetProgram().getShaderAttribute( Renderer->GetShadowMapMVPName( cascade_index ) );
            
            for (int ci = 0; ci < Renderer->GetNumCascade(); ci++) {
                
                CORE_MATH_VECTOR vvv( 0.0f, 0.0f, Renderer->GetCascadeEnd( ci + 1 ), 0.0f ), vres;
                
                vres = Renderer->GetCamera()->GetProjectionMatrix() * vvv;
                
                cascade_end[ci] = -vres.Z();//Why is it negative? -> Bullshit in matrix vect mul
            }
            
            GRAPHIC_SYSTEM_ApplyMatrix( ShadowmapMVP->AttributeIndex, 1, 1, &depthBias[0] )
            GRAPHIC_SYSTEM_ApplyFloatArray( EndClipSpace->AttributeIndex, Renderer->GetNumCascade(), cascade_end )
        }
        
        graphic_object->GetMeshTable()[ i ]->ApplyBuffers();
    }
    
    
    /*if ( node->GetEntity()->GetParent()) {
        renderable->Render( *Renderer, located, (GAMEPLAY_COMPONENT_POSITION * ) node->GetEntity()->GetParent()->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ) );
    }
    else {
        renderable->Render( *Renderer, located, NULL );
    }*/
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER
    collider;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > callback( Wrapper1<GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER, GAMEPLAY_COMPONENT_AABB_NODE *, &GAMEPLAY_COMPONENT_AABB_NODE_FRONT_TO_BACK_FRUSTUM_COLLIDER::Collide>, &collider );
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > callback_render( Wrapper1<GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER, GAMEPLAY_COMPONENT_AABB_NODE *, &GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::RenderFrontToBack>, this );
    
    Renderer = &renderer;
    Tree.Update();
    
    MVPMatrix = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
    ModelMatrix = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelMatrix );
    ViewMatrix = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ViewMatrix );
    TimeModulator = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::TimeModulator );
    ProjectionMatrix = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ProjectionMatrix );
    
    EndClipSpace = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::CascadeEndClipSpace );
    
    Depth[0] = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture );
    Depth[1] = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture1 );
    Depth[2] = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture2 );
    Depth[3] = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture3 );
    Depth[4] = &Effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture4 );
    
    Renderer->GetCamera()->ActivateForRender();
    Tree.QueryTopToBottom( Renderer->GetCamera()->GetFustrum(), callback );
    Effect->Apply(renderer, false, true );
    collider.RenderFrontToBack( callback_render );
    Effect->Discard();
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    //CORE_RUNTIME_Abort();
    
    GAMEPLAY_COMPONENT_SYSTEM::AddEntity( entity );
    
    Tree.Insert( entity );
}

void GAMEPLAY_COMPONENT_SYSTEM_RENDERER_BATCH_SHADER::RemoveEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    //CORE_RUNTIME_Abort();
    
    GAMEPLAY_COMPONENT_SYSTEM::RemoveEntity( entity );
    
    Tree.Remove( entity );
}
