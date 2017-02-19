//
//  GRAPHIC_SHADER_EFFECT_LOADER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_EFFECT_LOADER_h
#define GRAPHIC_SHADER_EFFECT_LOADER_h

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_FILESYSTEM.h"

class GRAPHIC_SHADER_EFFECT;

typedef RESOURCE_LOADER< GRAPHIC_SHADER_EFFECT > EFFECT_RESOURCE_LOADER_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_SHADER_EFFECT_LOADER, EFFECT_RESOURCE_LOADER_TYPE )

    GRAPHIC_SHADER_EFFECT_LOADER();
    virtual ~GRAPHIC_SHADER_EFFECT_LOADER();

    virtual GRAPHIC_SHADER_EFFECT * Load( const CORE_FILESYSTEM_PATH & file,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty ) override;

    virtual GRAPHIC_SHADER_EFFECT * Load( const void * memory, unsigned int size, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty) override;

    virtual void ReloadResource( GRAPHIC_SHADER_EFFECT * resource_to_reload ) override;

XS_CLASS_END


#endif /* GRAPHIC_SHADER_EFFECT_LOADER_hpp */
