// GameEngineWindows.cpp : Defines the entry point for the application.
//

#include "APPLICATION.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_WINDOW_WINDOWS.h"
//https://support.microsoft.com/en-us/help/125750/you-receive-an-unresolved-external-symbol-winmain-16-error-message-whe

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow ) {

    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    const char * application_name = "VKSample";

    APPLICATION * Game;

    Game = new APPLICATION();

    GRAPHIC_WINDOW_WINDOWS * window;


    window=new GRAPHIC_WINDOW_WINDOWS;

    Game->SetApplicationWindow( *window );
    Game->setApplicationName( application_name );

    window->SetWidth( 1024 );
    window->SetHeight( 768 );
    window->SetPositionX( 0 );
    window->SetPositionY( 0 );

    window->SetHInstance( hInstance );
    window->SetCommandLine( lpCmdLine );
    window->SetCommandShow( nCmdShow );

    window->Initialize();

    window->Display();
}
