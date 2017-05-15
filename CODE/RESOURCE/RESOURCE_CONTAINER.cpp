//
//  RESOURCE_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_CONTAINER.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_LOADER.h"
#include "RESOURCE.h"

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT(RESOURCE_PROXY, CORE_HELPERS_UNIQUE_IDENTIFIER)

typedef std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, RESOURCE_PROXY > RESOURCE_MAP_TYPE;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( RESOURCE_CONTAINER )
    XS_DEFINE_ClassMember( RESOURCE_MAP_TYPE , ResourceMap )
XS_END_INTERNAL_MEMORY_LAYOUT

RESOURCE_CONTAINER::RESOURCE_CONTAINER() :
    RESOURCE_PROXY() {
    
}

RESOURCE_CONTAINER::~RESOURCE_CONTAINER() {
    
}

void RESOURCE_CONTAINER::Load( const CORE_FILESYSTEM_PATH & path ) {
    
    CORE_DATA_STREAM
        stream;
    
    if ( CORE_DATA_LOADER< RESOURCE_CONTAINER >::Load(this, path, stream ) ) {
        
        std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, RESOURCE_PROXY >::iterator it = ResourceMap.begin();
        
        while (it != ResourceMap.end() ) {
            
            auto resource = BASE_RESOURCE::FactoryCreate( it->second.GetType() );
            resource->Load( it->first, stream );
            
            delete resource;
            
            it++;
        }
        
        stream.Close();
    }
}
