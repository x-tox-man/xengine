//
//  TOOL_ASSET_COMPILER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 13/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef TOOL_ASSET_COMPILER_hpp
#define TOOL_ASSET_COMPILER_hpp

#include "CORE_HELPERS_CLASS.h"

class TOOL_ASSET_COMPILER {
    
public :
    TOOL_ASSET_COMPILER(const char * source_path, const char * destination_dir, const char * options);
    ~TOOL_ASSET_COMPILER();
    
private :
    
    TOOL_ASSET_COMPILER( const TOOL_ASSET_COMPILER & other );
    
    void operator = ( const TOOL_ASSET_COMPILER & other );
};

#endif /* TOOL_ASSET_COMPILER_hpp */
