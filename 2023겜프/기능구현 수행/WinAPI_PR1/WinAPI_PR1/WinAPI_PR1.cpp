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
    //static wchar_t str[256];
    //static int cursor = 0;
    //static int col = 20;

	// static POINT position = { 100, 100 };
    // static int speed = 10;
    // static int size = 50;
    // static bool keyPressed = false;

    //static RECT box = { 0, 0, 600, 600 };
    //static int position = 25;
    //static int radius = 25;
    //static int speed = 5;
    //static bool isMoving = false;

    // static POINT mousePos = { 0, 0 };
    // static bool isClicked = false;

    //static RECT taggerBound = { 100, 100, 160, 130 };
    //static LPCWSTR taggerStr = L"겜마고";
    //static RECT myBound = { 0, 0, 0, 0 };
    //static LPCWSTR myStr = L"SEH00N";
    //static POINT mousePos = {0, 0};
    //static bool isClicked = false;

    static int space = 75;
    static POINT pos = { 0, 0 };
    static POINT LIMIT = { WINSIZEX / space, WINSIZEY / space };

    switch (message)
    {
    case WM_SIZE:
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_LBUTTONDBLCLK:
        //MessageBox(hWnd, L"마우스 더블클릭 됨!!", L"SEH00N", MB_OK | MB_ICONERROR);

        //InvalidateRect(hWnd, nullptr, true);

        break;
    case WM_LBUTTONDOWN:
        // isClicked = true;

        // isClicked = true;
        // 
        // mousePos.x = LOWORD(lParam);
        // mousePos.y = HIWORD(lParam);
        // 
        // SetTimer(hWnd, 0, 10, nullptr);
        // 
        // InvalidateRect(hWnd, nullptr, true);

        break;
    case WM_LBUTTONUP:
        // isClicked = false;

        //isClicked = false;
        //
        //mousePos.x = LOWORD(lParam);
        //mousePos.y = HIWORD(lParam);
        //
        //KillTimer(hWnd, 0);
        //
        //InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_MOUSEMOVE:
    {
        //int x = LOWORD(lParam);
        //int y = HIWORD(lParam);
        //
        //if (isClicked)
        //{
        //    HDC hdc = GetDC(hWnd);
        //    MoveToEx(hdc, mousePos.x, mousePos.y, nullptr);
        //    LineTo(hdc, x, y);
        //}
        //
        //mousePos.x = x;
        //mousePos.y = y;

        //mousePos.x = LOWORD(lParam);
        //mousePos.y = HIWORD(lParam);
        //
        //InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_TIMER:
        // position += speed;
        // 
        // if (position < 0)
        //     position = 0;
        // else if (position > box.right - radius)
        //     position = box.right - radius;
        // 
        // InvalidateRect(hWnd, nullptr, true);

        // if (taggerBound.left < myBound.left)
        // {
        //     taggerBound.left += 1;
        //     taggerBound.right += 1;
        // }
        // else if (taggerBound.left > myBound.left)
        // {
        //     taggerBound.left -= 1;
        //     taggerBound.right -= 1;
        // }
        // 
        // if (taggerBound.top < myBound.top)
        // {
        //     taggerBound.top += 1;
        //     taggerBound.bottom += 1;
        // }
        // else if (taggerBound.top > myBound.top)
        // {
        //     taggerBound.top -= 1;
        //     taggerBound.bottom -= 1;
        // }
        // 
        // InvalidateRect(hWnd, nullptr, true);

        break;
    case WM_KEYDOWN:
    {
        // POINT err = { 0, 0 };
        // 
        // switch (wParam)
        // {
        // case VK_RIGHT:
        //     err.x += speed;
        //     keyPressed = true;
        //     break;
        // case VK_LEFT:
        //     err.x -= speed;
        //     keyPressed = true;
        //     break;
        // case VK_UP:
        //     err.y -= speed;
        //     keyPressed = true;
        //     break;
        // case VK_DOWN:
        //     err.y += speed;
        //     keyPressed = true;
        //     break;
        // }
        // 
        // RECT screenRT;
        // GetClientRect(hWnd, &screenRT);
        // 
        // int screenX = screenRT.right - screenRT.left;
        // int screenY = screenRT.bottom - screenRT.top;
        // 
        // position.x += err.x;
        // position.y += err.y;
        // 
        // if (position.x > screenX - size)
        //     position.x = screenX - size;
        // else if (position.x < 0)
        //     position.x = 0;
        // 
        // if (position.y > screenY - size)
        //     position.y = screenY - size;
        // else if (position.y < 0)
        //     position.y = 0;
        // 
        // InvalidateRect(hWnd, nullptr, true);

        //if (wParam == VK_RETURN)
        //{
        //    if (isMoving)
        //        KillTimer(hWnd, 0);
        //    else
        //        SetTimer(hWnd, 0, 10, nullptr);
        //
        //    isMoving = !isMoving;
        //}

        switch (wParam)
        {
        case VK_LEFT:
            pos.x -= 1;
            if (pos.x < 0)
                pos.x = LIMIT.x;
            break;
        case VK_RIGHT:
            pos.x = (pos.x + 1) % LIMIT.x;
            break;
        case VK_UP:
            pos.y -= 1;
            if (pos.y < 0)
                pos.y = LIMIT.y;
            break;
        case VK_DOWN:
            pos.y = (pos.y + 1) % LIMIT.y;
            break;
        }

        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_KEYUP:
        //keyPressed = false;
        //InvalidateRect(hWnd, nullptr, true);


        break;
    case WM_CHAR:
    {
        //HDC hdc = GetDC(hWnd);
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

        // if (wParam == '\b')
        // {
        //     cursor--;
        //     str[cursor] = NULL;
        // 
        //     InvalidateRect(hWnd, nullptr, true);
        // }
        // else
        // {
        //     str[cursor++] = wParam;
        //     str[cursor] = NULL;
        // 
		// 	HDC hdc = GetDC(hWnd);
        // 
        //     for (int i = 0; i <= cursor / col; ++i)
        //     {
        //         int posX = 100;
        //         int posY = 100 + i * col;
        // 
        //         if (i == cursor / col)
        //             TextOut(hdc, posX, posY, str + i * col, cursor % col);
        //         else
        //             TextOut(hdc, posX, posY, str + i * col, col);
        //     }
        // }
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

            //for (int i = 0; i <= cursor / col; ++i)
            //{
            //    int posX = 100;
            //    int posY = 100 + i * col;
            //
            //    if (i == cursor / col)
            //        TextOut(hdc, posX, posY, str + i * col, cursor % col);
            //    else
            //        TextOut(hdc, posX, posY, str + i * col, col);
            //}

            // HBRUSH brush_white= CreateSolidBrush(RGB(255, 255, 255));
            // HBRUSH brush_blue= CreateSolidBrush(RGB(0, 0, 255));
            // 
			// SelectObject(hdc, keyPressed ? brush_blue : brush_white);
            // 
            // Ellipse(hdc, position.x, position.y, position.x + size, position.y + size);

            //Rectangle(hdc, box.left, box.top, box.right, box.bottom);
            //Ellipse(hdc, position - radius, 50 - radius, position + radius, 50 + radius);

            //LPCWSTR str = L"Hello, World!";
            //
            //RECT rt;
            //GetClientRect(hWnd, &rt);
            //
            //int posX = (rt.right - rt.left - wcslen(str) * 5) / 2;
            //int posY = (rt.bottom - rt.top) / 2;
            //
            //TextOut(hdc, posX, posY, str, wcslen(str));
            //
            //Rectangle(hdc, 10, 10, 110, 110);
 
            //if (isClicked)
            //{
            //    myBound.left = mousePos.x;
            //    myBound.right = myBound.left + 60;
            //    myBound.top = mousePos.y;
            //    myBound.bottom = myBound.top + 30;
            //    DrawText(hdc, myStr, wcslen(myStr), &myBound, DT_CENTER);
            //}
            //
            //DrawText(hdc, taggerStr, wcslen(taggerStr), &taggerBound, DT_CENTER);

            for (int i = 0; i < 20; ++i)
            {
                MoveToEx(hdc, 0, space* i, nullptr);
                LineTo(hdc, WINSIZEX, space* i);

                MoveToEx(hdc, space* i, 0, nullptr);
                LineTo(hdc, space* i, WINSIZEY);
            }

            int left = 12 + pos.x * space;
            int right = 12 + pos.y * space;

            Rectangle(hdc, left, right, left + 50, right + 50);

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
