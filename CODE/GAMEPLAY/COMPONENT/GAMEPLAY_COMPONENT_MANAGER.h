//
//  GAMEPLAY_COMPONENT_MANAGER.h
//  GAME-ENGINE
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
#include "CORE_DATA_STREAM.h"

class GAMEPLAY_COMPONENT_BASE_ENTITY;

#define ONE_COMPONENT_SIZE 64
#define ECS_SIZE ( 8 * 1024 ) // 8 Kb of cache TODO : tweak
#define ECS_ITEMS ( ECS_SIZE / ONE_COMPONENT_SIZE )
#define ECS_ITEMS_INDEX ( ECS_ITEMS / sizeof( int ) )

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_MANAGER )

    XS_DEFINE_UNIQUE( GAMEPLAY_COMPONENT_MANAGER )
    //XS_DEFINE_SERIALIZABLE

    ~GAMEPLAY_COMPONENT_MANAGER();

    void Initialize();
    void Finalize();

    void RemoveEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
        
        InvalidHandleTable.push_back( entity->GetHandle() );
    }

    inline GAMEPLAY_COMPONENT_ENTITY::PTR GetEntity( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle ) {
        
        return ( GAMEPLAY_COMPONENT_ENTITY * ) ( ( ( int * ) ECSData.GetMemoryBuffer() ) + handle.GetOffset() );
    }

    template< typename ... COMPONENT_TYPES >
    GAMEPLAY_COMPONENT_ENTITY::PTR CreateEntityWithComponents() {
        
        // using placement new
        auto entity = new (((int *) ECSData.GetMemoryBuffer() + Offset)) GAMEPLAY_COMPONENT_ENTITY( sizeof...( COMPONENT_TYPES ) );
        
        int base_offset = Offset;
        
        entity->GetHandle().SetOffset( Offset );
        Offset += sizeof( GAMEPLAY_COMPONENT_ENTITY ) / sizeof( int );
        
        (CreateComponentHolders< COMPONENT_TYPES >(), ...);
        (CreateComponents< COMPONENT_TYPES >( base_offset, entity ), ...);
        
        entity->GetHandle().SetSize( Offset - base_offset);
        
        return entity;
    }

    GAMEPLAY_COMPONENT_ENTITY::PTR Clone( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
        
        //auto clone = new (((int*)ECSData.GetMemoryBuffer() + Offset)) GAMEPLAY_COMPONENT_ENTITY( entity->GetHandle().GetSize() );
        int * adr1 = (((int *) ECSData.GetMemoryBuffer()) + Offset);
        int * adr2 =(((int *) ECSData.GetMemoryBuffer()) +  entity->GetHandle().GetOffset());
        memcpy( adr1, adr2,entity->GetHandle().GetSize() * 4);
        
        auto clone = (GAMEPLAY_COMPONENT_ENTITY * ) ((int *) ECSData.GetMemoryBuffer() + Offset);
        clone->SetComponentCount( entity->GetComponentCount() );
        clone->GetHandle().SetOffset( Offset );
        clone->GetHandle().SetSize( entity->GetHandle().GetSize() );
        //clone->Reset();
        Offset += entity->GetHandle().GetSize();
        
        return clone;
    }

    /*template< typename COMPONENT_TYPE >
    GAMEPLAY_COMPONENT_ENTITY::PTR AddComponentToEntity() {
        
        // using placement new
        auto entity =
        
        return entity;
    }*/

    void Clear();

    void SaveToStream( CORE_DATA_STREAM & stream );
    void LoadFromStream( CORE_DATA_STREAM & stream );

    inline GAMEPLAY_COMPONENT_ENTITY * FindEntity( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle ) {
    
        return GetEntity( handle );
    }

    inline void * GetEcsBasePointer() {
        
        return ECSData.GetMemoryBuffer();
    }

private :

    template< typename H >
    void CreateComponentHolders() {
        
        auto cmp = new (((int *) ECSData.GetMemoryBuffer()) + Offset) GAMEPLAY_COMPONENT_HOLDER( H::ComponentType, Offset );
        Offset += sizeof( GAMEPLAY_COMPONENT_HOLDER ) / sizeof( int );
    }

    template< typename H >
    void CreateComponents( int base_offset, GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
        
        auto cmp = new (((int *) ECSData.GetMemoryBuffer()) + Offset) H();
        entity->SetComponentHolderOffset( H::ComponentType, Offset - base_offset );
        Offset += sizeof( H ) / sizeof( int );
    }

    CORE_DATA_STREAM
        ECSData;
    unsigned int
        Offset;
    std::map< CORE_HELPERS_IDENTIFIER, GAMEPLAY_COMPONENT_ENTITY_HANDLE >
        NamedEntitiesTable;
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >
        InvalidHandleTable;
    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_HANDLE >
        EntitiesChildsTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__) */
