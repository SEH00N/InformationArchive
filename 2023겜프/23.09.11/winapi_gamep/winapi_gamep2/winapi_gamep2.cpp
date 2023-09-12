// winapi_gamep2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "math.h"
#include "winapi_gamep2.h"
#include <string>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

POINT objectPosition = { 200, 200 };
POINT objectScale = { 100, 100 };

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIGAMEP2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIGAMEP2));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIGAMEP2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIGAMEP2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1280, 720, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

double Magnitude(int x1, int y1, int x2, int y2)
{
    int distanceX = x2 - x1;
    int distanceY = y2 - y1;
    int dot = distanceX * distanceX + distanceY * distanceY;
    double distance = sqrt(dot);

    return distance;
}

bool InCircle(int x, int y, int ellipseX, int ellipseY, int radius)
{
    return (Magnitude(ellipseX, ellipseY, x, y) < radius);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT rectview;

    static int ellipseRadius = 50;
    static POINT ellipsePos = { 55, 55 };
    static POINT mouseFactor = { 0, 0 };

    static bool isKeyDown = false;
    static bool isTimerActive = false;
    static bool isFocused = false;
    static bool isClicked = false;

    static POINT mousePos = { 0, 0 };

    switch (message)
    {
    case WM_SIZE:
    {
        GetClientRect(hWnd, &rectview);
    }
    break;
    case WM_LBUTTONDBLCLK:
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        isFocused = InCircle(x, y, ellipsePos.x, ellipsePos.y, ellipseRadius);

        mouseFactor.x = ellipsePos.x - x;
        mouseFactor.y = ellipsePos.y - y;

        isClicked = true;

        mousePos.x = x;
        mousePos.y = y;

        //InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_MOUSEMOVE:
        if (isClicked)
        {
            HDC hdc = GetDC(hWnd);

            MoveToEx(hdc, mousePos.x, mousePos.y, nullptr);

            mousePos.x = LOWORD(lParam);
            mousePos.y = HIWORD(lParam);

            LineTo(hdc, mousePos.x, mousePos.y);
        }

        if (isFocused)
        {
            mousePos.x = LOWORD(lParam);
            mousePos.y = HIWORD(lParam);

            ellipsePos.x = mousePos.x + mouseFactor.x;
            ellipsePos.y = mousePos.y + mouseFactor.y;

            InvalidateRect(hWnd, nullptr, true);
        }
        break;
    case WM_LBUTTONUP:
        isFocused = false;
        isClicked = false;
        //InvalidateRect(hWnd, nullptr, true);
    case WM_CREATE:
    {
        isKeyDown = isTimerActive = false;
        GetClientRect(hWnd, &rectview);
    }
    break;
    case WM_KEYDOWN:
    {
        isKeyDown = true;

        if (wParam == VK_RETURN) {
            isTimerActive = !isTimerActive;

            if (isTimerActive)
                KillTimer(hWnd, 1);
            else
                SetTimer(hWnd, 1, 10, nullptr);
        }

        //switch(wParam)
        //{
        //    case VK_LEFT:
        //        if (rectview.left < (objectPosition.x - objectScale.x / 2) + 10)
        //            objectPosition.x -= 10;
        //        break;
        //    case VK_RIGHT:
        //        if (rectview.right > (objectPosition.x + objectScale.x / 2) - 10)
        //            objectPosition.x += 10;
        //        break;
        //    case VK_UP:
        //        objectPosition.y -= 10;
        //        break;
        //    case VK_DOWN:
        //        objectPosition.y += 10;
        //        break;
        //}
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_KEYUP:
        isKeyDown = false;
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_TIMER:
        if (600 > (objectPosition.x + objectScale.x / 2) - 10)
            objectPosition.x += 10;

        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        Rectangle(hdc, 0, 0, 600, 600);

        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, isKeyDown ? hBlueBrush : hWhiteBrush);

        int left = objectPosition.x - objectScale.x / 2;
        int right = objectPosition.x + objectScale.x / 2;
        int top = objectPosition.y - objectScale.y / 2;
        int bottom = objectPosition.y + objectScale.y / 2;
        Rectangle(hdc, left, top, right, bottom);


        SelectObject(hdc, oldBrush);

        left = ellipsePos.x - ellipseRadius;
        right = ellipsePos.x + ellipseRadius;
        top = ellipsePos.y - ellipseRadius;
        bottom = ellipsePos.y + ellipseRadius;

        if (isFocused)
            Rectangle(hdc, left, top, right, bottom);

        Ellipse(hdc, left, top, right, bottom);

        std::wstring wstr = L"겜프는 꿀잼";
        TextOut(hdc, rectview.right / 2, rectview.bottom / 2, wstr.c_str(), wstr.length());

            EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}