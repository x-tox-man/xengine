//
//  RESOURCE_CACHE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_CACHE.h"
#include "RESOURCE.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

#if PLATFORM_OSX && DEBUG
template<>
GRAPHIC_SHADER_EFFECT * RESOURCE_CACHE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER>::LoadResourceForPath( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_FILESYSTEM_PATH & path ) {
    
    if ( ItemMap.find( identifier ) == ItemMap.end() ) {
        
        ItemMap[ identifier ] = (GRAPHIC_SHADER_EFFECT *) loader.Load( path, identifier );
        ItemMap[ identifier ]->SetPath( path );
        ItemMap[ identifier ]->SetIdentifier( identifier );
        
        CORE_HELPERS_CALLBACK *callback = new CORE_HELPERS_CALLBACK( &Wrapper< RESOURCE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER> , &RESOURCE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER>::Reload>, (void *) ItemMap[ identifier ] );
        
        int l = (int) strlen( path.GetPath() );
        
        char * vsh_path = (char*) CORE_MEMORY_ALLOCATOR::Allocate ( l+1 );
        
        
        strncpy(vsh_path, path.GetPath(), l);
        vsh_path[l] = '\0';
        vsh_path[strlen(vsh_path) - 3 ] ='f';
        vsh_path[strlen(vsh_path) - 2 ] ='s';
        vsh_path[strlen(vsh_path) - 1 ] ='h';
        
        ItemMap[ identifier ]->Watcher.Setup( vsh_path, *callback );
        
        delete( callback );
        
        
        CORE_MEMORY_ALLOCATOR_Free( vsh_path );
    }
    
    return ItemMap[ identifier ];
}
#endif
