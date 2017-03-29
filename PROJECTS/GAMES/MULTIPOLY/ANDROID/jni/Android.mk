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
#LOCAL_SRC_FILES := /Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/ANDROID-NDK-BASE/compiled_libs/$(TARGET_ARCH_ABI)/libopenal.so

#include $(PREBUILT_SHARED_LIBRARY)

#include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cxx .cpp .cc

LOCAL_MODULE    	:= native-multipoly-app
LOCAL_C_INCLUDES 	:= /Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS \
/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS/openal_include \
/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS/openal_include/OpenAL \
/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS/png_include \
/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS/lua_include \
/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS/uv_include \
/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/HEADERS/mpg123_includes \
/Users/CBE/DevelopStatic/NDK/sources/cxx-stl/gnu-libstdc++/4.9/include

include engine.mk

LOCAL_SRC_FILES 	+= main.cpp \

LOCAL_CFLAGS 	:= -D__PLATFORM_ANDROID__ -DNDK_DEBUG=1 -DOPENGLES2 -D__AUDIO_OPENSL__=1 -DAUDIO_MPG -D__X_APP__ -DDEBUG=1 $(LOCAL_CFLAGS)

LOCAL_LDLIBS    := -llog -landroid -lGLESv2 -lOpenSLES -lEGL -lz -L/Users/CBE/DevelopStatic/NDK/sources/cxx-stl/stlport/libs/$(TARGET_ARCH_ABI) \
-l/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/compiled_libs/$(TARGET_ARCH_ABI)/libpng.a \
-l/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/compiled_libs/$(TARGET_ARCH_ABI)/liblua.a \
-l/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/compiled_libs/$(TARGET_ARCH_ABI)/libuv.a \
-l/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/compiled_libs/$(TARGET_ARCH_ABI)/libmpg123.a \
-l/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/ANDROID/compiled_libs/$(TARGET_ARCH_ABI)/libopenal.a

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

