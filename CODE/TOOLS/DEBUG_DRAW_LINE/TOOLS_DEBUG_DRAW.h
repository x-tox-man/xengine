//
//  TOOLS_DEBUG_DRAW_LINE.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/10/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef TOOLS_DEBUG_DRAW_LINE_hpp
#define TOOLS_DEBUG_DRAW_LINE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"
#include "CORE_HELPERS_COLOR.h"
#include "CORE_HELPERS_UNIQUE.h"

XS_CLASS_BEGIN( TOOLS_DEBUG_DRAW )

TOOLS_DEBUG_DRAW()
#if DEBUG
:
Line( NULL ),
Shader( NULL )
#endif
{
#if DEBUG
    Shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::LineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "LineShader" , "vsh", "OPENGL2" ) );
    
    Line = new GRAPHIC_OBJECT_SHAPE_LINE();
    Line->InitializeShape();
    Shader->Initialize( Line->GetShaderBindParameter() );
    Shader->SetMaterial( new GRAPHIC_MATERIAL() );
#endif
}

void DrawLine( GRAPHIC_RENDERER & renderer, const CORE_MATH_VECTOR & from, const CORE_MATH_VECTOR & to, const CORE_HELPERS_COLOR & color = CORE_COLOR_White ) {
    
#if DEBUG
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    Line->SetFrom( from );
    Line->SetTo( to );
    Line->UpdateShape();
    Line->Render( renderer, option, Shader );
    
#endif
}

static TOOLS_DEBUG_DRAW::PTR Instance;

private:

#if DEBUG
GRAPHIC_OBJECT_SHAPE_LINE::PTR
        Line;
    GRAPHIC_SHADER_EFFECT::PTR
        Shader;
#endif

XS_CLASS_END

#endif /* TOOLS_DEBUG_DRAW_LINE_hpp */
