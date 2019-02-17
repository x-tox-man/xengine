//
//  GAMEPLAY_COMPONENT_SYSTEM_LIGHTING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_LIGHTING.h"

GAMEPLAY_COMPONENT_SYSTEM_LIGHTING::GAMEPLAY_COMPONENT_SYSTEM_LIGHTING() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_LIGHTING::~GAMEPLAY_COMPONENT_SYSTEM_LIGHTING() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_LIGHTING::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_LIGHTING::Update( float time_step ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_LIGHTING::Render( GRAPHIC_RENDERER & renderer ) {
    
    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    
    renderer.GetSpotLightTable().clear();
    renderer.GetPointLightTable().clear();
    
    const GRAPHIC_CAMERA_FUSTRUM & fustrum = renderer.GetCamera()->GetFustrum();
    
    while (it != EntitiesTable.end() ) {
        
        GAMEPLAY_COMPONENT_ENTITY * entity = it->second->GetEntity();
        
        GAMEPLAY_COMPONENT_RENDER * renderable = (GAMEPLAY_COMPONENT_RENDER * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        GAMEPLAY_COMPONENT_POSITION * located = (GAMEPLAY_COMPONENT_POSITION * ) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        float d = renderable->GetObject().GetResource<GRAPHIC_OBJECT>()->GetMeshTable()[0]->GetBoundingShape().GetHalfDiagonal().X();
        
        //if ( fustrum.SphereInFrustum( located->GetPosition(), ( d > 0.0f) ? d : 1.0f ) ) {
        
            auto light = (GAMEPLAY_COMPONENT_LIGHT::PTR) it->second->GetComponent( GAMEPLAY_COMPONENT_TYPE_Light );
        
            GRAPHIC_OBJECT_RENDER_OPTIONS
                options,
                parent_options;
            CORE_MATH_MATRIX
                mvp,
                object_matrix;
            CORE_MATH_QUATERNION
                orientation;
        
            options.SetPosition( located->GetPosition() + located->GetPositionOffset() );
            options.SetOrientation(located->GetOrientation() );
            options.SetScaleFactor( CORE_MATH_VECTOR(1.0f, 1.0f,1.0f, 1.0f) );
        
            if ( entity->GetParent() != NULL ) {
                
                GAMEPLAY_COMPONENT_POSITION * parent_located = (GAMEPLAY_COMPONENT_POSITION * ) entity->GetParent()->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
                
                parent_options.SetPosition( parent_located->GetPosition() + parent_located->GetPositionOffset() );
                parent_options.SetOrientation( parent_located->GetOrientation() );
                parent_options.SetScaleFactor( CORE_MATH_VECTOR(1.0f, 1.0f,1.0f, 1.0f) );
                
                options.SetParent( &parent_options );
            }
        
            renderable->GetObject().GetResource<GRAPHIC_OBJECT>()->ComputeModelViewProjection(options, CORE_MATH_MATRIX(), renderer, mvp, object_matrix);
        
            //CORE_MATH_VECTOR wp = /*renderer.GetCamera()->GetViewMatrix() * */ located->GetPosition();

            switch (light->GetLight()->Type) {
                case GRAPHIC_SHADER_LIGHT_TYPE_Point:
                    light->GetLight()->InternalLight.Point.Position[0] = object_matrix[3];
                    light->GetLight()->InternalLight.Point.Position[1] = object_matrix[7];
                    light->GetLight()->InternalLight.Point.Position[2] = object_matrix[11];
                    light->GetLight()->InternalLight.Point.Position[3] = 1.0f;
                    
                    break;
                    
                case GRAPHIC_SHADER_LIGHT_TYPE_Spot:
                    light->GetLight()->InternalLight.Spot.Position[0] = object_matrix[3];
                    light->GetLight()->InternalLight.Spot.Position[1] = object_matrix[7];
                    light->GetLight()->InternalLight.Spot.Position[2] = object_matrix[11];
                    light->GetLight()->InternalLight.Spot.Position[3] = 1.0f;
                    
                    object_matrix[3] = 0.0f;
                    object_matrix[7] = 0.0f;
                    object_matrix[11] = 0.0f;
                    
                    orientation.FromMatrix( &object_matrix[0] );
                    orientation.Normalize();
                    
                    light->GetLight()->InternalLight.Spot.Orientation[0] = orientation.X();
                    light->GetLight()->InternalLight.Spot.Orientation[1] = orientation.Y();
                    light->GetLight()->InternalLight.Spot.Orientation[2] = orientation.Z();
                    light->GetLight()->InternalLight.Spot.Orientation[3] = orientation.W();
                    
                    break;
                    
                default:
                    abort();
                    break;
            }
        
            switch ( light->GetLight()->Type ) {
                case GRAPHIC_SHADER_LIGHT_TYPE_Point:
                    renderer.GetPointLightTable().push_back( light->GetLight() );
                    break;
                    
                case GRAPHIC_SHADER_LIGHT_TYPE_Spot:
                    renderer.GetSpotLightTable().push_back( light->GetLight() );
                    break;
                    
                default:
                    break;
            }
        //}
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_LIGHTING::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}
