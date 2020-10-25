//
//  GRAPHIC_MATERIAL_COLLECTION.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 9/07/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MATERIAL_COLLECTION_hpp
#define GRAPHIC_MATERIAL_COLLECTION_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_HELPERS_COLOR.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_MATERIAL.h"

class GRAPHIC_MATERIAL_COLLECTION_RESOURCE_LOADER;
class GRAPHIC_MATERIAL_COLLECTION;
class GRAPHIC_SHADER_PROGRAM_DATA_PROXY;

typedef RESOURCE< GRAPHIC_MATERIAL_COLLECTION, GRAPHIC_MATERIAL_COLLECTION_RESOURCE_LOADER > GR_MC_ANCESTOR_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GRAPHIC_MATERIAL_COLLECTION, GR_MC_ANCESTOR_TYPE )

    GRAPHIC_MATERIAL_COLLECTION();
    GRAPHIC_MATERIAL_COLLECTION( GRAPHIC_MATERIAL::PTR material );
    ~GRAPHIC_MATERIAL_COLLECTION();

CORE_HELPERS_FACTORY_Element( GRAPHIC_MATERIAL_COLLECTION, BASE_RESOURCE, RESOURCE_TYPE, RESOURCE_TYPE_MaterialCollection )

    XS_DEFINE_SERIALIZABLE

    void SetMaterialForName( GRAPHIC_MATERIAL::PTR material, const char * name );
    GRAPHIC_MATERIAL::PTR GetMaterialForName( const char * name );
    inline GRAPHIC_MATERIAL::PTR GetDefaultMaterial() { return MaterialTable.begin()->second; }
    inline std::map< std::string, GRAPHIC_MATERIAL::PTR > & GetMaterialTable() { return MaterialTable; }

    void Apply( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader, const char * material_name );

    void LoadMaterialForName( const char * name );

    void SetDiffuse( const CORE_HELPERS_COLOR & color );

private:

    std::map< std::string, GRAPHIC_MATERIAL::PTR >
        MaterialTable;

    static std::string DefaultMaterialName;

XS_CLASS_END

#endif /* GRAPHIC_MATERIAL_COLLECTION_hpp */
