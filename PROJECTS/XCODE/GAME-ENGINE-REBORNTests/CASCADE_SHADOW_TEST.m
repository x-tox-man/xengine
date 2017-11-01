//
//  CASCADE_SHADOW_TEST.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_RAY.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_SHAPE.h"
#include "CORE_DATA_STREAM.h"
#include "TestClass.h"
#include "TestClass2.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "ScriptEntity.h"
#include "RESOURCE.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_ATLAS_COMPILER.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_FONT.h"
#include "GRAPHIC_GLYPH.h"
#include "FONT_EDITOR.h"
#include "RESOURCE_CONTAINER.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_WINDOW_OSX_TEST.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GAMEPLAY_SCENE.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"

@interface CASCADE_SHADOW_TEST : XCTestCase

@end

@implementation CASCADE_SHADOW_TEST {
    CORE_FILESYSTEM file_system;
    GRAPHIC_WINDOW_OSX_TEST * Window;
    GRAPHIC_CAMERA
        * Camera,
        * LightShadowCamera;
    GRAPHIC_RENDER_TARGET
        RenderTarget,
        ShadowMapRenderTarget;
}

- (void)setUp {
    
    [super setUp];
    
    file_system.Initialize( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/" );
    
    CORE_FILESYSTEM::SetDefaultFilesystem( file_system );
    
    Window = new GRAPHIC_WINDOW_OSX_TEST();
    
    CORE_APPLICATION::SetApplicationInstance( *(new CORE_APPLICATION ));
    CORE_APPLICATION::GetApplicationInstance().SetApplicationWindow( *Window );
    
    Window->SetHeight( 768 );
    Window->SetWidth( 1024 );
    
    Window->Initialize();
    //Window->EnableBackgroundContext( true );
    
    CORE_MATH_QUATERNION lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 100000.0f, Window->GetWidth(), Window->GetHeight(), CORE_MATH_VECTOR::Zero, lookat );
    
    RenderTarget.Initialize( Window->GetWidth(), Window->GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, 0 );
    {
        LightShadowCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 10.0f, -10.0f, 10.0f, 10.0f, CORE_MATH_VECTOR( 0.0f, 0.0f, 5.0f, 0.0f), lookat );
        {
            CORE_MATH_MATRIX
                depthMVP;
            
            depthMVP = LightShadowCamera->GetProjectionMatrix();
            depthMVP *= LightShadowCamera->GetViewMatrix();
            
            CORE_MATH_MATRIX depthBias, biasMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                                        0.0f, 0.5f, 0.0f, 0.5f,
                                        0.0f, 0.0f, 0.5f, 0.5f,
                                        0.0f, 0.0f, 0.0f, 1.0f
                                        );
            
            depthBias = biasMatrix * depthMVP;
            
            CORE_MATH_VECTOR f,k, v( -1.5f, 0.0f, -4.0f, 1.0f ), w( 0.0f, 0.0f, 3.0f, 1.0f );
            
            f = v * depthBias;
            k = w * depthBias;
            
            printf("test");
        }
    }
    
    ShadowMapRenderTarget.InitializeDepthTexture( 1024, 1024, GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
}

