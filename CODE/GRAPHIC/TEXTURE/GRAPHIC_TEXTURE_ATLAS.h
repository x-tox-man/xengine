//
//  GRAPHIC_TEXTURE_ATLAS.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_TEXTURE_ATLAS__
#define __GAME_ENGINE_REBORN__GRAPHIC_TEXTURE_ATLAS__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_MATH_VECTOR.h"
#include "RESOURCE_IMAGE.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"

typedef std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, GRAPHIC_TEXTURE_BLOCK > GRAPHIC_TEXTURE_ATLAS_BLOCK_TABLE;

XS_CLASS_BEGIN_WITH_ANCESTOR_2( GRAPHIC_TEXTURE_ATLAS, GRAPHIC_TEXTURE, RESOURCE_IMAGE )

    GRAPHIC_TEXTURE_ATLAS();
    virtual ~GRAPHIC_TEXTURE_ATLAS();

    XS_DEFINE_SERIALIZABLE

    virtual void Initialize( const void * texture_data );
    void Load( const CORE_FILESYSTEM_PATH & atlas_path, const CORE_FILESYSTEM_PATH & image_path );

    void AddTexture( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const CORE_MATH_VECTOR & size, const CORE_MATH_VECTOR & offset );
    GRAPHIC_TEXTURE_BLOCK & GetTextureBlock( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) { return TextureBlockTable[ identifier ]; }

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER , GRAPHIC_TEXTURE_BLOCK > & GetTextureBlockTable() { return TextureBlockTable; }

private:

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER , GRAPHIC_TEXTURE_BLOCK >
        TextureBlockTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_TEXTURE_ATLAS__) */
