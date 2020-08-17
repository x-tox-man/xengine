//
//  GAMEPLAY_COMPONENT_ENTITY.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__

#define GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS 8
#define GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS 8

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"
#include "CORE_MATH_VECTOR.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "CORE_MATH_QUATERNION.h"

class GAMEPLAY_COMPONENT_POSITION;
class GAMEPLAY_COMPONENT_RENDER;
class GAMEPLAY_COMPONENT_PHYSICS;
class GAMEPLAY_COMPONENT_ANIMATION;
class GAMEPLAY_COMPONENT_ACTION;
class GAMEPLAY_COMPONENT_MANAGER;
class GAMEPLAY_COMPONENT_LIGHT;
class GAMEPLAY_COMPONENT_CAMERA;
class GAMEPLAY_COMPONENT_SCRIPT;

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_ENTITY )

    //XS_DEFINE_SERIALIZABLE

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT_ENTITY );

    GAMEPLAY_COMPONENT_ENTITY() :
        Handle(),
        ParentHandle(),
        //Childs(),
        ComponentCount( 0 ) {
        
    }

    virtual ~GAMEPLAY_COMPONENT_ENTITY() {
        
    }

    template<typename COMPONENT_TYPE>
    COMPONENT_TYPE * GetComponent() {
        
        int offset = GetComponentOffset( COMPONENT_TYPE::ComponentType );
        return offset == -1 ? NULL : (COMPONENT_TYPE *) ( ( ( int * ) this ) + offset);
    }

    template<typename COMPONENT_TYPE>
    COMPONENT_TYPE * GetComponent( int component_index_type ) {
        
        int offset = GetComponentOffset( component_index_type );
        return offset == -1 ? NULL : (COMPONENT_TYPE *) ( ( ( int * ) this ) + offset);
    }

    void SetCompononent( GAMEPLAY_COMPONENT * component, int component_type ) {
        
        CORE_RUNTIME_Abort();
        //Components[ component_index ] = component;
    }

    inline void SetChild( GAMEPLAY_COMPONENT_ENTITY * entity, GAMEPLAY_COMPONENT_ENTITY_HANDLE handle ) {
        
        /*Childs[ handle ] = entity;
        entity->SetParent( this );*/
        
        CORE_RUNTIME_Abort(); // TODO in parentchild system
    }

    void Reset();

public:

    inline int GetComponentOffset( int component_type ) {
        
        GAMEPLAY_COMPONENT_HOLDER * cmp = NULL;
        
        cmp = ((GAMEPLAY_COMPONENT_HOLDER*)( this + 1 ));
        
        for ( int i = 1; i <= ComponentCount; i++ ) {
            
            if ( cmp->Type == component_type ) {
                
                return cmp->Offset;
            }
            
            ++cmp;
        }
        
        return -1;
    }

    void SetComponentHolderOffset( int component_type, int offset ) {
        
        GAMEPLAY_COMPONENT_HOLDER * cmp = NULL;
        
        cmp = ((GAMEPLAY_COMPONENT_HOLDER*)( this + 1 ));
        
        for ( int i = 1; i <= ComponentCount; i++ ) {
            
            if ( cmp->Type == component_type ) {
                
                cmp->Offset = offset;
                break;
            }
            
            ++cmp;
        }
    }

    //inline GAMEPLAY_COMPONENT_ENTITY * GetChild( GAMEPLAY_COMPONENT_ENTITY_HANDLE & child ) { return Childs[ child ]; }
    //inline std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY::PTR > & GetChilds() { return Childs; }

    void SetPosition( const CORE_MATH_VECTOR & position );
    void SetPositionOffset( const CORE_MATH_VECTOR & offset );
    void SetOrientation( const CORE_MATH_QUATERNION & orientation );
    void Scale( float scale );
    void Resize( const CORE_MATH_VECTOR & size );

    inline GAMEPLAY_COMPONENT_ENTITY_HANDLE GetParentHandle() const { return ParentHandle; }
    inline void SetParentHandle( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & parent ) { ParentHandle = parent; }

    virtual void CollidesWith( GAMEPLAY_COMPONENT_ENTITY * other );

    friend class GAMEPLAY_COMPONENT_MANAGER;
    friend class GAMEPLAY_COMPONENT_SYSTEM_CHUNK;

    inline GAMEPLAY_COMPONENT_ENTITY_HANDLE & GetHandle() { return Handle; }
    inline void SetComponentCount( uint8_t component_count ) { ComponentCount = component_count; }
    inline uint8_t GetComponentCount() const { return ComponentCount; }

private:

    GAMEPLAY_COMPONENT_ENTITY( uint8_t component_count ) :
        Handle(),
        ParentHandle(),
        //Childs(),
        ComponentCount( component_count ) {
        
    }

    GAMEPLAY_COMPONENT_ENTITY_HANDLE
        Handle,
        ParentHandle;
    //TODO: Fixed Child array || create a childs system maybe see with Parent.
    //std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY::PTR >
        //Childs;
    uint8_t
        ComponentCount;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ENTITY__) */
