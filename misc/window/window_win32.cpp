#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>

extern "C" 
{
    #include "common.h"
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WNDCLASS CreateWindowClass(HINSTANCE hInstance)
{
    WNDCLASS result = {};

    result.lpfnWndProc   = WindowProc;
    result.hInstance     = hInstance;
    result.lpszClassName = L"className";

    return result;
}

HWND CreateSimpleWindow(WNDCLASS *wndClass, HINSTANCE hInstance)
{
    HWND result = CreateWindowEx(
        0,                                      
        wndClass->lpszClassName,                     
        L"Window",    
        WS_OVERLAPPEDWINDOW,            
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,          
        NULL,       
        hInstance,  
        NULL        
        );

    return result;
}


INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    WNDCLASS wndClass = CreateWindowClass(hInstance);
    RegisterClass(&wndClass);

    HWND window = CreateSimpleWindow(&wndClass, hInstance);

    if (window == NULL)
    {
        return 0;
    }

    ShowWindow(window, nCmdShow);

    bool running = true;

    MSG msg = {};
    while (running)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Update();
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND window, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } 
        return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC deviceContext = BeginPaint(window, &paint);

            RECT clientRect;
            GetClientRect(window, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;

            /*
            StretchDIBits(deviceContext,
                0, 0, width, height,
                0, 0, width, height,
                Buffer->Memory,
                &Buffer->Info,
                DIB_RGB_COLORS, SRCCOPY);
            */
            EndPaint(window, &paint);
        }
        return 0;
    }

    return DefWindowProc(window, uMsg, wParam, lParam);
}