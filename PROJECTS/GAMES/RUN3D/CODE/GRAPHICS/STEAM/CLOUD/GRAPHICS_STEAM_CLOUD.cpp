//
//  GRAPHICS_STEAM_CLOUD.cpp
//  Run3d
//
//  Created by Christophe Bernard on 27/03/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "GRAPHICS_STEAM_CLOUD.h"

GRAPHICS_STEAM_CLOUD::GRAPHICS_STEAM_CLOUD() :
    Emiter( NULL ) {
    
    GRAPHIC_PARTICLE_MANAGER * manager = new GRAPHIC_PARTICLE_MANAGER();
    Emiter = new GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_CLOUD, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL( "smoke" );
    
    auto effect = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ) )->GetResource< GRAPHIC_SHADER_EFFECT >();
    
    effect->SetMaterial( material );
    
    Emiter->Initialize(10, 5.0f, effect );
    
    GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_v = new GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_g = new GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>( 0.1f);
    
    Emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_g) );
    Emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_v) );
    Emiter->SetVelocity( CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ) );
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[0] = 100.0f;
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[1] = 100.0f;
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[2] = 0.0f;
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[3] = 0.0f;
    
    manager->AddEmiter(*((GRAPHIC_PARTICLE_EMITER_BASE_CLASS *) Emiter));
    
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().AddManager( *manager );
}

GRAPHICS_STEAM_CLOUD::~GRAPHICS_STEAM_CLOUD() {
    
}

void GRAPHICS_STEAM_CLOUD::Initialize() {
    
}

void GRAPHICS_STEAM_CLOUD::Update( float step ) {
    
    for(int i = 0; i < Emiter->GetParticleTable().size(); i++ ) {
        
        Emiter->GetParticleTable()[i].Life += step;
        
        if ( Emiter->GetParticleTable()[i].Life > 10.0f) {
            Emiter->GetParticleTable()[i].Life = 0.0f;
        }
        Emiter->GetParticleTable()[i].Orientation.X( Emiter->GetParticleTable()[i].Life );
    }
}

void GRAPHICS_STEAM_CLOUD::InternalEmit( GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_CLOUD, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> & emiter,
                                         int start,
                                         int end ) {
    
    for(int i = start; i < end; i++ ) {
        
        emiter.GetParticleTable()[i].Position = CORE_MATH_VECTOR( (5-(rand() % 10)) * 10.0f, 9.0f, (5-(rand() % 10)) * 10.0f );
        emiter.GetParticleTable()[i].Life = (1.0f + (5.0 - (rand() % 10)) * 0.1) * 10.0f;
        emiter.GetParticleTable()[i].Orientation.X( emiter.GetParticleTable()[i].Life );
        
        emiter.GetParticleAttributeTable()[i].Velocity.Set( -emiter.GetParticleTable()[i].Position[0] * 0.1f, 0.0, -emiter.GetParticleTable()[i].Position[2] * 0.1f, 1.0f);
        
        emiter.GetParticleAttributeTable()[i].Modulator = 1.0f;
        emiter.GetParticleAttributeTable()[i].Lifetime = 5.0f;
    }
}
