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
/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/HEADERS/uv_include \
/Users/CBE/DevelopStatic/NDK/sources/cxx-stl/gnu-libstdc++/4.9/include

include engine.mk

LOCAL_SRC_FILES 	+= main.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/Application.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_COMMAND.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_GAMEPLAY_COMMAND_ACTION_FIRE.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_GAMEPLAY_COMMAND_ORDER_ATTACK.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_GAMEPLAY_COMMAND_ORDER_BUILD.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_GAMEPLAY_COMMAND_ORDER_MOVE.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_MAIN_WINDOW.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_NETWORK_COMMAND_CLIENT_QUIT.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_NETWORK_COMMAND_CLIENT_READY.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/APPLICATION_OPTION_WINDOW.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/TestClass2.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/TestClass.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/ApplicationSoundBank.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/ApplicationTestCommands.cpp \
/Users/CBE/DevelopProjects/game-engine/PROJECTS/XCODE/GAME-ENGINE-REBORN/ScriptEntity.cpp

LOCAL_CFLAGS 	:= -D__PLATFORM_ANDROID__ -DNDK_DEBUG=1 -DOPENGLES2 -D__X_APP__ -DDEBUG=1 $(LOCAL_CFLAGS)

LOCAL_LDLIBS    := -llog -landroid -lGLESv2 -lEGL -lz -L/Users/CBE/DevelopStatic/NDK/sources/cxx-stl/stlport/libs/$(TARGET_ARCH_ABI) \
-l/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/libpng.a \
-l/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/liblua.a \
-l/Users/CBE/DevelopProjects/game-engine/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/libuv.a

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

