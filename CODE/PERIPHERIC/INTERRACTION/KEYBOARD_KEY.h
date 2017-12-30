//
//  KEYBOARD_KEY.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_KEYBOARD_KEY_h
#define GAME_ENGINE_REBORN_KEYBOARD_KEY_h

#include "CORE_RUNTIME_ENVIRONMENT.h"

#if PLATFORM_OSX
    enum KEYBOARD_KEY {
        KEYBOARD_KEY_NUM_None,
        KEYBOARD_KEY_NUM_0,
        KEYBOARD_KEY_NUM_1,
        KEYBOARD_KEY_NUM_2,
        KEYBOARD_KEY_NUM_3,
        KEYBOARD_KEY_NUM_4,
        KEYBOARD_KEY_NUM_5,
        KEYBOARD_KEY_NUM_6,
        KEYBOARD_KEY_NUM_7,
        KEYBOARD_KEY_NUM_8,
        KEYBOARD_KEY_NUM_9,

        KEYBOARD_KEY_CHAR_A,
        KEYBOARD_KEY_CHAR_B,
        KEYBOARD_KEY_CHAR_C,
        KEYBOARD_KEY_CHAR_D,
        KEYBOARD_KEY_CHAR_E,
        KEYBOARD_KEY_CHAR_F,
        KEYBOARD_KEY_CHAR_G,
        KEYBOARD_KEY_CHAR_H,
        KEYBOARD_KEY_CHAR_I,
        KEYBOARD_KEY_CHAR_J,
        KEYBOARD_KEY_CHAR_K,
        KEYBOARD_KEY_CHAR_L,
        KEYBOARD_KEY_CHAR_M,
        KEYBOARD_KEY_CHAR_N,
        KEYBOARD_KEY_CHAR_O,
        KEYBOARD_KEY_CHAR_P,
        KEYBOARD_KEY_CHAR_Q,
        KEYBOARD_KEY_CHAR_R,
        KEYBOARD_KEY_CHAR_S,
        KEYBOARD_KEY_CHAR_T,
        KEYBOARD_KEY_CHAR_U,
        KEYBOARD_KEY_CHAR_V,
        KEYBOARD_KEY_CHAR_W,
        KEYBOARD_KEY_CHAR_X,
        KEYBOARD_KEY_CHAR_Y,
        KEYBOARD_KEY_CHAR_Z,

        KEYBOARD_KEY_F_1,
        KEYBOARD_KEY_F_2,
        KEYBOARD_KEY_F_3,
        KEYBOARD_KEY_F_4,
        KEYBOARD_KEY_F_5,
        KEYBOARD_KEY_F_6,
        KEYBOARD_KEY_F_7,
        KEYBOARD_KEY_F_8,
        KEYBOARD_KEY_F_9,
        KEYBOARD_KEY_F_10,
        KEYBOARD_KEY_F_11,
        KEYBOARD_KEY_F_12,

        KEYBOARD_KEY_CTRL_LEFT,
        KEYBOARD_KEY_CTRL_RIGHT,
        KEYBOARD_KEY_ALT_LEFT,
        KEYBOARD_KEY_ALT_RIGHT,
        KEYBOARD_KEY_MAJ_LEFT,
        KEYBOARD_KEY_MAJ_RIGHT,
        KEYBOARD_KEY_TAB,
        KEYBOARD_KEY_ESC,
        KEYBOARD_KEY_ENTER,
        KEYBOARD_KEY_BACKSPACE,
        KEYBOARD_KEY_SPACE,
        KEYBOARD_KEY_ARROW_LEFT = 0x7B,
        KEYBOARD_KEY_ARROW_RIGHT = 0x7C,
        KEYBOARD_KEY_ARROW_UP = 0x7E,
        KEYBOARD_KEY_ARROW_DOWN = 0x7D,
        KEYBOARD_KEY_Count
    };
