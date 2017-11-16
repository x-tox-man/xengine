//
//  GRAPHIC_WINDOW_WINDOWS.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_WINDOW_WINDOWS__
#define __GAME_ENGINE_REBORN__GRAPHIC_WINDOW_WINDOWS__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_WINDOW.h"

#define MAX_LOADSTRING 100

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_WINDOWS, GRAPHIC_WINDOW )

GRAPHIC_WINDOW_WINDOWS();
~GRAPHIC_WINDOW_WINDOWS();

virtual void Initialize();
void Display();

void SetHInstance( HINSTANCE h_instance ) { hInstance = h_instance; }
void SetCommandLine( LPWSTR command_line ) { lpCmdLine = command_line; }
void SetCommandShow( int show_cmd ) { nCmdShow = show_cmd; }

private :

    ATOM MyRegisterClass( HINSTANCE hInstance );
    BOOL InitInstance( HINSTANCE, int );
    INT_PTR CALLBACK About( HWND, UINT, WPARAM, LPARAM );

    HINSTANCE hInst;                                // current instance
    WCHAR szTitle[ MAX_LOADSTRING ];                  // The title bar text
    WCHAR szWindowClass[ MAX_LOADSTRING ];            // the main window class name

    HINSTANCE hInstance;
    LPWSTR  lpCmdLine;
    int nCmdShow;
    HWND hWnd;
    long long StartTime;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_WINDOW_WINDOWS__) */