-(void) testCastSimpleCubeShadowToPlan {
    //----------------- Camera setup -----------------
    CORE_MATH_MATRIX rotation_mat;
    
    rotation_mat.Translate( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.0f ) );
    
    CORE_MATH_QUATERNION lookat;
    
    lookat.FromMatrix( &rotation_mat[0] );
    lookat.Normalize();
    
    Camera->UpdateCamera( CORE_MATH_VECTOR( 0.0f, -1.0f, 5.0f, 0.0f), lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    //----------------- Object setup -----------------
    auto cube_object = new GRAPHIC_OBJECT_SHAPE_CUBE;
    
    auto plan_object = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    cube_object->InitializeShape();
    plan_object->InitializeShape();
    
    auto effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    auto shadowmap_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShadowMapEffect"), CORE_FILESYSTEM_PATH::FindFilePath( "ShadowMapEffect" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    effect->Initialize( plan_object->GetShaderBindParameter() );
    effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    shadowmap_effect->Initialize( plan_object->GetShaderBindParameter() );
    shadowmap_effect->SetMaterial( new GRAPHIC_MATERIAL );
    
    //----------------- Scene setup -----------------
    GAMEPLAY_SCENE * scene = new GAMEPLAY_SCENE();
    
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    
    scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * rd = (GAMEPLAY_COMPONENT_SYSTEM_RENDERER*) scene->GetRenderableSystemTable()[0];
    
    rd->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity<GAMEPLAY_COMPONENT_ENTITY>();
    GAMEPLAY_COMPONENT_ENTITY * component_entity2 = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity<GAMEPLAY_COMPONENT_ENTITY>();
    GAMEPLAY_COMPONENT_ENTITY * ground_component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity<GAMEPLAY_COMPONENT_ENTITY>();
    
    GAMEPLAY_COMPONENT_HANDLE position_handle, render_handle, position_handle2, render_handle2, render_handle3, position_handle3;
    
    position_handle.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity->SetCompononent( position_handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    position_handle3.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    component_entity2->SetCompononent( position_handle3, GAMEPLAY_COMPONENT_TYPE_Position );
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION * ) position_handle.GetComponent();
    pos->InitializeObservable();
    pos->SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, -4.0f, 1.0f ) );
    
    auto pos3 = (GAMEPLAY_COMPONENT_POSITION * ) position_handle3.GetComponent();
    pos3->InitializeObservable();
    pos3->SetPosition( CORE_MATH_VECTOR( -0.3f, 0.0f, -4.0f, 1.0f ) );
    
    RESOURCE_PROXY shadowmap_effect_proxy( shadowmap_effect );
    RESOURCE_PROXY effect_proxy( effect );
    RESOURCE_PROXY object_proxy( cube_object );
    RESOURCE_PROXY plan_object_proxy( plan_object );
    
    position_handle2.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    ground_component_entity->SetCompononent( position_handle2, GAMEPLAY_COMPONENT_TYPE_Position );
    
    auto pos2 = (GAMEPLAY_COMPONENT_POSITION * ) position_handle2.GetComponent();
    pos2->InitializeObservable();
    pos2->SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f, 3.0f, 1.0f ) );
    CORE_MATH_QUATERNION orientation;
    orientation.RotateY( M_PI_4 );
    
    pos2->SetOrientation(orientation);
    
    render_handle.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( effect_proxy );
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetShadowmapEffect( shadowmap_effect_proxy );
    render_handle.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( object_proxy );
    
    render_handle2.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    render_handle2.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( effect_proxy );
    render_handle2.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( plan_object_proxy );
    render_handle2.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetShadowmapEffect( shadowmap_effect_proxy );
    
    render_handle3.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    render_handle3.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetEffect( effect_proxy );
    render_handle3.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetShadowmapEffect( shadowmap_effect_proxy );
    render_handle3.GetComponent<GAMEPLAY_COMPONENT_RENDER>()->SetObject( plan_object_proxy );
    
    component_entity->SetCompononent( render_handle, GAMEPLAY_COMPONENT_TYPE_Render );
    component_entity2->SetCompononent( render_handle3, GAMEPLAY_COMPONENT_TYPE_Render );
    ground_component_entity->SetCompononent( render_handle2, GAMEPLAY_COMPONENT_TYPE_Render );
    
    //rd->AddEntity( component_entity->GetHandle(), component_entity );
    rd->AddEntity( component_entity2->GetHandle(), component_entity2 );
    rd->AddEntity( ground_component_entity->GetHandle(), ground_component_entity );
    
    GRAPHIC_RENDERER::GetInstance().SetPassIndex( 1 );
    {
        GRAPHIC_RENDERER::GetInstance().SetCamera( LightShadowCamera );
        
        ShadowMapRenderTarget.Apply();
        
        scene->Render();
        
        GRAPHIC_TEXTURE * texture2 = ShadowMapRenderTarget.GetTargetTexture();
        texture2->SaveDepthTo(CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan-depth" , "png", "" ));

        ShadowMapRenderTarget.Discard();
    }
    
    GRAPHIC_RENDERER::GetInstance().SetPassIndex( 0 );
    {
        GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
        GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera(LightShadowCamera);
        GRAPHIC_RENDERER::GetInstance().SetDepthTexture( ShadowMapRenderTarget.GetTargetTexture() );
        
        RenderTarget.Apply();
        
        scene->Render();
        
        GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture();
        texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testCastSimpleCubeShadowToPlan" , "png", "" ) );
        
        RenderTarget.Discard();
    }
    
    Window->EnableBackgroundContext( false );
}

-(void) testCascadeShadowPlans {
    
    
}

@end
