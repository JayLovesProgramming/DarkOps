#include <windows.h>
#include "include/cef_app.h"
#include "include/internal/cef_win.h"
#include "include/internal/cef_types_wrappers.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h" // Include only on Windows
#include <iostream>

bool InitCEF(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, CefRefPtr<CefApp> app = nullptr)
{
#if defined(CEF_USE_SANDBOX)
    CefScopedSandboxInfo scoped_sandbox;
#endif

    // Create the main CEF application object using the Windows-specific constructor
    CefMainArgs main_args(hInstance);

    // Execute the secondary process if needed
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0)
    {
        return false; // Indicates that the secondary process was executed
    }

    // Specify CEF global settings
    CefSettings settings;

#if defined(CEF_USE_SANDBOX)
    settings.no_sandbox = false;
#else
    //settings.no_sandbox = true;
#endif

    // Initialize CEF
    if (!CefInitialize(main_args, settings, app, nullptr))
    {
        return false;
    }

    return true;
}

void ShutdownCEF()
{
    CefShutdown();
    std::cout << "SHUTDOWN CEF" << std::endl;
}

void CefLoop()
{
    CefRunMessageLoop();
    ShutdownCEF();
}
