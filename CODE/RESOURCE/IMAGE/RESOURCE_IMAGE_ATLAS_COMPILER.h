//
//  RESOURCE_IMAGE_ATLAS_COMPILER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__RESOURCE_IMAGE_ATLAS_COMPILER__
#define __GAME_ENGINE_REBORN__RESOURCE_IMAGE_ATLAS_COMPILER__

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "GRAPHIC_TEXTURE.h"
#include "RESOURCE_TYPE.h"
#include "RESOURCE_IMAGE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"

XS_CLASS_BEGIN( RESOURCE_IMAGE_ATLAS_COMPILER )

    RESOURCE_IMAGE_ATLAS_COMPILER();
    virtual    ~RESOURCE_IMAGE_ATLAS_COMPILER();

    class NODE {
        
        public :
        
        NODE() :
            Rec(),
            Image( NULL ),
            Childs() {
                
            Childs[0] = NULL;
            Childs[1] = NULL;
        }
        
        NODE * Insert( RESOURCE_IMAGE * img);
        
        CORE_MATH_SHAPE_RECTANGLE Rec;
        RESOURCE_IMAGE * Image;
        NODE * Childs[2];
    };

    void Compile( const char * destination_path, const std::vector< RESOURCE_IMAGE * > & resource_image_table );

private:

    std::vector< RESOURCE_IMAGE * >
        SortedImageTable;
    NODE
        * RootNode;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__RESOURCE_IMAGE_ATLAS_COMPILER__) */
