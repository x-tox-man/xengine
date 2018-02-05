//
//  RESOURCES.hpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef RESOURCES_hpp
#define RESOURCES_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "RESOURCE_CONTAINER.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_SHADER_BIND.h"
XS_CLASS_BEGIN( R3D_RESOURCES )

    XS_DEFINE_UNIQUE( R3D_RESOURCES )

    void Initialize();
    void Finalize();

    void LoadCommon();

    void LoadPackage( const CORE_FILESYSTEM_PATH & path );
    void UnloadPackage();

    RESOURCE_PROXY::PTR FindResourceProxy( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );

    RESOURCE_PROXY::PTR CreateEffect( const char * name, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const GRAPHIC_SHADER_BIND & bind );
    RESOURCE_PROXY::PTR CreateModel( const char * name, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
private:

    void AddResource( RESOURCE_PROXY::PTR & resource, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    RESOURCE_CONTAINER::PTR
        Resources;

XS_CLASS_END

#endif /* RESOURCES_hpp */
