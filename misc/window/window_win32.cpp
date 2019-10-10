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

    HWND hwnd = CreateSimpleWindow(&wndClass, hInstance);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        Update();
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}