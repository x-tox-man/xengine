//
//  AABBTree.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_AABB_TREE.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

GAMEPLAY_COMPONENT_AABB_TREE::GAMEPLAY_COMPONENT_AABB_TREE( float margin ) :
    Root( NULL ),
    FrontToBack( true ),
    Margin( margin ),
    InvalidNodesList() {
    
}

void GAMEPLAY_COMPONENT_AABB_TREE::Update() {
    
    if ( Root ) {
        
        std::list< GAMEPLAY_COMPONENT_AABB_NODE * >::iterator
            it;
        
        Root->Update( InvalidNodesList );
        
        it = InvalidNodesList.begin();
        
        while ( !InvalidNodesList.empty() && it != InvalidNodesList.end() ) {
            
            auto node = (*it);
            float margin = node->GetMargin();
            node->GetBoxWithMargin().SetPosition( node->GetBox().GetPosition() );
            node->GetBoxWithMargin().SetHalfDiagonal( node->GetBox().GetHalfDiagonal() + CORE_MATH_VECTOR( margin, margin, margin, 0.0f ) );
            node->Update( InvalidNodesList );
            it++;
        }
        
        InvalidNodesList.clear();
    }
}

void GAMEPLAY_COMPONENT_AABB_TREE::Remove( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    GAMEPLAY_COMPONENT_RENDER * render_component = (GAMEPLAY_COMPONENT_RENDER *) entity-> GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    if ( render_component ) {
        
        InvalidNodesList.push_back( &render_component->GetAABBNode() );
    }
}

void GAMEPLAY_COMPONENT_AABB_TREE::Reset() {
    
    if ( Root ) {
        
        if ( Root->Finalize() ) {
            
            delete Root;
        }
        
        Root = NULL;
    }
}

void GAMEPLAY_COMPONENT_AABB_TREE::QueryTopToBottom( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback ) {
    
    if ( Root != NULL ) {
        
        Root->QueryTopToBottom( fustrum, callback );
    }
}

void GAMEPLAY_COMPONENT_AABB_TREE::QueryBottomToTop( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback ) {
    
    if ( Root != NULL ) {
        
        Root->QueryBottomToTop( fustrum, callback );
    }
}

void GAMEPLAY_COMPONENT_AABB_TREE::Insert( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    Insert( entity, Margin );
}

void GAMEPLAY_COMPONENT_AABB_TREE::Insert( GAMEPLAY_COMPONENT_ENTITY * entity, float margin ) {
    
    GAMEPLAY_COMPONENT_RENDER * rend = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    GAMEPLAY_COMPONENT_POSITION * pos = (GAMEPLAY_COMPONENT_POSITION *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    auto node = &rend->GetAABBNode();
    node->Left = NULL;
    node->Right = NULL;
    node->SetEntity( entity );
    rend->ComputeSize( node->GetBox() );
    node->GetBox().SetPosition( node->GetBox().GetPosition() + pos->GetPosition() );
    node->GetBox().GetPosition().W( 1.0f );
    node->GetBoxWithMargin().SetPosition( node->GetBox().GetPosition() );
    node->GetBoxWithMargin().SetHalfDiagonal( node->GetBox().GetHalfDiagonal() +CORE_MATH_VECTOR( margin, margin, margin, 0.0f ) );
    
    if ( Root == NULL ) {
        
        Root = node;
    }
    else {
        Insert( node, &Root );
    }
}

void GAMEPLAY_COMPONENT_AABB_TREE::InsertBackToFront( GAMEPLAY_COMPONENT_AABB_NODE * node ) {
    
    CORE_RUNTIME_Abort();
}

void GAMEPLAY_COMPONENT_AABB_TREE::Insert( GAMEPLAY_COMPONENT_AABB_NODE * node, GAMEPLAY_COMPONENT_AABB_NODE ** parent ) {
    
    if ( (*parent)->IsLeaf() ) {
        //Create new parent
        
        auto temp = *parent;
        auto new_parent = new GAMEPLAY_COMPONENT_AABB_NODE( Margin );
        new_parent->Right = node;
        new_parent->Left = temp;
        *parent = new_parent;
        new_parent->UpdateCenterAndExtent();
    }
    else if ( node->GetBox().ContainsBox( (*parent)->GetBox() ) ) {
        //Create new parent
        
        auto temp = *parent;
        auto new_parent = new GAMEPLAY_COMPONENT_AABB_NODE( Margin );
        new_parent->Right = node;
        new_parent->Left = temp;
        *parent = new_parent;
        new_parent->UpdateCenterAndExtent();
    }
    else {
        
        if ( (*parent)->Left != NULL && (*parent)->Right != NULL ) {
            
            float distance_from_left = ((*parent)->Left->GetBox().GetPosition() - node->GetBox().GetPosition()).ComputeSquareLength();
            float distance_from_right = ((*parent)->Right->GetBox().GetPosition() - node->GetBox().GetPosition()).ComputeSquareLength();
            
            if ( distance_from_left < distance_from_right ) {
                
                Insert(node, &((*parent)->Left) );
                (*parent)->UpdateCenterAndExtent();
            }
            else {
                Insert(node, &((*parent)->Right) );
                (*parent)->UpdateCenterAndExtent();
            }
        }
        else {
            
            if ( (*parent)->Left == NULL ) {
                
                (*parent)->Left = node;
            }
            else {
                
                (*parent)->Right = node;
            }
        }
    }
}
