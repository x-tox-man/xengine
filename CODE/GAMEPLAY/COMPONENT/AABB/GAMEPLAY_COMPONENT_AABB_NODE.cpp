//
//  AABBNode.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_AABB_NODE.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

GAMEPLAY_COMPONENT_AABB_NODE::GAMEPLAY_COMPONENT_AABB_NODE( float margin ) :
    Left( NULL ),
    Right( NULL ),
    ZOrderLeft( NULL ),
    ZOrderRight( NULL ),
    Box(),
    BoxWithMargin(),
    Entity( NULL ),
    Margin( margin ) {
    
}

GAMEPLAY_COMPONENT_AABB_NODE::GAMEPLAY_COMPONENT_AABB_NODE( const GAMEPLAY_COMPONENT_AABB_NODE & other ) :
    Left( other.Left ),
    Right( other.Right ),
    ZOrderLeft( other.ZOrderLeft ),
    ZOrderRight( other.ZOrderRight ),
    Box( other.Box ),
    BoxWithMargin( other.BoxWithMargin ),
    Entity( other.Entity ),
    Margin( other.Margin ){
    
}

void GAMEPLAY_COMPONENT_AABB_NODE::Remove( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    abort();
}

void GAMEPLAY_COMPONENT_AABB_NODE::Update( std::list< GAMEPLAY_COMPONENT_AABB_NODE * > & invalid_nodes ) {
    
    if ( !BoxWithMargin.ContainsBox( Box ) ) {
        
        invalid_nodes.push_back( this );
    }
    else {

        if ( Left ) {
            
            if ( !BoxWithMargin.ContainsBox( Box ) ) {
                
                invalid_nodes.push_back( this );
            }
            else {
                
                Left->Update( invalid_nodes );
            }
        }

        if ( Right ) {
            
            if ( !BoxWithMargin.ContainsBox( Box ) ) {
                
                invalid_nodes.push_back( this );
            }
            else {
              
                Right->Update( invalid_nodes );
            }
        }
    }
}

bool GAMEPLAY_COMPONENT_AABB_NODE::Finalize() {
    
    if ( Left ) {
        
        if ( Left->Finalize() ) {
            
            delete Left;
            Left = NULL;
        }
    }
    
    if ( Right ) {
        
        if( Right->Finalize() ) {
            
            delete Right;
            Right = NULL;
        }
    }
    
    return Entity == NULL;
}

void GAMEPLAY_COMPONENT_AABB_NODE::QueryTopToBottom( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback ) {
    
    if ( Entity != NULL && fustrum.BoxInFrustum( Box ) ) {
        
        callback( this );
        ZOrderLeft = NULL;
        ZOrderRight = NULL;
    }
    
    if ( Left ) {
        
        Left->QueryTopToBottom( fustrum, callback );
    }
    if ( Right ) {
        
        Right->QueryTopToBottom( fustrum, callback );
    }
}

void GAMEPLAY_COMPONENT_AABB_NODE::QueryBottomToTop( const GRAPHIC_CAMERA_FUSTRUM & fustrum, CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback ) {
    
    if ( Left ) {
        
        Left->QueryBottomToTop( fustrum, callback );
    }
    if ( Right ) {
        
        Right->QueryBottomToTop( fustrum, callback );
    }
    
    if ( Entity != NULL && fustrum.BoxInFrustum( Box ) ) {
        
        callback( this );
    }
}

void GAMEPLAY_COMPONENT_AABB_NODE::RenderFrontToBack( CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_AABB_NODE * > & callback ) {
    
    if ( ZOrderLeft ) {
        
        ZOrderLeft->RenderFrontToBack( callback );
        ZOrderLeft = NULL;
    }
    if ( Entity ) {
        
        callback( this );
    }
    if ( ZOrderRight ) {
        
        ZOrderRight->RenderFrontToBack( callback );
        ZOrderRight = NULL;
    }
}

void GAMEPLAY_COMPONENT_AABB_NODE::InsertFrontToBack( GAMEPLAY_COMPONENT_AABB_NODE * node ) {
    
    if ( ZOrderLeft == NULL ) {
        ZOrderLeft = node;
    }
    else if ( ( Box.GetPosition().Z() - Box.GetHalfDiagonal().Z() ) > ( node->Box.GetPosition().Z() - node->Box.GetHalfDiagonal().Z() ) ) {
        ZOrderLeft->InsertFrontToBack( node );
    }
    else if ( ZOrderRight == NULL ) {
        ZOrderRight = node;
    }
    else  {
        ZOrderRight->InsertFrontToBack( node );
    }
}

void GAMEPLAY_COMPONENT_AABB_NODE::InsertBackToFront( GAMEPLAY_COMPONENT_AABB_NODE * node ) {
    
    if ( Left == NULL ) {
        Left = node;
    }
    else if ( ( Box.GetPosition().Z() + Box.GetHalfDiagonal().Z() ) <= ( node->Box.GetPosition().Z() + node->Box.GetHalfDiagonal().Z() ) ) {
        Left->InsertBackToFront( node );
    }
    else if ( Right == NULL ) {
        Right = node;
    }
    else if ( Right == NULL ) {
        Right->InsertBackToFront( node );
    }
    else {
        abort();
    }
}
