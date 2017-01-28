// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2016
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 2.1.0 (2016/01/25)

#include <GTEnginePCH.h>
#include <Applications/GteEnvironment.h>
#include <LowLevel/GteLogToOutputWindow.h>
#if PLATFORM_WINDOWS
    #include <windows.h>
#endif
using namespace gte;


LogToOutputWindow::LogToOutputWindow(int flags)
    :
    Logger::Listener(flags)
{
}

void LogToOutputWindow::Report(std::string const& message)
{
    std::wstring text = Environment::Convert(message);
    
    #if PLATFORM_WINDOWS
        OutputDebugString(text.c_str());
    #endif
    }

