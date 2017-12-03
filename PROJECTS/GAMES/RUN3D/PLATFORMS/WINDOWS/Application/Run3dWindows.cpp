// GameEngineWindows.cpp : Defines the entry point for the application.
//

#include "Run3dWindows.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "../../../CODE/APPLICATION/RUN3D_APPLICATION.h"
#include "GRAPHIC_WINDOW_WINDOWS.h"

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow ) {

    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    const char * application_name = "Run 3d";

    RUN3D_APPLICATION * Game;

    Game = new RUN3D_APPLICATION();

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
