//
//  GRAPHIC_SHADER_EFFECT.h
//  GAME-ENGINE-REBORN
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
#include "RESOURCE.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

class GRAPHIC_SHADER_EFFECT;
class GRAPHIC_SHADER_EFFECT_LOADER;

typedef RESOURCE< GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_LOADER> GRAPHIC_SHADER_EFFECT_RESOURCE_ANCESTOR;

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT, GRAPHIC_SHADER_EFFECT_RESOURCE_ANCESTOR )

    GRAPHIC_SHADER_EFFECT();
    virtual ~GRAPHIC_SHADER_EFFECT();

    static GRAPHIC_SHADER_EFFECT::PTR LoadEffectWithVertexAndFragmentPath( const CORE_FILESYSTEM_PATH & vertex_path, const CORE_FILESYSTEM_PATH & fragment_path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );

    void Initialize( const GRAPHIC_SHADER_BIND & bind );
    void Release();

    inline GRAPHIC_SHADER_PROGRAM_DATA_PROXY & GetProgram() { return Program; }
    inline const GRAPHIC_SHADER_BIND & GetSahderBind() { return Bind; }

    virtual void Apply();
    virtual void BindAttributes();

    protected :

    GRAPHIC_SHADER_PROGRAM_DATA_PROXY
        Program;
    GRAPHIC_SHADER_BIND
        Bind;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT__) */
