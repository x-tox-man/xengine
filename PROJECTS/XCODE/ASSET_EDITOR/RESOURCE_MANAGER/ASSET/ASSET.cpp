//
//  ASSET.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "ASSET.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( ASSET )
    XS_DEFINE_ClassMember(CORE_FILESYSTEM_PATH, Path)
    XS_DEFINE_ClassMember(ASSET_TYPE, Type)
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( ASSET, CORE_FILESYSTEM_PATH )

ASSET::ASSET() :
    Path(),
    Type() {
    
}

ASSET::ASSET( const ASSET & other) :
    Path(other.Path),
    Type(other.Type){

}

ASSET & ASSET::operator =( const ASSET & other) {
    
    Path = other.Path;
    Type = other.Type;
    
    return *this;
}

bool operator < ( const ASSET & left, const ASSET & right ) {
    
    return strcmp( left.Path.GetPath(), right.Path.GetPath());
}
