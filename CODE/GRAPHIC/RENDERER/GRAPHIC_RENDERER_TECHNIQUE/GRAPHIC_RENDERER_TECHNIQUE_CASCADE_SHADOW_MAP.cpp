//
//  GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP.h"

GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP() :
    GRAPHIC_RENDERER_TECHNIQUE(),
    CascadeProjectionInfo(),
    LightShadowCamera(),
    CascadeCount( 0 ),
    PrimaryRenderTarget( NULL ),
    ShadowMapRenderTarget() {
    
}

GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::~GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP() {
    
    for ( int i = 0; i < CascadeCount; i++) {
        
        CORE_MEMORY_ObjectSafeDeallocation( LightShadowCamera[i] );
    }
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::Initialize( GRAPHIC_RENDERER & renderer ) {
    
    CORE_MATH_QUATERNION
        rt_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    for ( int i = 0; i < CascadeCount; i++) {
        
        LightShadowCamera[i] = new GRAPHIC_CAMERA_ORTHOGONAL( renderer.GetCamera()->GetNear(), renderer.GetCamera()->GetFar(), renderer.GetCamera()->GetWidth(), renderer.GetCamera()->GetHeight(), CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
        LightShadowCamera[i]->ActivateForRender();
        
        GRAPHIC_SYSTEM::SetTextureOptions( ShadowMapRenderTarget[ i ]->GetTargetTexture( 0 ), GRAPHIC_TEXTURE_FILTERING_Nearest, GRAPHIC_TEXTURE_WRAP_Border, CORE_COLOR_Transparent );
    }
    
    ShadowMapEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShadowmapEffect"), CORE_FILESYSTEM_PATH::FindFilePath( "ShadowmapEffect" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    ShadowMapEffect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    Camera = renderer.GetCamera();
    renderer.SetNumCascade( 0 );
    renderer.EnableDepthTest();
    GRAPHIC_RENDERER_STATE_DESCRIPTOR backup_desc = renderer.GetDescriptor();
    renderer.GetDescriptor().DisableColor();
    
    {
        CalculateCascadeOrthoProjection( renderer );
        
        for ( int i = 0; i < CascadeCount; i++) {
        
            GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[ i ] );
            renderer.SetCamera( LightShadowCamera[ i ] );
            
            LightShadowCamera[ i ]->InitOrthoProjTransform(CascadeProjectionInfo[ i ].Left, CascadeProjectionInfo[ i ].Right, CascadeProjectionInfo[ i ].Bottom, CascadeProjectionInfo[ i ].Top, CascadeProjectionInfo[ i ].Near,  CascadeProjectionInfo[ i ].Far );
            
            ShadowMapRenderTarget[ i ]->Clear();
            ShadowMapRenderTarget[ i ]->Apply( renderer );
            
            renderer.DisableBlend();
            renderer.EnableDepthTest();
            
            GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
            //GRAPHIC_SYSTEM::ClearFrambufferDepth( 0.0f );
            
            renderer.SetShadowMappingEnabled( true );
            RendererCallback( renderer, GAMEPLAY_COMPONENT_SYSTEM_MASK_Opaque );
            renderer.SetShadowMappingEnabled( false );
            /*{
                static int acc = 0;
                
                acc++;
                if ( acc % 33 == 0 ) {
                    
                    GRAPHIC_TEXTURE * texture2;
                    
                    texture2= ShadowMapRenderTarget[ i ]->GetTargetTexture( 0 );
                    texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth1", "png", "" ) );
                }
            }*/
            ShadowMapRenderTarget[ i ]->Discard();
        }
    }
    
    renderer.SetDescriptor( backup_desc );
    renderer.SetCamera( Camera );
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    {
        renderer.GetCamera()->ActivateForRender();
        
        for ( int i = 0; i < CascadeCount; i++) {
            
            renderer.SetShadowMapCamera( i, LightShadowCamera[ i ] );
            renderer.SetDepthTexture( i, ShadowMapRenderTarget[ i ]->GetDepthTexture() );
        }
        
        /*{
            static int acc = 0;
            
            acc++;
            if ( acc % 33 == 0 ) {
                
                GRAPHIC_TEXTURE * texture2;
                
                ShadowMapRenderTarget[ 0 ]->Apply();
                texture2= ShadowMapRenderTarget[ 0 ]->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth1", "png", "" ) );
                
                ShadowMapRenderTarget[ 1 ]->Apply();
                texture2= ShadowMapRenderTarget[ 1 ]->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth2", "png", "" ) );
                
                ShadowMapRenderTarget[ 2 ]->Apply();
                texture2 = ShadowMapRenderTarget[ 2 ]->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth3", "png", "" ) );
            }
        }*/

        //PrimaryRenderTarget->Apply();
        
        renderer.SetNumCascade( CascadeCount );
        //RendererCallback1( renderer );
        //renderer.SetNumCascade( 0 );
        
#if DEBUG
        /*renderer.SetLightingIsEnabled( false );
        renderer.GetCamera()->GetFustrum().DebugDraw( *Camera);
        renderer.SetLightingIsEnabled( true );
        
        if ( DebugRenderActive ) {
            auto detect = ((GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION *) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[4]);
            
            detect->DebugDrawWorld();
        }*/
#endif
        
        //PrimaryRenderTarget->Discard();
        
        //GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 0, NULL );
        //GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 1, NULL );
        //GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 2, NULL );
    }
    
    //renderer.SetLightingIsEnabled( false );
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::UpdateCameras( const CORE_MATH_VECTOR & position , const CORE_MATH_VECTOR & direction, const CORE_MATH_VECTOR & up ) {
    
    for ( int i = 0; i < CascadeCount; i++) {
        
        LightShadowCamera[i]->UpdateCamera( position, direction, up );
    }
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::CalculateCascadeOrthoProjection( GRAPHIC_RENDERER & renderer )
{
    float screen_width = renderer.GetWidth();
    float screen_height = renderer.GetHeight();
    
    float aspect_ratio = screen_height / screen_width;
    float tanHalfHFOV = tanf( CORE_MATH_ToRadians( renderer.GetCamera()->GetFov() / 2.0f ) );
    float tanHalfVFOV = tanf( CORE_MATH_ToRadians( ( renderer.GetCamera()->GetFov() * aspect_ratio ) / 2.0f ) );
    GRAPHIC_CAMERA
        temp( renderer.GetCamera()->GetNear(), renderer.GetCamera()->GetFar(), screen_width, screen_height, renderer.GetCamera()->GetPosition(), renderer.GetCamera()->GetDirection(), renderer.GetCamera()->GetUp() );
    CORE_MATH_MATRIX
        view_matrix = temp.GetViewMatrix();
    
    temp.GetViewMatrix().GetInverse( view_matrix );
    
    renderer.SetCascadeEnd( 0, -5.0f );
    renderer.SetCascadeEnd( 1, 5.0f );
    renderer.SetCascadeEnd( 2, 30.0f );
    renderer.SetCascadeEnd( 3, 1500.0f );
    
    GRAPHIC_CAMERA orth( renderer.GetCamera()->GetNear(), renderer.GetCamera()->GetFar(), screen_width, screen_height, renderer.GetCamera()->GetPosition(), LightShadowCamera[0]->GetDirection(), LightShadowCamera[0]->GetUp() );
    
    CORE_MATH_MATRIX LightM = orth.GetViewMatrix();
    
    for ( int i=0; i < CascadeCount; i++ ) {
        
        float xn = renderer.GetCascadeEnd( i ) * tanHalfHFOV;
        float xf = renderer.GetCascadeEnd( i + 1 ) * tanHalfHFOV;
        float yn = renderer.GetCascadeEnd( i ) * tanHalfVFOV;
        float yf = renderer.GetCascadeEnd( i + 1 ) * tanHalfVFOV;
        
        CORE_MATH_VECTOR frustum_corners[ NUM_FRUSTUM_CORNERS ]={
            // near face
            CORE_MATH_VECTOR( xn, yn, -renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( -xn, yn, -renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( xn, -yn, -renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( -xn, -yn, -renderer.GetCascadeEnd( i ), 1.0 ),
            
            // far face
            CORE_MATH_VECTOR( xf, yf, -renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( -xf, yf, -renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( xf, -yf, -renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( -xf, -yf, -renderer.GetCascadeEnd( i + 1 ), 1.0 )
        };
        
        //What we see above matches step #1 of the description in the background section on how to calculate the orthographic projections for the cascades.The frustumCorners array is populated with the eight corners of each cascade in view space.Note that since the field of view is provided only for the horizontal axis we have to extrapolate it for the vertical axis( e.g, if the horizontal field of view is 90 degrees and the window has a width of 1000 and a height of 500 the vertical field of view will be only 45 degrees ).
        
        CORE_MATH_VECTOR frustum_corners_l[ NUM_FRUSTUM_CORNERS ];
        
        float minX= 1000000000.0f;
        float maxX= -1000000000.0f;
        float minY= 1000000000.0f;
        float maxY = -1000000000.0f;
        float minZ = 1000000000.0f;
        float maxZ= -1000000000.0f;
        
        for ( int j=0; j < NUM_FRUSTUM_CORNERS; j++ ) {
            
            // Transform the frustum coordinate from view to world space
            CORE_MATH_VECTOR vW = view_matrix * frustum_corners[ j ];
            //const CORE_MATH_VECTOR vW2 = ::operator*( frustum_corners[ j ], inverse_view_matrix );
            
            // Transform the frustum coordinate from world to light space
            frustum_corners_l[ j ] = LightM * vW;
            
            minX=fmin( minX, frustum_corners_l[ j ].X() );
            maxX=fmax( maxX, frustum_corners_l[ j ].X() );
            minY=fmin( minY, frustum_corners_l[ j ].Y() );
            maxY=fmax( maxY, frustum_corners_l[ j ].Y() );
            minZ=fmin( minZ, frustum_corners_l[ j ].Z() );
            maxZ=fmax( maxZ, frustum_corners_l[ j ].Z() );
        }
        //The above code contains step #2 until #4. Each frustum corner coordinate is multiplied by the inverse view transform in order to bring it into world space.It is then multiplied by the light transform in order to move it into light space.We then use a series of min / max functions in order to find the size of the bounding box of the cascade in light space.
        
        CascadeProjectionInfo[ i ].Right=maxX;
        CascadeProjectionInfo[ i ].Left=minX;
        CascadeProjectionInfo[ i ].Bottom=minY;
        CascadeProjectionInfo[ i ].Top=maxY;
        CascadeProjectionInfo[ i ].Far=maxZ;
        CascadeProjectionInfo[ i ].Near=minZ;
    }
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::DebugFustrum( GRAPHIC_RENDERER & renderer ) {
    
    LightShadowCamera[ 0 ]->GetFustrum().DebugDraw( *renderer.GetCamera() );
    LightShadowCamera[ 1 ]->GetFustrum().DebugDraw( *renderer.GetCamera() );
    LightShadowCamera[ 2 ]->GetFustrum().DebugDraw( *renderer.GetCamera() );
}
