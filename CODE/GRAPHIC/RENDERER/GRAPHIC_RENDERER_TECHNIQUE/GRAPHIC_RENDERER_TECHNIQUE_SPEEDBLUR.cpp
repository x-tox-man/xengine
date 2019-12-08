//
//  GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR.h"
#include "GRAPHIC_OBJECT_RENDER_OPTIONS.h"

GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR::GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    SpeedBlurEffect( NULL ),
    PlanObject( NULL ),
    TextureBlock( NULL ),
    TextureBlock2( NULL ),
    PrimaryRenderTarget( NULL ),
    FinalRenderTarget( NULL ) {
    
}
GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR::~GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    SpeedBlurEffect = new GRAPHIC_SHADER_EFFECT_SPEEDBLUR( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::FullScreenSpeedBlurShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "FullScreenSpeedBlurShader", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    SpeedBlurEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    ((GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR) SpeedBlurEffect)->BindAttributes();
    
    TextureBlock->SetTexture( FinalRenderTarget->GetTargetTexture( 0 ) );
    TextureBlock2->SetTexture( PrimaryRenderTarget->GetTargetTexture( 0 ) );
    
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, TextureBlock );
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::DepthTexture, TextureBlock2 );
}

void GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    CORE_MATH_MATRIX
        current_mat( &renderer.GetCamera()->GetProjectionMatrix()[0] );
    CORE_MATH_MATRIX
    inv( CORE_MATH_MATRIX::Identity );
    
    current_mat = renderer.GetCamera()->GetViewMatrix();
    current_mat.GetInverse( inv );
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::InverseCurrentModelViewIdentifier ).AttributeValue.Value.FloatMatrix4x4,
           (void*) &inv[0],
           16* sizeof(float) );
}

void GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    static CORE_MATH_VECTOR old_p;
    CORE_MATH_VECTOR
        delta_position = renderer.GetCamera()->GetPosition() - old_p;
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    memcpy(
           (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::ViewRayIdentifier ).AttributeValue.Value.FloatArray4,
           (void*) &delta_position[0],
           4* sizeof(float) );
    
    SpeedBlurEffect->SetMaterial( &Material );
    
    PlanObject->Render( GRAPHIC_RENDERER::GetInstance(), option, SpeedBlurEffect );
    
    
    {
        CORE_MATH_MATRIX previous_mat( &renderer.GetCamera()->GetProjectionMatrix()[0] );
        
        previous_mat *= renderer.GetCamera()->GetViewMatrix();
        
        memcpy(
               (void*) SpeedBlurEffect->GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::PreviousModelViewProjectionIdentifier ).AttributeValue.Value.FloatMatrix4x4,
               (void*) &previous_mat[0],
               16* sizeof(float) );
    }
    
    old_p = renderer.GetCamera()->GetPosition();
}
