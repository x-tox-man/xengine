//
//  GRAPHIC_PARTICLE_EMITER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 7/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_EMITER_hpp
#define GRAPHIC_PARTICLE_EMITER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MODIFIER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_PARTICLE_RENDERER.h"

class GRAPHIC_PARTICLE_EMITER_BASE_CLASS {
public:
    GRAPHIC_PARTICLE_EMITER_BASE_CLASS() {
        
    }
    
    virtual ~GRAPHIC_PARTICLE_EMITER_BASE_CLASS() = 0;
    
    void Initialize(float emition_rate, float particle_lifetime);
    virtual void Update(float time_step) {}
    virtual void Render(GRAPHIC_RENDERER & renderer) {}
};


template <typename PARTICLE_TYPE, typename EMITTER, typename PARTICLE_TYPE_ATTRIBUTE, size_t PARTICLE_ARRAY_SIZE>
class GRAPHIC_PARTICLE_EMITER : GRAPHIC_PARTICLE_EMITER_BASE_CLASS {
    
public :
    
    typedef GRAPHIC_PARTICLE_MODIFIER<PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > MODIFIER;
    
    GRAPHIC_PARTICLE_EMITER() :
        GRAPHIC_PARTICLE_EMITER_BASE_CLASS(),
        Position(),
        Velocity(),
        Effect( NULL ),
        EmitRate(0.0f),
        ParticleLifetime(0.0f),
        ModifierTable(),
        FirstIndex(0),
        LastIndex(0) {
        
    }
    
    virtual ~GRAPHIC_PARTICLE_EMITER() {
        
    }
    
    virtual void Initialize(int emition_rate, float particle_lifetime, GRAPHIC_SHADER_EFFECT * effect) {
        
        Effect = effect;
        
        EmitRate = emition_rate;
        ParticleLifetime = particle_lifetime;
        
        Renderer.Initialize( Effect );
    }
    
    virtual void Update(float time_step) {
        
        static float acc = 0.0f;
        typename std::vector< MODIFIER *>::iterator it = ModifierTable.begin();
        
        acc += EmitRate * time_step;
        int emit_count = (int)acc;
        acc -= emit_count;
        
        Emit( emit_count );
        
        while (it != ModifierTable.end() ) {
            
            (*it)->Apply( time_step, FirstIndex, LastIndex, ParticleTable, ParticleAttributeTable );
            
            ++it;
        }
    }
    
    virtual void Render(GRAPHIC_RENDERER & renderer) {
        
        Renderer.Render(ParticleTable, Effect, renderer, FirstIndex, LastIndex);
    }
    
    void AddModifier(MODIFIER & modifier) {
        
        ModifierTable.push_back( &modifier );
    }
    
    inline void SetPosition( const CORE_MATH_VECTOR & position ) { Position = position; }
    inline void SetVelocity( const CORE_MATH_VECTOR & velocity ) { Velocity = velocity; }
    
    inline const CORE_MATH_VECTOR & GetPosition() { return Position; }
    inline const CORE_MATH_VECTOR & GetVelocity() { return Velocity; }
    
    inline std::array< PARTICLE_TYPE, PARTICLE_ARRAY_SIZE > & GetParticleTable() { return ParticleTable; }
    inline std::array< PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > & GetParticleAttributeTable() { return ParticleAttributeTable; }
    
    inline GRAPHIC_PARTICLE_RENDERER<PARTICLE_TYPE, PARTICLE_ARRAY_SIZE> & GetRenderer() { return Renderer; }
    
private:
    
    std::array< PARTICLE_TYPE, PARTICLE_ARRAY_SIZE > ParticleTable;
    std::array< PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > ParticleAttributeTable;
    
    void Emit( int emit_count ) {
        
        int temp = PARTICLE_ARRAY_SIZE - LastIndex - emit_count;
        
        if(  emit_count == 0 ) {
            
            return;
        }
        
        // we are after segment's end so emit at the end then emit from the start
        if( temp > 0 ) {
            
            EMITTER::InternalEmit( *this, LastIndex, LastIndex + emit_count);
            
            LastIndex += emit_count;
        }
        else if( temp <= 0){
            
            LastIndex = 0;
        }
        
        if ( FirstIndex >= PARTICLE_ARRAY_SIZE - 1) {
            FirstIndex = 0;
        }
    }
    
    GRAPHIC_SHADER_EFFECT
        * Effect;
    int
        EmitRate,
        FirstIndex,
        LastIndex;
    float
        ParticleLifetime;
    std::vector< MODIFIER * >
        ModifierTable;
    CORE_MATH_VECTOR
        Position,
        Velocity;
    GRAPHIC_PARTICLE_RENDERER<PARTICLE_TYPE, PARTICLE_ARRAY_SIZE>
        Renderer;
};



#endif /* GRAPHIC_PARTICLE_EMITER_hpp */
