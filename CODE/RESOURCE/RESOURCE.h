//
//  RESOURCE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE__
#define __GAME_ENGINE_REBORN__RESOURCE__

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_TYPE.h"
#include "CORE_HELPERS_FACTORY.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "RESOURCE_CACHE.h"
#include "CORE_FILESYSTEM_FILE_WATCHER.h"
#include "CORE_HELPERS_FACTORY.h"

class BASE_RESOURCE {
    
public:
    
    BASE_RESOURCE() {
        
    }
    
    virtual ~BASE_RESOURCE() {
        
    }
    
    virtual void Load( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_DATA_STREAM & stream ) {}
    virtual void Save( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_DATA_STREAM & stream ) {}
    
    inline const CORE_HELPERS_UNIQUE_IDENTIFIER & GetIdentifier() const { return Identifier; }
    inline void SetIdentifier( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) { Identifier = identifier; }
    
    CORE_HELPERS_FACTORY_Define( BASE_RESOURCE, RESOURCE_TYPE );
    
protected :
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        Identifier;
};

template <typename __CHILD_RESOURCE_TYPE__, typename __CHILD_RESOURCE_LOADER_TYPE__ >
class RESOURCE : public BASE_RESOURCE {

public:
    
    RESOURCE()
    #if DEBUG
    : Watcher()
    #endif
    {
        
    }
    
    virtual ~RESOURCE() {
        
    }
    
    virtual void Load( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_DATA_STREAM & stream ) override {
        
        ResourceCache->LoadResourceFromStream( identifier, stream );
    }
    
    virtual void Save( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_DATA_STREAM & stream ) override {
    
        ResourceCache->SaveResourceFromStream( identifier, stream );
    }
    
    DEFINE_SGet( CORE_FILESYSTEM_PATH, Path );
    
    static RESOURCE_CACHE< __CHILD_RESOURCE_TYPE__, __CHILD_RESOURCE_LOADER_TYPE__ > * ResourceCache;
    
    static RESOURCE_CACHE< __CHILD_RESOURCE_TYPE__, __CHILD_RESOURCE_LOADER_TYPE__ > * GetResourceCache() { return ResourceCache; }
    
    static __CHILD_RESOURCE_TYPE__ * LoadResourceForPath( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_FILESYSTEM_PATH & path ) {
        
        return ResourceCache->LoadResourceForPath( identifier, path );
    }
    
    static __CHILD_RESOURCE_TYPE__ * GetResourceForIdentifier( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        return ResourceCache->GetResourceForIdentifier( identifier );
    }
    
    static void SetResourceForIdentifier( __CHILD_RESOURCE_TYPE__ * resource, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        return ResourceCache->SetResourceForIdentifier( resource, identifier );
    }
    
    void LoadResource( CORE_DATA_STREAM & stream ) {
        
        __CHILD_RESOURCE_TYPE__::LoadResource( stream );
    }
    
    static void FlushCache() {
        
        ResourceCache->FlushCache();
    }
    
    static __CHILD_RESOURCE_TYPE__ * ReloadResourceForKey( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        return ResourceCache->ReloadResource( identifier );
    }
    
public :
    
    #if DEBUG
    
        CORE_FILESYSTEM_FILE_WATCHER Watcher;
    
        void Reload() {
            
            ResourceCache->ReloadResourceForKey( Identifier );
        }
    #endif
};

template <typename __CHILD_RESOURCE_TYPE__, typename __CHILD_RESOURCE_LOADER_TYPE__ >
RESOURCE_CACHE< __CHILD_RESOURCE_TYPE__, __CHILD_RESOURCE_LOADER_TYPE__ > * RESOURCE< __CHILD_RESOURCE_TYPE__, __CHILD_RESOURCE_LOADER_TYPE__ >::ResourceCache = new RESOURCE_CACHE< __CHILD_RESOURCE_TYPE__, __CHILD_RESOURCE_LOADER_TYPE__ >();


#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE__) */
