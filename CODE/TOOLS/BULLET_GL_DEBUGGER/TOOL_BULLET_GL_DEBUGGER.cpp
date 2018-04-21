//
//  TOOL_BULLET_GL_DEBUGGER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/08/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "TOOL_BULLET_GL_DEBUGGER.h"
#include "GRAPHIC_RENDERER.h"

#ifdef __BULLET_PHYSICS__
TOOL_BULLET_GL_DEBUGGER::TOOL_BULLET_GL_DEBUGGER() :
    btIDebugDraw(),
    m_debugMode( 0 ),
    Line(),
    Shader() {
    
}

TOOL_BULLET_GL_DEBUGGER::~TOOL_BULLET_GL_DEBUGGER() {
    
}

void TOOL_BULLET_GL_DEBUGGER::Initialize() {
    
    Shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::LineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "LineShader" , "vsh", "OPENGL2" ) );
    
    Line.InitializeShape();
    Shader->Initialize( Line.GetShaderBindParameter() );
    Shader->SetMaterial( new GRAPHIC_MATERIAL() );
}
void TOOL_BULLET_GL_DEBUGGER::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    CORE_MATH_VECTOR
        v;
    
    v[0] = from.getX();
    v[1] = from.getY();
    v[2] = from.getZ();
    v[3] = 1.0f;
    Line.SetFrom( v );
    
    v[0] = to.getX();
    v[1] = to.getY();
    v[2] = to.getZ();
    v[3] = 1.0f;
    Line.SetTo( v );
    
    Line.UpdateShape();
    Shader->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    Line.Render( GRAPHIC_RENDERER::GetInstance(), option, Shader );
}

void TOOL_BULLET_GL_DEBUGGER::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    CORE_MATH_VECTOR
        v;
    
    v[0] = from.getX();
    v[1] = from.getY();
    v[2] = from.getZ();
    v[3] = 1.0f;
    Line.SetFrom( v );
    
    v[0] = to.getX();
    v[1] = to.getY();
    v[2] = to.getZ();
    v[3] = 1.0f;
    Line.SetTo( v );
    
    Line.UpdateShape();
    Shader->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    Line.Render( GRAPHIC_RENDERER::GetInstance(), option, Shader );
}

void TOOL_BULLET_GL_DEBUGGER::drawSphere(const btVector3& p, btScalar radius, const btVector3& color) {
    
}

void TOOL_BULLET_GL_DEBUGGER::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) {
    
}

void TOOL_BULLET_GL_DEBUGGER::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
    
}

void TOOL_BULLET_GL_DEBUGGER::reportErrorWarning(const char* warningString) {
    
}

void TOOL_BULLET_GL_DEBUGGER::draw3dText(const btVector3& location, const char* textString) {
    
}

void TOOL_BULLET_GL_DEBUGGER::setDebugMode(int debugMode) {
    
    m_debugMode = debugMode;
}

#endif
