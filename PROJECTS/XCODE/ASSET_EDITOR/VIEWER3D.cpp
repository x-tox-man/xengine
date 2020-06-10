//
//  VIEWER3D.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 19/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "VIEWER3D.h"
#include "CORE_APPLICATION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_RENDER_TARGET.h"

VIEWER3D::VIEWER3D() :
    PointLightOne(NULL),
    PointLightTwo(NULL),
    SpotLightOne(NULL),
    SpotLightTwo(NULL),
    Camera( NULL ),
    SelectedEntity( NULL ),
    CubeObject( NULL ),
    TrigerScreenshot( false ) {
    
}

VIEWER3D::~VIEWER3D() {
    
}

void VIEWER3D::Initialize() {
    
    CORE_MATH_VECTOR position( 0.0f, 50.0f, 0.0f, 1.0f);
    
    CORE_MATH_MATRIX m;
    m.YRotate(M_PI);
    CORE_MATH_QUATERNION lookat;
    
    lookat.ToMatrix(m.GetRow(0));
    
    lookat.Normalize();
    
    Camera = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_CAMERA >();
    
    Camera->GetComponentCamera()->Initialize( 1.0f, 10000.0f, CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight(), position, CORE_MATH_VECTOR::ZAxis * lookat, CORE_MATH_VECTOR::YAxis * lookat );
    
    DirectionalLight = new GRAPHIC_SHADER_LIGHT;
    
    CORE_MATH_VECTOR diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    CORE_MATH_VECTOR direction(0.0f, -1.0f, 0.0f, 1.0f);
    
    DirectionalLight->InitializeDirectional( diffuse, direction, 0.5f, 0.5f);
    
    CORE_MATH_VECTOR diffuse_1(0.9f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR diffuse_2(0.0f, 0.0f, 0.9f, 1.0f);
    
    CORE_MATH_VECTOR direction_1(0.0f, 1.0f, 0.0f, 0.0f);
    CORE_MATH_VECTOR direction_2(0.0f, -1.0f, 0.0f, 0.0f);
    
    CORE_MATH_VECTOR point1_position(-10.0f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR point2_position(10.0f, 0.0f, 0.0f, 1.0f);
    
    PointLightOne = new GRAPHIC_SHADER_LIGHT;
    PointLightOne->InitializePoint(diffuse_1, point1_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    PointLightTwo = new GRAPHIC_SHADER_LIGHT;
    PointLightTwo->InitializePoint(diffuse_2, point2_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    SpotLightOne = new GRAPHIC_SHADER_LIGHT;
    SpotLightOne->InitializeSpot(diffuse_1, point1_position, direction_1, 0.1f, 0.2f, 0.4f, 0.001f, 1.0f, 1.0f );
    
    SpotLightTwo = new GRAPHIC_SHADER_LIGHT;
    SpotLightTwo->InitializeSpot(diffuse_2, point2_position, direction_2, 0.1f, 0.2f, 0.9f, 0.1f, 1.0f, 1.0f );
    
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( DirectionalLight );
    GRAPHIC_RENDERER::GetInstance().SetPointLight( PointLightOne, 0 );
    GRAPHIC_RENDERER::GetInstance().SetPointLight( PointLightTwo, 1 );
    GRAPHIC_RENDERER::GetInstance().SetSpotLight( SpotLightOne, 0 );
    GRAPHIC_RENDERER::GetInstance().SetSpotLight( SpotLightTwo, 1 );
    
    InitializeScene();
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( &Camera->GetComponentCamera()->GetCamera() );
}

void VIEWER3D::Update( const float time_step ) {
    
    CORE_MATH_VECTOR
        vector = PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetScreenCoordinates();
    CORE_MATH_QUATERNION
        rotation_quat;
    CORE_MATH_MATRIX
        inverse,
        rotation_mat( CORE_MATH_MATRIX::Identity );
    
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_P ) ) {
        
        TrigerScreenshot = true;
    }
    
    rotation_mat.Translate(CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    /*rotation_quat.X( 0.0f );
     rotation_quat.Y( 0.0f );
     rotation_quat.Z( 0.0f );
     rotation_quat.W( 1.0f );*/
    
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonClicked() ) {
        
        rotation_mat.XRotate( (vector[1]-0.5f)*2.0f * M_PI_2 );
        rotation_mat.ZRotate( (vector[0]-0.5f)*2.0f * M_PI_2 );
    }
    
    rotation_mat.GetInverse(inverse);
    
    rotation_quat.FromMatrix( &rotation_mat[0] );
    rotation_quat.Normalize();
    
    CORE_MATH_VECTOR
        direction(250.0f, 0.0f, 0.0f, 0.0f ),
        position = Camera->GetComponentCamera()->GetPosition(),
        result( direction * inverse );
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_Z ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] = result[0] * time_step;
        add[1] = result[1] * time_step;
        add[2] = result[2] * time_step;
        
        rot.YRotate(-M_PI_2);
        
        position += add*rot;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_S ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        rot.YRotate(-M_PI_2);
        
        position -= add*rot;
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_A ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] = result[0] * time_step;
        add[1] = result[1] * time_step;
        add[2] = result[2] * time_step;
        
        rot.ZRotate(-M_PI_2);
        
        position += add*rot;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_E ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        rot.ZRotate(-M_PI_2);
        
        position -= add*rot;
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_Q ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        position -= add*rot;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_D ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        position += add*rot;
    }

    //Camera->UpdateCamera(position, rotation_quat);
    
    Scene->Update( time_step );
}

