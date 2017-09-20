//
//  TOOL_BULLET_GL_DEBUGGER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/08/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef TOOL_BULLET_GL_DEBUGGER_hpp
#define TOOL_BULLET_GL_DEBUGGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include <LinearMath/btIDebugDraw.h>
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"

class TOOL_BULLET_GL_DEBUGGER : public btIDebugDraw
{
    int m_debugMode;
    
public:
    
    TOOL_BULLET_GL_DEBUGGER();
    virtual ~TOOL_BULLET_GL_DEBUGGER();
    
    void Initialize();
    
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
    
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    
    virtual void drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
    
    virtual void drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);
    
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    
    virtual void reportErrorWarning(const char* warningString);
    
    virtual void draw3dText(const btVector3& location, const char* textString);
    
    virtual void setDebugMode(int debugMode);
    
    virtual int getDebugMode() const { return m_debugMode; }
    
private:
    
    GRAPHIC_OBJECT_SHAPE_LINE
        Line;
    GRAPHIC_SHADER_EFFECT::PTR
        Shader;
};

#endif /* TOOL_BULLET_GL_DEBUGGER_hpp */
