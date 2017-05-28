//
//  RESOURCE_IMAGE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_RESOURCE_IMAGE_h
#define GAME_ENGINE_REBORN_RESOURCE_IMAGE_h

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"

class RESOURCE_IMAGE : public RESOURCE< RESOURCE_IMAGE, RESOURCE_IMAGE_PNG_LOADER > {
    
    public :

    RESOURCE_IMAGE();
    virtual ~RESOURCE_IMAGE();

    inline GRAPHIC_TEXTURE_INFO & GetImageInfo() { return TextureInfo; }
    inline const GRAPHIC_TEXTURE_INFO & GetImageInfo() const { return TextureInfo; }
    inline void SetImageRawData( void * raw_data) { RawData = raw_data; }
    inline const void * GetImageRawData() const { return RawData; }

    void Blit( RESOURCE_IMAGE * image, int x_offset, int y_offset, int rows, int columns, int mask );

    GRAPHIC_TEXTURE * CreateTextureObject( bool generate_mip_map );

    private:

    GRAPHIC_TEXTURE_INFO TextureInfo;

    char * Path;
    void * RawData;

XS_CLASS_END

#endif
