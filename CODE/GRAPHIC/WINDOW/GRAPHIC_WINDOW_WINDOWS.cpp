//
//  GRAPHIC_WINDOW_WINDOWS.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_WINDOW_WINDOWS.h"
#include "CORE_APPLICATION.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_RENDERER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"

#include <GL/glew.h>
#include <time.h>
#include <Winbase.h>

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

void CreateOpenGlContext( HDC hdc );
void DeleteOpenGlContext( HDC hdc );

HGLRC OGLContext = NULL;

GRAPHIC_WINDOW_WINDOWS::GRAPHIC_WINDOW_WINDOWS() :
    GRAPHIC_WINDOW(),
    hInstance(),
    lpCmdLine(),
    nCmdShow( 0 ),
    hWnd( 0 ),
    StartTime( 0 ) {

    StartTime=clock();
}

GRAPHIC_WINDOW_WINDOWS::~GRAPHIC_WINDOW_WINDOWS() {

}

void GRAPHIC_WINDOW_WINDOWS::Initialize() {

    lstrcpyW( szTitle, L"GameEngineReborn" );
    lstrcpyW( szWindowClass, L"GAMEENGINEWINDOWS" );

    int result = MyRegisterClass( hInstance );

    // Perform application initialization:
    if ( !InitInstance( hInstance, nCmdShow ) ) {

        CORE_RUNTIME_Abort();
    }
}

void GRAPHIC_WINDOW_WINDOWS::GRAPHIC_WINDOW_WINDOWS::Display() {

    MSG msg;

    long long elapsed =  0.0f;

    while ( msg.message != WM_QUIT ) {
    
        while ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) ) {

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        elapsed = (float)( clock() - StartTime );

        StartTime = clock();

        if ( msg.message != WM_QUIT ) {

            if ( !wglMakeCurrent( GetDC( hWnd ), OGLContext ) ) {

                CORE_RUNTIME_Abort();
            }

            glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

            GRAPHIC_RENDERER::GetInstance().BeginFrame();
            GRAPHIC_RENDERER::GetInstance().Render();
            GRAPHIC_RENDERER::GetInstance().EndFrame();

            CORE_APPLICATION::GetApplicationInstance().Update( ((float) elapsed ) *0.001f );

            SwapBuffers( GetDC( hWnd ) );
        }
    }
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM GRAPHIC_WINDOW_WINDOWS::GRAPHIC_WINDOW_WINDOWS::MyRegisterClass( HINSTANCE hInstance ) {

    WNDCLASSEXW wcex;

    wcex.cbSize=sizeof( WNDCLASSEX );

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINEWINDOWS));
    wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW( IDC_GAMEENGINEWINDOWS );
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL;//LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

    return RegisterClassExW( &wcex );
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL GRAPHIC_WINDOW_WINDOWS::InitInstance( HINSTANCE hInstance, int nCmdShow ) {

    hInst = hInstance; // Store instance handle in our global variable

    RECT window_rect;

    window_rect.top = GetPositionY();
    window_rect.left = GetPositionX();
    window_rect.right = GetPositionX() + GetWidth();
    window_rect.bottom = GetPositionY() + GetHeight();

    AdjustWindowRectEx( &window_rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE );

    hWnd=CreateWindowW( szWindowClass, szTitle, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, CW_USEDEFAULT, CW_USEDEFAULT, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, nullptr, nullptr, hInstance, nullptr );

    if ( !hWnd )
    {
        return FALSE;
    }

    CreateOpenGlContext( GetDC( hWnd ) );
    CORE_APPLICATION::GetApplicationInstance().Initialize();

    ShowWindow( hWnd, nCmdShow );
    SetForegroundWindow( hWnd );
    SetFocus( hWnd );
    UpdateWindow( hWnd );

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message ) {

        case WM_MOUSEMOVE:
        {
            RECT rect;

            GetClientRect( hWnd, &rect );

            int width = ( rect.right - rect.left );
            int height =( rect.bottom - rect.top );

            float x=( float ) ( GET_X_LPARAM( lParam ) ) / width;
            float y=1.0f -( ( float ) ( GET_Y_LPARAM( lParam ) ) / height );

            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( x, y );

            break;
        }
        case WM_LBUTTONDOWN :
        {
            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonClicked();

            break;
        }
        case WM_LBUTTONUP:
        {
            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonReleased();

            break;
        }
        case WM_RBUTTONDOWN:
        {
            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetRightButtonClicked();

            break;
        }
        case WM_RBUTTONUP:
        {
            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetRightButtonReleased();

            break;
        }
        case WM_KEYDOWN :
        {
            unsigned int code = GET_WM_VKEYTOITEM_CODE( wParam );

            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyPressed( PERIPHERIC_INTERACTION_KEYBOARD::KeyFromCode( code ) );

            break;
        }
        case WM_KEYUP:
        {
            unsigned int code=GET_WM_VKEYTOITEM_CODE( wParam );

            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyReleased( PERIPHERIC_INTERACTION_KEYBOARD::KeyFromCode( code ) );

            break;
        }
        case WM_COMMAND:
        {
            int wmId=LOWORD( wParam );
            // Parse the menu selections:
            switch ( wmId ) {
        
            default:
                return DefWindowProc( hWnd, message, wParam, lParam );
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint( hWnd, &ps );
            
            // TODO: Add any drawing code that uses hdc here...
            EndPaint( hWnd, &ps );
        }
        break;
        case WM_CLOSE:
        case WM_DESTROY:
            GRAPHIC_RENDERER::GetInstance().SetRenderCallback(new CORE_HELPERS_CALLBACK());
            PostQuitMessage( 0 );
            if ( WaitForSingleObject( hWnd, 1000 ) == WAIT_TIMEOUT ) {
                
                TerminateProcess( hWnd, 0 );
            }

            CORE_APPLICATION::GetApplicationInstance().Finalize();
            
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK GRAPHIC_WINDOW_WINDOWS::About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER( lParam );
    switch ( message )
    {
    case WM_INITDIALOG:
        return ( INT_PTR ) TRUE;

    case WM_COMMAND:
        if ( LOWORD( wParam ) == IDOK || LOWORD( wParam ) == IDCANCEL )
        {
            EndDialog( hDlg, LOWORD( wParam ) );
            return ( INT_PTR ) TRUE;
        }
        break;
    }
    return ( INT_PTR ) FALSE;
}

void CreateOpenGlContext( HDC hdc ) {

    PIXELFORMATDESCRIPTOR pfd=
    {
        sizeof( PIXELFORMATDESCRIPTOR ),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
        PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
        32,                        //Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                        //Number of bits for the depthbuffer
        8,                        //Number of bits for the stencilbuffer
        0,                        //Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixel_format = ChoosePixelFormat( hdc, &pfd );

    if ( !SetPixelFormat( hdc, pixel_format, &pfd ) ) {

        CORE_RUNTIME_Abort();
    }

    OGLContext= wglCreateContext( hdc );

    if ( !wglMakeCurrent( hdc, OGLContext ) ) {

        CORE_RUNTIME_Abort();
    }

    GLint GlewInitResult=glewInit();

    if ( GLEW_OK != GlewInitResult )
    {
        const GLubyte * error=glewGetErrorString( GlewInitResult );
        printf( "ERROR: %s\n", error );
        exit( EXIT_FAILURE );
    }

    /*if ( GLEW_VERSION_4_0 )
    {
        Yay! OpenGL 1.3 is supported!
    }*/
}

void DeleteOpenGlContext( HDC hdc ) {

    wglMakeCurrent( hdc, NULL );
}