//
//  ASSET_EDITOR.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef ASSET_EDITOR_hpp
#define ASSET_EDITOR_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_APPLICATION.h"
#include "CORE_FILESYSTEM.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "ASSET_SCREEN.h"
#include "CORE_DATA_TYPES.h"
#include "CORE_HELPERS_COLOR.h"
#include "GRAPHIC_UI_TEXT.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "VIEWER3D.h"
#include "RESOURCE_CONTAINER.h"
#include "ASSET.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(ASSET_EDITOR, CORE_APPLICATION)

    ASSET_EDITOR();
    virtual ~ASSET_EDITOR();

    XS_DEFINE_SERIALIZABLE

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Update( float time_step ) override;
    virtual void Render() override;

    GRAPHIC_UI_ELEMENT * CreateUIText( const char * item_name, const char * text_value, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor, GRAPHIC_UI_FRAME * parent = NULL );
    GRAPHIC_UI_ELEMENT * CreateUIItem( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor, GRAPHIC_UI_FRAME * parent = NULL );
    GRAPHIC_UI_FRAME * CreateUIFrame( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor, GRAPHIC_UI_FRAME * parent = NULL );

    GRAPHIC_UI_RENDER_STYLE * SetStyleForItem( int state, GRAPHIC_UI_ELEMENT * item, const char * texture_name, const CORE_HELPERS_COLOR & color );

    inline CORE_FILESYSTEM_PATH * GetProjectPath() { return ProjectPath; }
    inline RESOURCE_CONTAINER & GetResourceContainer() { return ResourceContainer; }
    inline VIEWER3D * Get3dViewer() { return &Viewer3d; }

    void SetProjectPath( const CORE_FILESYSTEM_PATH & path ) {
        if ( ProjectPath ) {
            delete ProjectPath;
        }
        
        ProjectPath = new CORE_FILESYSTEM_PATH( path );
    }

    void Create3dObject(const char * path);

    ASSET_SCREEN & GetGUIView() { return BaseUiScreen; }

    void OnDraggedPath( const char * );

    void Load( const CORE_FILESYSTEM_PATH & path );
    void Save( const CORE_FILESYSTEM_PATH & path );
    void Save( CORE_DATA_STREAM & stream );

    void SaveAssets();
    void SaveResources();
    void SaveScene();
    void SaveUI();
    void Close();

private:

    void OnScreenResized( int, int );

    CORE_FILESYSTEM_PATH
        * ProjectPath;
    GRAPHIC_CAMERA_ORTHOGONAL
        * InterfaceCamera;
    ASSET_SCREEN
        BaseUiScreen;
    VIEWER3D
        Viewer3d;
    RESOURCE_CONTAINER
        ResourceContainer;
    std::map<CORE_FILESYSTEM_PATH, ASSET>
        AssetTable;

XS_CLASS_END

#endif /* ASSET_EDITOR_hpp */
