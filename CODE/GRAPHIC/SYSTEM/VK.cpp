//
//  VK.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/01/18.
//  Copyright (c) 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM.h"

#if X_VK

    CORE_PARALLEL_LOCK_MUTEX GRAPHIC_SYSTEM::GraphicSystemLock;
    const char * GRAPHIC_SYSTEM::ShaderDirectoryPath="OPENGL2";
    CORE_HELPERS_COLOR GRAPHIC_SYSTEM::ClearColor=CORE_COLOR_Blue;

    GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {

    }

    void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version ) {

        // initialize the VkApplicationInfo structure
        VkApplicationInfo app_info={};
        app_info.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pNext=NULL;
        app_info.pApplicationName = app_name;
        app_info.applicationVersion = app_version;
        app_info.pEngineName = "XENGINE";
        app_info.engineVersion=1;
        app_info.apiVersion=VK_API_VERSION_1_0;

        // initialize the VkInstanceCreateInfo structure
        VkInstanceCreateInfo inst_info={};
        inst_info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        inst_info.pNext=NULL;
        inst_info.flags=0;
        inst_info.pApplicationInfo=&app_info;
        inst_info.enabledExtensionCount=0;
        inst_info.ppEnabledExtensionNames=NULL;
        inst_info.enabledLayerCount=0;
        inst_info.ppEnabledLayerNames=NULL;

        GFX_CHECK( vkCreateInstance( &inst_info, NULL, &VKInstance ); )
    }

    void GRAPHIC_SYSTEM::Finalize() {

        vkDestroyInstance( VKInstance, NULL );
    }

#endif