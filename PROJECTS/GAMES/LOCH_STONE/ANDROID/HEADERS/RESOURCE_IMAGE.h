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
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( RESOURCE_IMAGE, RESOURCE )

RESOURCE_IMAGE();

#if !PLATFORM_ANDROID
    CORE_HELPERS_FACTORY_Element( RESOURCE_IMAGE, RESOURCE, RESOURCE_TYPE, RESOURCE_TYPE_ImagePng )
#endif

inline GRAPHIC_TEXTURE_INFO & GetImageInfo() { return TextureInfo; }
inline const GRAPHIC_TEXTURE_INFO & GetImageInfo() const { return TextureInfo; }
inline void SetImageRawData( void * raw_data) { RawData = raw_data; }
inline const void * GetImageRawData() const { return RawData; }

void Blit( RESOURCE_IMAGE * image, int x_offset, int y_offset, int rows, int columns, int mask );

GRAPHIC_TEXTURE * CreateTextureObject();

private:

GRAPHIC_TEXTURE_INFO TextureInfo;

char * Path;
void * RawData;

XS_CLASS_END

#endif
