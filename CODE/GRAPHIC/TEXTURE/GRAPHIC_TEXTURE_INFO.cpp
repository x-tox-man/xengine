//
//  GRAPHIC_TEXTURE_INFO.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXTURE_INFO.h"

int GRAPHIC_TEXTURE_INFO_GetPixelBitSizeByColorType( GRAPHIC_TEXTURE_IMAGE_TYPE image_type, int bit_depth ) {
    
    static int PIXEL_SIZES[ GRAPHIC_TEXTURE_IMAGE_TYPE_Count ] = { 3, 4, 1, 2, 2, 3, 4 };
    
    return PIXEL_SIZES[ image_type ] * bit_depth;
}
