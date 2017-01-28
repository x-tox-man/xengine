# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_MODULE := openal
#LOCAL_SRC_FILES := /Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/libopenal.so

#include $(PREBUILT_SHARED_LIBRARY)

#include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cxx .cpp .cc

LOCAL_MODULE    	:= nativeapptest
LOCAL_C_INCLUDES 	:= /Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS/openal_include \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS/openal_include/OpenAL \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS/png_include \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS/lua_include \
/Users/CBE/DevelopStatic/NDK/sources/cxx-stl/gnu-libstdc++/4.9/include

LOCAL_SRC_FILES 	:= main.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/AUDIO/AUDIO_INTERFACE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/AUDIO/AUDIO_MP3_LOADER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/AUDIO/AUDIO_SOUND.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/AUDIO/AUDIO_SOUND_BANK.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/AUDIO/AUDIO_SYSTEM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/AUDIO/OPENAL/AUDIO_OPENAL.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/CORE_ABSTRACT_PROGRAM_FACTORY.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/CORE_ABSTRACT_PROGRAM_MANAGER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/CORE_ABSTRACT_PROGRAM_RUNTIME.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/CORE_ABSTRACT_PROGRAM_STATE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/GOOGLE_CHROME_V8/CORE_ABSTRACT_PROGRAM_V8.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/GOOGLE_CHROME_V8/CORE_ABSTRACT_RUNTIME_V8.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/LUA/CORE_ABSTRACT_PROGRAM_LUA.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/ABSTRACT/PROGRAM/LUA/CORE_ABSTRACT_RUNTIME_LUA.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/APPLICATION/CORE_APPLICATION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/DATA/BUFFER/CORE_DATA_BUFFER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/DATA/STREAM/CORE_DATA_STREAM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/CALLBACK/CORE_HELPERS_CALLBACK.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/CLASS/CORE_HELPERS_CLASS.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/IDENTIFIER/CORE_HELPER_UNIQUE_IDENTIFIER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/IDENTIFIER/CORE_HELPERS_IDENTIFIER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/IDENTIFIER/CORE_HELPERS_IDENTIFIER_SYSTEM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/LOGGER/CORE_HELPERS_LOGGER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/SCALAR/CORE_HELPERS_SCALAR.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/HELPERS/UNIQUE/CORE_HELPERS_UNIQUE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/MATRIX/CORE_MATH_MATRIX.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/POSE/CORE_MATH_POSE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/QUATERNION/CORE_MATH_QUATERNION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/RAY/CORE_MATH_RAY.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/SHAPE/CORE_MATH_SHAPE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/SHAPE/CORE_MATH_SHAPE_BOX.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/SHAPE/CORE_MATH_SHAPE_RECTANGLE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/SHAPE/CORE_MATH_SHAPE_SPHERE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MATH/VECTOR/CORE_MATH_VECTOR.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/MEMORY/ALLOCATOR/CORE_MEMORY_ALLOCATOR.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/CORE/TIMELINE/CORE_TIMELINE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/FILESYSTEM/CORE_FILESYSTEM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/FILESYSTEM/CORE_FILESYSTEM_FILE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/FILESYSTEM/CORE_FILESYSTEM_FILE_ANDROID.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/FILESYSTEM/CORE_FILESYSTEM_PATH.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/FILESYSTEM/CORE_FILESYSTEM_PATH_ANDROID.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/FIXED_STATE/CORE_FIXED_STATE_MACHINE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/ACTION/GAMEPLAY_ACTION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/ACTION/GAMEPLAY_ACTION_SYSTEM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT_ANIMATION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT_ENTITY.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT_MANAGER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT_PHYSICS.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT_POSITION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/GAMEPLAY_COMPONENT_RENDER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM_PICKING.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM_RENDERER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/COMPONENT/SYSTEM/GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GAMEPLAY/SCENE/GAMEPLAY_SCENE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/CAMERA/GRAPHIC_CAMERA.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/CAMERA/GRAPHIC_CAMERA_ORTHOGONAL.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/ANIMATION/GRAPHIC_MESH_ANIMATION.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/ANIMATION/GRAPHIC_MESH_ANIMATION_JOINT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/ANIMATION/GRAPHIC_MESH_ANIMATION_MODE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/ANIMATION/GRAPHIC_MESH_ANIMATION_SKELETON.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/ANIMATION/GRAPHIC_MESH_SUB_SKELETON.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/GRAPHIC_MESH.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/GRAPHIC_MESH_MANAGER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/GRAPHIC_MESH_OPENGLES2.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/GRAPHIC_MESH_POLYGON_RENDER_MODE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/MESH/GRAPHIC_MESH_SURFACE_RENDER_MODE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/GRAPHIC_OBJECT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/GRAPHIC_OBJECT_ANIMATED.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_AXIS.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_CUBE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_GRID.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_LINE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_PLAN.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/OBJECT/SHAPE/GRAPHIC_OBJECT_SHAPE_SPHERE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/RENDERER/GRAPHIC_RENDERER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SHADER/GRAPHIC_SHADER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SHADER/GRAPHIC_SHADER_ATTRIBUTE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SHADER/GRAPHIC_SHADER_BIND.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SHADER/GRAPHIC_SHADER_OPENGLES2.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SHADER/PROGRAM/GRAPHIC_SHADER_PROGRAM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SHADER/PROGRAM/GRAPHIC_SHADER_PROGRAM_OPENGLES2.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/SYSTEM/OPENGLES_2.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/TEXT/GRAPHIC_FONT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/TEXT/GRAPHIC_TEXT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/TEXTURE/GRAPHIC_TEXTURE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/TEXTURE/GRAPHIC_TEXTURE_ATLAS.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/TEXTURE/GRAPHIC_TEXTURE_BLOCK.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/TEXTURE/GRAPHIC_TEXTURE_INFO.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/UI/GRAPHIC_UI_ELEMENT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/UI/GRAPHIC_UI_FRAME.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/UI/GRAPHIC_UI_PLACEMENT.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/UI/GRAPHIC_UI_RENDER_STYLE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/WINDOW/GRAPHIC_WINDOW.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/GRAPHIC/WINDOW/GRAPHIC_WINDOW_ANDROID.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/PERIPHERIC/INTERRACTION/PERIPHERIC_INTERACTION_KEYBOARD.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/PERIPHERIC/INTERRACTION/PERIPHERIC_INTERACTION_MOUSE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/PERIPHERIC/INTERRACTION/PERIPHERIC_INTERACTION_SYSTEM.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/PERIPHERIC/INTERRACTION/PERIPHERIC_INTERACTION_TOUCH.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/RESOURCE/IMAGE/PNG/RESOURCE_IMAGE_PNG_LOADER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/RESOURCE/IMAGE/PNG/RESOURCE_IMAGE_PNG_WRITER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/RESOURCE/IMAGE/RESOURCE_IMAGE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/RESOURCE/RESOURCE.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/RESOURCE/RESOURCE_COMPILER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/RESOURCE/RESOURCE_LOADER.cpp \
/Users/CBE/DevelopProjects/game-engine/CODE/SERVICE/LOGGER/SERVICE_LOGGER.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/Application.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_MAIN_WINDOW.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/TestClass2.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/TestClass.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/ScriptEntity.cpp

LOCAL_CFLAGS 	:= -D__PLATFORM_ANDROID__ -DNDK_DEBUG=1 -DOPENGLES2 -D__X_APP__ -DDEBUG=1 $(LOCAL_CFLAGS)

LOCAL_LDLIBS    := -llog -landroid -lGLESv2 -lEGL -lz -L/Users/CBE/DevelopStatic/NDK/sources/cxx-stl/stlport/libs/$(TARGET_ARCH_ABI) \
-l/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/libpng.a \
-l/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/liblua.a

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

