# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.crg/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := liblua
LOCAL_CFLAGS    := -DLUA_ANSI
LOCAL_C_INCLUDES 	:= ../src/
LOCAL_SRC_FILES :=  ../src/lapi.c \
../src/lcode.c \
../src/lctype.c \
../src/ldebug.c \
../src/ldo.c \
../src/ldump.c \
../src/lfunc.c \
../src/lgc.c \
../src/llex.c \
../src/lmem.c \
../src/lobject.c \
../src/lopcodes.c \
../src/lparser.c \
../src/lstate.c  \
../src/lstring.c \
../src/ltable.c \
../src/ltm.c \
../src/lundump.c \
../src/lvm.c \
../src/lzio.c \
../src/lauxlib.c \
../src/lbaselib.c \
../src/lbitlib.c \
../src/lcorolib.c \
../src/ldblib.c \
../src/liolib.c \
../src/lmathlib.c \
../src/loslib.c \
../src/lstrlib.c \
../src/ltablib.c \
../src/loadlib.c \
../src/linit.c 

include $(BUILD_STATIC_LIBRARY)