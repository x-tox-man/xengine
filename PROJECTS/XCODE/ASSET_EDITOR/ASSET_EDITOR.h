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

XS_CLASS_BEGIN_WITH_ANCESTOR(ASSET_EDITOR, CORE_APPLICATION)

    ASSET_EDITOR();
    virtual ~ASSET_EDITOR();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Update( float time_step ) override;
    virtual void Render() override;

    GRAPHIC_UI_ELEMENT * CreateItem( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor );
    GRAPHIC_UI_FRAME * CreateFrame( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor );

    GRAPHIC_UI_RENDER_STYLE * SetStyleForItem( int state, GRAPHIC_UI_ELEMENT * item, const char * texture_name, const CORE_HELPERS_COLOR & color );

    ASSET_SCREEN & GetGUIView() { return BaseUiScreen; }

private:

    void OnScreenResized( int, int );


    CORE_FILESYSTEM
        DefaultFileystem;
    GRAPHIC_CAMERA_ORTHOGONAL
        * InterfaceCamera;
    ASSET_SCREEN
        BaseUiScreen;

XS_CLASS_END

#endif /* ASSET_EDITOR_hpp */
