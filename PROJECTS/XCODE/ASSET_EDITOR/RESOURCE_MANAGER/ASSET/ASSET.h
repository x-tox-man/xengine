//
//  ASSET.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef ASSET_hpp
#define ASSET_hpp

#include "CORE_FILESYSTEM_PATH.h"
#include "ASSET_TYPE.h"

XS_CLASS_BEGIN_WITH_COPY(ASSET)

    XS_DEFINE_SERIALIZABLE

    ASSET();

    ASSET & operator =( const ASSET & other);

    friend bool operator < ( const ASSET & left, const ASSET & right );

private:

    CORE_FILESYSTEM_PATH
        Path;
    ASSET_TYPE
        Type;
    
XS_CLASS_END

bool operator < ( const ASSET & left, const ASSET & right );

#endif /* ASSET_hpp */