#elif PLATFORM_WINDOWS
    enum KEYBOARD_KEY {
        KEYBOARD_KEY_NUM_None,
        KEYBOARD_KEY_NUM_0=0x30,
        KEYBOARD_KEY_NUM_1=0x31,
        KEYBOARD_KEY_NUM_2=0x32,
        KEYBOARD_KEY_NUM_3=0x33,
        KEYBOARD_KEY_NUM_4=0x34,
        KEYBOARD_KEY_NUM_5=0x35,
        KEYBOARD_KEY_NUM_6=0x36,
        KEYBOARD_KEY_NUM_7=0x37,
        KEYBOARD_KEY_NUM_8=0x38,
        KEYBOARD_KEY_NUM_9=0x39,

        KEYBOARD_KEY_CHAR_A=0x41,
        KEYBOARD_KEY_CHAR_B=0x42,
        KEYBOARD_KEY_CHAR_C=0x43,
        KEYBOARD_KEY_CHAR_D=0x44,
        KEYBOARD_KEY_CHAR_E=0x45,
        KEYBOARD_KEY_CHAR_F=0x46,
        KEYBOARD_KEY_CHAR_G=0x47,
        KEYBOARD_KEY_CHAR_H=0x48,
        KEYBOARD_KEY_CHAR_I=0x49,
        KEYBOARD_KEY_CHAR_J=0x4A,
        KEYBOARD_KEY_CHAR_K=0x4B,
        KEYBOARD_KEY_CHAR_L=0x4C,
        KEYBOARD_KEY_CHAR_M=0x4D,
        KEYBOARD_KEY_CHAR_N=0x4E,
        KEYBOARD_KEY_CHAR_O=0x4F,
        KEYBOARD_KEY_CHAR_P=0x50,
        KEYBOARD_KEY_CHAR_Q=0x51,
        KEYBOARD_KEY_CHAR_R=0x52,
        KEYBOARD_KEY_CHAR_S=0x53,
        KEYBOARD_KEY_CHAR_T=0x54,
        KEYBOARD_KEY_CHAR_U=0x55,
        KEYBOARD_KEY_CHAR_V=0x56,
        KEYBOARD_KEY_CHAR_W=0x57,
        KEYBOARD_KEY_CHAR_X=0x58,
        KEYBOARD_KEY_CHAR_Y=0x59,
        KEYBOARD_KEY_CHAR_Z=0x5A,

        KEYBOARD_KEY_F_1=0x72,
        KEYBOARD_KEY_F_2=0x73,
        KEYBOARD_KEY_F_3=0x74,
        KEYBOARD_KEY_F_4=0x75,
        KEYBOARD_KEY_F_5=0x76,
        KEYBOARD_KEY_F_6=0x77,
        KEYBOARD_KEY_F_7=0x78,
        KEYBOARD_KEY_F_8=0x79,
        KEYBOARD_KEY_F_9=0x7A,
        KEYBOARD_KEY_F_10=0x7B,
        KEYBOARD_KEY_F_11=0x7C,
        KEYBOARD_KEY_F_12=0x7D,

        KEYBOARD_KEY_CTRL_LEFT=0x11,
        KEYBOARD_KEY_CTRL_RIGHT=0x11,
        KEYBOARD_KEY_ALT_LEFT=0x12,
        KEYBOARD_KEY_ALT_RIGHT=0x12,
        KEYBOARD_KEY_MAJ_LEFT=0x10,
        KEYBOARD_KEY_MAJ_RIGHT=0x10,
        KEYBOARD_KEY_TAB=0x09,
        KEYBOARD_KEY_ESC=0x1B,
        KEYBOARD_KEY_ENTER=0x0D,
        KEYBOARD_KEY_BACKSPACE=0x08,
        KEYBOARD_KEY_SPACE=0x20,
        KEYBOARD_KEY_ARROW_LEFT=0x25,
        KEYBOARD_KEY_ARROW_RIGHT=0x27,
        KEYBOARD_KEY_ARROW_UP=0x26,
        KEYBOARD_KEY_ARROW_DOWN=0x28,
        KEYBOARD_KEY_Count
    };
#else
enum KEYBOARD_KEY {
    KEYBOARD_KEY_NUM_None,
    KEYBOARD_KEY_NUM_0,
    KEYBOARD_KEY_NUM_1,
    KEYBOARD_KEY_NUM_2,
    KEYBOARD_KEY_NUM_3,
    KEYBOARD_KEY_NUM_4,
    KEYBOARD_KEY_NUM_5,
    KEYBOARD_KEY_NUM_6,
    KEYBOARD_KEY_NUM_7,
    KEYBOARD_KEY_NUM_8,
    KEYBOARD_KEY_NUM_9,

    KEYBOARD_KEY_CHAR_A,
    KEYBOARD_KEY_CHAR_B,
    KEYBOARD_KEY_CHAR_C,
    KEYBOARD_KEY_CHAR_D,
    KEYBOARD_KEY_CHAR_E,
    KEYBOARD_KEY_CHAR_F,
    KEYBOARD_KEY_CHAR_G,
    KEYBOARD_KEY_CHAR_H,
    KEYBOARD_KEY_CHAR_I,
    KEYBOARD_KEY_CHAR_J,
    KEYBOARD_KEY_CHAR_K,
    KEYBOARD_KEY_CHAR_L,
    KEYBOARD_KEY_CHAR_M,
    KEYBOARD_KEY_CHAR_N,
    KEYBOARD_KEY_CHAR_O,
    KEYBOARD_KEY_CHAR_P,
    KEYBOARD_KEY_CHAR_Q,
    KEYBOARD_KEY_CHAR_R,
    KEYBOARD_KEY_CHAR_S,
    KEYBOARD_KEY_CHAR_T,
    KEYBOARD_KEY_CHAR_U,
    KEYBOARD_KEY_CHAR_V,
    KEYBOARD_KEY_CHAR_W,
    KEYBOARD_KEY_CHAR_X,
    KEYBOARD_KEY_CHAR_Y,
    KEYBOARD_KEY_CHAR_Z,

    KEYBOARD_KEY_F_1,
    KEYBOARD_KEY_F_2,
    KEYBOARD_KEY_F_3,
    KEYBOARD_KEY_F_4,
    KEYBOARD_KEY_F_5,
    KEYBOARD_KEY_F_6,
    KEYBOARD_KEY_F_7,
    KEYBOARD_KEY_F_8,
    KEYBOARD_KEY_F_9,
    KEYBOARD_KEY_F_10,
    KEYBOARD_KEY_F_11,
    KEYBOARD_KEY_F_12,

    KEYBOARD_KEY_CTRL_LEFT,
    KEYBOARD_KEY_CTRL_RIGHT,
    KEYBOARD_KEY_ALT_LEFT,
    KEYBOARD_KEY_ALT_RIGHT,
    KEYBOARD_KEY_MAJ_LEFT,
    KEYBOARD_KEY_MAJ_RIGHT,
    KEYBOARD_KEY_TAB,
    KEYBOARD_KEY_ESC,
    KEYBOARD_KEY_ENTER,
    KEYBOARD_KEY_BACKSPACE,
    KEYBOARD_KEY_SPACE,
    KEYBOARD_KEY_ARROW_LEFT,
    KEYBOARD_KEY_ARROW_RIGHT,
    KEYBOARD_KEY_ARROW_UP,
    KEYBOARD_KEY_ARROW_DOWN,
    KEYBOARD_KEY_Count
};
#endif

#endif
