//
//  GRAPHIC_RENDER_TARGET_VK.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 03/01/18.
//  Copyright (c) 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDER_TARGET.h"
#include "CORE_APPLICATION.h"
#include "GRAPHIC_SYSTEM.h"

#if X_VK

GRAPHIC_RENDER_TARGET::GRAPHIC_RENDER_TARGET() {
    
    abort();
}

GRAPHIC_RENDER_TARGET::~GRAPHIC_RENDER_TARGET() {

    Finalize();
}

bool GRAPHIC_RENDER_TARGET::Initialize( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool generates_separate_depth_texture, int attachment ) {

    TargetTexture=new GRAPHIC_TEXTURE;

    TargetTexture->GetTextureInfo().Width=width;
    TargetTexture->GetTextureInfo().Height=height;
    TargetTexture->GetTextureInfo().ImageType=type;

    TargetTexture->Initialize( uses_depth );

    ItUsesDepth = uses_depth;

    abort();

    return true;
}

bool GRAPHIC_RENDER_TARGET::InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type )
{
    abort();

    TargetTexture = new GRAPHIC_TEXTURE;

    TargetTexture->GetTextureInfo().Width=width;
    TargetTexture->GetTextureInfo().Height=height;
    TargetTexture->GetTextureInfo().ImageType=type;

    TargetTexture->InitializeDepth( type );

    return true;
}

void GRAPHIC_RENDER_TARGET::Finalize() {

    abort();

    if ( TargetTexture ) {

        GRAPHIC_SYSTEM::ReleaseTexture( TargetTexture );
    }
}

void GRAPHIC_RENDER_TARGET::Apply() {

   abort();
}

void GRAPHIC_RENDER_TARGET::Discard() {

    abort();
}

#endif
