    //
//  GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"

GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    Material(),
    ConeObject( NULL ),
    SphereObject( NULL ),
    PreviousCamera( NULL ),
    PlanObject( NULL ),
    TextureBlock1(),
    TextureBlock2(),
    TextureBlock3(),
    TextureBlock4(),
    TextureBlock5(),
    TextureBlock6(),
    AmbientDirectionalDefferedEffect( NULL ),
    SpotDeferredEffect( NULL ),
    PointDefferedEffect( NULL ),
    NullTechniqueEffect( NULL ),
    GBUFFER_TYPES( GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_None ) {
    
}

GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::~GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING() {
    
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ConfigureGBufferBeforeInit( GRAPHIC_RENDERER & renderer, int types ) {
    
    assert( types != GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_None );
    assert( renderer.GetWidth() > 0.0f && renderer.GetHeight() > 0.0f );
    
    RenderTarget = new GRAPHIC_RENDER_TARGET;
    GBUFFER_TYPES = types;
    
    RenderTarget->Initialize( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, true, 4, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    /*if ( true ) { //types & GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_Diffuse ) {
        
        RenderTarget->Initialize( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, true, true, 1, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    }
    
    if ( GBUFFER_TYPES & GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_Normal ) {
        
        RenderTarget->AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH32 );
    }
    
    if ( GBUFFER_TYPES & GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_Specular ) {
        
        RenderTarget->AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY );
    }
    
    if ( GBUFFER_TYPES & GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_AmbientOcclusion ) {
        
        RenderTarget->AddAttachment( renderer.GetWidth(), renderer.GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
    }*/
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    //Must call ConfigureGBufferBeforeInit
    assert( GBUFFER_TYPES != GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_GBUFFER_None );
    
    AmbientDirectionalDefferedEffect = new GRAPHIC_SHADER_EFFECT_DEFERRED( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredAmbiantAndDirectionnal"), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredAmbiantAndDirectionnal" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    
    //AmbientDirectionalDefferedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredAmbiantAndDirectionnal" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredAmbiantAndDirectionnal", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    PointDefferedEffect = new GRAPHIC_SHADER_EFFECT_DEFERRED( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredPoint"), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredPointLight" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    //PointDefferedEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredPoint" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredPointLight", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    SpotDeferredEffect = new GRAPHIC_SHADER_EFFECT_DEFERRED( GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredSpot"), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredSpotLight" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) ) );
    //SpotDeferredEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::DeferredSpot" ), CORE_FILESYSTEM_PATH::FindFilePath( "DeferredSpotLight", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    NullTechniqueEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::NullTechnique" ), CORE_FILESYSTEM_PATH::FindFilePath( "NullTechnique", "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    AmbientDirectionalDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    //AmbientDirectionalDefferedEffect->BindAttributes();
    
    PointDefferedEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    //PointDefferedEffect->BindAttributes();
    
    SpotDeferredEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    //SpotDeferredEffect->BindAttributes();
    
    auto collection = new GRAPHIC_MATERIAL_COLLECTION;
    auto mat = new GRAPHIC_MATERIAL();
    collection->SetMaterialForName(mat, ConeObject->GetMeshTable()[0]->GetName() );
    collection->SetMaterialForName(mat, GRAPHIC_SHADER_EFFECT::DefaultMaterialName );
    
    NullTechniqueEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    NullTechniqueEffect->SetMaterialCollection( collection );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    renderer.GetCamera()->ActivateForRender();
    renderer.SetLightingIsEnabled( true );
    
    RenderTarget->Clear();
    
    RenderTarget->Apply( renderer );
    RendererCallback( renderer, GAMEPLAY_COMPONENT_SYSTEM_MASK_Opaque );
    RenderTarget->Discard();
    RenderTarget->BindForReading();
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    /*static int
        acc = 0;
        acc++;*/
    
    option.SetPosition( CORE_MATH_VECTOR::Zero );
    option.SetOrientation( CORE_MATH_QUATERNION() );
    option.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    RenderTarget->BindForReading();
    
    if ( FinalRenderTarget != NULL ) {
        FinalRenderTarget->Clear();
        FinalRenderTarget->Apply( renderer );
    }
    else {
        abort();//TODO:
    }
    
    /*if ( (acc % 33) == 0 ) {
        GRAPHIC_TEXTURE * texture2;
        RenderTarget->SetReadBuffer( 0 );
        texture2 = RenderTarget->GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING1" , "png", "" ));
        RenderTarget->SetReadBuffer( 1 );
        texture2 = RenderTarget->GetTargetTexture( 1 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING2" , "png", "" ));
        RenderTarget->SetReadBuffer( 2 );
        texture2 = RenderTarget->GetTargetTexture( 2 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING3" , "png", "" ));
        
        RenderTarget->SetReadBuffer( 3 );
        texture2 = RenderTarget->GetTargetTexture( 3 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING4" , "png", "" ));
        
        RenderTarget->SetReadBuffer( 4 );
        texture2 = RenderTarget->GetTargetTexture( 4 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING5" , "png", "" ));
    }*/
    
    TextureBlock1.SetTexture( RenderTarget->GetTargetTexture( 0 ) );
    TextureBlock2.SetTexture( RenderTarget->GetTargetTexture( 1 ) );
    TextureBlock3.SetTexture( RenderTarget->GetTargetTexture( 2 ) );
    TextureBlock4.SetTexture( RenderTarget->GetTargetTexture( 3 ) );
    TextureBlock5.SetTexture( RenderTarget->GetDepthTexture() );
    
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut, &TextureBlock1 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut1, &TextureBlock2 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut2, &TextureBlock3 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut3, &TextureBlock4 ) ;
    Material.SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTextureOut4, &TextureBlock5 ) ;
    
    AmbientDirectionalDefferedEffect->SetMaterial( &Material );
    PointDefferedEffect->SetMaterial( &Material );
    SpotDeferredEffect->SetMaterial( &Material, ConeObject->GetMeshTable()[0]->GetName()  );
    
    renderer.SetLightingIsEnabled( true );
    renderer.DisableDepthTest();

    PlanObject->Render( renderer, option, AmbientDirectionalDefferedEffect );
    renderer.EnableDepthTest();//GRAPHIC_SYSTEM_COMPARE_OPERATION_Less, false );
    renderer.SetDeferredLightingIsEnabled( true );
    
    GRAPHIC_CAMERA::PTR backup_camera = renderer.GetCamera();
    renderer.SetCamera( PreviousCamera );
    
    ApplyPointLightPass( renderer );
    ApplySpotLightPass( renderer );
    
    renderer.SetDeferredLightingIsEnabled( false );
    renderer.SetLightingIsEnabled( false );
    renderer.SetCamera( backup_camera );
    renderer.DisableStencilTest();

    if ( FinalRenderTarget != NULL ) {
        
        FinalRenderTarget->Discard();
        FinalRenderTarget->BindForReading();


    /*if ( (acc % 33) == 0 ) {
        
        acc = 0;
        FinalRenderTarget->BindForReading();
        FinalRenderTarget->SetReadBuffer( 0 );
        GRAPHIC_TEXTURE * texture2 = FinalRenderTarget->GetTargetTexture( 0 );
        texture2->SaveTo(CORE_FILESYSTEM_PATH::FindFilePath( "testGRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADINGFinal" , "png", "" ));*/
    }
    
    renderer.GetDescriptor().ItDoesStencilTest = false;
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyStencilPassForPoint( GRAPHIC_RENDERER & renderer, GRAPHIC_OBJECT_RENDER_OPTIONS & option, GRAPHIC_SHADER_LIGHT * light ) {
    
    renderer.EnableDepthTest();
    
    FinalRenderTarget->Discard();
    FinalRenderTarget->BindForReading();
    FinalRenderTarget->ClearStencil();
    FinalRenderTarget->Apply( renderer );
    
    renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    //renderer.DisableBlend();
    
    GRAPHIC_SYSTEM::DisableFaceCulling();
    
    renderer.EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Always, 0, 0 );
    renderer.SetStencilOperation( GRAPHIC_POLYGON_FACE_Back, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_IncrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    renderer.SetStencilOperation( GRAPHIC_POLYGON_FACE_Front, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_DecrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    
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
        
        renderer.EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Always, 0, 0xFF );
        renderer.DisableDepthTest();
        renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        renderer.SetBlendFunction( GRAPHIC_SYSTEM_BLEND_EQUATION_Add );

        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Front );
        
        SphereObject->Render( renderer, option, PointDefferedEffect );
        
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        renderer.DisableBlend();
    }
    
    renderer.SetDeferredPointIndex( -1 );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplyStencilPassForSpot( GRAPHIC_RENDERER & renderer, GRAPHIC_OBJECT_RENDER_OPTIONS & option, GRAPHIC_SHADER_LIGHT * light ) {
    
    renderer.EnableDepthTest();
    
    FinalRenderTarget->Discard();
    FinalRenderTarget->BindForReading();
    FinalRenderTarget->ClearStencil();
    FinalRenderTarget->Apply( renderer );
    
    renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
    //renderer.DisableBlend();
    
    GRAPHIC_SYSTEM::DisableFaceCulling();
    
    renderer.EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Always, 0, 0 );
    renderer.SetStencilOperation( GRAPHIC_POLYGON_FACE_Back, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_IncrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    renderer.SetStencilOperation( GRAPHIC_POLYGON_FACE_Front, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_DecrementWrap, GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep );
    
    ConeObject->Render( renderer, option, NullTechniqueEffect );
}

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::ApplySpotLightPass( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    for (unsigned int i = 0 ; i < renderer.GetSpotLightTable().size(); i++) {
        
        /*CORE_MATH_VECTOR
            vector, rs;
        CORE_MATH_QUATERNION
            orientation;
        CORE_MATH_MATRIX
            rot;*/
        
        auto light = renderer.GetSpotLightTable()[ i ];
        renderer.SetDeferredSpotIndex( i );
        
        /*vector.Set(1.0f, 0.0, 0.0, 0.0f );
        
        orientation.X( light->InternalLight.Spot.Orientation[0] );
        orientation.Y( light->InternalLight.Spot.Orientation[1] );
        orientation.Z( light->InternalLight.Spot.Orientation[2] );
        orientation.W( light->InternalLight.Spot.Orientation[3] );
        orientation.ToMatrix( rot.GetRow( 0 ) );
        
        rs = rot * vector;
        
        light->InternalLight.Spot.Direction[0] = rs.X();
        light->InternalLight.Spot.Direction[1] = rs.Y();
        light->InternalLight.Spot.Direction[2] = rs.Z();*/
        
        float scale = CalculateSpotLightSphereAndExtent( *light );
        
        option.SetScaleFactor(CORE_MATH_VECTOR( scale, scale, scale, 1.0f ) );
        option.SetPosition( light->InternalLight.Spot.Position );
        option.SetOrientation( CORE_MATH_QUATERNION( light->InternalLight.Spot.Orientation[0], light->InternalLight.Spot.Orientation[1], light->InternalLight.Spot.Orientation[2], light->InternalLight.Spot.Orientation[3] ) );
        
        ApplyStencilPassForSpot( renderer, option, light );
        
        renderer.EnableStencilTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Always, 0, 0xFF );
        renderer.DisableDepthTest();
        renderer.EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_One, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        renderer.SetBlendFunction( GRAPHIC_SYSTEM_BLEND_EQUATION_Add );
    
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Front );
        
        ConeObject->Render( renderer, option, SpotDeferredEffect );
        
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        renderer.DisableBlend();
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

void GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING::SetPreviousCamera( GRAPHIC_CAMERA::PTR camera ) {
    
    PreviousCamera = camera;
    AmbientDirectionalDefferedEffect->PreviousCamera = camera;
    SpotDeferredEffect->PreviousCamera = camera;
    PointDefferedEffect->PreviousCamera = camera;
}
