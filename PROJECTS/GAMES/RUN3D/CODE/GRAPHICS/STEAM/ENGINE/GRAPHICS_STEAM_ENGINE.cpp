//
//  GRAPHICS_STEAM_ENGINE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 15/10/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "GRAPHICS_STEAM_ENGINE.h"

GRAPHICS_STEAM_ENGINE::GRAPHICS_STEAM_ENGINE() :
    Emiter( NULL ) {
    
    GRAPHIC_PARTICLE_MANAGER * manager = new GRAPHIC_PARTICLE_MANAGER();
    Emiter = new GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_ENGINE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL( "smoke" );
    
    auto effect = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ) )->GetResource< GRAPHIC_SHADER_EFFECT >();
    
    effect->SetMaterial( material );
    
    Emiter->Initialize(400, 5.0f, effect );
    
    GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_v = new GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_g = new GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>( 1.81f);
    
    Emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_g) );
    Emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_v) );
    Emiter->SetVelocity( CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ) );
    
    manager->AddEmiter(*((GRAPHIC_PARTICLE_EMITER_BASE_CLASS *) Emiter));
    
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().AddManager( *manager );
}

GRAPHICS_STEAM_ENGINE::~GRAPHICS_STEAM_ENGINE() {
    
}

void GRAPHICS_STEAM_ENGINE::Initialize() {
    
}

void GRAPHICS_STEAM_ENGINE::InternalEmit( GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_ENGINE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> & emiter,
                                         int start,
                                         int end ) {
    
    for(int i = start; i < end; i++ ) {
        
        emiter.GetParticleTable()[i].Position = emiter.GetPosition();
        
        emiter.GetParticleAttributeTable()[i].Velocity.Set( emiter.GetVelocity().X() + (500-(rand() % 1000)) * 0.005f , emiter.GetVelocity().Y() + (500-(rand() % 1000)) * 0.005f, emiter.GetVelocity().Z() + (500-(rand() % 1000)) * 0.005f, 1.0f);
        
        emiter.GetParticleAttributeTable()[i].Modulator = 1.0f;
        emiter.GetParticleAttributeTable()[i].Lifetime = 5.0f;
    }
}

