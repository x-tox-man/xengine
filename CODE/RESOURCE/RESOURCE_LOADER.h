//
//  RESOURCE_LOADER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE_LOADER__
#define __GAME_ENGINE_REBORN__RESOURCE_LOADER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "RESOURCE.h"

template < typename __RESOURCE_TYPE__ >
class RESOURCE_LOADER {
    
public:
    RESOURCE_LOADER() {
        
    }
    
    virtual ~RESOURCE_LOADER() {
        
    }
    
    virtual __RESOURCE_TYPE__ * Load( const CORE_FILESYSTEM_PATH & file, int resource_load_flag = 0 ,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty ) { return NULL; }
    
    virtual __RESOURCE_TYPE__ * Load( CORE_DATA_STREAM & stream, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty) { return NULL; }
    
    virtual void ReloadResource( __RESOURCE_TYPE__ * resource_to_reload ) {};
    
    virtual void CompileResource( const CORE_FILESYSTEM_PATH & source_file, const CORE_FILESYSTEM_PATH & destination_file ) {}
};

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_LOADER__) */