void VIEWER3D::Render( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( &Camera->GetComponentCamera()->GetCamera() );
    renderer.SetNumCascade( 0 );
    Scene->Render( renderer, GAMEPLAY_COMPONENT_SYSTEM_MASK_All );
    RenderSelectedObjectBox();
    
    if ( TrigerScreenshot ) {
        Screenshot();
        
        TrigerScreenshot = false;
    }
}

void VIEWER3D::Load( const char * path, CORE_HELPERS_CALLBACK & callback ) {
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
        auto program = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderPoNoUVTaBi" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", "OPENGL2" ) );
    
        program->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    
        auto mesh = GRAPHIC_OBJECT::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( path ), CORE_FILESYSTEM_PATH( path ));
    
        CreateMesh( mesh, program );
    
        if ( callback.IsConnected() )
            callback();
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
}

void VIEWER3D::Screenshot() {
    
    GRAPHIC_RENDER_TARGET
        RenderTarget;
    
    RenderTarget.Initialize( CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight(), GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA, false, false, false, 0, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE_All );
    
    RenderTarget.Apply( GRAPHIC_RENDERER::GetInstance() );
    
    Scene->Render( GRAPHIC_RENDERER::GetInstance(), GAMEPLAY_COMPONENT_SYSTEM_MASK_All );
    
    GRAPHIC_TEXTURE * texture = RenderTarget.GetTargetTexture( 0 );
    texture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath( "testRenderCubeAt00" , "png", "" ) );
    
    RenderTarget.Discard();
}

void VIEWER3D::InitializeScene() {
    
    Scene = new GAMEPLAY_SCENE();
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = new GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION;
    
    bullet_system->Initialize();
    
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    Scene->InsertUpdatableSystem( bullet_system );
    
    Scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
}

void VIEWER3D::CreateMesh( GRAPHIC_OBJECT * mesh, GRAPHIC_SHADER_EFFECT * effect ) {
    
    auto mat =  new GRAPHIC_MATERIAL;
    if ( CubeObject == NULL ) {
        CubeObject = new GRAPHIC_OBJECT_SHAPE_CUBE;
        CubeObject->InitializeShape();
        
        CubeEffect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShaderColor"), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
        
        CubeEffect->Initialize( CubeObject->GetShaderBindParameter() );
        
        CubeEffect->SetMaterial( mat );
        SERVICE_LOGGER_Error( "ALL APP InitializeGraphics 57" );
    }
    static int component_index = 0;
    
    GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL;
    material->SetDiffuse( CORE_COLOR_White );
    
    effect->SetMaterial( material );
    
    GRAPHIC_MATERIAL_COLLECTION *
        collection = new GRAPHIC_MATERIAL_COLLECTION;
    
    //TODO: better
    collection->SetMaterialForName( material, mesh->GetMeshTable()[0]->GetName() );
    
    
    GAMEPLAY_COMPONENT_ENTITY * entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT_PHYSICS >();
    
    RESOURCE_PROXY * proxy_object = new RESOURCE_PROXY( mesh );
    RESOURCE_PROXY * proxy_effect = new RESOURCE_PROXY( effect );
    
    entity->GetComponentRender()->SetObject( *proxy_object );
    
    if ( mat != NULL ) {
        RESOURCE_PROXY
            proxy( collection );
        
        entity->GetComponentRender()->SetMaterialCollection( proxy );
        SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture create mat\n" );
    }
    entity->GetComponentRender()->SetEffect( *proxy_effect );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) Scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( entity );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) Scene->GetUpdatableSystemTable()[4];
    
    //( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapePlane( position );
    
    //bullet_system->AddEntity(component_entity);
}

void VIEWER3D::RenderSelectedObjectBox() {
    
    if ( SelectedEntity == NULL || CubeObject == NULL) {
        return;
    }
    
    GAMEPLAY_COMPONENT_POSITION
        * component;
    GAMEPLAY_COMPONENT_RENDER
        * component_grap;
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;

    GRAPHIC_SYSTEM::SetPolygonMode( GRAPHIC_SYSTEM_POLYGON_FILL_MODE_Line );
    
    component = ( GAMEPLAY_COMPONENT_POSITION * ) SelectedEntity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    component_grap = ( GAMEPLAY_COMPONENT_RENDER * ) SelectedEntity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    if ( component_grap == NULL ) {
        
        return;
    }

    CORE_MATH_MATRIX
        mat;
    
    options.SetPosition( component->GetPosition() );
    options.SetOrientation( component->GetOrientation() );
    options.SetScaleFactor( CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    if ( component_grap->GetEffect().GetType() == NULL || component_grap->GetObject().GetType() == NULL ) {
        
        return;
    }
    
    auto obj = component_grap->GetObject().GetResource<GRAPHIC_OBJECT>();

    obj->GetMeshTable()[0]->GetBoundingShape().GetOrientation().ToMatrix( mat.GetRow(0) );

    CubeObject->GetMeshTable()[0]->SetTransform( obj->GetMeshTable()[0]->GetTransform() * mat );

    CubeObject->UpdateGeometry( obj->GetMeshTable()[0]->GetBoundingShape().GetPosition(), obj->GetMeshTable()[0]->GetBoundingShape().GetHalfDiagonal() + CORE_MATH_VECTOR(100.0f,100.0f,100.0f,1.f) );

    CubeObject->Render(GRAPHIC_RENDERER::GetInstance(), options, CubeEffect );

    GRAPHIC_SYSTEM::SetPolygonMode( GRAPHIC_SYSTEM_POLYGON_FILL_MODE_Full );
}
