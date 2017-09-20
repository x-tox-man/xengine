//
//  GRAPHIC_MATERIAL_COLLECTION.hpp
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN( GRAPHIC_MATERIAL_COLLECTION )

    GRAPHIC_MATERIAL_COLLECTION();
    GRAPHIC_MATERIAL_COLLECTION( GRAPHIC_MATERIAL::PTR material );
    ~GRAPHIC_MATERIAL_COLLECTION();

    XS_DEFINE_SERIALIZABLE

    void SetMaterialForName( GRAPHIC_MATERIAL::PTR material, const char * name );
    GRAPHIC_MATERIAL::PTR GetMaterialForName( std::string & name );
    GRAPHIC_MATERIAL::PTR GetDefaultMaterial() { return MaterialTable.begin()->second; }

    void Apply( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader );

    void LoadMaterialForName( const char * name );

    void SetDiffuse( const CORE_HELPERS_COLOR & color );

private:

    std::map<std::string, GRAPHIC_MATERIAL::PTR>
        MaterialTable;

    static std::string DefaultMaterialName;

XS_CLASS_END

#endif /* GRAPHIC_MATERIAL_COLLECTION_hpp */
