//
//  GRAPHIC_RENDER_TARGET_OPENGLES2.cpp
//  GAME-ENGINE
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
    
    ItUsesDepth = uses_depth;
    
    GFX_CHECK( glGenFramebuffers( 1, &FrameBuffer ); )
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ); )
    
    TargetTexture->Initialize( ItUsesDepth );
    
    if ( ItUsesDepth ) {
        GFX_CHECK( glGenRenderbuffers(1, &DepthrenderBuffer ); )
        GFX_CHECK( glBindRenderbuffer(GL_RENDERBUFFER, DepthrenderBuffer ); )
        GFX_CHECK( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height ); )
    }
    
    
    GFX_CHECK( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TargetTexture->GetTextureHandle(), 0); )
    
    if ( ItUsesDepth ) {
        
        GFX_CHECK( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthrenderBuffer ); )
    }
    
    GLenum ret_val = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    
    if( ret_val == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS" );
        CORE_RUNTIME_Abort();
    }
    else if( ret_val == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" );
        CORE_RUNTIME_Abort();
    }
    else if( ret_val == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" );
        CORE_RUNTIME_Abort();
    }
    else if( ret_val == GL_FRAMEBUFFER_UNSUPPORTED ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_UNSUPPORTED" );
        CORE_RUNTIME_Abort();
    }
    
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, 0 ); )
    
    return true;
}

bool GRAPHIC_RENDER_TARGET::InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type )
{
    GFX_CHECK( glGenFramebuffers( 1, &FrameBuffer ); )
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ); )
    
    TargetTexture = new GRAPHIC_TEXTURE;
    
    TargetTexture->GetTextureInfo().Width = width;
    TargetTexture->GetTextureInfo().Height = height;
    TargetTexture->GetTextureInfo().ImageType = type;
    
    TargetTexture->InitializeDepth( type );
    
    GFX_CHECK( glEnable(GL_DEPTH_TEST); )
    GFX_CHECK( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, TargetTexture->GetDepthTextureHandle(), 0); )
    
    //GFX_CHECK( glDrawBuffer( GL_NONE ); ) // No color buffer is drawn to.
    //GFX_CHECK( glReadBuffer(GL_NONE); )
    
    GFX_CHECK( glClear( GL_DEPTH_BUFFER_BIT ); )
    
    if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ) {
        
        CORE_RUNTIME_Abort();
    }
    
    return true;
}

void GRAPHIC_RENDER_TARGET::Finalize() {
    
    if ( FrameBuffer ) {
        
        GFX_CHECK( glDeleteFramebuffers(1, &FrameBuffer ); )
    }
    
    if ( DepthrenderBuffer ) {
        
        GFX_CHECK( glDeleteRenderbuffers(1, &DepthrenderBuffer ); )
    }
    
    if ( TargetTexture ) {
        
        GRAPHIC_SYSTEM::ReleaseTexture( TargetTexture );
    }
}

void GRAPHIC_RENDER_TARGET::Apply() {
    
    // Activation du test de profondeur
    GFX_CHECK( glEnable( GL_DEPTH_TEST ); )
    GFX_CHECK( glDepthFunc( GL_LESS ); )
    
    // Activation et binding la texture
    if ( TargetTexture->GetTextureHandle()) {
        GFX_CHECK( glBindTexture( GL_TEXTURE_2D, TargetTexture->GetTextureHandle()); )
    }
    else if ( TargetTexture->GetDepthTextureHandle() ) {
        GFX_CHECK( glBindTexture( GL_TEXTURE_2D, TargetTexture->GetDepthTextureHandle()); )
    }
    
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ); )
    GFX_CHECK( glViewport( 0, 0, TargetTexture->GetTextureInfo().Width, TargetTexture->GetTextureInfo().Height); ) // Render on the whole framebuffer, complete from the lower left corner to the upper right
    
    GLenum ret_val = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    
    if( ret_val == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS" );
        CORE_RUNTIME_Abort();
    }
    else if( ret_val == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" );
        CORE_RUNTIME_Abort();
    }
    else if( ret_val == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" );
        CORE_RUNTIME_Abort();
    }
    else if( ret_val == GL_FRAMEBUFFER_UNSUPPORTED ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_RENDER_TARGET GL_FRAMEBUFFER_UNSUPPORTED" );
        CORE_RUNTIME_Abort();
    }
    
    GFX_CHECK( glClearColor(GRAPHIC_SYSTEM::ClearColor.GetX(), GRAPHIC_SYSTEM::ClearColor.GetY(), GRAPHIC_SYSTEM::ClearColor.GetZ(), 1.0f ); )
    
    if ( TargetTexture->GetTextureHandle() == 0 && TargetTexture->GetDepthTextureHandle() ) {
        GFX_CHECK( glClear( GL_DEPTH_BUFFER_BIT ); )
    }
    else {
        GFX_CHECK( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); )
    }
}

void GRAPHIC_RENDER_TARGET::Discard() {
    
    
    GFX_CHECK( glBindFramebuffer(GL_FRAMEBUFFER, 0 ); )
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, 0); )
    GFX_CHECK( glViewport( 0, 0, CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight()); )
    GFX_CHECK( glDisable(GL_DEPTH_TEST); )
    //on the whole framebuffer, complete from the lower left corner to the upper right
}

#endif
