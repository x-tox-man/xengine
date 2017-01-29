//
//  GRAPHIC_RENDER_TARGET_OPENGLES2.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 14/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDER_TARGET.h"
#include "CORE_APPLICATION.h"

#if OPENGLES2

GRAPHIC_RENDER_TARGET::GRAPHIC_RENDER_TARGET() :
    FrameBuffer(),
    TargetTexture( NULL ),
    ItUsesDepth( false ) {
    
}

GRAPHIC_RENDER_TARGET::~GRAPHIC_RENDER_TARGET() {

    Finalize();
}

bool GRAPHIC_RENDER_TARGET::Initialize(int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool generates_separate_depth_texture, int attachment ) {
    
    TargetTexture = new GRAPHIC_TEXTURE;
    
    TargetTexture->GetTextureInfo().Width = width;
    TargetTexture->GetTextureInfo().Height = height;
    TargetTexture->GetTextureInfo().ImageType = type;
    
    TargetTexture->Initialize( uses_depth );
    
    ItUsesDepth = uses_depth;
    
    GFX_CHECK( glGenFramebuffers( 1, &FrameBuffer ); )
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ); )
    
    if ( ItUsesDepth ) {
        
        GFX_CHECK( glGenRenderbuffers(1, &DepthrenderBuffer ); )
        GFX_CHECK( glBindRenderbuffer(GL_RENDERBUFFER, DepthrenderBuffer ); )
        GFX_CHECK( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height ); )
        GFX_CHECK( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthrenderBuffer ); )
    }
    
    GFX_CHECK( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, TargetTexture->GetTextureHandle(), 0, 0); )
    
    if ( generates_separate_depth_texture ) {
        
        GFX_CHECK( glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, TargetTexture->GetDepthTextureHandle(), 0, 0); )
    }
    
    // Set the list of draw buffers.
    DrawBuffers[0] = static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + attachment);
    //GFX_CHECK( glDrawBuffers( 1, DrawBuffers ); ) // "1" is the size of DrawBuffers )
    
    if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ) {
        
        return false;
    }
    
    return true;
}

void GRAPHIC_RENDER_TARGET::Finalize() {
    
    if ( TargetTexture ) {
        
        GRAPHIC_SYSTEM::ReleaseTexture( TargetTexture );
    }
}

void GRAPHIC_RENDER_TARGET::Apply() {
    
    // Activation du test de profondeur
    GFX_CHECK( glEnable( GL_DEPTH_TEST ); )
    GFX_CHECK( glDepthFunc(GL_ALWAYS); )
    
    // Activation et binding la texture
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, TargetTexture->GetTextureHandle()); )
    GFX_CHECK( glActiveTexture( GL_TEXTURE0 ); )
    
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ); )
    GFX_CHECK( glViewport( 0, 0, TargetTexture->GetTextureInfo().Width, TargetTexture->GetTextureInfo().Height); ) // Render on the whole framebuffer, complete from the lower left corner to the upper right
    GFX_CHECK( glBindTexture(GL_TEXTURE_2D, 0); )
    
    //TODO: clear is maybe too expensive
    GFX_CHECK( glClearColor( 0.0, 0.0f, 0.4f, 1.0f ); )
    GFX_CHECK( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); )
}

void GRAPHIC_RENDER_TARGET::Discard() {
    
    GFX_CHECK( glBindFramebuffer(GL_FRAMEBUFFER, 0 ); )
    GFX_CHECK( glViewport( 0, 0, CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight()); )
    GFX_CHECK( glDisable( GL_DEPTH_TEST ); )
    //on the whole framebuffer, complete from the lower left corner to the upper right
}

#endif
