//
//  GRAPHIC_TEXTURE_INFO.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_TEXTURE_INFO_h
#define GAME_ENGINE_REBORN_GRAPHIC_TEXTURE_INFO_h

enum GRAPHIC_TEXTURE_IMAGE_TYPE {
    GRAPHIC_TEXTURE_IMAGE_TYPE_RGB = 0,
    GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA,
    GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY,
    GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY_A,
    GRAPHIC_TEXTURE_IMAGE_TYPE_Count
};

typedef struct {
    GRAPHIC_TEXTURE_IMAGE_TYPE ImageType;
    int ColorChannelWidth;
    int PixelSize;
    int Width;
    int Height;
}GRAPHIC_TEXTURE_INFO;

int GRAPHIC_TEXTURE_INFO_GetPixelBitSizeByColorType( GRAPHIC_TEXTURE_IMAGE_TYPE image_type, int bit_depth );

#endif
