    //
//  GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.h"

GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    Material(),
    ConeObject( NULL ),
    SphereObject( NULL ),
    GameCamera( NULL ),
    PlanObject( NULL ),
    TextureBlock1(),
    TextureBlock2(),
    TextureBlock3(),
    TextureBlock4(),
    TextureBlock5(),
    RenderTarget(),
    FinalRenderTarget( NULL ),
    AmbientDirectionalDefferedEffect( NULL ),
    SpotDeferredEffect( NULL ),
    PointDefferedEffect( NULL ),
    NullTechniqueEffect( NULL ) {
    
}

GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::~GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    RenderTarget.Initialize(renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    RenderTarget.AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
    RenderTarget.AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
    RenderTarget.AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
    RenderTarget.AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA );
    
    AmbientDirectionalDefferedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredAmbiantAndDirectionnal" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredAmbiantAndDirectionnal", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    PointDefferedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredPoint" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredPoint", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    //PointDefferedEffect = new GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredPoint"), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredPoint" , "", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    SpotDeferredEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredSpot" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredSpot", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    NullTechniqueEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::NullTechnique" ), CORE_FILESYSTEM_PATH::FindFilePath( "NullTechnique", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    AmbientDirectionalDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    //AmbientDirectionalDefferedEffect->BindAttributes();
    
    PointDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    //PointDefferedEffect->BindAttributes();
    
    SpotDeferredEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    //SpotDeferredEffect->BindAttributes();
    
    NullTechniqueEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    NullTechniqueEffect->SetMaterial( new GRAPHIC_MATERIAL() );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    renderer.GetCamera()->ActivateForRender();
    renderer.SetLightingIsEnabled( false );
    RenderTarget.Apply();
    GRAPHIC_SYSTEM::ClearFrambufferColor();
    GRAPHIC_SYSTEM::ClearFrambufferDepth( 1.0 );
    RenderTarget.BindForWriting();
    RendererCallback( renderer );
    renderer.SetLightingIsEnabled( true );
    RenderTarget.Discard();
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    static int
        acc = 0;
        acc++;
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    if ( FinalRenderTarget != NULL )
        FinalRenderTarget->Apply();
    
    RenderTarget.BindForReading();
    
    /*if ( (acc % 33) == 0 ) {
        GRAPHIC_TEXTURE * texture2;
        RenderTarget.SetReadBuffer( 0 );
        texture2 = RenderTarget.GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING1" , "png", "" ));
        RenderTarget.SetReadBuffer( 1 );
        texture2 = RenderTarget.GetTargetTexture( 1 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING2" , "png", "" ));
        RenderTarget.SetReadBuffer( 2 );
        texture2 = RenderTarget.GetTargetTexture( 2 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING3" , "png", "" ));
        
        RenderTarget.SetReadBuffer( 3 );
        texture2 = RenderTarget.GetTargetTexture( 3 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING4" , "png", "" ));
        
        RenderTarget.SetReadBuffer( 4 );
        texture2 = RenderTarget.GetTargetTexture( 4 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING5" , "png", "" ));
    }*/
    
    TextureBlock1.SetTexture( RenderTarget.GetTargetTexture( 0 ) );
    TextureBlock2.SetTexture( RenderTarget.GetTargetTexture( 1 ) );
    TextureBlock3.SetTexture( RenderTarget.GetTargetTexture( 2 ) );
    TextureBlock4.SetTexture( RenderTarget.GetTargetTexture( 3 ) );
    TextureBlock5.SetTexture( RenderTarget.GetTargetTexture( 4 ) );
    
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut, &TextureBlock1 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut1, &TextureBlock2 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut2, &TextureBlock3 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut3, &TextureBlock4 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut4, &TextureBlock5 ) ;
    
    AmbientDirectionalDefferedEffect->SetMaterial( &Material );
    PointDefferedEffect->SetMaterial( &Material );
    SpotDeferredEffect->SetMaterial( &Material );
    
    renderer.SetLightingIsEnabled( true );
    
    GRAPHIC_SYSTEM::DisableDepthTest();
    GRAPHIC_SYSTEM::Clear();

    PlanObject->Render( renderer, option, AmbientDirectionalDefferedEffect );
    GRAPHIC_SYSTEM::EnableDepthTest(GRAPHIC_SYSTEM_COMPARE_OPERATION_Less, false );
    
    renderer.SetDeferredLightingIsEnabled( true );
    GRAPHIC_CAMERA::PTR backup_camera = renderer.GetCamera();
    renderer.SetCamera( GameCamera );
    
    ApplyPointLightPass( renderer );
    ApplySpotLightPass( renderer );
    
    renderer.SetDeferredLightingIsEnabled( false );
    renderer.SetLightingIsEnabled( false );
    renderer.SetCamera( backup_camera );
    
    GRAPHIC_SYSTEM::DisableStencil();

    if ( FinalRenderTarget != NULL ) {
        
        FinalRenderTarget->Discard();


    /*if ( (acc % 33) == 0 ) {
        
        acc = 0;
        FinalRenderTarget->BindForReading();
        FinalRenderTarget->SetReadBuffer( 0 );
        GRAPHIC_TEXTURE * texture2 = FinalRenderTarget->GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADINGFinal" , "png", "" ));*/
    }
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyStencilPassForPoint( GRAPHIC_RENDERER & renderer, GRAPHIC_OBJECT_RENDER_OPTIONS & option, GRAPHIC_SHADER_LIGHT * light ) {
    
    GRAPHIC_SYSTEM::EnableDepthTest(GRAPHIC_SYSTEM_COMPARE_OPERATION_Less, true );
    GRAPHIC_SYSTEM::DisableFaceCulling();
    GRAPHIC_SYSTEM::ClearFrambufferStencil();
    GRAPHIC_SYSTEM::EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Always, 0, 0 );
    GRAPHIC_SYSTEM::SetStencilOperation( GRAPHIC_POLYGON_FACE_Back, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_IncrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    GRAPHIC_SYSTEM::SetStencilOperation( GRAPHIC_POLYGON_FACE_Front, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_DecrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    
    SphereObject->Render( renderer, option, NullTechniqueEffect );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyPointLightPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    for (unsigned int i = 0 ; i < renderer.GetPointLightTable().size(); i++) {
        
        auto light = renderer.GetPointLightTable()[ i ];
        renderer.SetDeferredPointIndex( i );
        
        float scale = CalculatePointLightSphereAndExtent( *light );
        
        option.SetScaleFactor(CORE_MATH_VECTOR( scale, scale, scale, 1.0f ) );
        option.SetPosition( light->InternalLight.Point.Position );
        option.SetOrientation( CORE_MATH_QUATERNION() );
        
        ApplyStencilPassForPoint( renderer, option, light );
        
        GRAPHIC_SYSTEM::EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_NotEqual, 0, 0xFF );
        GRAPHIC_SYSTEM::DisableDepthTest();
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_One );
        GRAPHIC_SYSTEM::SetBlendFunction( GRAPHIC_SYSTEM_BLEND_EQUATION_Add );
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Front );
        
        SphereObject->Render( renderer, option, PointDefferedEffect );
        
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        GRAPHIC_SYSTEM::DisableBlend();
    }
    
    renderer.SetDeferredPointIndex( -1 );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyStencilPassForSpot( GRAPHIC_RENDERER & renderer, GRAPHIC_OBJECT_RENDER_OPTIONS & option, GRAPHIC_SHADER_LIGHT * light ) {
    
    GRAPHIC_SYSTEM::EnableDepthTest(GRAPHIC_SYSTEM_COMPARE_OPERATION_Less, true );
    GRAPHIC_SYSTEM::DisableFaceCulling();
    GRAPHIC_SYSTEM::ClearFrambufferStencil();
    GRAPHIC_SYSTEM::EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Always, 0, 0 );
    GRAPHIC_SYSTEM::SetStencilOperation( GRAPHIC_POLYGON_FACE_Back, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_IncrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    GRAPHIC_SYSTEM::SetStencilOperation( GRAPHIC_POLYGON_FACE_Front, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_DecrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    
    SphereObject->Render( renderer, option, NullTechniqueEffect );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplySpotLightPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    for (unsigned int i = 0 ; i < renderer.GetSpotLightTable().size(); i++) {
        
        CORE_MATH_VECTOR
            vector, rs;
        CORE_MATH_QUATERNION
            orientation;
        CORE_MATH_MATRIX
            rot;
        
        auto light = renderer.GetSpotLightTable()[ i ];
        renderer.SetDeferredSpotIndex( i );
        
        vector.Set(1.0f, 0.0, 0.0, 0.0f );
        
        orientation.X( light->InternalLight.Spot.Orientation[0] );
        orientation.Y( light->InternalLight.Spot.Orientation[1] );
        orientation.Z( light->InternalLight.Spot.Orientation[2] );
        orientation.W( light->InternalLight.Spot.Orientation[3] );
        orientation.ToMatrix( rot.GetRow( 0 ) );
        
        rs = rot * vector;
        
        light->InternalLight.Spot.Direction[0] = rs.X();
        light->InternalLight.Spot.Direction[1] = rs.Y();
        light->InternalLight.Spot.Direction[2] = rs.Z();
        
        float scale = CalculateSpotLightSphereAndExtent( *light );
        
        option.SetScaleFactor(CORE_MATH_VECTOR( scale, scale, scale, 1.0f ) );
        option.SetPosition( light->InternalLight.Spot.Position );
        option.SetOrientation( orientation );
        
        ApplyStencilPassForSpot( renderer, option, light );
        
        GRAPHIC_SYSTEM::EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_NotEqual, 0, 0xFF );
        GRAPHIC_SYSTEM::DisableDepthTest();
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_One );
        GRAPHIC_SYSTEM::SetBlendFunction( GRAPHIC_SYSTEM_BLEND_EQUATION_Add );
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Front );
        
        SphereObject->Render( renderer, option, SpotDeferredEffect );
        
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        GRAPHIC_SYSTEM::DisableBlend();
    }
    
    renderer.SetDeferredSpotIndex( -1 );
}

float GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::CalculatePointLightSphereAndExtent(const GRAPHIC_SHADER_LIGHT & light) const{
    float MaxChannel = fmax(fmax(light.InternalLight.Point.Color[0], light.InternalLight.Point.Color[1]), light.InternalLight.Point.Color[2]);
    
    float ret = (- light.InternalLight.Point.Linear + sqrtf( light.InternalLight.Point.Linear * light.InternalLight.Point.Linear - 4 * light.InternalLight.Point.Exp * (light.InternalLight.Point.Constant - 256 * MaxChannel * light.InternalLight.Point.DiffuseIntensity)))
    /
    (2 * light.InternalLight.Point.Exp);
    
    return ret;
}

float GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::CalculateSpotLightSphereAndExtent(const GRAPHIC_SHADER_LIGHT & light) const {
    float MaxChannel = fmax(fmax(light.InternalLight.Point.Color[0], light.InternalLight.Point.Color[1]), light.InternalLight.Point.Color[2]);
    
    float ret = (- light.InternalLight.Spot.Linear + sqrtf( light.InternalLight.Spot.Linear * light.InternalLight.Spot.Linear - 4 * light.InternalLight.Spot.Exp * (light.InternalLight.Spot.Constant - 256 * MaxChannel * light.InternalLight.Spot.DiffuseIntensity)))
    /
    (2 * light.InternalLight.Spot.Exp);
    
    return ret;
}
