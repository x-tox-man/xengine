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
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"


#if PLATFORM_OSX && DEBUG

template<>
void RESOURCE_CACHE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER>::SetupCache( GRAPHIC_SHADER_EFFECT * effect, const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    CORE_HELPERS_CALLBACK *callback = new CORE_HELPERS_CALLBACK( &Wrapper< RESOURCE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER> , &RESOURCE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER>::Reload>, (void *) effect );
    
    ItemMap[ identifier ] = effect;
    
    int l = (int) strlen( path.GetPath() );
    
    char vsh_path[128];
    
    strncpy(vsh_path, path.GetPath(), l);
    vsh_path[l] = '\0';
    vsh_path[strlen(vsh_path) - 3 ] ='f';
    vsh_path[strlen(vsh_path) - 2 ] ='s';
    vsh_path[strlen(vsh_path) - 1 ] ='h';
    
    effect->Watcher.Setup( vsh_path, *callback );
    
    delete( callback );
}

template<>
GRAPHIC_SHADER_EFFECT * RESOURCE_CACHE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER>::LoadResourceForPath( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_FILESYSTEM_PATH & path, int resource_load_flag ) {
    
    if ( ItemMap.find( identifier ) == ItemMap.end() ) {
        
        ItemMap[ identifier ] = (GRAPHIC_SHADER_EFFECT *) loader.Load( path, resource_load_flag, identifier );
        ItemMap[ identifier ]->SetPath( path );
        ItemMap[ identifier ]->SetIdentifier( identifier );
        
        RESOURCE_CACHE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER>::SetupCache( ItemMap[ identifier ], path, identifier );
    }
    
    return ItemMap[ identifier ];
}

#endif
