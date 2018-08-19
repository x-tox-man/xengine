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
        
            CORE_MATH_VECTOR wp = /*renderer.GetCamera()->GetViewMatrix() * */ located->GetPosition();
            light->GetLight()->InternalLight.Point.Position[0] = wp.X();
            light->GetLight()->InternalLight.Point.Position[1] = wp.Y();
            light->GetLight()->InternalLight.Point.Position[2] = wp.Z();
            light->GetLight()->InternalLight.Point.Position[3] = 1.0f;
            
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
