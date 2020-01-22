//
//  GRAPHIC_MATERIAL.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MATERIAL_h
#define GRAPHIC_MATERIAL_h

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_HELPERS_COLOR.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "RESOURCE.h"

class GRAPHIC_MATERIAL_RESOURCE_LOADER;
class GRAPHIC_MATERIAL;
class GRAPHIC_SHADER_PROGRAM_DATA_PROXY;

typedef RESOURCE< GRAPHIC_MATERIAL, GRAPHIC_MATERIAL_RESOURCE_LOADER > GR_M_ANCESTOR_TYPE;

typedef struct {
    CORE_HELPERS_COLOR
        Diffuse,
        Specular,
        Ambient;
    float
        SpecularIntensity,
        Shininess;
} InnerMaterial;

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GRAPHIC_MATERIAL, GR_M_ANCESTOR_TYPE )

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GRAPHIC_MATERIAL, BASE_RESOURCE, RESOURCE_TYPE, RESOURCE_TYPE_Material )

    GRAPHIC_MATERIAL();
    GRAPHIC_MATERIAL( const char * image_path );
    ~GRAPHIC_MATERIAL();

    void Apply( GRAPHIC_RENDERER &, GRAPHIC_SHADER_PROGRAM_DATA_PROXY *, bool, bool );
    void ApplyTexture( GRAPHIC_SHADER_PROGRAM_DATA_PROXY * shader );
    void Discard( GRAPHIC_RENDERER & renderer );

    inline GRAPHIC_TEXTURE_BLOCK * GetTexture(const CORE_HELPERS_IDENTIFIER & identifier) {return TextureTable[identifier];  }
    inline void SetTexture( const CORE_HELPERS_IDENTIFIER & identifier, GRAPHIC_TEXTURE_BLOCK * texture ) { TextureTable[identifier] = texture; }

    inline const CORE_HELPERS_COLOR & GetDiffuse() const { return InnerMaterial.Diffuse; }
    inline CORE_HELPERS_COLOR & GetDiffuse() { return InnerMaterial.Diffuse; }
    inline void SetDiffuse( const CORE_HELPERS_COLOR & diffuse ) { InnerMaterial.Diffuse = diffuse; }

    inline int GetTextureCount() const { return TextureTable.size(); }
    int GetFirstDepthTextureIndex() const;

    InnerMaterial
        InnerMaterial;

private:

    void TryAndFillFor( const char * path, const char * extension, const CORE_HELPERS_IDENTIFIER & identifier );
    void ApplyLights( GRAPHIC_SHADER_PROGRAM_DATA_PROXY *, GRAPHIC_RENDERER & );

    std::string
        Name;
    std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_TEXTURE_BLOCK * >
        TextureTable;
    bool
        DepthIsEnabled,
        CubeMapIsEnabled;

XS_CLASS_END

#endif /* GRAPHIC_MATERIAL_hpp */
