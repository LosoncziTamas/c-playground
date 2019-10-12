#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>

extern "C" 
{
    #include "common.h"
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

struct OffscreenBuffer
{
    BITMAPINFO info;
    void *memory;
    int width;
    int height;
    int pitch;
};

struct WindowSize
{
    int width;
    int height;
};

static OffscreenBuffer globalbuffer;

WindowSize GetWindowSize(HWND window)
{
    WindowSize result = {};

    RECT clientRect;
    GetClientRect(window, &clientRect);
    result.width = clientRect.right - clientRect.left;
    result.height = clientRect.bottom - clientRect.top;

    return result;
}

WNDCLASS CreateWindowClass(HINSTANCE hInstance)
{
    WNDCLASS result = {};

    result.lpfnWndProc   = WindowProc;
    result.hInstance     = hInstance;
    result.lpszClassName = L"className";

    return result;
}

void Win32ResizeDIBSection(OffscreenBuffer *buffer, int width, int height)
{
    if(buffer->memory)
    {
        VirtualFree(buffer->memory, 0, MEM_RELEASE);
    }

    buffer->width = width;
    buffer->height = height;

    int BytesPerPixel = 4;

    buffer->info.bmiHeader.biSize = sizeof(buffer->info.bmiHeader);
    buffer->info.bmiHeader.biWidth = buffer->width;
    buffer->info.bmiHeader.biHeight = -buffer->height;
    buffer->info.bmiHeader.biPlanes = 1;
    buffer->info.bmiHeader.biBitCount = 32;
    buffer->info.bmiHeader.biCompression = BI_RGB;

    int BitmapmemorySize = (buffer->width*buffer->height)*BytesPerPixel;
    buffer->memory = VirtualAlloc(0, BitmapmemorySize, MEM_COMMIT, PAGE_READWRITE);
    buffer->pitch = width*BytesPerPixel;
}

void RenderStuffTobuffer(OffscreenBuffer *buffer)
{
    for (int i = 0; i < buffer->height * buffer->width; ++i)
    {
        char* pixelMem = (char*)buffer->memory + i;
        *pixelMem = 255;
    }
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
    WindowSize winSize = GetWindowSize(window);
    Win32ResizeDIBSection(&globalbuffer, winSize.width, winSize.height);
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
            WindowSize winSize = GetWindowSize(window);
            HDC deviceContext = BeginPaint(window, &paint);        
                RenderStuffTobuffer(&globalbuffer);

            StretchDIBits(deviceContext,
                0, 0, winSize.width, winSize.height,
                0, 0, winSize.width, winSize.height,
                globalbuffer.memory,
                &globalbuffer.info,
                DIB_RGB_COLORS, SRCCOPY);
            
            EndPaint(window, &paint);
        }
        return 0;
    }

    return DefWindowProc(window, uMsg, wParam, lParam);
}