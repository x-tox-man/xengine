//
//  GRAPHIC_SHADER_EFFECT.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_DATA_STREAM.h"
#include "RESOURCE.h"
#include "GRAPHIC_MATERIAL_COLLECTION.h"

class GRAPHIC_SHADER_EFFECT;
class GRAPHIC_MATERIAL;
class GRAPHIC_SHADER_EFFECT_LOADER;

typedef RESOURCE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER> GRAPHIC_SHADER_EFFECT_RESOURCE_ANCESTOR;

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_RESOURCE_ANCESTOR )

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GRAPHIC_SHADER_EFFECT, BASE_RESOURCE, RESOURCE_TYPE, RESOURCE_TYPE_Effect )

    GRAPHIC_SHADER_EFFECT();
    virtual ~GRAPHIC_SHADER_EFFECT();

    static GRAPHIC_SHADER_EFFECT::PTR LoadEffectWithVertexAndFragmentPath( const CORE_FILESYSTEM_PATH & vertex_path, const CORE_FILESYSTEM_PATH & fragment_path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static GRAPHIC_SHADER_EFFECT::PTR LoadEffectWithVertexAndFragmentPathAndMaterial( const CORE_FILESYSTEM_PATH & vertex_path, const CORE_FILESYSTEM_PATH & fragment_path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const char * material_name );

    void Initialize( const GRAPHIC_SHADER_BIND & bind );
    void Release();

    inline GRAPHIC_SHADER_PROGRAM_DATA_PROXY & GetProgram() { return Program; }
    inline const GRAPHIC_SHADER_BIND & GetShaderBind() { return Bind; }

    inline GRAPHIC_MATERIAL_COLLECTION::PTR GetMaterialCollection() { return MaterialCollection; }
    inline void SetMaterial( GRAPHIC_MATERIAL::PTR material, const char * name = "DefaultMaterial" ) { MaterialCollection->SetMaterialForName( material, name ); }
    inline GRAPHIC_MATERIAL::PTR GetMaterial( const char * name = "DefaultMaterial" ) { std::string mat_name( name ); return MaterialCollection->GetMaterialForName( mat_name ); }

    inline void SetDiffuse( const CORE_HELPERS_COLOR & color ) { MaterialCollection->SetDiffuse( color ); }

    virtual void Apply( GRAPHIC_RENDERER & renderer );
    virtual void Apply( GRAPHIC_RENDERER & renderer, bool activate_material );
    void SelectMaterial( std::string & material_name );
    virtual void Discard();
    virtual void BindAttributes();
    void BindAttribute( GRAPHIC_SHADER_ATTRIBUTE &shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier );

    protected :

    GRAPHIC_SHADER_PROGRAM_DATA_PROXY
        Program;
    GRAPHIC_SHADER_BIND
        Bind;
    GRAPHIC_MATERIAL_COLLECTION::PTR
        MaterialCollection;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT__) */
