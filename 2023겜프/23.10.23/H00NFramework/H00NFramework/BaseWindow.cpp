#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"

int BaseWindow::Run(HINSTANCE hInstance, int cmdShow)
{
    this->hInstance = hInstance;

    this->MyRegisterClass();
    this->WindowCreate();
    this->WindowShow(cmdShow);
    this->WindowUpdate();

    if (Core::GetInstance()->Init(hWnd, resolution) == false)
    {
        MessageBox(hWnd, L"Core Instance Initialize Failed", L"ERROR", MB_OK);
    }
    
    return MessageLoop();
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H00NFRAMEWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = nullptr; // MAKEINTRESOURCEW(IDC_H00NFRAMEWORK);
    wcex.lpszClassName  = WINDOW_CLASS_NAME;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{
    int winPosX = (GetSystemMetrics(SM_CXSCREEN) - resolution.x) / 2;
    int winPosY = (GetSystemMetrics(SM_CYSCREEN) - resolution.y) / 2;

    hWnd = CreateWindowW(
        WINDOW_CLASS_NAME, L"SEH00N", WS_OVERLAPPEDWINDOW, 
        winPosX, winPosY, resolution.x, resolution.y,
        nullptr, nullptr, hInstance, nullptr
    );

    RECT rt = { winPosX, winPosY, winPosX + resolution.x, winPosY + resolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(hWnd, winPosX, winPosY, rt.right - rt.left, rt.bottom - rt.top, true);
}

void BaseWindow::WindowShow(int cmdShow)
{
    ShowWindow(hWnd, cmdShow);
}

void BaseWindow::WindowUpdate()
{
    UpdateWindow(hWnd);
}

LRESULT BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int BaseWindow::MessageLoop()
{
    MSG msg;
    memset(&msg, 0, sizeof(&msg));

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Core::GetInstance()->GameLoop();
            // tasks kind of rendering...
        }
    }

    Core::GetInstance()->Release();

    return (int)msg.wParam;
}

BaseWindow::BaseWindow(POINT resolution) : hInstance{ 0 }, hWnd{ 0 }, resolution{ resolution }
{
}

BaseWindow::~BaseWindow()
{
}
