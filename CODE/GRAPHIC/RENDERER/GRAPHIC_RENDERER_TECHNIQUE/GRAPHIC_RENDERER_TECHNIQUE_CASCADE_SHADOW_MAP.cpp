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
    LightSourcePose() {
    
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
        LightShadowCamera[i] = new GRAPHIC_CAMERA_ORTHOGONAL( 0.1f, 10.0f, 4.0f, 4.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 9.0f, 0.0f), rt_lookat );
    }
    
    GRAPHIC_SYSTEM::SetTextureOptions(ShadowMapRenderTarget1->GetTargetTexture( 0 ), GRAPHIC_TEXTURE_FILTERING_Nearest, GRAPHIC_TEXTURE_WRAP_Border, CORE_COLOR_Transparent);
    GRAPHIC_SYSTEM::SetTextureOptions(ShadowMapRenderTarget2->GetTargetTexture( 0 ), GRAPHIC_TEXTURE_FILTERING_Nearest, GRAPHIC_TEXTURE_WRAP_Border, CORE_COLOR_Transparent );
    GRAPHIC_SYSTEM::SetTextureOptions(ShadowMapRenderTarget3->GetTargetTexture( 0 ), GRAPHIC_TEXTURE_FILTERING_Nearest, GRAPHIC_TEXTURE_WRAP_Border, CORE_COLOR_Transparent );
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::ApplyFirstPass( GRAPHIC_RENDERER & renderer ) {
    
    Camera = renderer.GetCamera();
    renderer.SetNumCascade( 0 );
    
    GRAPHIC_RENDERER::GetInstance().SetPassIndex( 1 );
    {
        for ( int i = 0; i < CascadeCount; i++) {
            
            LightShadowCamera[i]->UpdateCamera( LightSourcePose.GetPosition(), LightSourcePose.GetOrientation() );
            //LightShadowCamera[i]->UpdateCamera( CORE_MATH_VECTOR::Zero, LightSourcePose.GetOrientation() );
        }
        
        CalculateCascadeOrthoProjection( renderer );
        
        LightShadowCamera[0]->InitOrthoProjTransform(CascadeProjectionInfo[ 0 ].Left, CascadeProjectionInfo[ 0 ].Right, CascadeProjectionInfo[ 0 ].Bottom, CascadeProjectionInfo[ 0 ].Top, CascadeProjectionInfo[ 0 ].Near,  CascadeProjectionInfo[ 2 ].Far );
        GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[0] );
        renderer.SetCamera( LightShadowCamera[0] );
        
        ShadowMapRenderTarget1->Apply();
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        GRAPHIC_SYSTEM::DisableBlend();
        //GRAPHIC_SYSTEM::DisableFaceCulling();
        GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
        GRAPHIC_SYSTEM::ClearFrambufferDepth( 0.0f );
        RendererCallback( renderer );
        {
            /*static int acc = 0;
            
            acc++;
            if ( acc % 33 == 0 ) {
                
                GRAPHIC_TEXTURE * texture2;
                
                texture2= ShadowMapRenderTarget1->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth1", "png", "" ) );
            }*/
        }
        ShadowMapRenderTarget1->Discard();
        
        LightShadowCamera[1]->InitOrthoProjTransform(CascadeProjectionInfo[ 1 ].Left, CascadeProjectionInfo[ 1 ].Right, CascadeProjectionInfo[ 1 ].Bottom, CascadeProjectionInfo[ 1 ].Top, CascadeProjectionInfo[ 0 ].Near,  CascadeProjectionInfo[ 2 ].Far );
        GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[1] );
        renderer.SetCamera( LightShadowCamera[1] );
        
        ShadowMapRenderTarget2->Apply();
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        GRAPHIC_SYSTEM::DisableBlend();
        //GRAPHIC_SYSTEM::DisableFaceCulling();
        GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
        GRAPHIC_SYSTEM::ClearFrambufferDepth( 0.0f );
        RendererCallback( renderer );
        
        {
            /*static int acc = 0;
            
            acc++;
            if ( acc % 33 == 0 ) {
                
                GRAPHIC_TEXTURE * texture2;
                
                texture2= ShadowMapRenderTarget2->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth2", "png", "" ) );
            }*/
        }
        
        ShadowMapRenderTarget2->Discard();
        
        LightShadowCamera[2]->InitOrthoProjTransform(CascadeProjectionInfo[ 2 ].Left, CascadeProjectionInfo[ 2 ].Right, CascadeProjectionInfo[ 2 ].Bottom, CascadeProjectionInfo[ 2 ].Top, CascadeProjectionInfo[ 0 ].Near, CascadeProjectionInfo[ 2 ].Far );
        GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera[2] );
        renderer.SetCamera( LightShadowCamera[2] );
        
        ShadowMapRenderTarget3->Apply();
        GRAPHIC_SYSTEM::EnableBackfaceCulling( GRAPHIC_POLYGON_FACE_Back );
        GRAPHIC_SYSTEM::DisableBlend();
        //GRAPHIC_SYSTEM::DisableFaceCulling();
        GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_Greater, true );
        GRAPHIC_SYSTEM::ClearFrambufferDepth( 0.0f );
        RendererCallback( renderer );
        
        {
            /*static int acc = 0;
            
            acc++;
            if ( acc % 33 == 0 ) {
                
                GRAPHIC_TEXTURE * texture2;
                texture2 = ShadowMapRenderTarget3->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth3", "png", "" ) );
            }*/
        }
        
        ShadowMapRenderTarget3->Discard();
    }
    
    GRAPHIC_RENDERER::GetInstance().SetPassIndex( 0 );
    renderer.SetCamera( Camera );
}

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::ApplySecondPass( GRAPHIC_RENDERER & renderer ) {
    
    {
        renderer.GetCamera()->ActivateForRender();
        
        
        GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( 0, LightShadowCamera[ 0 ] );
        GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( 1, LightShadowCamera[ 1 ] );
        GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( 2, LightShadowCamera[ 2 ]);
        
        GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 0, ShadowMapRenderTarget1->GetTargetTexture( 0 ) );
        GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 1, ShadowMapRenderTarget2->GetTargetTexture( 0 ) );
        GRAPHIC_RENDERER::GetInstance().SetDepthTexture( 2, ShadowMapRenderTarget3->GetTargetTexture( 0 ) );
        
        /*{
            static int acc = 0;
            
            acc++;
            if ( acc % 33 == 0 ) {
                
                GRAPHIC_TEXTURE * texture2;
                
                ShadowMapRenderTarget1->Apply();
                texture2= ShadowMapRenderTarget1->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth1", "png", "" ) );
                
                ShadowMapRenderTarget2->Apply();
                texture2= ShadowMapRenderTarget2->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth2", "png", "" ) );
                
                ShadowMapRenderTarget3->Apply();
                texture2 = ShadowMapRenderTarget3->GetTargetTexture( 0 );
                texture2->SaveDepthTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth3", "png", "" ) );
            }
        }*/

        //PrimaryRenderTarget->Apply();
        
        LightSourcePose.GetOrientation().Normalize();
        
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

void GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP::CalculateCascadeOrthoProjection( GRAPHIC_RENDERER & renderer )
{
    CORE_MATH_MATRIX
        view_matrix = renderer.GetCamera()->GetViewMatrix(),
        inverse_view_matrix = view_matrix;
    
    renderer.SetCascadeEnd( 0, -5.0f );
    renderer.SetCascadeEnd( 1, 5.0f );
    renderer.SetCascadeEnd( 2, 10.0f );
    renderer.SetCascadeEnd( 3, 20.f );
    
    float screen_width = renderer.GetWidth();
    float screen_height = renderer.GetHeight();
    
    view_matrix.GetInverse( inverse_view_matrix );
    
    float aspect_ratio = screen_height / screen_width;
    float tanHalfHFOV = tanf( CORE_MATH_ToRadians( renderer.GetCamera()->GetFov() / 2.0f ) );
    float tanHalfVFOV = tanf( CORE_MATH_ToRadians( ( renderer.GetCamera()->GetFov() * aspect_ratio ) / 2.0f ) );
    
    GRAPHIC_CAMERA_ORTHOGONAL orth( renderer.GetCamera()->GetFar(), renderer.GetCamera()->GetNear(), screen_width, screen_height, CORE_MATH_VECTOR::Zero, LightShadowCamera[0]->GetOrientation() );
    
    CORE_MATH_MATRIX LightM = LightShadowCamera[0]->GetViewMatrix();
    //<LightShadowCamera[0]->GetViewMatrix().GetInverse( LightM );
    
    for ( int i=0; i < CascadeCount; i++ ) {
        float xn = renderer.GetCascadeEnd( i ) * tanHalfHFOV;
        float xf = renderer.GetCascadeEnd( i + 1 ) * tanHalfHFOV;
        float yn = renderer.GetCascadeEnd( i ) * tanHalfVFOV;
        float yf = renderer.GetCascadeEnd( i + 1 ) * tanHalfVFOV;
        
        CORE_MATH_VECTOR frustum_corners[ NUM_FRUSTUM_CORNERS ]={
            // near face
            CORE_MATH_VECTOR( xn, yn, renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( -xn, yn, renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( xn, -yn, renderer.GetCascadeEnd( i ), 1.0 ),
            CORE_MATH_VECTOR( -xn, -yn, renderer.GetCascadeEnd( i ), 1.0 ),
            
            // far face
            CORE_MATH_VECTOR( xf, yf, renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( -xf, yf, renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( xf, -yf, renderer.GetCascadeEnd( i + 1 ), 1.0 ),
            CORE_MATH_VECTOR( -xf, -yf, renderer.GetCascadeEnd( i + 1 ), 1.0 )
        };
        
        /**
         CORE_MATH_VECTOR frustum_corners[ NUM_FRUSTUM_CORNERS ]={
         // near face
         CORE_MATH_VECTOR( xn, renderer.GetCascadeEnd( i ), yn, 1.0 ),
         CORE_MATH_VECTOR( -xn, renderer.GetCascadeEnd( i ), yn, 1.0 ),
         CORE_MATH_VECTOR( xn, renderer.GetCascadeEnd( i ), -yn, 1.0 ),
         CORE_MATH_VECTOR( -xn, renderer.GetCascadeEnd( i ), -yn, 1.0 ),
         
         // far face
         CORE_MATH_VECTOR( xf, renderer.GetCascadeEnd( i + 1 ), yf, 1.0 ),
         CORE_MATH_VECTOR( -xf, renderer.GetCascadeEnd( i + 1 ), yf, 1.0 ),
         CORE_MATH_VECTOR( xf, renderer.GetCascadeEnd( i + 1 ), -yf, 1.0 ),
         CORE_MATH_VECTOR( -xf, renderer.GetCascadeEnd( i + 1 ), -yf, 1.0 )
         };
         */
        
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
            CORE_MATH_VECTOR vW = frustum_corners[ j ] * inverse_view_matrix;
            //const CORE_MATH_VECTOR vW2 = ::operator*( frustum_corners[ j ], inverse_view_matrix );
            
            // Transform the frustum coordinate from world to light space
            frustum_corners_l[ j ] = vW * LightM;
            
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
