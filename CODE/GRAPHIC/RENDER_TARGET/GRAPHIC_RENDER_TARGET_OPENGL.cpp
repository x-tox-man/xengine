//
//  GRAPHIC_RENDER_TARGET_OPENGL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDER_TARGET.h"
#include "CORE_APPLICATION.h"

#if OPENGL2PLUS

GRAPHIC_RENDER_TARGET::GRAPHIC_RENDER_TARGET() :
    FrameBuffer(),
    TargetTextures(),
    ItUsesDepth( false ) {
    
}

GRAPHIC_RENDER_TARGET::~GRAPHIC_RENDER_TARGET() {

    Finalize();
}

bool GRAPHIC_RENDER_TARGET::Initialize(int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool generates_separate_depth_texture, int attachments, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode ) {
    
    ItUsesDepth = uses_depth;
    Attachments = attachments;
    Mode = mode;
    
    GRAPHIC_SYSTEM::CreateFrameBuffer( this, mode );
    
    if ( ItUsesDepth ) {
        
        GRAPHIC_SYSTEM::CreateDepthBuffer( this, width, height );
    }
    
    for ( int i = 0; i < attachments; i++ ) {
        
        TargetTextures[i] = new GRAPHIC_TEXTURE;
        
        TargetTextures[i]->GetTextureInfo().Width = width;
        TargetTextures[i]->GetTextureInfo().Height = height;
        TargetTextures[i]->GetTextureInfo().ImageType = type;
        TargetTextures[i]->Initialize( ( uses_depth && i == 0 ) );
        
        GFX_CHECK( glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, TargetTextures[i]->GetTextureHandle(), 0 ); )
    }
    
    if ( generates_separate_depth_texture ) {
        
        GFX_CHECK( glFramebufferTexture( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, TargetTextures[0]->GetDepthTextureHandle(), 0/*mipmap level*/); )
    }

    // Set the list of draw buffers.
    for( int i = 0; i < attachments; i++ ) {
        
        DrawBuffers[ i ] = static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + i);
    }
    GFX_CHECK( glDrawBuffers( attachments, DrawBuffers ); ) // "1" is the size of DrawBuffers )
    
    return glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE;
}

void GRAPHIC_RENDER_TARGET::AddAttachment( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    GFX_CHECK( glBindFramebuffer( OPENGL_4_GetFrameBufferMode( Mode ), FrameBuffer ); )
    
    ++Attachments;
    
    TargetTextures[Attachments - 1] = new GRAPHIC_TEXTURE;
    
    TargetTextures[Attachments - 1]->GetTextureInfo().Width = width;
    TargetTextures[Attachments - 1]->GetTextureInfo().Height = height;
    TargetTextures[Attachments - 1]->GetTextureInfo().ImageType = type;
    TargetTextures[Attachments - 1]->Initialize( false );
    
    GFX_CHECK( glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (Attachments - 1), GL_TEXTURE_2D, TargetTextures[ Attachments - 1 ]->GetTextureHandle(), 0 ); )
    
    // Set the list of draw buffers.
    for( int i = 0; i < Attachments; i++ ) {
        
        DrawBuffers[ i ] = static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + i);
    }
    GFX_CHECK( glDrawBuffers( Attachments, DrawBuffers ); ) // "1" is the size of DrawBuffers )
    
    assert( glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE );
}

bool GRAPHIC_RENDER_TARGET::InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type )
{
    GFX_CHECK( glGenFramebuffers( 1, &FrameBuffer ); )
    GFX_CHECK( glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ); )
    
    TargetTextures[0] = new GRAPHIC_TEXTURE;
    TargetTextures[0]->GetTextureInfo().Width = width;
    TargetTextures[0]->GetTextureInfo().Height = height;
    TargetTextures[0]->GetTextureInfo().ImageType = type;
    TargetTextures[0]->InitializeDepth( type );
    
    Attachments = 1;
    Mode = GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All;
    
    GFX_CHECK( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, TargetTextures[0]->GetDepthTextureHandle(), 0); )
    
    //GFX_CHECK( glDrawBuffer( GL_NONE ); ) // No color buffer is drawn to.
    //GFX_CHECK( glReadBuffer(GL_NONE); )
    
    GFX_CHECK( glClear( GL_DEPTH_BUFFER_BIT ); )
    
    CORE_RUNTIME_Assert( glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE );
    
    return true;
}

void GRAPHIC_RENDER_TARGET::Finalize() {
    
    if ( FrameBuffer ) {
        
        GFX_CHECK( glDeleteFramebuffers(1, &FrameBuffer ); )
    }
    
    if ( DepthrenderBuffer ) {
        
        GFX_CHECK( glDeleteRenderbuffers(1, &DepthrenderBuffer ); )
    }
    
    for ( int i = 0; i < Attachments; i++ ) {
        
        GRAPHIC_SYSTEM::ReleaseTexture( TargetTextures[ i ] );
    }
}

void GRAPHIC_RENDER_TARGET::Apply() {
    
    // Activation du test de profondeur
    GFX_CHECK( glEnable( GL_DEPTH_TEST ); )
    GFX_CHECK( glDepthFunc( GL_LESS ); )
    
    GFX_CHECK( glBindFramebuffer( OPENGL_4_GetFrameBufferMode( Mode ), FrameBuffer ); )
    GFX_CHECK( glViewport( 0, 0, TargetTextures[ 0 ]->GetTextureInfo().Width, TargetTextures[ 0 ]->GetTextureInfo().Height); ) // Render on the whole framebuffer, complete from the lower left corner to the upper right
    
    GLenum en = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    
    if( en != GL_FRAMEBUFFER_COMPLETE ) {
        
        CORE_RUNTIME_Abort();
    }
    
    GFX_CHECK( glClearColor(GRAPHIC_SYSTEM::ClearColor.GetX(), GRAPHIC_SYSTEM::ClearColor.GetY(), GRAPHIC_SYSTEM::ClearColor.GetZ(), 1.0f ); )
    GFX_CHECK( glClearDepth(1.0f); )
    
    if ( TargetTextures[0]->GetTextureHandle() == 0 && TargetTextures[0]->GetDepthTextureHandle() ) {
        GFX_CHECK( glClear( GL_DEPTH_BUFFER_BIT ); )
    }
    else {
        GFX_CHECK( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); )
    }
}

void GRAPHIC_RENDER_TARGET::Discard() {
    
    GFX_CHECK( glBindFramebuffer(GL_FRAMEBUFFER, 0 ); )
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, 0); )
    GFX_CHECK( glViewport( 0, 0, CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight()); )
    GFX_CHECK( glDisable(GL_DEPTH_TEST); )
    //on the whole framebuffer, complete from the lower left corner to the upper right
}

void GRAPHIC_RENDER_TARGET::BindForWriting() {
    
    GFX_CHECK( glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBuffer); )
}

void GRAPHIC_RENDER_TARGET::BindForReading() {
    
    GFX_CHECK( glBindFramebuffer(GL_READ_FRAMEBUFFER, FrameBuffer); )
}

void GRAPHIC_RENDER_TARGET::SetReadBuffer( int type )
{
    GFX_CHECK( glReadBuffer(GL_COLOR_ATTACHMENT0 + type); )
}

void GRAPHIC_RENDER_TARGET::SetWriteBuffer( int type )
{
    GFX_CHECK( glDrawBuffer(GL_COLOR_ATTACHMENT0 + type); )
}

#endif
