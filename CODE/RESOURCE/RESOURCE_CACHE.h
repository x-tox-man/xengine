//
//  RESOURCE_CACHE.hpp
//  GAME-ENGINE
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
#include "CORE_DATA_STREAM.h"

template < typename __RESOURCE_TYPE__, typename __RESOURCE_LOADER__ >
class RESOURCE_CACHE {
    
private :
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, __RESOURCE_TYPE__ * > ItemMap;
    __RESOURCE_LOADER__ loader;
    
public:
    
    RESOURCE_CACHE() :
        ItemMap() {
        
    }
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, __RESOURCE_TYPE__ * > & GetItemMap() { return ItemMap; }
    
    typedef RESOURCE_CACHE< __RESOURCE_TYPE__, __RESOURCE_LOADER__ > LOCAL_RESOURCE_CACHETYPE;
    
    __RESOURCE_TYPE__ * ReloadResourceForKey( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        loader.ReloadResource( ItemMap[ identifier ] );
        
        return ItemMap[ identifier ];
    }
    
    __RESOURCE_TYPE__ * GetResourceForIdentifier( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        #if DEBUG
        if ( ItemMap.find( identifier ) == ItemMap.end() ) {
            
            return NULL;
        }
        #endif
        
        return ItemMap[ identifier ];
    }
    
    void SetResourceForIdentifier( __RESOURCE_TYPE__ * resource, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
        
        #if DEBUG
        if ( ItemMap.find( identifier ) != ItemMap.end() ) {
            
            CORE_RUNTIME_Abort();
        }
        #endif
        
        ItemMap[ identifier ] = resource;
    }
    
    __RESOURCE_TYPE__ * LoadResourceForPath( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_FILESYSTEM_PATH & path ) {
        
#if DEBUG
        assert( identifier != CORE_HELPERS_UNIQUE_IDENTIFIER::Empty );
#endif
        if ( ItemMap.find( identifier ) == ItemMap.end() ) {
            
            __RESOURCE_TYPE__ * rs = (__RESOURCE_TYPE__ *) loader.Load( path, identifier );
            
            if ( rs == NULL ) {
                return rs;
            }
            
            ItemMap[ identifier ] = rs;
            ItemMap[ identifier ]->SetIdentifier( identifier );
        }
        
        return ItemMap[ identifier ];
    }
    
    __RESOURCE_TYPE__ * LoadResourceFromStream( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_DATA_STREAM & stream ) {
        
        if ( ItemMap.find( identifier ) == ItemMap.end() ) {
            
            ItemMap[ identifier ] = (__RESOURCE_TYPE__ *) loader.Load( stream, identifier );
            ItemMap[ identifier ]->SetIdentifier( identifier );
        }
        
        return ItemMap[ identifier ];
    }
    
    void SaveResourceFromStream( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_DATA_STREAM & stream ) {
        auto rs = ItemMap[ identifier ];
        
        XS_CLASS_SERIALIZER< __RESOURCE_TYPE__, CORE_DATA_STREAM >::template Serialize<std::true_type>( "resource", rs, stream );
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
