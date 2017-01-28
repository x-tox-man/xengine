//
//  GRAPHIC_PARTICLE_EMITER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 7/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_EMITER_hpp
#define GRAPHIC_PARTICLE_EMITER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MODIFIER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_MATERIAL.h"
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

template <typename PARTICLE_TYPE, typename PARTICLE_TYPE_ATTRIBUTE, size_t PARTICLE_ARRAY_SIZE>
class GRAPHIC_PARTICLE_EMITER : GRAPHIC_PARTICLE_EMITER_BASE_CLASS {
    
public :
    
    typedef GRAPHIC_PARTICLE_MODIFIER<PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > MODIFIER;
    GRAPHIC_PARTICLE_EMITER() :
        GRAPHIC_PARTICLE_EMITER_BASE_CLASS(),
        Material(),
        EmitRate(0.0f),
        ParticleLifetime(0.0f),
        ModifierTable(),
        FirstIndex(0),
        LastIndex(0) {
        
    }
    
    virtual ~GRAPHIC_PARTICLE_EMITER() {
        
    }
    
    virtual void Initialize(int emition_rate, float particle_lifetime, GRAPHIC_MATERIAL * material) {
        
        Material = material;
        
        EmitRate = emition_rate;
        ParticleLifetime = particle_lifetime;
        
        Renderer.Initialize( *Material );
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
        
        Renderer.Render(ParticleTable, *Material, renderer);
    }
    
    void InternalEmit( int start, int end ) {
        
        for(int i = start; i <= end; i++ ) {
            ParticleTable[i].Position.Set(10.0f, 10.0f, 0.0f, 1.0f);
            
            ParticleAttributeTable[i].Velocity.Set((rand() % 100 - 50) * 0.5f , 10.0f, (rand() % 100 - 50) * 0.5f, 1.0f);
            ParticleAttributeTable[i].Modulator = 1.0f;
            ParticleAttributeTable[i].Lifetime = 5.0f;
        }
    }
    
    void AddModifier(MODIFIER & modifier) {
        
        ModifierTable.push_back( &modifier );
    }
    
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
            
            InternalEmit( LastIndex, LastIndex + emit_count);
            
            LastIndex += emit_count;
        }
        else if( temp <= 0){
            int emit_at_end = emit_count + temp;
            int emit_at_start = emit_count - emit_at_end;
            
            InternalEmit( LastIndex, emit_at_end);
            InternalEmit( 0, emit_at_start);
            
            LastIndex = emit_at_start;
            FirstIndex = LastIndex + 1;
        }
        
        if ( FirstIndex == PARTICLE_ARRAY_SIZE - 1) {
            FirstIndex = 0;
        }
    }
    
    GRAPHIC_MATERIAL * Material;
    
    int EmitRate;
    float ParticleLifetime;
    int FirstIndex;
    int LastIndex;
    
    std::vector< MODIFIER * > ModifierTable;
    GRAPHIC_PARTICLE_RENDERER<PARTICLE_TYPE, PARTICLE_ARRAY_SIZE> Renderer;
};



#endif /* GRAPHIC_PARTICLE_EMITER_hpp */
