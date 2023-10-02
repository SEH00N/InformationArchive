#include "framework.h"
#include "WinAPI_PR1.h"
#include <time.h>
#include <string>

#define MAX_LOADSTRING 100

#define WINSIZEX 1280
#define WINSIZEY 720
#define TITLE L"SEH00N"

HINSTANCE hInst;
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    LoadStringW(hInstance, IDC_WINAPIPR1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPR1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPR1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIPR1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   srand((unsigned int)time(NULL));

   int width = GetSystemMetrics(SM_CXFULLSCREEN);
   int height = GetSystemMetrics(SM_CYFULLSCREEN);

   int posX = (width - WINSIZEX) >> 1;
   int posY = (height - WINSIZEY) >> 1;

   HWND hWnd = CreateWindowW(szWindowClass, TITLE, WS_OVERLAPPEDWINDOW/* | WS_HSCROLL*/,
       posX, posY, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDBLCLK:
        MessageBox(hWnd, L"마우스 더블클릭 됨!!", L"SEH00N", MB_OK | MB_ICONERROR);
        break;

    case WM_CHAR:
    {
        HDC hdc = GetDC(hWnd);

        //wchar_t str[2];
        //str[0] = wParam;
        //str[1] = NULL;
        //
        //TextOut(hdc, rand() % WINSIZEX, rand() % WINSIZEY, str, wcslen(str));



        //static wchar_t str[256];
        //static int cursor = 0;
        //
        //if (wParam == ' ')
        //{
		//	InvalidateRect(hWnd, nullptr, true);
        //    cursor = 0;
        //    str[1] = NULL;
        //}
        //else
        //{
        //    str[cursor++] = wParam;
        //    str[cursor] = NULL;
        //}
        //
        //TextOut(hdc, 100, 100, str, wcslen(str));
    }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            //for (int i = 0; i < 16; ++i)
            //{
            //    MoveToEx(hdc, 0, WINSIZEY / 16 * i, nullptr);
            //    LineTo(hdc, WINSIZEX, WINSIZEY / 16 * i);
            //}
            //for (int i = 0; i < 26; ++i)
            //{
            //    MoveToEx(hdc, WINSIZEX / 26 * i, 0, nullptr);
            //    LineTo(hdc, WINSIZEX / 26 * i, WINSIZEY);
            //}



            //int space = 20;
            //int size = 50;
            //int x = 100;
            //int y = 100;
            //
            //for (int i = 0; i < 25; ++i)
            //{
            //    int col = i % 5;
            //    int row = i / 5;
            //
            //    int left = x + (space + size) * col;
            //    int top = y + (space + size) * row;
            //
            //    if (row % 2 == 0) // 네모
            //        Rectangle(hdc, left, top, left + size, top + size);
            //    else // 동그라미
            //        Ellipse(hdc, left, top, left + size, top + size);
            //}



            //HBRUSH brush = CreateHatchBrush(HS_FDIAGONAL, RGB(30, 255, 30));
            //HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
            //
            //SelectObject(hdc, brush);
            //SelectObject(hdc, pen);
            //
            //Rectangle(hdc, 100, 100, 250, 150);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
