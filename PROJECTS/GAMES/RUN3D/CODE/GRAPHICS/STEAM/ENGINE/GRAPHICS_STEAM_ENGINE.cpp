//
//  GRAPHICS_STEAM_ENGINE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 15/10/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "GRAPHICS_STEAM_ENGINE.h"

/*GRAPHICS_STEAM_ENGINE::GRAPHICS_STEAM_ENGINE() :

    Emiter( NULL ) {
    
    GRAPHIC_PARTICLE_MANAGER * manager = new GRAPHIC_PARTICLE_MANAGER();
    Emiter = new GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_ENGINE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL( "smoke" );
    
    auto effect = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ) )->GetResource< GRAPHIC_SHADER_EFFECT >();

    effect->BindAttribute( Emiter->GetRenderer().GetScaleFactorAttribute(), CORE_HELPERS_IDENTIFIER( "ScaleFactor" ) );
    effect->SetMaterial( material );
    
    Emiter->Initialize(400, 5.0f, effect );
    
    GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_v = new GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>();
    
    GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> * mod_g = new GRAPHIC_PARTICLE_MODIFIER_GRAVITY< GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE>( 0.1f);
    
    Emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_g) );
    Emiter->AddModifier( *((GRAPHIC_PARTICLE_MODIFIER<GRAPHIC_PARTICLE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> *) mod_v) );
    Emiter->SetVelocity( CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ) );
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[0] = 0.0f;
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[1] = 10.0f;
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[2] = -5.0f;
    Emiter->GetRenderer().GetScaleFactorAttribute().AttributeValue.Value.FloatArray4[3] = 0.0f;

    manager->AddEmiter(*((GRAPHIC_PARTICLE_EMITER_BASE_CLASS *) Emiter));
    
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().AddManager( *manager );
}

GRAPHICS_STEAM_ENGINE::~GRAPHICS_STEAM_ENGINE() {
    
}

void GRAPHICS_STEAM_ENGINE::Initialize() {
    
}

void GRAPHICS_STEAM_ENGINE::Update( float step ) {
    
    for(int i = 0; i < Emiter->GetParticleTable().size(); i++ ) {
        
        Emiter->GetParticleTable()[i].Life += step;
        
        if ( Emiter->GetParticleTable()[i].Life > 10.0f) {
            Emiter->GetParticleTable()[i].Life = 0.0f;
        }
        //Emiter->GetParticleTable()[i].Orientation.X( Emiter->GetParticleTable()[i].Life );
    }
}

void GRAPHICS_STEAM_ENGINE::InternalEmit( GRAPHIC_PARTICLE_EMITER<GRAPHIC_PARTICLE, GRAPHICS_STEAM_ENGINE, GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES, PARTICLE_SIZE> & emiter,
                                         int start,
                                         int end ) {
    
    for(int i = start; i < end; i++ ) {
        
        emiter.GetParticleTable()[i].Position = emiter.GetPosition();
        emiter.GetParticleTable()[i].Life = 0.0f;
        
        //emiter.GetParticleAttributeTable()[i].Velocity.Set( -emiter.GetVelocity().X() + (500-(rand() % 1000)) * 0.0001f , -emiter.GetVelocity().Y() + (500-(rand() % 1000)) * 0.0001f, emiter.GetVelocity().Z()*0.001f, 1.0f);
        emiter.GetParticleAttributeTable()[i].Velocity.Set( emiter.GetVelocity().X(), emiter.GetVelocity().Y(), emiter.GetVelocity().Z() - 0.001f, 1.0f);
        
        emiter.GetParticleAttributeTable()[i].Modulator = 1.0f;
        emiter.GetParticleAttributeTable()[i].Lifetime = 5.0f;
    }
}
 */

