//
//  ASSET_EDITOR.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "ASSET_EDITOR.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_DATA_LOADER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_DATA_JSON.h"

typedef std::map<CORE_FILESYSTEM_PATH, ASSET> ASSET_TYPE_TABLE;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( ASSET_EDITOR )
    XS_DEFINE_ClassMember( "AssetTable", ASSET_TYPE_TABLE, AssetTable)
XS_END_INTERNAL_MEMORY_LAYOUT

ASSET_EDITOR::ASSET_EDITOR() :
    CORE_APPLICATION(),
    ProjectPath( NULL ),
    InterfaceCamera( NULL ),
    BaseUiScreen(),
    Viewer3d(),
    ResourceContainer(),
    RefreshCallback() {
    
    SetApplicationInstance( *this );
}

ASSET_EDITOR::~ASSET_EDITOR() {
    
}

void ASSET_EDITOR::Initialize() {
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    CORE_HELPERS_CALLBACK_2<int, int> resizeCallback( &Wrapper2<ASSET_EDITOR, int, int, &ASSET_EDITOR::OnScreenResized>, this );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    GRAPHIC_RENDERER::GetInstance().SetResizeViewCallback( resizeCallback );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    
    BaseUiScreen.GetPlacement().Initialize( NULL, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR(ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight()), GRAPHIC_UI_Center );
    BaseUiScreen.Initialize();
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
    GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(&BaseUiScreen, "BaseView" );
    
    Viewer3d.Initialize();
    
    CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().Initialize();
    CORE_ABSTRACT_RUNTIME_LUA * runtime = (CORE_ABSTRACT_RUNTIME_LUA *) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[ CORE_ABSTRACT_PROGRAM_RUNTIME_Lua ];
    
    CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().BindRuntime<CORE_ABSTRACT_RUNTIME_LUA>( *runtime );
}

void ASSET_EDITOR::Finalize() {
    
}

void ASSET_EDITOR::Update( float time_step ) {
    
    Viewer3d.Update( time_step );
    GRAPHIC_UI_SYSTEM::GetInstance().Update(time_step);
}

void ASSET_EDITOR::Render() {
    
    Viewer3d.Render( GRAPHIC_RENDERER::GetInstance() );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( InterfaceCamera );
    
    GRAPHIC_UI_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
}

GRAPHIC_UI_ELEMENT * ASSET_EDITOR::CreateUIText( const char * item_name, const char * text_value, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor, GRAPHIC_UI_FRAME * parent ) {
    
    GRAPHIC_UI_TEXT * element = new GRAPHIC_UI_TEXT;
    
    CORE_RUNTIME_Abort();
    /*element->SetSize(12);
    element->SetText( text_value );
    element->SetSize( 1.0f );
    element->SetColor( CORE_COLOR_Red );
    element->SetFont( &BaseUiScreen.GetFont() );
    
    element->GetPlacement().Initialize( &BaseUiScreen.GetPlacement(),
                                       position,
                                       CORE_MATH_VECTOR::One,
                                           anchor );
    
    element->Initialize();
    
    if ( parent == NULL ) {
        
        BaseUiScreen.AddObject( element );
    
        BaseUiScreen.OnPlacementPropertyChanged();
    }
    else {
        parent->AddObject( element );
        
        parent->OnPlacementPropertyChanged();
    }*/
    
    return element;
}

GRAPHIC_UI_ELEMENT * ASSET_EDITOR::CreateUIItem( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor, GRAPHIC_UI_FRAME * parent ) {
    
    GRAPHIC_UI_ELEMENT * element = new GRAPHIC_UI_ELEMENT;
    
    element->SetIdentifier( CORE_HELPERS_IDENTIFIER( item_name ) );
    element->GetPlacement().Initialize(&BaseUiScreen.GetPlacement(), position, size, anchor);
    
    element->Initialize();
    
    if ( parent == NULL ) {
        
        BaseUiScreen.AddObject( element );
        BaseUiScreen.OnPlacementPropertyChanged();
    }
    else {
        parent->AddObject( element );
        parent->OnPlacementPropertyChanged();
    }
    
    return element;
}

GRAPHIC_UI_FRAME * ASSET_EDITOR::CreateUIFrame( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor, GRAPHIC_UI_FRAME * parent ) {
    
    GRAPHIC_UI_FRAME * frame = new GRAPHIC_UI_FRAME;
    
    frame->SetIdentifier( CORE_HELPERS_IDENTIFIER( item_name ) );
    frame->SetPosition( position );
    frame->GetPlacement().SetSize( size );
    
    frame->Initialize();
    
    if ( parent == NULL ) {
        
        BaseUiScreen.AddObject( frame );
        BaseUiScreen.OnPlacementPropertyChanged();
    }
    else {
        parent->AddObject( frame );
        parent->OnPlacementPropertyChanged();
    }
    
    return frame;
}

GRAPHIC_UI_RENDER_STYLE * ASSET_EDITOR::SetStyleForItem( int state, GRAPHIC_UI_ELEMENT * element, const char * texture_name, const CORE_HELPERS_COLOR & color ) {
    
    GRAPHIC_UI_RENDER_STYLE * default_style = new GRAPHIC_UI_RENDER_STYLE;
    
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_style );
    
    return default_style;
}

void ASSET_EDITOR::OnScreenResized( int width, int height ) {
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    CORE_MATH_VECTOR size( width, height );
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize( size );
    BaseUiScreen.GetPlacement().SetSize(size);
    
    CORE_MEMORY_ObjectSafeDeallocation( InterfaceCamera );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, width, height, CORE_MATH_VECTOR(0.0f, 0.0f), CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
}

void ASSET_EDITOR::OnDraggedPath( const char * path ) {
    
    Viewer3d.Load( path, RefreshCallback );
}

void ASSET_EDITOR::Save ( const CORE_FILESYSTEM_PATH & path ) {
    
    CORE_DATA_LOADER< ASSET_EDITOR >::Save( this, path );
}

void ASSET_EDITOR::Save( CORE_DATA_STREAM & stream ) {

    stream.Open();
    
    XS_CLASS_SERIALIZER< ASSET_EDITOR, CORE_DATA_STREAM >::template Serialize< std::true_type >( "EDITOR", *this, stream );
    
    stream.Close();
}

void ASSET_EDITOR::Load( const CORE_FILESYSTEM_PATH & path) {
    
    ProjectPath = new CORE_FILESYSTEM_PATH( path );
    
    CORE_DATA_LOADER< ASSET_EDITOR >::Load( this, path );
}

void ASSET_EDITOR::SaveAssets() {
    
}

void ASSET_EDITOR::SaveResources() {
    
}

void ASSET_EDITOR::SaveScene() {
    
}

void ASSET_EDITOR::SaveUI() {
    
}

void ASSET_EDITOR::Close() {
    
    CORE_MEMORY_ObjectSafeDeallocation( ProjectPath );
}
