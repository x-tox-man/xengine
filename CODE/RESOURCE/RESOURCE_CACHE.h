//
//  RESOURCE_CACHE.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef RESOURCE_CACHE_h
#define RESOURCE_CACHE_h

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_HELPERS_CALLBACK.h"

template < typename __RESOURCE_TYPE__, typename __RESOURCE_LOADER__ >
class RESOURCE_CACHE {
    
private :
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, __RESOURCE_TYPE__ * > ItemMap;
    __RESOURCE_LOADER__ loader;
    
public:
    
    RESOURCE_CACHE() :
        ItemMap() {
        
    }
    
    typedef RESOURCE_CACHE< __RESOURCE_TYPE__, __RESOURCE_LOADER__ > LOCAL_RESOURCE_CACHETYPE;
    
    __RESOURCE_TYPE__ * ReloadResourceForKey( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        loader.ReloadResource( ItemMap[ identifier ] );
        
        return ItemMap[ identifier ];
    }
    
    __RESOURCE_TYPE__ * GetResourceForIdentifier( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        if ( ItemMap.find( identifier ) != ItemMap.end() ) {
            
            CORE_RUNTIME_Abort();
        }
        
        return ItemMap[ identifier ];
    }
    
    __RESOURCE_TYPE__ * LoadResourceForPath( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_FILESYSTEM_PATH & path ) {
        
        if ( ItemMap.find( identifier ) == ItemMap.end() ) {
            
            ItemMap[ identifier ] = (__RESOURCE_TYPE__ *) loader.Load( path, identifier );
            ItemMap[ identifier ]->SetIdentifier( identifier );
        }
        
        return ItemMap[ identifier ];
    }
    
    void FlushCache( ) {
        
        typename std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, __RESOURCE_TYPE__ * >::iterator it;
        
        it = ItemMap.begin();
        
        while ( it!= ItemMap.end() ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( it->second );
            
            
            it++;
        }
        
        ItemMap.clear();
    }
};

#endif /* RESOURCE_CACHE_hpp */
