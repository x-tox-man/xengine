//
//  GAMEPLAY_COMPONENT_MANAGER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "CORE_HELPERS_UNIQUE.h"

class GAMEPLAY_COMPONENT_BASE_ENTITY;

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_MANAGER )

    XS_DEFINE_UNIQUE( GAMEPLAY_COMPONENT_MANAGER )

    ~GAMEPLAY_COMPONENT_MANAGER();

    void Initialize();

    template <typename __ENTITY_TARGET_TYPE__>
    __ENTITY_TARGET_TYPE__ * CreateEntity() {
        
        int index = (int) InternalVector.size();
        
        if( index == 0) {
            
            if ( InternalVector.size() != 16 ) {
                
                InternalVector.resize(16);
            }
            
            InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_ENTITY * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_ENTITY ) );
            InternalVector[0].LastIndex = 0;
        }
        
        int size = sizeof( __ENTITY_TARGET_TYPE__ ) - sizeof( GAMEPLAY_COMPONENT_ENTITY );
        
#if DEBUG
        if ((size / sizeof( GAMEPLAY_COMPONENT_ENTITY ) ) > 2048 - InternalVector[0].LastIndex - 1) {
            abort();
        }
#endif
        
        __ENTITY_TARGET_TYPE__ * en = (__ENTITY_TARGET_TYPE__ *) new (InternalVector[ 0 ].MemoryArray + ( ++InternalVector[ 0 ].LastIndex ) ) __ENTITY_TARGET_TYPE__();
        
        while( size > 0 ) {
            
            InternalVector[ 0 ].LastIndex++;
            size -= sizeof( GAMEPLAY_COMPONENT_ENTITY );
        }
        
        en->GetHandle().SetIndex( InternalVector[ 0 ].LastIndex );
        en->GetHandle().SetOffset( 0 );
        
        return en;
    }

    template <typename __ENTITY_TYPE__>
    GAMEPLAY_COMPONENT_ENTITY * CloneEntity( __ENTITY_TYPE__ * entity ) {
        
        auto ent = ( GAMEPLAY_COMPONENT_ENTITY * ) CreateEntity< __ENTITY_TYPE__ >();
        
        for (int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS; i++) {
            
            if ( entity->GetComponent( i ) != NULL ) {
                
                const GAMEPLAY_COMPONENT_HANDLE & handle = entity->GetComponentHandle( i );
                
                ent->SetCompononent( handle.Clone(), i );
            }
        }
        
        for (int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++) {
            
            if ( entity->GetChild( i ) != NULL ) {
                
                ent->SetChild( entity->GetChild( i )->Clone(), i);
            }
        }
        
        return ent;
    }

    inline GAMEPLAY_COMPONENT_ENTITY * GetEntity( int index ) {
        
        if ( index > InternalVector[ 0 ].LastIndex ) {
            return NULL;
        }
        
        return &InternalVector[0].MemoryArray[ index ];
    }

    void Clear();

    void SaveToStream( CORE_DATA_STREAM & stream );
    void LoadFromStream( CORE_DATA_STREAM & stream );

    inline GAMEPLAY_COMPONENT_ENTITY * FindEntity( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle ) {
    
        return &InternalVector[ handle.GetOffset() ].MemoryArray[ handle.GetIndex() -1 ]; //Fix this minus One that hangs around
    }

private :

    struct INTERNAL_ARRAY{
        int LastIndex;
        GAMEPLAY_COMPONENT_ENTITY * MemoryArray;
    };

    std::vector< INTERNAL_ARRAY >
        InternalVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__) */
